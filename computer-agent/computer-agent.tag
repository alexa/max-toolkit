<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::speechStore::ActiveAgentSpeechStoreInterface</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1speechStore_1_1ActiveAgentSpeechStoreInterface.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::audio::AudioStore</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1audio_1_1AudioStore.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::Computer</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1Computer.html</filename>
    <member kind="function" static="yes">
      <type>static std::unique_ptr&lt; Computer &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1Computer.html</anchorfile>
      <anchor>a626c794c73a5d9ef970bdca7935f74a6</anchor>
      <arglist>(const std::string &amp;name, const std::string &amp;wakeword, std::shared_ptr&lt; MAX::audio::AudioReaderInterface &gt; audioReader, std::shared_ptr&lt; avssdkUtils::mediaPlayer::MediaPlayerInterface &gt; mediaPlayer, std::shared_ptr&lt; speechStore::ActiveAgentSpeechStoreInterface &gt; activeSpeechStore, std::shared_ptr&lt; MAX::utils::Log &gt; logger, const std::string &amp;logComponentName)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::audio::ComputerSoundFilePlayer</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1audio_1_1ComputerSoundFilePlayer.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::utils::ControlTypeUtils</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1utils_1_1ControlTypeUtils.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::lex::LexClient</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1lex_1_1LexClient.html</filename>
    <member kind="function">
      <type></type>
      <name>LexClient</name>
      <anchorfile>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1lex_1_1LexClient.html</anchorfile>
      <anchor>af9d437f27206934dbdcbe61c0120d84d</anchor>
      <arglist>(std::shared_ptr&lt; response::ResponseHandler &gt; responseHandler, std::shared_ptr&lt; MAX::audio::AudioReaderInterface &gt; audioReader)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LexClient</name>
      <anchorfile>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1lex_1_1LexClient.html</anchorfile>
      <anchor>aac75be99838e0eb0ab33c3a9866311fc</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::response::Response</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1response_1_1Response.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::response::ResponseHandler</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1response_1_1ResponseHandler.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::audio::SoundPlayerActivityHandler</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1audio_1_1SoundPlayerActivityHandler.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::response::SpeechResponder</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1response_1_1SpeechResponder.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::dialog::UserDialogRequest</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1dialog_1_1UserDialogRequest.html</filename>
    <base>multiAgentExperience::dialog::DialogRequestInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::samples::agents::computer::VoiceActivityDetector</name>
    <filename>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1VoiceActivityDetector.html</filename>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1VoiceActivityDetector.html</anchorfile>
      <anchor>abb0e45d72ffaf94b8dd6c11cf9e7a324</anchor>
      <arglist>(size_t samplesPerSecond)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1VoiceActivityDetector.html</anchorfile>
      <anchor>ada033eb6cd43b516c06c68d856437688</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>processFrame</name>
      <anchorfile>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1VoiceActivityDetector.html</anchorfile>
      <anchor>ad990df41b8b6722f131152d0ae5b8e23</anchor>
      <arglist>(int16_t *frame, size_t frameSize)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSilenced</name>
      <anchorfile>classmultiAgentExperience_1_1samples_1_1agents_1_1computer_1_1VoiceActivityDetector.html</anchorfile>
      <anchor>aabb90b6b1750020c4f3ed42de78cc397</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Computer Agent</title>
    <filename>index</filename>
  </compound>
</tagfile>
