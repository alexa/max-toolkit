/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "SampleApplication/AgentManager/Alexa/DefaultClientFactory.h"

#include <algorithm>
#include <cctype>
#include <csignal>
#include <fstream>

#include <acsdkAlerts/Storage/SQLiteAlertStorage.h>
#include <acsdkBluetooth/BasicDeviceConnectionRule.h>
#include <acsdkBluetooth/SQLiteBluetoothStorage.h>
#include <acsdkEqualizerInterfaces/EqualizerStorageInterface.h>
#include <acsdkEqualizerImplementations/MiscDBEqualizerStorage.h>
#include <acsdkEqualizerImplementations/SDKConfigEqualizerConfiguration.h>
#include <acsdkNotifications/SQLiteNotificationsStorage.h>
#include <ACL/Transport/HTTP2TransportFactory.h>
#include <ACL/Transport/PostConnectSequencerFactory.h>
#include <Audio/AudioFactory.h>
#include <Audio/MicrophoneInterface.h>
#include <AVSCommon/AVS/Initialization/AlexaClientSDKInit.h>
#include <AVSCommon/SDKInterfaces/Bluetooth/BluetoothDeviceConnectionRuleInterface.h>
#include <AVSCommon/SDKInterfaces/Bluetooth/BluetoothDeviceManagerInterface.h>
#include <AVSCommon/SDKInterfaces/Diagnostics/ProtocolTracerInterface.h>
#include <AVSCommon/SDKInterfaces/Endpoints/EndpointBuilderInterface.h>
#include <AVSCommon/Utils/Configuration/ConfigurationNode.h>
#include <AVSCommon/Utils/DeviceInfo.h>
#include <AVSCommon/Utils/LibcurlUtils/HTTPContentFetcherFactory.h>
#include <AVSCommon/Utils/LibcurlUtils/LibcurlHTTP2ConnectionFactory.h>
#include <AVSCommon/Utils/Logger/Logger.h>
#include <AVSCommon/Utils/Logger/LoggerSinkManager.h>
#include <AVSCommon/Utils/MediaPlayer/PooledMediaPlayerFactory.h>
#include <AVSCommon/Utils/Network/InternetConnectionMonitor.h>
#include <AVSCommon/Utils/Power/NoOpPowerResourceManager.h>
#include <AVSCommon/Utils/UUIDGeneration/UUIDGeneration.h>
#include <AVSGatewayManager/AVSGatewayManager.h>
#include <AVSGatewayManager/Storage/AVSGatewayManagerStorage.h>
#include <CBLAuthDelegate/CBLAuthDelegate.h>
#include <CBLAuthDelegate/SQLiteCBLAuthDelegateStorage.h>
#include <CapabilitiesDelegate/CapabilitiesDelegate.h>
#include <CapabilitiesDelegate/Storage/SQLiteCapabilitiesDelegateStorage.h>
#include <ContextManager/ContextManager.h>
#include <InterruptModel/config/InterruptModelConfiguration.h>
#include <MediaPlayer/MediaPlayer.h>
#include <SynchronizeStateSender/SynchronizeStateSenderFactory.h>
#include <SampleApp/ExternalCapabilitiesBuilder.h>
#include <SampleApp/LocaleAssetsManager.h>
#include <SampleApp/SampleEqualizerModeController.h>
#include <Settings/Storage/SQLiteDeviceSettingStorage.h>
#include <SQLiteStorage/SQLiteMiscStorage.h>
#include <MultiAgentExperience/Samples/Agents/Computer/Computer.h>
#include <MultiAgentExperience/Experience/ExperienceObserverInterface.h>
#include <MultiAgentExperience/Application/MAXFactory.h>
#include <MultiAgentExperience/Application/MAXInterface.h>

#include "SampleApplication/Utils/RadiantLogger.h"
#include "SampleApplication/AgentManager/Alexa/NoopCBLAuthRequester.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace alexa {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("DefaultClientFactory");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/// The sample rate of microphone audio data.
static const unsigned int SAMPLE_RATE_HZ = 16000;

/// The number of audio channels.
static const unsigned int NUM_CHANNELS = 1;

/// The size of each word within the stream.
static const size_t WORD_SIZE = 2;

/// The default number of MediaPlayers used by AudioPlayer CA/ Can be overridden in the Configuration using @c
/// AUDIO_MEDIAPLAYER_POOL_SIZE_KEY
static const unsigned int AUDIO_MEDIAPLAYER_POOL_SIZE_DEFAULT = 2;

/// Key for the root node value containing configuration values for SampleApp.
static const std::string SAMPLE_APP_CONFIG_KEY("sampleApp");

/// Key for the root node value containing configuration values for Equalizer.
static const std::string EQUALIZER_CONFIG_KEY("equalizer");

/// Key for the @c firmwareVersion value under the @c SAMPLE_APP_CONFIG_KEY configuration node.
static const std::string FIRMWARE_VERSION_KEY("firmwareVersion");

/// Key for the @c endpoint value under the @c SAMPLE_APP_CONFIG_KEY configuration node.
static const std::string ENDPOINT_KEY("endpoint");

/// Key for setting if display cards are supported or not under the @c SAMPLE_APP_CONFIG_KEY configuration node.
static const std::string DISPLAY_CARD_KEY("displayCardsSupported");

/// Key for the Audio MediaPlayer pool size.
static const std::string AUDIO_MEDIAPLAYER_POOL_SIZE_KEY("audioMediaPlayerPoolSize");

using namespace alexaClientSDK;
using namespace alexaClientSDK::avsCommon;
using namespace alexaClientSDK::avsCommon::sdkInterfaces;
using namespace acsdkExternalMediaPlayer;

using MediaPlayerInterface = alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface;
using ApplicationMediaInterfaces = alexaClientSDK::avsCommon::sdkInterfaces::ApplicationMediaInterfaces;

/// The @c m_playerToMediaPlayerMap Map of the adapter to their speaker-type and MediaPlayer creation methods.
std::unordered_map<std::string, avsCommon::sdkInterfaces::ChannelVolumeInterface::Type>
    DefaultClientFactory::m_playerToSpeakerTypeMap;

/// The singleton map from @c playerId to @c ExternalMediaAdapter creation functions.
std::unordered_map<std::string, ExternalMediaPlayer::AdapterCreateFunction>
    DefaultClientFactory::m_adapterToCreateFuncMap;

/**
 * Creates an audio format appropriate to the AVS SDK.
 *
 * @return An audio format appropriate to the AVS SDK.
 */
static alexaClientSDK::avsCommon::utils::AudioFormat createAudioFormat() {
    alexaClientSDK::avsCommon::utils::AudioFormat compatibleAudioFormat;
    compatibleAudioFormat.sampleRateHz = SAMPLE_RATE_HZ;
    compatibleAudioFormat.sampleSizeInBits = WORD_SIZE * CHAR_BIT;
    compatibleAudioFormat.numChannels = NUM_CHANNELS;
    compatibleAudioFormat.endianness = alexaClientSDK::avsCommon::utils::AudioFormat::Endianness::LITTLE;
    compatibleAudioFormat.encoding = alexaClientSDK::avsCommon::utils::AudioFormat::Encoding::LPCM;
    return compatibleAudioFormat;
};

/**
 * Utility function to create a tap audio provider.
 *
 * @param sharedDataStream The underlying SDS to use.
 * @return An audio provider.
 */
static capabilityAgents::aip::AudioProvider createTapToTalkAudioProvider(
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream) {
    bool tapAlwaysReadable = true;
    bool tapCanOverride = true;
    bool tapCanBeOverridden = true;

    return alexaClientSDK::capabilityAgents::aip::AudioProvider(
        sharedDataStream,
        createAudioFormat(),
        alexaClientSDK::capabilityAgents::aip::ASRProfile::NEAR_FIELD,
        tapAlwaysReadable,
        tapCanOverride,
        tapCanBeOverridden);
}

/**
 * Utility function to create a wakeword audio provider.
 *
 * @param sharedDataStream The underlying SDS to use.
 * @return An audio provider.
 */
static capabilityAgents::aip::AudioProvider createWakeWordAudioProvider(
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream) {
    bool wakeAlwaysReadable = true;
    bool wakeCanOverride = false;
    bool wakeCanBeOverridden = true;

    return alexaClientSDK::capabilityAgents::aip::AudioProvider(
        sharedDataStream,
        createAudioFormat(),
        alexaClientSDK::capabilityAgents::aip::ASRProfile::NEAR_FIELD,
        wakeAlwaysReadable,
        wakeCanOverride,
        wakeCanBeOverridden);
}

std::shared_ptr<alexaClientSDK::defaultClient::DefaultClient> DefaultClientFactory::create(
    const AgentsConfig::AgentConfig& config,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ActiveAgentSpeechStoreInterface> agentSpeechStore,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache) {
    static std::shared_ptr<alexaClientSDK::defaultClient::DefaultClient> defaultClient;
    static DefaultClientFactory wrapper;
    LX(DEBUG3, "");
    if (!defaultClient) {
        LX(DEBUG3, "Creating.");
        defaultClient =
            wrapper.instantiateDefaultClient(config, audioDataAccessProvider, agentSpeechStore, metadataCache);
        if (!defaultClient) {
            LX(ERROR, "Failed to create DefaultClient.");
            return nullptr;
        }
    }

    return defaultClient;
}

std::shared_ptr<alexaClientSDK::defaultClient::DefaultClient> DefaultClientFactory::instantiateDefaultClient(
    const AgentsConfig::AgentConfig& agentConfig,
    std::shared_ptr<utils::AudioDataDirectAccessInterface> audioDataAccessProvider,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ActiveAgentSpeechStoreInterface> agentSpeechStore,
    std::shared_ptr<audioManager::wakeword::WakewordMetadataCache> metadataCache) {
    LX(DEBUG3, "");

    std::vector<std::shared_ptr<std::istream>> configJsonStreams;

    if (agentConfig.configFilePath.empty()) {
        LX(ERROR, "Config filename is empty.");
        return nullptr;
    }

    auto configInFile = std::shared_ptr<std::ifstream>(new std::ifstream(agentConfig.configFilePath));
    if (!configInFile->good()) {
        LX(ERROR, "Failed to read config file:" + agentConfig.configFilePath);
        return nullptr;
    }

    configJsonStreams.push_back(configInFile);

    // Add the InterruptModel Configuration.
    configJsonStreams.push_back(alexaClientSDK::afml::interruptModel::InterruptModelConfiguration::getConfig());

    // We may have initialized the AVS SDK elsewhere for the purposes of MediaPlayer creation. Let's undo that if so.
    if (avsCommon::avs::initialization::AlexaClientSDKInit::isInitialized()) {
        avsCommon::avs::initialization::AlexaClientSDKInit::uninitialize();
    }

    if (!avsCommon::avs::initialization::AlexaClientSDKInit::initialize(configJsonStreams)) {
        LX(ERROR, "Failed to initialize AVS SDK.");
        return nullptr;
    }

    auto config = alexaClientSDK::avsCommon::utils::configuration::ConfigurationNode::getRoot();
    auto sampleAppConfig = config[SAMPLE_APP_CONFIG_KEY];

    auto httpContentFetcherFactory = std::make_shared<avsCommon::utils::libcurlUtils::HTTPContentFetcherFactory>();

    // Creating the misc DB object to be used by various components.
    std::shared_ptr<alexaClientSDK::storage::sqliteStorage::SQLiteMiscStorage> miscStorage =
        alexaClientSDK::storage::sqliteStorage::SQLiteMiscStorage::create(config);

    //// Creating Equalizer specific implementations
    auto equalizerConfigBranch = config[EQUALIZER_CONFIG_KEY];
    auto equalizerConfiguration = acsdkEqualizer::SDKConfigEqualizerConfiguration::create(equalizerConfigBranch);
    std::shared_ptr<defaultClient::EqualizerRuntimeSetup> equalizerRuntimeSetup = nullptr;

    bool equalizerEnabled = false;
    if (equalizerConfiguration && equalizerConfiguration->isEnabled()) {
        equalizerEnabled = true;
        equalizerRuntimeSetup = std::make_shared<defaultClient::EqualizerRuntimeSetup>();
        auto equalizerStorage = acsdkEqualizer::MiscDBEqualizerStorage::createEqualizerStorageInterface(miscStorage);
        auto equalizerModeController = sampleApp::SampleEqualizerModeController::create();

        equalizerRuntimeSetup->setStorage(equalizerStorage);
        equalizerRuntimeSetup->setConfiguration(equalizerConfiguration);
        equalizerRuntimeSetup->setModeController(equalizerModeController);
    }

    auto speakerMediaInterfaces = createApplicationMediaPlayer(httpContentFetcherFactory, false, "SpeakMediaPlayer");
    if (!speakerMediaInterfaces) {
        LX(ERROR, "Failed to create application media interfaces for speech.");
        return nullptr;
    }

    auto m_speakMediaPlayer = speakerMediaInterfaces->mediaPlayer;

    int poolSize = 0;
    sampleAppConfig.getInt(AUDIO_MEDIAPLAYER_POOL_SIZE_KEY, &poolSize, AUDIO_MEDIAPLAYER_POOL_SIZE_DEFAULT);
    std::vector<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface>> audioSpeakers;

    for (int index = 0; index < poolSize; index++) {
        std::shared_ptr<MediaPlayerInterface> mediaPlayer;
        std::shared_ptr<avsCommon::sdkInterfaces::SpeakerInterface> speaker;
        std::shared_ptr<acsdkEqualizerInterfaces::EqualizerInterface> equalizer;

        auto audioMediaInterfaces =
            createApplicationMediaPlayer(httpContentFetcherFactory, equalizerEnabled, "AudioMediaPlayer");
        if (!audioMediaInterfaces) {
            LX(ERROR, "Failed to create application media interfaces for audio.");
            return nullptr;
        }
        m_audioMediaPlayerPool.push_back(audioMediaInterfaces->mediaPlayer);
        audioSpeakers.push_back(audioMediaInterfaces->speaker);
        if (equalizerRuntimeSetup) {
            equalizerRuntimeSetup->addEqualizer(audioMediaInterfaces->equalizer);
        }
    }

    avsCommon::utils::Optional<avsCommon::utils::mediaPlayer::Fingerprint> fingerprint =
        (*(m_audioMediaPlayerPool.begin()))->getFingerprint();
    auto audioMediaPlayerFactory = std::unique_ptr<alexaClientSDK::mediaPlayer::PooledMediaPlayerFactory>();
    if (fingerprint.hasValue()) {
        audioMediaPlayerFactory =
            alexaClientSDK::mediaPlayer::PooledMediaPlayerFactory::create(m_audioMediaPlayerPool, fingerprint.value());
    } else {
        audioMediaPlayerFactory = alexaClientSDK::mediaPlayer::PooledMediaPlayerFactory::create(m_audioMediaPlayerPool);
    }
    if (!audioMediaPlayerFactory) {
        LX(ERROR, "Failed to create media player factory for content!");
        return nullptr;
    }

    auto notificationMediaInterfaces =
        createApplicationMediaPlayer(httpContentFetcherFactory, false, "NotificationsMediaPlayer");
    if (!notificationMediaInterfaces) {
        LX(ERROR, "Failed to create application media interfaces for notifications!");
        return nullptr;
    }
    auto m_notificationsMediaPlayer = notificationMediaInterfaces->mediaPlayer;

    auto bluetoothMediaInterfaces =
        createApplicationMediaPlayer(httpContentFetcherFactory, false, "BluetoothMediaPlayer");
    if (!bluetoothMediaInterfaces) {
        LX(ERROR, "Failed to create application media interfaces for bluetooth!");
        return nullptr;
    }
    auto m_bluetoothMediaPlayer = bluetoothMediaInterfaces->mediaPlayer;

    auto ringtoneMediaInterfaces =
        createApplicationMediaPlayer(httpContentFetcherFactory, false, "RingtoneMediaPlayer");
    if (!ringtoneMediaInterfaces) {
        LX(ERROR, "Failed to create application media interfaces for ringtones!");
        return nullptr;
    }
    auto m_ringtoneMediaPlayer = ringtoneMediaInterfaces->mediaPlayer;

    auto alertsMediaInterfaces = createApplicationMediaPlayer(httpContentFetcherFactory, false, "AlertsMediaPlayer");
    if (!alertsMediaInterfaces) {
        LX(ERROR, "Failed to create application media interfaces for alerts!");
        return nullptr;
    }

    auto m_alertsMediaPlayer = alertsMediaInterfaces->mediaPlayer;

    auto systemSoundMediaInterfaces =
        createApplicationMediaPlayer(httpContentFetcherFactory, false, "SystemSoundMediaPlayer");
    if (!systemSoundMediaInterfaces) {
        LX(ERROR, "Failed to create application media interfaces for system sound player!");
        return nullptr;
    }
    auto m_systemSoundMediaPlayer = systemSoundMediaInterfaces->mediaPlayer;

    if (!createMediaPlayersForAdapters(httpContentFetcherFactory, equalizerRuntimeSetup)) {
        LX(ERROR, "Could not create mediaPlayers for adapters");
        return nullptr;
    }

    auto audioFactory = std::make_shared<alexaClientSDK::applicationUtilities::resources::audio::AudioFactory>();

    // Creating the alert storage object to be used for rendering and storing alerts.
    auto alertStorage =
        alexaClientSDK::acsdkAlerts::storage::SQLiteAlertStorage::create(config, audioFactory->alerts());

    // Creating the message storage object to be used for storing message to be sent later.
    auto messageStorage = alexaClientSDK::certifiedSender::SQLiteMessageStorage::create(config);

    // Creating notifications storage object to be used for storing notification indicators.
    auto notificationsStorage = alexaClientSDK::acsdkNotifications::SQLiteNotificationsStorage::create(config);

    // Creating new device settings storage object to be used for storing AVS Settings.
    auto deviceSettingsStorage = alexaClientSDK::settings::storage::SQLiteDeviceSettingStorage::create(config);

    // Creating bluetooth storage object to be used for storing uuid to mac mappings for devices.
    auto bluetoothStorage = alexaClientSDK::acsdkBluetooth::SQLiteBluetoothStorage::create(config);

#ifdef KWD
    bool wakeWordEnabled = true;
#else
    bool wakeWordEnabled = false;
#endif

    auto m_localeAssetsManager = alexaClientSDK::sampleApp::LocaleAssetsManager::create(wakeWordEnabled);
    if (!m_localeAssetsManager) {
        LX(ERROR, "Failed to create Locale Assets Manager.");
        return nullptr;
    }

    // Creating customerDataManager which will be used by the
    auto customerDataManager = std::make_shared<registrationManager::CustomerDataManager>();

    // Creating the deviceInfo object
    std::shared_ptr<alexaClientSDK::avsCommon::utils::DeviceInfo> m_deviceInfo =
        avsCommon::utils::DeviceInfo::create(config);
    if (!m_deviceInfo) {
        LX(ERROR, "Creation of DeviceInfo failed.");
        return nullptr;
    }

    auto cblRequester = std::make_shared<NoopCBLAuthRequester>();

    // Supply a SALT for UUID generation, this should be as unique to each individual device as possible
    alexaClientSDK::avsCommon::utils::uuidGeneration::setSalt(
        m_deviceInfo->getClientId() + m_deviceInfo->getDeviceSerialNumber());

    // Creating the AuthDelegate - this component takes care of LWA and authorization of the client.
    auto authDelegateStorage = authorization::cblAuthDelegate::SQLiteCBLAuthDelegateStorage::create(config);
    std::shared_ptr<alexaClientSDK::acl::AuthDelegateInterface> m_authDelegate =
        authorization::cblAuthDelegate::CBLAuthDelegate::create(
            config, customerDataManager, std::move(authDelegateStorage), cblRequester, nullptr, m_deviceInfo);

    if (!m_authDelegate) {
        LX(ERROR, "Creation of AuthDelegate failed.");
        return nullptr;
    }

    // Creating the CapabilitiesDelegate - This component provides the client with the ability to send messages to the
    // Capabilities API.
    auto capabilitiesDelegateStorage =
        alexaClientSDK::capabilitiesDelegate::storage::SQLiteCapabilitiesDelegateStorage::create(config);

    auto m_capabilitiesDelegate = alexaClientSDK::capabilitiesDelegate::CapabilitiesDelegate::create(
        m_authDelegate, std::move(capabilitiesDelegateStorage), customerDataManager);

    if (!m_capabilitiesDelegate) {
        LX(ERROR, "Creation of CapabilitiesDelegate failed.");
        return nullptr;
    }

    m_shutdownRequiredList.push_back(m_capabilitiesDelegate);

    // INVALID_FIRMWARE_VERSION is passed to @c getInt() as a default in case FIRMWARE_VERSION_KEY is not found.
    int firmwareVersion = static_cast<int>(avsCommon::sdkInterfaces::softwareInfo::INVALID_FIRMWARE_VERSION);
    sampleAppConfig.getInt(FIRMWARE_VERSION_KEY, &firmwareVersion, firmwareVersion);

    // Check to see if displayCards is supported on the device. The default is supported unless specified otherwise in
    // the configuration.
    bool displayCardsSupported;
    config[SAMPLE_APP_CONFIG_KEY].getBool(DISPLAY_CARD_KEY, &displayCardsSupported, true);

    // Creating the InternetConnectionMonitor that will notify observers of internet connection status changes.
    auto internetConnectionMonitor =
        avsCommon::utils::network::InternetConnectionMonitor::create(httpContentFetcherFactory);
    if (!internetConnectionMonitor) {
        LX(ERROR, "Failed to create InternetConnectionMonitor.");
        return nullptr;
    }

    // Creating the Context Manager - This component manages the context of each of the components to update to AVS.
    // It is required for each of the capability agents so that they may provide their state just before any event is
    // fired off.
    auto contextManager = contextManager::ContextManager::create(*m_deviceInfo);
    if (!contextManager) {
        LX(ERROR, "Creation of ContextManager failed.");
        return nullptr;
    }

    auto avsGatewayManagerStorage = avsGatewayManager::storage::AVSGatewayManagerStorage::create(miscStorage);
    if (!avsGatewayManagerStorage) {
        LX(ERROR, "Creation of AVSGatewayManagerStorage failed.");
        return nullptr;
    }
    auto avsGatewayManager =
        avsGatewayManager::AVSGatewayManager::create(std::move(avsGatewayManagerStorage), customerDataManager, config);
    if (!avsGatewayManager) {
        LX(ERROR, "Creation of AVSGatewayManager failed.");
        return nullptr;
    }

    auto synchronizeStateSenderFactory = synchronizeStateSender::SynchronizeStateSenderFactory::create(contextManager);
    if (!synchronizeStateSenderFactory) {
        LX(ERROR, "Creation of SynchronizeStateSenderFactory failed.");
        return nullptr;
    }

    std::vector<std::shared_ptr<avsCommon::sdkInterfaces::PostConnectOperationProviderInterface>> providers;
    providers.push_back(synchronizeStateSenderFactory);
    providers.push_back(avsGatewayManager);
    providers.push_back(m_capabilitiesDelegate);

    // Create a factory for creating objects that handle tasks that need to be
    // performed right after establishing a connection to AVS.
    auto postConnectSequencerFactory = acl::PostConnectSequencerFactory::create(providers);

    std::shared_ptr<avsCommon::sdkInterfaces::diagnostics::ProtocolTracerInterface> deviceProtocolTracer;

    // Create a factory to create objects that establish a connection with AVS.
    auto transportFactory = std::make_shared<acl::HTTP2TransportFactory>(
        std::make_shared<avsCommon::utils::libcurlUtils::LibcurlHTTP2ConnectionFactory>(),
        postConnectSequencerFactory,
        nullptr,
        deviceProtocolTracer);

    // Create the BluetoothDeviceManager to communicate with the Bluetooth stack.
    std::unique_ptr<avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceManagerInterface> bluetoothDeviceManager;

    // Create the connectionRules to communicate with the Bluetooth stack.
    std::unordered_set<
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceConnectionRuleInterface>>
        enabledConnectionRules;
    enabledConnectionRules.insert(alexaClientSDK::acsdkBluetooth::BasicDeviceConnectionRule::create());

    if (agentConfig.wakewords.empty()) {
        LX(DEBUG0, "No wakewords provided for Alexa. Only tap to talk will be enabled.");
    }

    auto tapToTalkAudioProvider = std::make_shared<capabilityAgents::aip::AudioProvider>(
        createTapToTalkAudioProvider(audioDataAccessProvider->getSDSHandle()));

    auto wakewordAudioProvider = std::make_shared<capabilityAgents::aip::AudioProvider>(
        createWakeWordAudioProvider(audioDataAccessProvider->getSDSHandle()));

    auto agentTransferMediaInterfaces =
        createApplicationMediaPlayer(httpContentFetcherFactory, false, "AgentTransferMediaPlayer");
    if (!speakerMediaInterfaces) {
        LX(ERROR, "Failed to create application media interfaces for speech.");
        return nullptr;
    }

    const auto& adapterCreateFunctionMap = m_adapterToCreateFuncMap;

    static auto powerResourceManager = std::make_shared<avsCommon::utils::power::NoOpPowerResourceManager>();

    auto wakeword = getAgentPrimaryWakeword(agentConfig);

    std::shared_ptr<alexaClientSDK::defaultClient::DefaultClient> client =
        alexaClientSDK::defaultClient::DefaultClient::create(
            agentConfig.name,
            wakeword,
            m_deviceInfo,
            customerDataManager,
            m_externalMusicProviderMediaPlayersMap,
            m_externalMusicProviderSpeakersMap,
            adapterCreateFunctionMap,
            m_speakMediaPlayer,
            std::move(audioMediaPlayerFactory),
            m_alertsMediaPlayer,
            m_notificationsMediaPlayer,
            m_bluetoothMediaPlayer,
            m_ringtoneMediaPlayer,
            m_systemSoundMediaPlayer,
            speakerMediaInterfaces->speaker,
            audioSpeakers,
            alertsMediaInterfaces->speaker,
            notificationMediaInterfaces->speaker,
            bluetoothMediaInterfaces->speaker,
            ringtoneMediaInterfaces->speaker,
            systemSoundMediaInterfaces->speaker,
            {},
            equalizerRuntimeSetup,
            audioFactory,
            m_authDelegate,
            std::move(alertStorage),
            std::move(messageStorage),
            std::move(notificationsStorage),
            std::move(deviceSettingsStorage),
            std::move(bluetoothStorage),
            miscStorage,
            {},
            {},
            std::move(internetConnectionMonitor),
            displayCardsSupported,
            m_capabilitiesDelegate,
            contextManager,
            transportFactory,
            avsGatewayManager,
            m_localeAssetsManager,
            enabledConnectionRules,
            nullptr,
            firmwareVersion,
            true,
            nullptr,
            std::move(bluetoothDeviceManager),
            nullptr,
            powerResourceManager,
            nullptr,
            std::make_shared<alexaClientSDK::sampleApp::ExternalCapabilitiesBuilder>(m_deviceInfo),
            std::make_shared<alexaClientSDK::capabilityAgents::speakerManager::DefaultChannelVolumeFactory>(),
            true,
            std::make_shared<alexaClientSDK::acl::MessageRouterFactory>(),
            nullptr,
            capabilityAgents::aip::AudioProvider::null(),
            tapToTalkAudioProvider,
            agentTransferMediaInterfaces->mediaPlayer,
            wakewordAudioProvider,
            agentSpeechStore,
            metadataCache);

    if (!client) {
        LX(ERROR, "Failed to create default SDK client.");
        return nullptr;
    }

    client->connect();

    return client;
}

DefaultClientFactory::AdapterRegistration::AdapterRegistration(
    const std::string& playerId,
    ExternalMediaPlayer::AdapterCreateFunction createFunction) {
    LX(DEBUG3, "id:" + playerId);
    if (m_adapterToCreateFuncMap.find(playerId) != m_adapterToCreateFuncMap.end()) {
        LX(WARN, "Adapter already exists for playerID:" + playerId);
    }

    m_adapterToCreateFuncMap[playerId] = createFunction;
}

DefaultClientFactory::MediaPlayerRegistration::MediaPlayerRegistration(
    const std::string& playerId,
    avsCommon::sdkInterfaces::ChannelVolumeInterface::Type speakerType) {
    LX(DEBUG3, "id:" + playerId);
    if (m_playerToSpeakerTypeMap.find(playerId) != m_playerToSpeakerTypeMap.end()) {
        LX(DEBUG3, "MediaPlayer already exists for playerId:" + playerId);
    }

    m_playerToSpeakerTypeMap[playerId] = speakerType;
}

bool DefaultClientFactory::createMediaPlayersForAdapters(
    std::shared_ptr<avsCommon::utils::libcurlUtils::HTTPContentFetcherFactory> httpContentFetcherFactory,
    std::shared_ptr<defaultClient::EqualizerRuntimeSetup> equalizerRuntimeSetup) {
    bool equalizerEnabled = nullptr != equalizerRuntimeSetup;

    for (auto& entry : m_playerToSpeakerTypeMap) {
        auto applicationMediaInterfaces = createApplicationMediaPlayer(
            httpContentFetcherFactory, equalizerEnabled, entry.first + "MediaPlayer", false);
        if (applicationMediaInterfaces) {
            m_externalMusicProviderMediaPlayersMap[entry.first] = applicationMediaInterfaces->mediaPlayer;
            m_externalMusicProviderSpeakersMap[entry.first] = applicationMediaInterfaces->speaker;
            if (equalizerEnabled) {
                equalizerRuntimeSetup->addEqualizer(applicationMediaInterfaces->equalizer);
            }
        } else {
            LX(ERROR, "Failed to create application media interface:" + entry.first);
            return false;
        }
    }

    return true;
}

std::shared_ptr<ApplicationMediaInterfaces> DefaultClientFactory::createApplicationMediaPlayer(
    std::shared_ptr<avsCommon::utils::libcurlUtils::HTTPContentFetcherFactory> httpContentFetcherFactory,
    bool enableEqualizer,
    const std::string& name,
    bool enableLiveMode) {
    auto mediaPlayer = alexaClientSDK::mediaPlayer::MediaPlayer::create(
        httpContentFetcherFactory, enableEqualizer, name, enableLiveMode);
    if (!mediaPlayer) {
        return nullptr;
    }
    auto speaker = std::static_pointer_cast<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface>(mediaPlayer);
    auto equalizer = std::static_pointer_cast<acsdkEqualizerInterfaces::EqualizerInterface>(mediaPlayer);
    auto requiresShutdown = std::static_pointer_cast<alexaClientSDK::avsCommon::utils::RequiresShutdown>(mediaPlayer);
    auto applicationMediaInterfaces =
        std::make_shared<ApplicationMediaInterfaces>(mediaPlayer, speaker, equalizer, requiresShutdown);

    if (applicationMediaInterfaces->requiresShutdown) {
        m_shutdownRequiredList.push_back(applicationMediaInterfaces->requiresShutdown);
    }
    return applicationMediaInterfaces;
}

}  // namespace alexa
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
