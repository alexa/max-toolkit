<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::crosswake::ActiveAgentSpeechStoreInterface</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1crosswake_1_1ActiveAgentSpeechStoreInterface.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::sampleApplication::agentManager::AgentsConfig::AgentConfig</name>
    <filename>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentsConfig_1_1AgentConfig.html</filename>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentsConfig_1_1AgentConfig.html</anchorfile>
      <anchor>a70a56495e7acd85084760b7fdfb28936</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::string &gt;</type>
      <name>wakewords</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentsConfig_1_1AgentConfig.html</anchorfile>
      <anchor>ae6a5f1b9859b47081579c6acb9da4e46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>configFilePath</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentsConfig_1_1AgentConfig.html</anchorfile>
      <anchor>a53af152ce1e6992afb88be8dc95ca180</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::AgentFactory</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentFactory.html</filename>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; MAX::agent::Agent &gt;</type>
      <name>createAgent</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentFactory.html</anchorfile>
      <anchor>ab4f4eff0a51032a0f18376f19d91af95</anchor>
      <arglist>(const AgentsConfig::AgentConfig &amp;config, const MAX::audio::AudioFormat &amp;audioFormat, std::shared_ptr&lt; utils::AudioDataDirectAccessInterface &gt; audioDataAccessProvider, std::shared_ptr&lt; audioManager::wakeword::crosswake::SimpleCrosswakeDetector &gt; crosswakeDetector, std::shared_ptr&lt; audioManager::wakeword::WakewordMetadataCache &gt; metadataCache)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::AgentManager</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager.html</filename>
    <base>multiAgentExperience::sampleApplication::agentManager::GestureHandlerInterface</base>
    <class kind="struct">multiAgentExperience::sampleApplication::agentManager::AgentManager::AgentSummary</class>
    <member kind="function">
      <type>std::set&lt; AgentSummary &gt;</type>
      <name>getAgentSummaries</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager.html</anchorfile>
      <anchor>ac3a04181eb4d6985ba332031a3d1b63f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>enableAgent</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager.html</anchorfile>
      <anchor>a24ccfa9774fda8ab42dc74012929dea1</anchor>
      <arglist>(const MAX::actor::ActorId &amp;agentName)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>disableAgent</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager.html</anchorfile>
      <anchor>a2332236e0204db70a70b220bf402b0e7</anchor>
      <arglist>(const MAX::actor::ActorId &amp;agentName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invokeGesture</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager.html</anchorfile>
      <anchor>ae9c75649e784f250e9d11374006a9915</anchor>
      <arglist>(GestureType gesture, const std::string &amp;wakeword) override</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; AgentManager &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager.html</anchorfile>
      <anchor>a0b3130f4ec4fcdbfbde20e80f60d86d8</anchor>
      <arglist>(std::shared_ptr&lt; MAX::agent::AgentManagerInterface &gt; maxAgentManager, const rapidjson::Document &amp;parsedJsonDocumentRoot, const MAX::audio::AudioFormat &amp;audioFormat, std::shared_ptr&lt; utils::AudioDataDirectAccessInterface &gt; audioDataAccessProvider, std::shared_ptr&lt; audioManager::wakeword::crosswake::SimpleCrosswakeDetector &gt; crosswakeDetector, std::shared_ptr&lt; audioManager::wakeword::WakewordMetadataCache &gt; metadataCache)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invokeGesture</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager.html</anchorfile>
      <anchor>ae9c75649e784f250e9d11374006a9915</anchor>
      <arglist>(GestureType gesture, const std::string &amp;wakeword) override</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::sampleApplication::agentManager::AgentsConfig</name>
    <filename>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentsConfig.html</filename>
    <class kind="struct">multiAgentExperience::sampleApplication::agentManager::AgentsConfig::AgentConfig</class>
    <member kind="variable">
      <type>std::vector&lt; AgentConfig &gt;</type>
      <name>agentConfigs</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentsConfig.html</anchorfile>
      <anchor>af05722025a3601b6acd4947012f96a71</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::sampleApplication::agentManager::AgentManager::AgentSummary</name>
    <filename>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager_1_1AgentSummary.html</filename>
    <member kind="function">
      <type></type>
      <name>AgentSummary</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager_1_1AgentSummary.html</anchorfile>
      <anchor>a3229b9c7090c6933cf265bea2ca2c636</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager_1_1AgentSummary.html</anchorfile>
      <anchor>a9f9fe9706d976e19a5628672398af166</anchor>
      <arglist>(const AgentSummary &amp;rhs) const</arglist>
    </member>
    <member kind="variable">
      <type>MAX::actor::ActorId</type>
      <name>id</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager_1_1AgentSummary.html</anchorfile>
      <anchor>a4a1562a3700332f88e3b883bae8b6e36</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::set&lt; std::string &gt;</type>
      <name>wakewords</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager_1_1AgentSummary.html</anchorfile>
      <anchor>ace691ed4b6ea08da68aea424c726e3ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>enabled</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1AgentManager_1_1AgentSummary.html</anchorfile>
      <anchor>af81760abe74edd70e2bcdd4171ba147b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::alexa::AlexaActiveAgentSpeechStore</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1alexa_1_1AlexaActiveAgentSpeechStore.html</filename>
    <base>multiAgentExperience::sampleApplication::audioManager::wakeword::crosswake::ActiveAgentSpeechStoreInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::alexa::AlexaAgentFactory</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1alexa_1_1AlexaAgentFactory.html</filename>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; MAX::agent::Agent &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1alexa_1_1AlexaAgentFactory.html</anchorfile>
      <anchor>ada0a81511a94acc254ca1362101e55b9</anchor>
      <arglist>(const AgentsConfig::AgentConfig &amp;config, const MAX::audio::AudioFormat &amp;audioFormat, std::shared_ptr&lt; utils::AudioDataDirectAccessInterface &gt; audioDataAccessProvider, std::shared_ptr&lt; audioManager::wakeword::crosswake::SimpleCrosswakeDetector &gt; crosswakeDetector, std::shared_ptr&lt; audioManager::wakeword::WakewordMetadataCache &gt; metadataCache)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::AnimationEngine</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1AnimationEngine.html</filename>
    <member kind="function">
      <type></type>
      <name>AnimationEngine</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1AnimationEngine.html</anchorfile>
      <anchor>a678d9b347f09597c8a758eba4eb0f1df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AnimationEngine</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1AnimationEngine.html</anchorfile>
      <anchor>ad5105a62f3c91805c06acbbed0327473</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>loadAnimation</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1AnimationEngine.html</anchorfile>
      <anchor>a90420a32bd0af89b65fd53f059ee6968</anchor>
      <arglist>(const std::string &amp;file, size_t id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>playAnimation</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1AnimationEngine.html</anchorfile>
      <anchor>aba217839f4eaceb59b2ed910fe9bee51</anchor>
      <arglist>(size_t id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stopAll</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1AnimationEngine.html</anchorfile>
      <anchor>a183c057f6a635f3cec2ce45dbf365179</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::AnimationLine</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1AnimationLine.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::AnimationSequence</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1AnimationSequence.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::Application</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1Application.html</filename>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1Application.html</anchorfile>
      <anchor>a35d65a50238a3a526adc4912dba95940</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; Application &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1Application.html</anchorfile>
      <anchor>aba4c524e0a2881c12aa957d05d597ffb</anchor>
      <arglist>(const std::string &amp;maxConfigPath)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::sampleApplication::ApplicationConfig</name>
    <filename>structmultiAgentExperience_1_1sampleApplication_1_1ApplicationConfig.html</filename>
    <member kind="function">
      <type></type>
      <name>ApplicationConfig</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1ApplicationConfig.html</anchorfile>
      <anchor>a77c8d8f0356bd94245184aac9c07f6cd</anchor>
      <arglist>(MAX::utils::Log::Level defaultLevel)</arglist>
    </member>
    <member kind="variable">
      <type>MAX::utils::Log::Level</type>
      <name>globalLogLevel</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1ApplicationConfig.html</anchorfile>
      <anchor>acc5af00558758c3fb0abffd4fcfda89e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; std::string, MAX::utils::Log::Level &gt;</type>
      <name>componentOverrides</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1ApplicationConfig.html</anchorfile>
      <anchor>a75e27c26fbe79e4111e14cf77853de5c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::utils::AudioDataDirectAccessInterface</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1AudioDataDirectAccessInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AudioDataDirectAccessInterface</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1AudioDataDirectAccessInterface.html</anchorfile>
      <anchor>a65b057a72063caf5e0036d04e1715a02</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream &gt;</type>
      <name>getSDSHandle</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1AudioDataDirectAccessInterface.html</anchorfile>
      <anchor>ad90d641a1182636b4c27d0c623b32a2e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream::Reader &gt;</type>
      <name>createSDSReader</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1AudioDataDirectAccessInterface.html</anchorfile>
      <anchor>a5dd343621d787473fca9b968fed367af</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::AudioManager</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</filename>
    <base>multiAgentExperience::sampleApplication::utils::AudioDataDirectAccessInterface</base>
    <member kind="function">
      <type>audio::AudioFormat</type>
      <name>getAudioFormat</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>a92aff8f3c86fd059d3e3c7dbf66ede83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGestureHandler</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>a62b20e6e0cee832aa6004851376a21d2</anchor>
      <arglist>(std::shared_ptr&lt; agentManager::GestureHandlerInterface &gt; gestureHandler)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; audioManager::wakeword::WakewordMetadataCache &gt;</type>
      <name>getMetadataCache</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>a732c9436b9dae828b86f7cd86b3c031c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>muteMicrophone</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>ab3bcd4f0b841845ebc52f0f7322f5aff</anchor>
      <arglist>(bool isMuted)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isMicrophoneMuted</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>a248e41ed7270e3919ec5c8b8c5032a50</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream &gt;</type>
      <name>getSDSHandle</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>a03bae700b2181054208cd108f6e3c4bf</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream::Reader &gt;</type>
      <name>createSDSReader</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>af9366c550c43366aafae9308fbd304ec</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; AudioManager &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>a4dc1cf769b4d5167652cb1d29f82192c</anchor>
      <arglist>(std::shared_ptr&lt; audioManager::wakeword::crosswake::SimpleCrosswakeDetector &gt; crosswakeDetector, std::shared_ptr&lt; MAX::application::WakeWordObserverInterface &gt; wakewordObserver, const rapidjson::Document &amp;parsedJsonDocumentRoot)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream &gt;</type>
      <name>getSDSHandle</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>a03bae700b2181054208cd108f6e3c4bf</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream::Reader &gt;</type>
      <name>createSDSReader</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1AudioManager.html</anchorfile>
      <anchor>af9366c550c43366aafae9308fbd304ec</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::avssdk::AVSSDK_KWDAdapter</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</filename>
    <base>multiAgentExperience::sampleApplication::audioManager::wakeword::WakewordEngine</base>
    <member kind="function">
      <type>std::string</type>
      <name>getName</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</anchorfile>
      <anchor>a80abdfaf538154874f74074871310a6f</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>WakewordEngine::CreateMethod</type>
      <name>getCreateMethod</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</anchorfile>
      <anchor>a74716638d73f92faf1ff2e06c9328d76</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::set&lt; std::string &gt;</type>
      <name>getWakewords</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</anchorfile>
      <anchor>a73a3b7a90060afb89d71ff4b0581aafb</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGestureHandler</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</anchorfile>
      <anchor>a95551912a125e006b655c5b53fb32d7b</anchor>
      <arglist>(std::shared_ptr&lt; agentManager::GestureHandlerInterface &gt; gestureHandler) override</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getName</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</anchorfile>
      <anchor>a80abdfaf538154874f74074871310a6f</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>WakewordEngine::CreateMethod</type>
      <name>getCreateMethod</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</anchorfile>
      <anchor>a74716638d73f92faf1ff2e06c9328d76</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::set&lt; std::string &gt;</type>
      <name>getWakewords</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</anchorfile>
      <anchor>a73a3b7a90060afb89d71ff4b0581aafb</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGestureHandler</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapter.html</anchorfile>
      <anchor>a95551912a125e006b655c5b53fb32d7b</anchor>
      <arglist>(std::shared_ptr&lt; agentManager::GestureHandlerInterface &gt; gestureHandler) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::avssdk::AVSSDK_KWDAdapterKeywordObserver</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapterKeywordObserver.html</filename>
    <member kind="function">
      <type></type>
      <name>AVSSDK_KWDAdapterKeywordObserver</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapterKeywordObserver.html</anchorfile>
      <anchor>acb0c90265e8390746c94d2352275901f</anchor>
      <arglist>(std::shared_ptr&lt; audioManager::wakeword::WakewordMetadataCache &gt; metadataCache, std::shared_ptr&lt; audioManager::wakeword::crosswake::SimpleCrosswakeDetector &gt; crosswakeDetector, std::shared_ptr&lt; MAX::application::WakeWordObserverInterface &gt; wakewordObserver)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGestureHandler</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1avssdk_1_1AVSSDK__KWDAdapterKeywordObserver.html</anchorfile>
      <anchor>a9e8721a375eca437d934e3dd6a3e86c5</anchor>
      <arglist>(std::shared_ptr&lt; agentManager::GestureHandlerInterface &gt; gestureHandler)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::Buffer</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1Buffer.html</filename>
    <base>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::NonCopyable</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::computer::ComputerActiveAgentSpeechStore</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1computer_1_1ComputerActiveAgentSpeechStore.html</filename>
    <base>multiAgentExperience::sampleApplication::audioManager::wakeword::crosswake::ActiveAgentSpeechStoreInterface</base>
    <base>multiAgentExperience::samples::agents::computer::speechStore::ActiveAgentSpeechStoreInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::computer::ComputerAgentFactory</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1computer_1_1ComputerAgentFactory.html</filename>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; MAX::agent::Agent &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1computer_1_1ComputerAgentFactory.html</anchorfile>
      <anchor>ac21a176f72eedf5ff860818b7134505d</anchor>
      <arglist>(const AgentsConfig::AgentConfig &amp;config, const MAX::audio::AudioFormat &amp;audioFormat, std::shared_ptr&lt; utils::AudioDataDirectAccessInterface &gt; audioDataAccessProvider, std::shared_ptr&lt; audioManager::wakeword::crosswake::SimpleCrosswakeDetector &gt; simpleCrosswakeDetector)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::computer::ComputerAudioReader</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1computer_1_1ComputerAudioReader.html</filename>
    <member kind="function">
      <type></type>
      <name>~ComputerAudioReader</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1computer_1_1ComputerAudioReader.html</anchorfile>
      <anchor>a0cb6534d8371efb5cf679db7d4dcb25f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; ComputerAudioReader &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1computer_1_1ComputerAudioReader.html</anchorfile>
      <anchor>ab6b1875a204e89402a39b08c31b3befc</anchor>
      <arglist>(const MAX::audio::AudioFormat &amp;audioFormat, std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream::Reader &gt; sdsReader)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::universalDeviceCommandManager::console::ConsoleCommandRenderer</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1universalDeviceCommandManager_1_1console_1_1ConsoleCommandRenderer.html</filename>
    <base>multiAgentExperience::sampleApplication::universalDeviceCommandManager::UniversalDeviceCommandRendererInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::console::ConsoleExperienceRenderer</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1console_1_1ConsoleExperienceRenderer.html</filename>
    <base>multiAgentExperience::sampleApplication::experienceManager::ExperienceRendererInterface</base>
    <member kind="function">
      <type></type>
      <name>ConsoleExperienceRenderer</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1console_1_1ConsoleExperienceRenderer.html</anchorfile>
      <anchor>af6f88466ff9e31d65e5d1a28f25ff32f</anchor>
      <arglist>(std::shared_ptr&lt; uiManager::ConsolePrinter &gt; consolePrinter)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::uiManager::ConsolePrinter</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1ConsolePrinter.html</filename>
    <member kind="function">
      <type>void</type>
      <name>print</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1ConsolePrinter.html</anchorfile>
      <anchor>aede8ce3c8b5fe448016f79e3d151cbe1</anchor>
      <arglist>(const std::string &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prettyPrint</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1ConsolePrinter.html</anchorfile>
      <anchor>ac62c587ed7fe71adc641f9eb816ae6fa</anchor>
      <arglist>(const std::string &amp;message, const char decorationCharacter=&apos;#&apos;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prettyPrint</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1ConsolePrinter.html</anchorfile>
      <anchor>a6c83f1df59358713ebfb7ed3c67cd778</anchor>
      <arglist>(const std::vector&lt; std::string &gt; &amp;message, const char decorationCharacter=&apos;#&apos;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::uiManager::ConsoleReader</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1ConsoleReader.html</filename>
    <member kind="function">
      <type></type>
      <name>ConsoleReader</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1ConsoleReader.html</anchorfile>
      <anchor>a1102c9450f64f82b93b8410328a2ae1b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ConsoleReader</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1ConsoleReader.html</anchorfile>
      <anchor>aecb75202981a821709d24234b2ea5c25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>read</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1ConsoleReader.html</anchorfile>
      <anchor>a26006033147b10e7c07dbff3aa725755</anchor>
      <arglist>(const std::chrono::milliseconds timeout, char *data)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::utils::avssdk::CustomLogger</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1avssdk_1_1CustomLogger.html</filename>
    <member kind="function">
      <type></type>
      <name>CustomLogger</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1avssdk_1_1CustomLogger.html</anchorfile>
      <anchor>a7f927e0143d859a7c07bc7d4c32ded50</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::alexa::DefaultClientFactory</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1alexa_1_1DefaultClientFactory.html</filename>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; alexaClientSDK::defaultClient::DefaultClient &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1alexa_1_1DefaultClientFactory.html</anchorfile>
      <anchor>a64206bac323c2f65ace0beba7c806f1f</anchor>
      <arglist>(const AgentsConfig::AgentConfig &amp;config, std::shared_ptr&lt; utils::AudioDataDirectAccessInterface &gt; audioDataAccessProvider, std::shared_ptr&lt; alexaClientSDK::avsCommon::sdkInterfaces::ActiveAgentSpeechStoreInterface &gt; agentSpeechStore, std::shared_ptr&lt; audioManager::wakeword::WakewordMetadataCache &gt; metadataCache)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::DrawContext</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1DrawContext.html</filename>
    <base>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::NonCopyable</base>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::WakewordEnginesConfig::EngineConfig</name>
    <filename>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEnginesConfig_1_1EngineConfig.html</filename>
    <member kind="function">
      <type></type>
      <name>EngineConfig</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEnginesConfig_1_1EngineConfig.html</anchorfile>
      <anchor>a231822fc991e0cdb267e8a60ef08c209</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEnginesConfig_1_1EngineConfig.html</anchorfile>
      <anchor>a9a3873456cbdbc346cda4ed85dbb535e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>WakewordEngine::CreateMethod</type>
      <name>createMethod</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEnginesConfig_1_1EngineConfig.html</anchorfile>
      <anchor>a72c0d0028c53d244c795e2c59637caf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::string &gt;</type>
      <name>wakewords</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEnginesConfig_1_1EngineConfig.html</anchorfile>
      <anchor>ac3106eac871cdf7caf4c5159c77b3b4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>resourceFolder</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEnginesConfig_1_1EngineConfig.html</anchorfile>
      <anchor>a24fe7553c873b28105b1f461212f6af0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::ExperienceManager</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1ExperienceManager.html</filename>
    <member kind="function">
      <type>void</type>
      <name>addRenderer</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1ExperienceManager.html</anchorfile>
      <anchor>a7c4373c77e4989ae73432721e70d3f6e</anchor>
      <arglist>(std::shared_ptr&lt; ExperienceRendererInterface &gt; renderer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeRenderer</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1ExperienceManager.html</anchorfile>
      <anchor>a6e247516e7bd9417a3438a840046d8ff</anchor>
      <arglist>(std::shared_ptr&lt; ExperienceRendererInterface &gt; renderer)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; ExperienceManager &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1ExperienceManager.html</anchorfile>
      <anchor>a85d103d9ffeca37c7d2038553a6d7918</anchor>
      <arglist>(std::shared_ptr&lt; MAX::experience::ExperienceManagerInterface &gt; maxExperienceManager)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::ExperienceRendererInterface</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1ExperienceRendererInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ExperienceRendererInterface</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1ExperienceRendererInterface.html</anchorfile>
      <anchor>a177375c59b116228a1a8e6574afcef87</anchor>
      <arglist>()=default</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::GestureHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1GestureHandlerInterface.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>GestureType</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1GestureHandlerInterface.html</anchorfile>
      <anchor>a51df460700ab4f712ed548bfe4338ee1</anchor>
      <arglist></arglist>
      <enumvalue file="classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1GestureHandlerInterface.html" anchor="a51df460700ab4f712ed548bfe4338ee1afcd6420c60a17418a6de745d6546d966">TAP</enumvalue>
      <enumvalue file="classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1GestureHandlerInterface.html" anchor="a51df460700ab4f712ed548bfe4338ee1a0c6d9dfb485b43c6fba87439f9f73ac4">HOLD</enumvalue>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~GestureHandlerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1GestureHandlerInterface.html</anchorfile>
      <anchor>a5b8329bc24e5b702aaa9856cced03b39</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>invokeGesture</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1GestureHandlerInterface.html</anchorfile>
      <anchor>a27321db0a13d4f53aeefbb165c373116</anchor>
      <arglist>(GestureType gesture, const std::string &amp;wakeword)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::uiManager::InputHandler</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InputHandler.html</filename>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InputHandler.html</anchorfile>
      <anchor>a27ad4f167feac55cb8cb86847b01fb74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; InputHandler &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InputHandler.html</anchorfile>
      <anchor>aafb36dbe7a5e488824b65a4d79b1a8b6</anchor>
      <arglist>(std::shared_ptr&lt; agentManager::AgentManager &gt; agentManager, std::shared_ptr&lt; InteractionHandler &gt; interactionHandler, std::shared_ptr&lt; universalDeviceCommandManager::UniversalDeviceCommandManager &gt; udcManager, std::weak_ptr&lt; audioManager::AudioManager &gt; audioManager)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::uiManager::InteractionHandler</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InteractionHandler.html</filename>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InteractionHandler.html</anchorfile>
      <anchor>a6e607b329b69b50916d7d7073cafc9aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printWelcomeScreen</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InteractionHandler.html</anchorfile>
      <anchor>a17726b95221461224567592bc115b918</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printHelpMessage</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InteractionHandler.html</anchorfile>
      <anchor>a2424a29053724983415afa5039a2ce22</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printMicrophoneStatus</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InteractionHandler.html</anchorfile>
      <anchor>a48c8da6f04d7001eb1114be708ea0313</anchor>
      <arglist>(bool isMuted)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>printInvokingStop</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InteractionHandler.html</anchorfile>
      <anchor>a4614dd6339d5a0df7a38b72f5d104ffb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; InteractionHandler &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1InteractionHandler.html</anchorfile>
      <anchor>a3321bdc87d82cefeeee6be685d416661</anchor>
      <arglist>(std::shared_ptr&lt; agentManager::AgentManager &gt; agentManager, std::shared_ptr&lt; uiManager::ConsolePrinter &gt; consolePrinter)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::sampleApplication::audioManager::microphone::MicrophoneConfig</name>
    <filename>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneConfig.html</filename>
    <member kind="function">
      <type></type>
      <name>MicrophoneConfig</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneConfig.html</anchorfile>
      <anchor>a8cd230b965600fbe8fb55d94420bd36f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>suggestedLatencySeconds</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneConfig.html</anchorfile>
      <anchor>aec7f86cea9dccf84cc93920148ec4a11</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::microphone::MicrophoneInterface</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneInterface.html</filename>
    <base>multiAgentExperience::utils::data::DataWriterInterface</base>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MicrophoneInterface</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneInterface.html</anchorfile>
      <anchor>ac42803565472d49d982f1fb501c8c6ed</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>startStreamingData</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneInterface.html</anchorfile>
      <anchor>a666448fbcff81ce5697d98a389a34287</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>stopStreamingData</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneInterface.html</anchorfile>
      <anchor>ae8f1f9e7d42021a4aa9a704d65938212</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>mute</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneInterface.html</anchorfile>
      <anchor>a0c3dadc06881e44b8a89d70b5a1efd4a</anchor>
      <arglist>(bool enabled)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isMuted</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1MicrophoneInterface.html</anchorfile>
      <anchor>a23a392d92d4bf1bda2232c061fc074b6</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::NonCopyable</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1NonCopyable.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::agentManager::alexa::NoopCBLAuthRequester</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1agentManager_1_1alexa_1_1NoopCBLAuthRequester.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::PiSenseMatrix</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1experienceManager_1_1senseHat_1_1ledController_1_1PiSenseMatrix.html</filename>
    <base>multiAgentExperience::sampleApplication::experienceManager::senseHat::ledController::NonCopyable</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::microphone::PortAudioMicrophone</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</filename>
    <base>multiAgentExperience::sampleApplication::audioManager::microphone::MicrophoneInterface</base>
    <member kind="function">
      <type></type>
      <name>~PortAudioMicrophone</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>a9051697db0e7f1be2c29e3ac3fb0feb6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>startStreamingData</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>af6792826b3f16a1b74fe6ff44216c837</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stopStreamingData</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>a334d84b2d96bb94d1fcfa9b43c902592</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mute</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>adf693b31bcf28a0d0d790e35e8c1cce8</anchor>
      <arglist>(bool enabled) override</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isMuted</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>ac05aabf8f62afa0f0255453b8d5a3803</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; PortAudioMicrophone &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>af5007603c684b99f03e009296fbed71e</anchor>
      <arglist>(const audio::AudioFormat &amp;format, const MicrophoneConfig &amp;config)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>startStreamingData</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>af6792826b3f16a1b74fe6ff44216c837</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stopStreamingData</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>a334d84b2d96bb94d1fcfa9b43c902592</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mute</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>adf693b31bcf28a0d0d790e35e8c1cce8</anchor>
      <arglist>(bool enabled) override</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isMuted</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1microphone_1_1PortAudioMicrophone.html</anchorfile>
      <anchor>ac05aabf8f62afa0f0255453b8d5a3803</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::utils::RadiantLogger</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1RadiantLogger.html</filename>
    <base>multiAgentExperience::utils::Log</base>
    <member kind="function">
      <type>void</type>
      <name>setComponentLevel</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1RadiantLogger.html</anchorfile>
      <anchor>ad5f71a736bda5b2a59f8e800d91b3b62</anchor>
      <arglist>(const std::string &amp;componentName, MAX::utils::Log::Level level)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; RadiantLogger &gt;</type>
      <name>instance</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1RadiantLogger.html</anchorfile>
      <anchor>a2b4d87eee2cd15193f18718769d45088</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>MAX_APP_COMPONENT_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1RadiantLogger.html</anchorfile>
      <anchor>a5fa570bc376f81c204c156af529cee8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>AVS_SDK_COMPONENT_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1RadiantLogger.html</anchorfile>
      <anchor>ac9dacf9a231c010141e14bbf5be6fcea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>MAX_LIB_COMPONENT_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1RadiantLogger.html</anchorfile>
      <anchor>a1187bc92a3a2a5cbd3498de4fdff693c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>COMPUTER_AGENT_COMPONENT_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1utils_1_1RadiantLogger.html</anchorfile>
      <anchor>a4596570f7ed4cace6cb49bbc1b7427a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::sds::SDSReader</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1sds_1_1SDSReader.html</filename>
    <base>multiAgentExperience::audio::AudioReaderInterface</base>
    <member kind="function">
      <type></type>
      <name>SDSReader</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1sds_1_1SDSReader.html</anchorfile>
      <anchor>a3faeb93c3c666965197e499add644eeb</anchor>
      <arglist>(const std::string &amp;readerName, const multiAgentExperience::audio::AudioFormat &amp;audioFormat, std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream::Reader &gt; reader, bool enabled)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SDSReader</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1sds_1_1SDSReader.html</anchorfile>
      <anchor>a2ad396d42058446c438f6bfdc6ddeb0c</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::crosswake::SimpleCrosswakeDetector</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1crosswake_1_1SimpleCrosswakeDetector.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::kittai::SnowboyKWD</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</filename>
    <base>multiAgentExperience::sampleApplication::audioManager::wakeword::WakewordEngine</base>
    <member kind="function">
      <type>bool</type>
      <name>isCompatible</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>a8b11c551750231d380660efa9e34832a</anchor>
      <arglist>(MAX::audio::AudioFormat audioFormat)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startWatching</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>aee2e05264f5b64cef49fdee55ff4b3e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stopWatching</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>a2762bd8a46980a0269497cbb43e21345</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getName</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>ae13f275686aa6c5d8566a3b33406c0ab</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>WakewordEngine::CreateMethod</type>
      <name>getCreateMethod</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>a8b6847cbca73e26aa500885d2b0c57cd</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::set&lt; std::string &gt;</type>
      <name>getWakewords</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>af99c05f6a5176c2ad6ac5e0905140dd0</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; SnowboyKWD &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>af2caa23298b926af9fd017757f221812</anchor>
      <arglist>(const WakewordEnginesConfig::EngineConfig &amp;config, std::shared_ptr&lt; audioManager::wakeword::crosswake::SimpleCrosswakeDetector &gt; crosswakeDetector, std::shared_ptr&lt; MAX::application::WakeWordObserverInterface &gt; wakewordObserver, std::shared_ptr&lt; MAX::audio::AudioReaderInterface &gt; audioReader)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getName</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>ae13f275686aa6c5d8566a3b33406c0ab</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>WakewordEngine::CreateMethod</type>
      <name>getCreateMethod</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>a8b6847cbca73e26aa500885d2b0c57cd</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::set&lt; std::string &gt;</type>
      <name>getWakewords</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyKWD.html</anchorfile>
      <anchor>af99c05f6a5176c2ad6ac5e0905140dd0</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::kittai::SnowboyWrapper</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</filename>
    <member kind="function">
      <type></type>
      <name>SnowboyWrapper</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>a25e2ac9cfac61fab5b4ac7cae3c8691f</anchor>
      <arglist>(const char *resourceFilename, const char *model)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SnowboyWrapper</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>a52e5c0620d8d42dc80f6b5bd52bc2438</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RunDetection</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>ac47dea9549fc563274891daa41ae3fc6</anchor>
      <arglist>(const int16_t *const data, const int arrayLength, bool isEnd=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSensitivity</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>a1a72415bf4b2d8b07c209d39e86b576d</anchor>
      <arglist>(const char *sensitivity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetAudioGain</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>a1778077fd016da1641e29d74dbe9aa74</anchor>
      <arglist>(const float audioGain)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyFrontend</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>a9adafd4fd6552d420e46dd7341e6ee17</anchor>
      <arglist>(const bool applyFrontend)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SampleRate</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>ae517cd65f00dcfb33e2f0d95fc28b06a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>NumChannels</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>ac5aa863bc020a3b226317760a1e13155</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>BitsPerSample</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1kittai_1_1SnowboyWrapper.html</anchorfile>
      <anchor>af0329c23c8bd77e1524f62c8b6dacfef</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::uiManager::UIManager</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1UIManager.html</filename>
    <member kind="function">
      <type>std::shared_ptr&lt; uiManager::ConsolePrinter &gt;</type>
      <name>getConsolePrinter</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1UIManager.html</anchorfile>
      <anchor>a63a2537ef27bdafe9a72af81441cdabb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>start</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1UIManager.html</anchorfile>
      <anchor>ae870037d2ff908618145659968044b21</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; UIManager &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1uiManager_1_1UIManager.html</anchorfile>
      <anchor>a73f35ac3bbe543fdba30344fc2e1a5b4</anchor>
      <arglist>(std::shared_ptr&lt; agentManager::AgentManager &gt; agentManager, std::shared_ptr&lt; universalDeviceCommandManager::UniversalDeviceCommandManager &gt; udcManager, std::weak_ptr&lt; audioManager::AudioManager &gt; audioManager)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::universalDeviceCommandManager::UniversalDeviceCommandManager</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1universalDeviceCommandManager_1_1UniversalDeviceCommandManager.html</filename>
    <member kind="function">
      <type>void</type>
      <name>addRenderer</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1universalDeviceCommandManager_1_1UniversalDeviceCommandManager.html</anchorfile>
      <anchor>aed2b7a10f9781b8d2bc55301784f0cbc</anchor>
      <arglist>(std::weak_ptr&lt; UniversalDeviceCommandRendererInterface &gt; renderer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clearRenderers</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1universalDeviceCommandManager_1_1UniversalDeviceCommandManager.html</anchorfile>
      <anchor>aa9e6c3ef69f0a66cd96327805f796ff2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invokeStop</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1universalDeviceCommandManager_1_1UniversalDeviceCommandManager.html</anchorfile>
      <anchor>ab1d016cd6cf06e1200a530b588699f22</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; UniversalDeviceCommandManager &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1universalDeviceCommandManager_1_1UniversalDeviceCommandManager.html</anchorfile>
      <anchor>aba533ad1a3a5f970fd544b1f3cacbb14</anchor>
      <arglist>(std::shared_ptr&lt; MAX::control::ControlManagerInterface &gt; maxControlManager, std::shared_ptr&lt; MAX::control::ControlInvokerInterface &gt; maxControlInvoker)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::universalDeviceCommandManager::UniversalDeviceCommandRendererInterface</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1universalDeviceCommandManager_1_1UniversalDeviceCommandRendererInterface.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::WakewordEngine</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>CreateMethod</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</anchorfile>
      <anchor>a224eca114a6706474fac7f3c067d0bbd</anchor>
      <arglist></arglist>
      <enumvalue file="classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html" anchor="a224eca114a6706474fac7f3c067d0bbdab6074cb7ef4c50a74b954eaab5a32e93">AVS_SDK</enumvalue>
      <enumvalue file="classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html" anchor="a224eca114a6706474fac7f3c067d0bbda72baef04098f035e8a320b03ad197818">CUSTOM</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>WakewordEngine</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</anchorfile>
      <anchor>a534f17ded84c3d96ae5ea9316f89ec44</anchor>
      <arglist>(std::shared_ptr&lt; crosswake::SimpleCrosswakeDetector &gt; crosswakeDetector, std::shared_ptr&lt; MAX::application::WakeWordObserverInterface &gt; observer)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~WakewordEngine</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</anchorfile>
      <anchor>aef60034952c56440b69c0000b7af39c2</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::string</type>
      <name>getName</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</anchorfile>
      <anchor>aae728d261209d38f4e7d37b02e172c40</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual CreateMethod</type>
      <name>getCreateMethod</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</anchorfile>
      <anchor>a35c5f96b6f139da870f755d9006ef89e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::set&lt; std::string &gt;</type>
      <name>getWakewords</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</anchorfile>
      <anchor>adffc123606fe29d181fd1bd208d5ab84</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setGestureHandler</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</anchorfile>
      <anchor>ae08d29eb682e58ebfb93f80e1d889d39</anchor>
      <arglist>(std::shared_ptr&lt; agentManager::GestureHandlerInterface &gt; gestureHandler)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::shared_ptr&lt; crosswake::SimpleCrosswakeDetector &gt;</type>
      <name>m_crosswakeDetector</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngine.html</anchorfile>
      <anchor>a944080bde687f600f970f0e0ce5cc73c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::WakewordEngineFactory</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngineFactory.html</filename>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; WakewordEngine &gt;</type>
      <name>createWakewordEngine</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEngineFactory.html</anchorfile>
      <anchor>a9ad94b45a899a8083d9465084754c3e8</anchor>
      <arglist>(audio::AudioFormat audioFormat, const WakewordEnginesConfig::EngineConfig &amp;config, std::shared_ptr&lt; crosswake::SimpleCrosswakeDetector &gt; crosswakeDetector, std::shared_ptr&lt; MAX::application::WakeWordObserverInterface &gt; wakewordObserver, std::shared_ptr&lt; audioManager::wakeword::WakewordMetadataCache &gt; metadataCache, std::shared_ptr&lt; alexaClientSDK::avsCommon::avs::AudioInputStream &gt; sharedDataStream)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::WakewordEnginesConfig</name>
    <filename>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEnginesConfig.html</filename>
    <class kind="struct">multiAgentExperience::sampleApplication::audioManager::wakeword::WakewordEnginesConfig::EngineConfig</class>
    <member kind="variable">
      <type>std::vector&lt; EngineConfig &gt;</type>
      <name>engineConfigs</name>
      <anchorfile>structmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordEnginesConfig.html</anchorfile>
      <anchor>a8bd91ff534dc1e702cfe134587f3cae8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::sampleApplication::audioManager::wakeword::WakewordMetadataCache</name>
    <filename>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordMetadataCache.html</filename>
    <member kind="function">
      <type>void</type>
      <name>setMetadata</name>
      <anchorfile>classmultiAgentExperience_1_1sampleApplication_1_1audioManager_1_1wakeword_1_1WakewordMetadataCache.html</anchorfile>
      <anchor>a8865eb7c985cefca5ce2ae1ff423fc0d</anchor>
      <arglist>(const alexaClientSDK::avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface::Metadata &amp;data)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>MAX Sample Application</title>
    <filename>index</filename>
  </compound>
</tagfile>
