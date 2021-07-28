<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::Activity</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1Activity.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::FocusManagerInterface::Activity</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</filename>
    <member kind="function">
      <type>const std::string</type>
      <name>getInterface</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</anchorfile>
      <anchor>ae5c393f10793cc81619d7f7a23d622b9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::chrono::milliseconds</type>
      <name>getPatienceDuration</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</anchorfile>
      <anchor>a3c0d71972acc6ca510a094878bc1ae60</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ContentType</type>
      <name>getContentType</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</anchorfile>
      <anchor>a16b34b7fe3b02c1e7e4c47b83a64f7fb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setContentType</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</anchorfile>
      <anchor>a442b607fc51f5b6461b4b36f51554574</anchor>
      <arglist>(ContentType contentType)</arglist>
    </member>
    <member kind="function">
      <type>MixingBehavior</type>
      <name>getMixingBehavior</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</anchorfile>
      <anchor>a901d6e08361ec73b310a6c113139a7ad</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; ChannelObserverInterface &gt;</type>
      <name>getChannelObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</anchorfile>
      <anchor>afec1c79660d2093e277562db54445d65</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>notifyObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</anchorfile>
      <anchor>ad8728af41101e12f9c29923ed0d79c15</anchor>
      <arglist>(FocusState focus, MixingBehavior behavior)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; Activity &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface_1_1Activity.html</anchorfile>
      <anchor>ad6abbc8dc4ffff8e4b34422e23769485</anchor>
      <arglist>(const std::string &amp;interfaceName, const std::shared_ptr&lt; ChannelObserverInterface &gt; &amp;channelObserver, const std::chrono::milliseconds &amp;patienceDuration=std::chrono::milliseconds::zero(), const ContentType contentType=ContentType::NONMIXABLE)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::ActivityChannels</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1ActivityChannels.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::activity::ActivityControllerInterface</name>
    <filename>classmultiAgentExperience_1_1activity_1_1ActivityControllerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ActivityControllerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityControllerInterface.html</anchorfile>
      <anchor>a12419185816ca4ba4a41c41c7b6e2400</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityControllerInterface.html</anchorfile>
      <anchor>a2a737dfda6580bd800cc70563fc9ea5b</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ActivityControllerTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ActivityControllerTransformer.html</filename>
    <base>multiAgentExperience::activity::ActivityControllerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ActivityControllerTransformer.html</anchorfile>
      <anchor>afd3179670efc3bd766a01d2907ec4162</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ActivityControllerTransformer.html</anchorfile>
      <anchor>afd3179670efc3bd766a01d2907ec4162</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::ActivityControllerTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1ActivityControllerTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::activity::ActivityHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1activity_1_1ActivityHandlerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ActivityHandlerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityHandlerInterface.html</anchorfile>
      <anchor>acffbfedf8ef59f9aa3bd7f857684596a</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onDenied</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityHandlerInterface.html</anchorfile>
      <anchor>a8122453d1d4a5d7bb1ac813a1a08b012</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onReady</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityHandlerInterface.html</anchorfile>
      <anchor>af48c7961436d4936ac5d43cc97b12ba7</anchor>
      <arglist>(std::shared_ptr&lt; ActivityControllerInterface &gt; activityController, multiAgentExperience::activity::ActivityFocus focus, std::shared_ptr&lt; control::ControlRegistryInterface &gt; controlRegistry, std::shared_ptr&lt; experience::ExperienceControllerInterface &gt; experienceControl)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onFocusStateChange</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityHandlerInterface.html</anchorfile>
      <anchor>aeeff4c3dce8f6e9d13dc35a9950ad4e0</anchor>
      <arglist>(multiAgentExperience::activity::ActivityFocus focus)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onStop</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityHandlerInterface.html</anchorfile>
      <anchor>a2b4fdfe13b00e017036858e1871e08aa</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::ActivityLifecycle</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1ActivityLifecycle.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::ActivityLifecycleTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1ActivityLifecycleTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::ActivityManager</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1ActivityManager.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::library::activity::ActivityManagerFactory</name>
    <filename>structmultiAgentExperience_1_1library_1_1activity_1_1ActivityManagerFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::activity::ActivityManagerInterface</name>
    <filename>classmultiAgentExperience_1_1activity_1_1ActivityManagerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ActivityManagerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityManagerInterface.html</anchorfile>
      <anchor>a4fb534a0118c1c500c2081495e2c9813</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>request</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityManagerInterface.html</anchorfile>
      <anchor>af1aa84a262422edc0c66b532082f8158</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::activity::ActivityRequestInterface &gt; request)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityManagerInterface.html</anchorfile>
      <anchor>a370b5ae3bb210c68ffa95a2030443c20</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::activity::ActivityRequestInterface &gt; request)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::ActivityManagerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1ActivityManagerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ActivityManagerTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ActivityManagerTransformer.html</filename>
    <base>multiAgentExperience::activity::ActivityManagerInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ActivityManagerTransformerFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ActivityManagerTransformerFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::ActivityManagerTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1ActivityManagerTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::ActivityRequest</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1ActivityRequest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::activity::ActivityRequestInterface</name>
    <filename>classmultiAgentExperience_1_1activity_1_1ActivityRequestInterface.html</filename>
    <member kind="function">
      <type></type>
      <name>ActivityRequestInterface</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityRequestInterface.html</anchorfile>
      <anchor>ab47c71634e6c6e151dab14e8940cc14e</anchor>
      <arglist>(ActivityType activityType, std::shared_ptr&lt; ActivityHandlerInterface &gt; handler)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ActivityRequestInterface</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityRequestInterface.html</anchorfile>
      <anchor>a9944131860a74ebf9d642300ffa84be9</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>ActivityType</type>
      <name>getType</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityRequestInterface.html</anchorfile>
      <anchor>a26ce5b39b2d6b818843efa9efe56f577</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; ActivityHandlerInterface &gt;</type>
      <name>getHandler</name>
      <anchorfile>classmultiAgentExperience_1_1activity_1_1ActivityRequestInterface.html</anchorfile>
      <anchor>a22fcea4f8fca8d19c8053e58822a3213</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::ActivityRequestLifecycle</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1ActivityRequestLifecycle.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::ActivityRequestLifecycleTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1ActivityRequestLifecycleTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ActivityRequestTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ActivityRequestTransformer.html</filename>
    <base>multiAgentExperience::library::activity::ActivityRequest</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ActivityRequestTransformerFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ActivityRequestTransformerFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::ActivityRequestTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1ActivityRequestTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::ActivityTrackerInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1ActivityTrackerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ActivityTrackerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1ActivityTrackerInterface.html</anchorfile>
      <anchor>a7d8e5e54b8d6ecb5cc37a04b55029148</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>notifyOfActivityUpdates</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1ActivityTrackerInterface.html</anchorfile>
      <anchor>a639acb228e45d3b8f7311be3bc08a22c</anchor>
      <arglist>(const std::vector&lt; Channel::State &gt; &amp;channelStates)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ActivityTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ActivityTransformer.html</filename>
    <base>multiAgentExperience::library::activity::Activity</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::ActivityTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1ActivityTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::agent::Agent</name>
    <filename>classmultiAgentExperience_1_1agent_1_1Agent.html</filename>
    <member kind="function">
      <type></type>
      <name>Agent</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>a6556439e5fced10466a46d4b0afb1d11</anchor>
      <arglist>(const actor::ActorId &amp;id, const std::string &amp;wakeword)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Agent</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>a72fb756e4d989cd4e64b54ede0004169</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initializeCoreInterfaces</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>aed0829b7cd664016bde13966ff27b42c</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::activity::ActivityManagerInterface &gt; activityManager, std::shared_ptr&lt; multiAgentExperience::dialog::DialogManagerInterface &gt; dialogManager, std::shared_ptr&lt; AgentTransferManagerInterface &gt; agentTransferManager)</arglist>
    </member>
    <member kind="function">
      <type>actor::ActorId</type>
      <name>getId</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>ae3e68d2ab13ceb9aeee0b73b8be1c966</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>getName</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>af9acf0646477235358d4dd4cbf485b33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getWakeword</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>a332ae8d7a7192cc037a7e2d509f8b21f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onWakeWordDetected</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>a6936e4650ddfe9b5968038cd61a90126</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onTapDetected</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>a74d9186195396570a97b479de76588a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onAgentTransfer</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>ac26d37b1d97a5522e0acfb3e190d9213</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>handleOnWakeWordDetected</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>a24c86daf284c156e7f62d9feca6e1d0d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>handleOnTapDetected</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>a2d5aa7f4b2a0c422a49836dd4b5518af</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>handleOnAgentTransfer</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>abf6648085ddab5eabef8229249b7c189</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>onInitialized</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>ac6e646df0a4b1d73fb6c002b7266e093</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::shared_ptr&lt; multiAgentExperience::activity::ActivityManagerInterface &gt;</type>
      <name>m_activityManager</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>aa5bee445941585fc05a46f0308934e0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::shared_ptr&lt; multiAgentExperience::dialog::DialogManagerInterface &gt;</type>
      <name>m_dialogManager</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>addd5d4d119ac621999af1be32ddf46b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::shared_ptr&lt; AgentTransferManagerInterface &gt;</type>
      <name>m_agentTransferManager</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1Agent.html</anchorfile>
      <anchor>a897ddf9dd28faca163424e3f2c9d195a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::application::AgentManager</name>
    <filename>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</filename>
    <base>multiAgentExperience::agent::AgentManagerInterface</base>
    <base>multiAgentExperience::application::WakeWordObserverInterface</base>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::agent::Agent &gt;</type>
      <name>getAgentById</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</anchorfile>
      <anchor>ace44e6279904af0425178f0847757bc9</anchor>
      <arglist>(const multiAgentExperience::actor::ActorId &amp;id)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>registerAgent</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</anchorfile>
      <anchor>a4e60d1cb3065c27460852ad434ffaa73</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::agent::Agent &gt; agent) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deregisterAgent</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</anchorfile>
      <anchor>ad68513ec827c8ff19030834deeecf61e</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::agent::Agent &gt; agent) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onWakeWordDetected</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</anchorfile>
      <anchor>af2c39144fa331336e394d384b5d3f3f5</anchor>
      <arglist>(const std::string &amp;wakeWord) override</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; AgentManager &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</anchorfile>
      <anchor>adc251fc9e98d5502732a199c8f2ab2bc</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::library::core::transformer::AgentTransferManagerTransformerFactory &gt; agentTransferManagerTransformerFactory, std::shared_ptr&lt; multiAgentExperience::library::core::transformer::ActivityManagerTransformerFactory &gt; activityManagerTransformerFactory, std::shared_ptr&lt; multiAgentExperience::library::core::transformer::DialogManagerTransformerFactory &gt; dialogManagerTransformerFactory)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>registerAgent</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</anchorfile>
      <anchor>a4e60d1cb3065c27460852ad434ffaa73</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::agent::Agent &gt; agent) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deregisterAgent</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</anchorfile>
      <anchor>ad68513ec827c8ff19030834deeecf61e</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::agent::Agent &gt; agent) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onWakeWordDetected</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1AgentManager.html</anchorfile>
      <anchor>af2c39144fa331336e394d384b5d3f3f5</anchor>
      <arglist>(const std::string &amp;wakeWord) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::agent::AgentManagerInterface</name>
    <filename>classmultiAgentExperience_1_1agent_1_1AgentManagerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AgentManagerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1AgentManagerInterface.html</anchorfile>
      <anchor>a9d86f227395174407f9a2daaaaa24539</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>registerAgent</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1AgentManagerInterface.html</anchorfile>
      <anchor>aa25436cb59e31814811ba7bc021d8498</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::agent::Agent &gt; agent)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>deregisterAgent</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1AgentManagerInterface.html</anchorfile>
      <anchor>a48bc7df5b86531f267b559a55eb67e63</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::agent::Agent &gt; agent)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::AgentStore</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1AgentStore.html</filename>
    <base>multiAgentExperience::library::core::transformer::AgentStoreInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::AgentStoreInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1AgentStoreInterface.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::agent::AgentTransferManager</name>
    <filename>classmultiAgentExperience_1_1library_1_1agent_1_1AgentTransferManager.html</filename>
    <member kind="function">
      <type>void</type>
      <name>invokeAgent</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1agent_1_1AgentTransferManager.html</anchorfile>
      <anchor>ad52542996a3dd41c2ad767a2d95520e1</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::agent::Agent &gt; agent)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::agent::AgentTransferManagerInterface</name>
    <filename>classmultiAgentExperience_1_1agent_1_1AgentTransferManagerInterface.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>invokeAgent</name>
      <anchorfile>classmultiAgentExperience_1_1agent_1_1AgentTransferManagerInterface.html</anchorfile>
      <anchor>ace07182311933280ad9aa77e30a5c3d4</anchor>
      <arglist>(const actor::ActorId &amp;agentId)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::agent::test::AgentTransferManagerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1agent_1_1test_1_1AgentTransferManagerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::AgentTransferManagerTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1AgentTransferManagerTransformer.html</filename>
    <base>multiAgentExperience::agent::AgentTransferManagerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>invokeAgent</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1AgentTransferManagerTransformer.html</anchorfile>
      <anchor>a16a01efd6176505c76e353888ccb2612</anchor>
      <arglist>(const actor::ActorId &amp;agentId) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::AgentTransferManagerTransformerFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1AgentTransferManagerTransformerFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::AgentTransferManagerTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1AgentTransferManagerTransformerTest.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::audio::AudioFormat</name>
    <filename>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>Encoding</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>afb183382a8960b7b0fe6dc4493618b1c</anchor>
      <arglist></arglist>
      <enumvalue file="structmultiAgentExperience_1_1audio_1_1AudioFormat.html" anchor="afb183382a8960b7b0fe6dc4493618b1cad4e44911dba62cfb025d1dd56fab93ad">LPCM</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Endianness</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>aa39f89bdc77f49956e577c3e1c022164</anchor>
      <arglist></arglist>
      <enumvalue file="structmultiAgentExperience_1_1audio_1_1AudioFormat.html" anchor="aa39f89bdc77f49956e577c3e1c022164a1314341b466dcb5e2c880b76414c49fe">LITTLE</enumvalue>
      <enumvalue file="structmultiAgentExperience_1_1audio_1_1AudioFormat.html" anchor="aa39f89bdc77f49956e577c3e1c022164aa60c6c694491d75b439073b8cb05b139">BIG</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>AudioFormat</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>a12e8c7399c651aa16618d4f688289825</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AudioFormat</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>a51a832f8736e76bc0a32aaca0d55859f</anchor>
      <arglist>(std::size_t sampleRateHz, std::size_t numChannels, std::size_t wordsPerSample, std::size_t wordSizeBits=CHAR_BIT, Encoding encoding=Encoding::LPCM, Endianness endianness=Endianness::LITTLE)</arglist>
    </member>
    <member kind="variable">
      <type>std::size_t</type>
      <name>sampleRateHz</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>a63ece32cfb7c600da28c396e84ccb755</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::size_t</type>
      <name>numChannels</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>a4865eb66cb54fc9ade1656ab2702f6f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::size_t</type>
      <name>wordsPerSample</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>ad863b42ce4b53d08f97b777f2144db93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::size_t</type>
      <name>wordSizeBits</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>ad76e6ba6af91cf293276b6e141c29e62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Encoding</type>
      <name>encoding</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>a23360f25d981dc72bac68957b2a4a51c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Endianness</type>
      <name>endianness</name>
      <anchorfile>structmultiAgentExperience_1_1audio_1_1AudioFormat.html</anchorfile>
      <anchor>a386787aa106ea30332bf437d56b7b129</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::audio::AudioReaderInterface</name>
    <filename>classmultiAgentExperience_1_1audio_1_1AudioReaderInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AudioReaderInterface</name>
      <anchorfile>classmultiAgentExperience_1_1audio_1_1AudioReaderInterface.html</anchorfile>
      <anchor>acc8a40284879d0bc939e48d004685f99</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual AudioFormat</type>
      <name>getAudioFormat</name>
      <anchorfile>classmultiAgentExperience_1_1audio_1_1AudioReaderInterface.html</anchorfile>
      <anchor>a918fea0f2b9a7ce3a107a09b0e708e89</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ssize_t</type>
      <name>read</name>
      <anchorfile>classmultiAgentExperience_1_1audio_1_1AudioReaderInterface.html</anchorfile>
      <anchor>a10489a74ee39862937a9a8cc49e04f50</anchor>
      <arglist>(void *buf, size_t nBytes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>seekToNow</name>
      <anchorfile>classmultiAgentExperience_1_1audio_1_1AudioReaderInterface.html</anchorfile>
      <anchor>a48d30432c9d447bfa906742aea759b8d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>close</name>
      <anchorfile>classmultiAgentExperience_1_1audio_1_1AudioReaderInterface.html</anchorfile>
      <anchor>a7c655d5c0686fd2355a1cd0d39c96e98</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::Channel</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</filename>
    <class kind="struct">multiAgentExperience::library::activity::Channel::State</class>
    <member kind="function">
      <type></type>
      <name>Channel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a6fff2d40b2d1cfe7f5c67728c6ce7ae6</anchor>
      <arglist>(const std::string &amp;name, const unsigned int priority, bool isVirtual=false)</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>getName</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a32da9acd11769bd4392459a1df0e1ebe</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getPriority</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>ad8fdd250311b40b72071be08900f280f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setFocus</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a713a3f7c9135b9485fd4548633737b3b</anchor>
      <arglist>(FocusState focus, MixingBehavior behavior, bool forceUpdate=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPrimaryActivity</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a98bfb90fb6461bb5f113bcfcf309d4e4</anchor>
      <arglist>(std::shared_ptr&lt; FocusManagerInterface::Activity &gt; activity)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>releaseActivity</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a4ea453cdd3d21583023ac2b9f7d22832</anchor>
      <arglist>(std::shared_ptr&lt; ChannelObserverInterface &gt; observer)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>releaseActivity</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a4eb43fc7129f976dffe2b27a691229ff</anchor>
      <arglist>(const std::string &amp;interfaceName)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isActive</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a5d5eed679969ef3083a05c353f3ee015</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>aa23be08eaee88bd4a060cf3adf7acb48</anchor>
      <arglist>(const Channel &amp;rhs) const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getInterface</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>af7f1d20a72a8525ba4fd4c71eafe2c89</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Channel::State</type>
      <name>getState</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a6edf8bf6671ed87401b5bf5b8c85a58f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Channel::State &gt;</type>
      <name>getActivityUpdates</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a548c706178cac25efd155865c0b38c2c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; FocusManagerInterface::Activity &gt;</type>
      <name>getPrimaryActivity</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>ac680888ecbdd1bb8d7e2811d43abe5a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; FocusManagerInterface::Activity &gt;</type>
      <name>getActivity</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>a7e2ae4b4fb09b88c4a45fe45953c5ed8</anchor>
      <arglist>(const std::string &amp;interfaceName)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>getInterfaceList</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1Channel.html</anchorfile>
      <anchor>af6cffcb5444d19e8a0ff7cdafe8a8453</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::FocusManager::ChannelConfiguration</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager_1_1ChannelConfiguration.html</filename>
    <member kind="function">
      <type></type>
      <name>ChannelConfiguration</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager_1_1ChannelConfiguration.html</anchorfile>
      <anchor>acd4397e483935014de0e08042c0820bf</anchor>
      <arglist>(const std::string &amp;configName, unsigned int configPriority)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>toString</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager_1_1ChannelConfiguration.html</anchorfile>
      <anchor>ad1bce4ce73065e222835318c4296a11e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>readChannelConfiguration</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager_1_1ChannelConfiguration.html</anchorfile>
      <anchor>a79b6928ddb69202fc1cea793881ddeb6</anchor>
      <arglist>(const std::string &amp;channelTypeKey, std::vector&lt; FocusManager::ChannelConfiguration &gt; *virtualChannelConfigurations)</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager_1_1ChannelConfiguration.html</anchorfile>
      <anchor>a18e13cb4aad41d39fe5cb3fbd3b06cad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>priority</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager_1_1ChannelConfiguration.html</anchorfile>
      <anchor>ae4f96e716bfb47b588951d28ca7d693d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::ChannelObserverInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1ChannelObserverInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ChannelObserverInterface</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1ChannelObserverInterface.html</anchorfile>
      <anchor>a9159dace1c668daeb9c48babcb90af50</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onFocusChanged</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1ChannelObserverInterface.html</anchorfile>
      <anchor>a8a3af6eeadcae73b5dd71756c8847d9c</anchor>
      <arglist>(FocusState newFocus, MixingBehavior behavior)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::ChannelToActivityObserver</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1ChannelToActivityObserver.html</filename>
    <base>multiAgentExperience::library::activity::ChannelObserverInterface</base>
    <member kind="function">
      <type>void</type>
      <name>onFocusChanged</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1ChannelToActivityObserver.html</anchorfile>
      <anchor>a37c62aee12d772371e7b0819af1eec93</anchor>
      <arglist>(FocusState newFocus, MixingBehavior behavior) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onFocusChanged</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1ChannelToActivityObserver.html</anchorfile>
      <anchor>a37c62aee12d772371e7b0819af1eec93</anchor>
      <arglist>(FocusState newFocus, MixingBehavior behavior) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::ChannelToActivityObserverTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1ChannelToActivityObserverTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::CombinedDialogStateHandlersLifecycle</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1CombinedDialogStateHandlersLifecycle.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>startListening</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1CombinedDialogStateHandlersLifecycle.html</anchorfile>
      <anchor>a8a574a56b724f1769efc2bed958a1db5</anchor>
      <arglist>(std::set&lt; multiAgentExperience::control::ControlType &gt; controls)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>startThinking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1CombinedDialogStateHandlersLifecycle.html</anchorfile>
      <anchor>ab45977e8c6f815fac2ccff68fb59bb52</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>startSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1CombinedDialogStateHandlersLifecycle.html</anchorfile>
      <anchor>a27711a4b4946b091d5368f62083295e2</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::control::ControlRegistryInterface &gt; controlRegistry)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stopCurrentDialogState</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1CombinedDialogStateHandlersLifecycle.html</anchorfile>
      <anchor>a3a117cecef3d3a6440a17cd40bb25de8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1CombinedDialogStateHandlersLifecycle.html</anchorfile>
      <anchor>ac991db03b86b75ec38f3334f81eb78c5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::CombinedDialogStateHandlersLifecycleFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1CombinedDialogStateHandlersLifecycleFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::CombinedDialogStateHandlersLifecycleTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1CombinedDialogStateHandlersLifecycleTest.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::library::control::CompareControlRecordsByPriority</name>
    <filename>structmultiAgentExperience_1_1library_1_1control_1_1CompareControlRecordsByPriority.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::control::Control</name>
    <filename>structmultiAgentExperience_1_1control_1_1Control.html</filename>
    <member kind="function">
      <type></type>
      <name>Control</name>
      <anchorfile>structmultiAgentExperience_1_1control_1_1Control.html</anchorfile>
      <anchor>a7f00f50306cb2b0f84a295ea190405e1</anchor>
      <arglist>(ControlType type, ControlTask task)</arglist>
    </member>
    <member kind="variable">
      <type>ControlId</type>
      <name>id</name>
      <anchorfile>structmultiAgentExperience_1_1control_1_1Control.html</anchorfile>
      <anchor>a04ad56e814ace203a2aafa0bead8bf05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ControlType</type>
      <name>type</name>
      <anchorfile>structmultiAgentExperience_1_1control_1_1Control.html</anchorfile>
      <anchor>afa63021ab2a44095381378d437317b8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ControlTask</type>
      <name>task</name>
      <anchorfile>structmultiAgentExperience_1_1control_1_1Control.html</anchorfile>
      <anchor>aa4a135b6af84de78761a0d5696c07fb4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::Control</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1Control.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::library::control::ControlAccessKeyFactory</name>
    <filename>structmultiAgentExperience_1_1library_1_1control_1_1ControlAccessKeyFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::ControlAccessKeys</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1ControlAccessKeys.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::ControlAccessKeysTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1ControlAccessKeysTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::ControlInvoker</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1ControlInvoker.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::ControlInvokerFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1ControlInvokerFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::control::ControlInvokerInterface</name>
    <filename>classmultiAgentExperience_1_1control_1_1ControlInvokerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ControlInvokerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlInvokerInterface.html</anchorfile>
      <anchor>acd401cc5500992f03f5b042b84013475</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>invokeControl</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlInvokerInterface.html</anchorfile>
      <anchor>ae8070f0962399f7aa63dfa6df353aef9</anchor>
      <arglist>(const multiAgentExperience::control::ControlType &amp;controlType)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::ControlInvokerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1ControlInvokerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ControlInvokerTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlInvokerTransformer.html</filename>
    <base>multiAgentExperience::control::ControlInvokerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>invokeControl</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlInvokerTransformer.html</anchorfile>
      <anchor>a7452eabcd07d58e8b8179b3fa110e081</anchor>
      <arglist>(const multiAgentExperience::control::ControlType &amp;controlType) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::ControlInvokerTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1ControlInvokerTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::control::ControlManagerInterface</name>
    <filename>classmultiAgentExperience_1_1control_1_1ControlManagerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ControlManagerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlManagerInterface.html</anchorfile>
      <anchor>a2cd5975deea34494669e7aef6c312749</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addObserver</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlManagerInterface.html</anchorfile>
      <anchor>a1eecd64ef0a532d53982db500c9c3e14</anchor>
      <arglist>(std::weak_ptr&lt; ControlObserverInterface &gt; observer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>clearObservers</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlManagerInterface.html</anchorfile>
      <anchor>ae41c530ae8b14004eca50a02e59f154a</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ControlManagerTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlManagerTransformer.html</filename>
    <base>multiAgentExperience::control::ControlManagerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>addObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlManagerTransformer.html</anchorfile>
      <anchor>ae8411949b927e79efe6f079bb87ff6c7</anchor>
      <arglist>(std::weak_ptr&lt; multiAgentExperience::control::ControlObserverInterface &gt; observer) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clearObservers</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlManagerTransformer.html</anchorfile>
      <anchor>af6c2b77fa1428fc9c332a567cfeff8f9</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::ControlManagerTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1ControlManagerTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::test::verifiers::ControlNameSetVerifier</name>
    <filename>classmultiAgentExperience_1_1library_1_1test_1_1verifiers_1_1ControlNameSetVerifier.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::control::ControlObserverInterface</name>
    <filename>classmultiAgentExperience_1_1control_1_1ControlObserverInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ControlObserverInterface</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlObserverInterface.html</anchorfile>
      <anchor>ab9ccb6e7ad8c151766b9d7e33e72fe18</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onControlChange</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlObserverInterface.html</anchorfile>
      <anchor>a49009255d7372ae81534417514050929</anchor>
      <arglist>(const std::set&lt; ControlType &gt; &amp;controls)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ControlObserverReferenceBrokenCallback</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlObserverReferenceBrokenCallback.html</filename>
    <base>WrappedWeakReferenceBrokenCallbackInterface&lt; ControlStoreObserverTransformer &gt;</base>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::library::control::ControlRecord</name>
    <filename>structmultiAgentExperience_1_1library_1_1control_1_1ControlRecord.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::ControlRegistry</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1ControlRegistry.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::ControlRegistryFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1ControlRegistryFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::control::ControlRegistryInterface</name>
    <filename>classmultiAgentExperience_1_1control_1_1ControlRegistryInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ControlRegistryInterface</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlRegistryInterface.html</anchorfile>
      <anchor>acf622ad537e2a42783abc67007b7f494</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update</name>
      <anchorfile>classmultiAgentExperience_1_1control_1_1ControlRegistryInterface.html</anchorfile>
      <anchor>ab3d1fd686336ba279d84ce7b1296e9b3</anchor>
      <arglist>(std::set&lt; std::shared_ptr&lt; Control &gt;&gt; controls)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ControlRegistryTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlRegistryTransformer.html</filename>
    <base>multiAgentExperience::control::ControlRegistryInterface</base>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlRegistryTransformer.html</anchorfile>
      <anchor>a22c4b682ea202d262bc352b179b530c7</anchor>
      <arglist>(std::set&lt; std::shared_ptr&lt; multiAgentExperience::control::Control &gt;&gt; controls) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlRegistryTransformer.html</anchorfile>
      <anchor>a22c4b682ea202d262bc352b179b530c7</anchor>
      <arglist>(std::set&lt; std::shared_ptr&lt; multiAgentExperience::control::Control &gt;&gt; controls) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::ControlStore</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1ControlStore.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::ControlStoreObserverInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1ControlStoreObserverInterface.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::ControlStoreObserverTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1ControlStoreObserverTransformer.html</filename>
    <base>multiAgentExperience::library::control::ControlStoreObserverInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::ControlStoreTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1ControlStoreTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::test::verifiers::ControlTypeSetVerifier</name>
    <filename>classmultiAgentExperience_1_1library_1_1test_1_1verifiers_1_1ControlTypeSetVerifier.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::CurrentActivities</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1CurrentActivities.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::CurrentActivityRequests</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1CurrentActivityRequests.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::CurrentControls</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1CurrentControls.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::utils::data::DataObserverInterface</name>
    <filename>classmultiAgentExperience_1_1utils_1_1data_1_1DataObserverInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DataObserverInterface</name>
      <anchorfile>classmultiAgentExperience_1_1utils_1_1data_1_1DataObserverInterface.html</anchorfile>
      <anchor>a79a583b3d8da339f6405f85bf16e865f</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::pair&lt; bool, std::size_t &gt;</type>
      <name>onData</name>
      <anchorfile>classmultiAgentExperience_1_1utils_1_1data_1_1DataObserverInterface.html</anchorfile>
      <anchor>ae3c6fd0357a9c5a855e73694e217faa7</anchor>
      <arglist>(const void *buffer, std::size_t numWords)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::utils::data::DataWriterInterface</name>
    <filename>classmultiAgentExperience_1_1utils_1_1data_1_1DataWriterInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DataWriterInterface</name>
      <anchorfile>classmultiAgentExperience_1_1utils_1_1data_1_1DataWriterInterface.html</anchorfile>
      <anchor>a7c2cb3c8488a6becb78936f165f8ceb8</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::pair&lt; bool, std::size_t &gt;</type>
      <name>write</name>
      <anchorfile>classmultiAgentExperience_1_1utils_1_1data_1_1DataWriterInterface.html</anchorfile>
      <anchor>a25fd7f704d9d8cc903ef89bd91af8e60</anchor>
      <arglist>(const void *buffer, std::size_t numWords)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addObserver</name>
      <anchorfile>classmultiAgentExperience_1_1utils_1_1data_1_1DataWriterInterface.html</anchorfile>
      <anchor>a9560ec91c573d7e565337c245b581e11</anchor>
      <arglist>(std::shared_ptr&lt; DataObserverInterface &gt; observer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>removeObserver</name>
      <anchorfile>classmultiAgentExperience_1_1utils_1_1data_1_1DataWriterInterface.html</anchorfile>
      <anchor>a53ef14b8a68f0289053f91fd9e32c2a5</anchor>
      <arglist>(std::shared_ptr&lt; DataObserverInterface &gt; observer)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::Dialog</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1Dialog.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogActivity</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogActivity.html</filename>
    <base>multiAgentExperience::library::activity::Activity</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogActivityRequest</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogActivityRequest.html</filename>
    <base>multiAgentExperience::library::activity::ActivityRequest</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::DialogManagerIntegrationTest::DialogAdapter</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1DialogManagerIntegrationTest_1_1DialogAdapter.html</filename>
    <base>multiAgentExperience::library::dialog::Dialog</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogArbitrator</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogArbitrator.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::DialogArbitratorTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1DialogArbitratorTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogController</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogController.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::DialogControllerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1DialogControllerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DialogControllerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogControllerInterface.html</anchorfile>
      <anchor>ac88f6d977162878ca8bb5f2bb36cd9b2</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startListening</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogControllerInterface.html</anchorfile>
      <anchor>aedf58ec76c3dd935f4f95458f2d77c8b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startThinking</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogControllerInterface.html</anchorfile>
      <anchor>a6674809cf6e9b196636cb607bc54ab54</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogControllerInterface.html</anchorfile>
      <anchor>a43b23b47b1aaa8db70b58a92b6dead74</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>invokeControlAndStartSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogControllerInterface.html</anchorfile>
      <anchor>a2d072558ed3d5e1dbd8435635203c4c9</anchor>
      <arglist>(const multiAgentExperience::control::ControlType &amp;controlType)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogControllerInterface.html</anchorfile>
      <anchor>a06d30404abf9ecc951d29f1cac1501bf</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stopAndInvokeControl</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogControllerInterface.html</anchorfile>
      <anchor>a425cdf82b61248401e6ea0deaddfd528</anchor>
      <arglist>(const multiAgentExperience::control::ControlType &amp;controlType)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogControllerTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</filename>
    <base>multiAgentExperience::dialog::DialogControllerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>startListening</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>a62cdb718d966874e9d9e48b1a5424d17</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startThinking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>a6300010943f92ca1af0eb49abb98bed7</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>ae588a1edde210954c9c9e0de173b5386</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invokeControlAndStartSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>a5e25ad49283384329dcaeb7f7e320b4c</anchor>
      <arglist>(const multiAgentExperience::control::ControlType &amp;controlType) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>affeb21c2b097ed62f16aa153397c2a6c</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stopAndInvokeControl</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>a2337f17fa964c28e2a7d271dd7947349</anchor>
      <arglist>(const multiAgentExperience::control::ControlType &amp;controlType) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startListening</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>a62cdb718d966874e9d9e48b1a5424d17</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startThinking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>a6300010943f92ca1af0eb49abb98bed7</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>ae588a1edde210954c9c9e0de173b5386</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invokeControlAndStartSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>a5e25ad49283384329dcaeb7f7e320b4c</anchor>
      <arglist>(const multiAgentExperience::control::ControlType &amp;controlType) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>affeb21c2b097ed62f16aa153397c2a6c</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stopAndInvokeControl</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformer.html</anchorfile>
      <anchor>a2337f17fa964c28e2a7d271dd7947349</anchor>
      <arglist>(const multiAgentExperience::control::ControlType &amp;controlType) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogControllerTransformerFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogControllerTransformerFactory.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::library::core::transformer::test::DialogControllerValue</name>
    <filename>structmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1DialogControllerValue.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::library::dialog::test::DialogControllerValue</name>
    <filename>structmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1DialogControllerValue.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::DialogControllerVerifier</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1DialogControllerVerifier.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogLifecycle</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogLifecycle.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogLifecycleFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogLifecycleFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::DialogLifecycleTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1DialogLifecycleTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogLifecycleTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogLifecycleTransformer.html</filename>
    <base>multiAgentExperience::library::dialog::Dialog</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::DialogLifecycleTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1DialogLifecycleTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogManager</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogManager.html</filename>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::library::dialog::DialogManagerFactory</name>
    <filename>structmultiAgentExperience_1_1library_1_1dialog_1_1DialogManagerFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::DialogManagerIntegrationTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1DialogManagerIntegrationTest.html</filename>
    <class kind="class">multiAgentExperience::library::dialog::test::DialogManagerIntegrationTest::DialogAdapter</class>
    <class kind="class">multiAgentExperience::library::dialog::test::DialogManagerIntegrationTest::InterruptibleDialog</class>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::DialogManagerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DialogManagerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>a7d8f869d11a7919f8495bc7e52756b04</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>request</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>aecce4cf8420a5580db890f4ecd23988b</anchor>
      <arglist>(std::shared_ptr&lt; DialogRequestInterface &gt; request)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>aeb274c3fcb2d6e65698094acdf5d5213</anchor>
      <arglist>(std::shared_ptr&lt; DialogRequestInterface &gt; request)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setAllHandlers</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>ab7045b2147fc3c85a868e001c5189891</anchor>
      <arglist>(std::shared_ptr&lt; ListeningHandlerInterface &gt; listeningHandler, std::shared_ptr&lt; ThinkingHandlerInterface &gt; thinkingHandler, std::shared_ptr&lt; SpeakingHandlerInterface &gt; speakingHandler)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>removeAllHandlers</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>a338e39df5b9b3fa874668498b0f965ee</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setListeningHandler</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>ae3ef31a688482189cfe614c0b72f937a</anchor>
      <arglist>(std::shared_ptr&lt; ListeningHandlerInterface &gt; handler)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>removeListeningHandler</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>acf263cf051f485400cf3ed671c12ecba</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setThinkingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>a3f15456f9150564eaaf20aaf6b2be767</anchor>
      <arglist>(std::shared_ptr&lt; ThinkingHandlerInterface &gt; handler)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>removeThinkingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>aab9c31041698cc06884f72e972a47fd9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setSpeakingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>aed1921ea11ebe29ac18d5e3a125d0e0f</anchor>
      <arglist>(std::shared_ptr&lt; SpeakingHandlerInterface &gt; handler)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>removeSpeakingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogManagerInterface.html</anchorfile>
      <anchor>a2d7133eff7f9e0e026ccef04f7c9f5c3</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogManagerTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</filename>
    <base>multiAgentExperience::dialog::DialogManagerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>request</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>ae0106c16586045c3bf6b11b3f3006cc2</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::DialogRequestInterface &gt; request) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>acb972af2b2b1095619fa7763747b4d9d</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::DialogRequestInterface &gt; request) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAllHandlers</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>ade99d8943864d28d145fe49297bf2a73</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::ListeningHandlerInterface &gt; listeningHandler, std::shared_ptr&lt; multiAgentExperience::dialog::ThinkingHandlerInterface &gt; thinkingHandler, std::shared_ptr&lt; multiAgentExperience::dialog::SpeakingHandlerInterface &gt; speakingHandler) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeAllHandlers</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>ab92f3e8199cfdd76ae82c434b4c02d2c</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setListeningHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>aeb1791d8e2e427865ec24164141d706c</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::ListeningHandlerInterface &gt; handler) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeListeningHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>acad5dcdd17153dbd9ac131491c6b5906</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setThinkingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>ad2ca4d0ddde312d5a113a940a7def5db</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::ThinkingHandlerInterface &gt; handler) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeThinkingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>a039c6be2c272978a727f991a4846ed61</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSpeakingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>a58969d1919f2a7baf1a79c8c2c28516c</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::SpeakingHandlerInterface &gt; handler) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeSpeakingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>a99fc486343fd7debcb9534fdbbed38b7</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>request</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>ae0106c16586045c3bf6b11b3f3006cc2</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::DialogRequestInterface &gt; request) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>acb972af2b2b1095619fa7763747b4d9d</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::DialogRequestInterface &gt; request) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAllHandlers</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>ade99d8943864d28d145fe49297bf2a73</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::ListeningHandlerInterface &gt; listeningHandler, std::shared_ptr&lt; multiAgentExperience::dialog::ThinkingHandlerInterface &gt; thinkingHandler, std::shared_ptr&lt; multiAgentExperience::dialog::SpeakingHandlerInterface &gt; speakingHandler) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeAllHandlers</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>ab92f3e8199cfdd76ae82c434b4c02d2c</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setListeningHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>aeb1791d8e2e427865ec24164141d706c</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::ListeningHandlerInterface &gt; handler) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeListeningHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>acad5dcdd17153dbd9ac131491c6b5906</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setThinkingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>ad2ca4d0ddde312d5a113a940a7def5db</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::ThinkingHandlerInterface &gt; handler) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeThinkingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>a039c6be2c272978a727f991a4846ed61</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSpeakingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>a58969d1919f2a7baf1a79c8c2c28516c</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::SpeakingHandlerInterface &gt; handler) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeSpeakingHandler</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer.html</anchorfile>
      <anchor>a99fc486343fd7debcb9534fdbbed38b7</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogManagerTransformerFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformerFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::DialogManagerTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1DialogManagerTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogRequest</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogRequest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::DialogRequestInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1DialogRequestInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~DialogRequestInterface</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogRequestInterface.html</anchorfile>
      <anchor>a0d18f65542ab863e8f1aa396ab2d4a47</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onDenied</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogRequestInterface.html</anchorfile>
      <anchor>aa01981c0568820b29b8d344a637b08ea</anchor>
      <arglist>(const std::string &amp;denialMessage)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onDialogStarted</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogRequestInterface.html</anchorfile>
      <anchor>ae0a4f072483e5e296be993c9789fba60</anchor>
      <arglist>(std::shared_ptr&lt; DialogControllerInterface &gt; controller)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onError</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogRequestInterface.html</anchorfile>
      <anchor>a695c733b1ae8c5b55ca16e54e219db89</anchor>
      <arglist>(const std::string &amp;errorMessage)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onDialogStopped</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1DialogRequestInterface.html</anchorfile>
      <anchor>ae8172eb24c42acb2f9ea6f16ff2db5e6</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogRequestLifecycle</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogRequestLifecycle.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogRequestLifecycle</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogRequestLifecycle.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>start</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogRequestLifecycle.html</anchorfile>
      <anchor>a4a8d772926b919b5580b92953cd0e061</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::DialogControllerInterface &gt; dialogController)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isStarted</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogRequestLifecycle.html</anchorfile>
      <anchor>a0e311e3e62677bbf7d1b57887e847969</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogRequestLifecycle.html</anchorfile>
      <anchor>a28819789192753073fc13a2dbb9f1fc1</anchor>
      <arglist>(const std::string &amp;errorMessage)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deny</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogRequestLifecycle.html</anchorfile>
      <anchor>aaad21521c1affcd78ca6123e048ca589</anchor>
      <arglist>(const std::string &amp;denialMessage)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>beforeStop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogRequestLifecycle.html</anchorfile>
      <anchor>af807eee4af164d74e0e01d702424a889</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogRequestLifecycle.html</anchorfile>
      <anchor>a5b4255b0d3603607db0f12af08c5705c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::DialogRequestLifecycleTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1DialogRequestLifecycleTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogRequestTransformer</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogRequestTransformer.html</filename>
    <base>multiAgentExperience::library::dialog::DialogRequest</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::DialogRequestTransformerTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1DialogRequestTransformerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogState</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogState.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::DialogStateFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1DialogStateFactory.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogStateHandlerLifecycle</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogStateHandlerLifecycle.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::DialogStateHandlerLifecycleTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1DialogStateHandlerLifecycleTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::DialogStateHandlerRegistry</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogStateHandlerRegistry.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::DialogStateHandlerRegistryTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1DialogStateHandlerRegistryTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::utils::threading::Executor</name>
    <filename>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1Executor.html</filename>
    <member kind="function">
      <type></type>
      <name>Executor</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1Executor.html</anchorfile>
      <anchor>ae63fa332a9fa2199890797592a9dcf28</anchor>
      <arglist>(bool async=true, const std::chrono::milliseconds &amp;delayExit=std::chrono::milliseconds(1000))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Executor</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1Executor.html</anchorfile>
      <anchor>a66d68fa4cc2ebc427c0c98e633d05a51</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>submit</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1Executor.html</anchorfile>
      <anchor>ac41c3f92210cb7b73b34a0fc212bf314</anchor>
      <arglist>(Task task, Args &amp;&amp;... args) -&gt; std::future&lt; decltype(task(args...))&gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>submitToFront</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1Executor.html</anchorfile>
      <anchor>a2c61a5f8933bfec6ea4d1c47b0bb3de4</anchor>
      <arglist>(Task task, Args &amp;&amp;... args) -&gt; std::future&lt; decltype(task(args...))&gt;</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>waitForSubmittedTasks</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1Executor.html</anchorfile>
      <anchor>ab18af745f4a7ffea85d4cdc78d19e131</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shutdown</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1Executor.html</anchorfile>
      <anchor>ada9452b4832e8cc90a4daff3baff4b6b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isShutdown</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1Executor.html</anchorfile>
      <anchor>adab487d54db1ee5cdbc7ca2cd1a139fa</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::experience::Experience</name>
    <filename>structmultiAgentExperience_1_1experience_1_1Experience.html</filename>
    <member kind="variable">
      <type>actor::ActorId</type>
      <name>actorId</name>
      <anchorfile>structmultiAgentExperience_1_1experience_1_1Experience.html</anchorfile>
      <anchor>a52f813a26828d064955d021ba3d955e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SessionId</type>
      <name>sessionId</name>
      <anchorfile>structmultiAgentExperience_1_1experience_1_1Experience.html</anchorfile>
      <anchor>a7c7ad399ccf03752c0b2899e61848b72</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ExperienceId</type>
      <name>experienceId</name>
      <anchorfile>structmultiAgentExperience_1_1experience_1_1Experience.html</anchorfile>
      <anchor>ad60323b67b00519b10cb8225d878a898</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::experience::ExperienceController</name>
    <filename>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceController.html</filename>
    <base>multiAgentExperience::experience::ExperienceControllerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>startExperience</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceController.html</anchorfile>
      <anchor>a22f81d8c6cf79fa5198f8ca4985cc712</anchor>
      <arglist>(const multiAgentExperience::experience::ExperienceId &amp;experience) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>endExperience</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceController.html</anchorfile>
      <anchor>add3884a867866542e19ce30e2992766b</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invalidate</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceController.html</anchorfile>
      <anchor>a1548d8b90e626515e8c6abe721b2a1e4</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>startExperience</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceController.html</anchorfile>
      <anchor>a22f81d8c6cf79fa5198f8ca4985cc712</anchor>
      <arglist>(const multiAgentExperience::experience::ExperienceId &amp;experience) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>endExperience</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceController.html</anchorfile>
      <anchor>add3884a867866542e19ce30e2992766b</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invalidate</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceController.html</anchorfile>
      <anchor>a1548d8b90e626515e8c6abe721b2a1e4</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::experience::ExperienceControllerInterface</name>
    <filename>classmultiAgentExperience_1_1experience_1_1ExperienceControllerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ExperienceControllerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceControllerInterface.html</anchorfile>
      <anchor>a4ed5df22fc53566a711e9999a9e56755</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>startExperience</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceControllerInterface.html</anchorfile>
      <anchor>aa6f9fc978cbc4ce2f155bb056969449d</anchor>
      <arglist>(const ExperienceId &amp;experience)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>endExperience</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceControllerInterface.html</anchorfile>
      <anchor>a48508c4fe8bafb8b014906119fa4e8f2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>invalidate</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceControllerInterface.html</anchorfile>
      <anchor>ac4ac6acda6a5dbeeb921f92876512be3</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::experience::ExperienceManager</name>
    <filename>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceManager.html</filename>
    <base>multiAgentExperience::experience::ExperienceManagerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>addObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceManager.html</anchorfile>
      <anchor>a79e1702ae84014ce72e428cba8a9f169</anchor>
      <arglist>(std::weak_ptr&lt; multiAgentExperience::experience::ExperienceObserverInterface &gt; observer) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clearObservers</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceManager.html</anchorfile>
      <anchor>a0beefbd27d5132473b0e6b06de8bd37b</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceManager.html</anchorfile>
      <anchor>a79e1702ae84014ce72e428cba8a9f169</anchor>
      <arglist>(std::weak_ptr&lt; multiAgentExperience::experience::ExperienceObserverInterface &gt; observer) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clearObservers</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1experience_1_1ExperienceManager.html</anchorfile>
      <anchor>a0beefbd27d5132473b0e6b06de8bd37b</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::experience::ExperienceManagerInterface</name>
    <filename>classmultiAgentExperience_1_1experience_1_1ExperienceManagerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ExperienceManagerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceManagerInterface.html</anchorfile>
      <anchor>af22b5e4f43efd2c1641191f2858a463f</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addObserver</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceManagerInterface.html</anchorfile>
      <anchor>a91511d0763219024ffd6d07befbb5b71</anchor>
      <arglist>(std::weak_ptr&lt; ExperienceObserverInterface &gt; observer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>clearObservers</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceManagerInterface.html</anchorfile>
      <anchor>a71bc0541b6f129351f1e92dbe7bc7cc2</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::experience::test::ExperienceManagerTest</name>
    <filename>classmultiAgentExperience_1_1experience_1_1test_1_1ExperienceManagerTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::experience::ExperienceObserverInterface</name>
    <filename>classmultiAgentExperience_1_1experience_1_1ExperienceObserverInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ExperienceObserverInterface</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceObserverInterface.html</anchorfile>
      <anchor>a4008521016a20fc830bec25d694cd13f</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onExperienceChange</name>
      <anchorfile>classmultiAgentExperience_1_1experience_1_1ExperienceObserverInterface.html</anchorfile>
      <anchor>a99a127f48d19a338cb88cecf330200ec</anchor>
      <arglist>(const std::vector&lt; Experience &gt; &amp;experiences)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::utils::error::FinallyGuard</name>
    <filename>classmultiAgentExperience_1_1library_1_1utils_1_1error_1_1FinallyGuard.html</filename>
    <member kind="function">
      <type></type>
      <name>FinallyGuard</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1error_1_1FinallyGuard.html</anchorfile>
      <anchor>a3d318e53d8a065e18e7cd715ee7456a9</anchor>
      <arglist>(const std::function&lt; void()&gt; &amp;finallyFunction)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FinallyGuard</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1error_1_1FinallyGuard.html</anchorfile>
      <anchor>a8b93c2960eab2af3c7c29a37a1932e3b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::FocusManager</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</filename>
    <base>multiAgentExperience::library::activity::FocusManagerInterface</base>
    <class kind="class">multiAgentExperience::library::activity::FocusManager::ChannelConfiguration</class>
    <member kind="function">
      <type></type>
      <name>FocusManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>ab3d5caff69c8cbd6c3cc916753c229c3</anchor>
      <arglist>(const std::vector&lt; ChannelConfiguration &gt; &amp;channelConfigurations, std::shared_ptr&lt; multiAgentExperience::library::utils::threading::Executor &gt; executor=std::make_shared&lt; multiAgentExperience::library::utils::threading::Executor &gt;(), std::shared_ptr&lt; ActivityTrackerInterface &gt; activityTrackerInterface=nullptr, const std::vector&lt; ChannelConfiguration &gt; &amp;virtualChannelConfigurations=std::vector&lt; ChannelConfiguration &gt;(), std::shared_ptr&lt; InterruptModel &gt; interruptModel=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acquireChannel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>ab7993d1288712d7e23fd277de593765a</anchor>
      <arglist>(const std::string &amp;channelName, std::shared_ptr&lt; ChannelObserverInterface &gt; channelObserver, const std::string &amp;interfaceName) override</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>acquireChannel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>a7db083bf9d1878ce6a0a7d5b22379c3a</anchor>
      <arglist>(const std::string &amp;channelName, std::shared_ptr&lt; FocusManagerInterface::Activity &gt; channelActivity) override</arglist>
    </member>
    <member kind="function">
      <type>std::future&lt; bool &gt;</type>
      <name>releaseChannel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>a39f9f96e4df399c733072c4bc94df461</anchor>
      <arglist>(const std::string &amp;channelName, std::shared_ptr&lt; ChannelObserverInterface &gt; channelObserver) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stopForegroundActivity</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>aad5f838afe5fa6d8def5a0ab67af3ea4</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stopAllActivities</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>ab0bddd97aa06ff1a14278a1c642ec546</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>acfed58847fed26dd1c3127c84f69e15b</anchor>
      <arglist>(const std::shared_ptr&lt; FocusManagerObserverInterface &gt; &amp;observer) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>ab00f0393a3e544841fa6eb25998f886a</anchor>
      <arglist>(const std::shared_ptr&lt; FocusManagerObserverInterface &gt; &amp;observer) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>modifyContentType</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>afd8b894dc3caebc21c0ce63f2f5a891c</anchor>
      <arglist>(const std::string &amp;channelName, const std::string &amp;interfaceName, ContentType contentType) override</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const std::vector&lt; FocusManager::ChannelConfiguration &gt;</type>
      <name>getDefaultAudioChannels</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>a8ed3296988b8da92d7947544ed324582</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const std::vector&lt; FocusManager::ChannelConfiguration &gt;</type>
      <name>getDefaultVisualChannels</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManager.html</anchorfile>
      <anchor>a6800b2aaac0065d8a98049658f123f99</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::FocusManagerActivityChannels</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerActivityChannels.html</filename>
    <base>multiAgentExperience::library::activity::ActivityChannels</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::FocusManagerActivityChannelsTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1FocusManagerActivityChannelsTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::FocusManagerInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</filename>
    <class kind="class">multiAgentExperience::library::activity::FocusManagerInterface::Activity</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FocusManagerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a501f1ced273966359ab07e8d54adf1e6</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>acquireChannel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>ae313e8edeeb2301a93509aea84ea06f4</anchor>
      <arglist>(const std::string &amp;channelName, std::shared_ptr&lt; ChannelObserverInterface &gt; channelObserver, const std::string &amp;interfaceName)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>acquireChannel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>aaa59dc1dd0b5e82f85957b42acdb9129</anchor>
      <arglist>(const std::string &amp;channelName, std::shared_ptr&lt; FocusManagerInterface::Activity &gt; channelActivity)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::future&lt; bool &gt;</type>
      <name>releaseChannel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>aafa1dd4d3b76de02bce12ed91884b89e</anchor>
      <arglist>(const std::string &amp;channelName, std::shared_ptr&lt; ChannelObserverInterface &gt; channelObserver)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stopForegroundActivity</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a0c26d5d5e12f5f5632396c39aab5c857</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stopAllActivities</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>aefbd75c9c8246eb44cd39a2f41af65f7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a7a94ace92453137b6b0011593d81b2f8</anchor>
      <arglist>(const std::shared_ptr&lt; FocusManagerObserverInterface &gt; &amp;observer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>removeObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a2e46f6a06db3b7884d0e2fc87db2c501</anchor>
      <arglist>(const std::shared_ptr&lt; FocusManagerObserverInterface &gt; &amp;observer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>modifyContentType</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a07c743dbc740a2ffbfa4e4b3fc4023c7</anchor>
      <arglist>(const std::string &amp;channelName, const std::string &amp;interfaceName, ContentType contentType)=0</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr const char *</type>
      <name>DIALOG_CHANNEL_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>ab45f247fec0c54815977254f094eef2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr unsigned int</type>
      <name>DIALOG_CHANNEL_PRIORITY</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>aa65c4dd2f6abf2facdd5292fdbf3fc0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr const char *</type>
      <name>COMMUNICATIONS_CHANNEL_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a7293a656ea4935d1a6674f2a8b4b4c14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr unsigned int</type>
      <name>COMMUNICATIONS_CHANNEL_PRIORITY</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>afa1f317153a74b738d6d415146cc1345</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr const char *</type>
      <name>ALERT_CHANNEL_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a01672d7d95a0177bf81b4cd940d24633</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr unsigned int</type>
      <name>ALERT_CHANNEL_PRIORITY</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>ab599647ab742edbc62d8577a5cc5503e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr const char *</type>
      <name>CONTENT_CHANNEL_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a1b13ae64a091baa3b9b8faa7069417f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr unsigned int</type>
      <name>CONTENT_CHANNEL_PRIORITY</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a4b188e70b7e8ef2922b2529361d03940</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr const char *</type>
      <name>VISUAL_CHANNEL_NAME</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>a2dbe2b19ff5ce4836ce21b2b2088f38b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr unsigned int</type>
      <name>VISUAL_CHANNEL_PRIORITY</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerInterface.html</anchorfile>
      <anchor>ac51d4cea8e6f2cc9fd03068038199d25</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::FocusManagerObserverInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerObserverInterface.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onFocusChanged</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1FocusManagerObserverInterface.html</anchorfile>
      <anchor>a5c32d64e22a376560c50af51b2926484</anchor>
      <arglist>(const std::string &amp;channelName, FocusState newFocus)=0</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; multiAgentExperience::library::activity::ActivityRequest &gt;</name>
    <filename>structstd_1_1hash_3_01multiAgentExperience_1_1library_1_1activity_1_1ActivityRequest_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; multiAgentExperience::library::control::Control &gt;</name>
    <filename>structstd_1_1hash_3_01multiAgentExperience_1_1library_1_1control_1_1Control_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; multiAgentExperience::library::control::ControlName &gt;</name>
    <filename>structstd_1_1hash_3_01multiAgentExperience_1_1library_1_1control_1_1ControlName_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; multiAgentExperience::library::core::transformer::DialogLifecycleTransformer &gt;</name>
    <filename>structstd_1_1hash_3_01multiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogLifecycleTransformer_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; multiAgentExperience::library::core::transformer::DialogManagerTransformer &gt;</name>
    <filename>structstd_1_1hash_3_01multiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogManagerTransformer_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; multiAgentExperience::library::core::transformer::DialogState &gt;</name>
    <filename>structstd_1_1hash_3_01multiAgentExperience_1_1library_1_1core_1_1transformer_1_1DialogState_01_4.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::DialogManagerIntegrationTest::InterruptibleDialog</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1DialogManagerIntegrationTest_1_1InterruptibleDialog.html</filename>
    <base>multiAgentExperience::library::dialog::test::DialogManagerIntegrationTest::DialogAdapter</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::InterruptModel</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1InterruptModel.html</filename>
    <member kind="function">
      <type>MixingBehavior</type>
      <name>getMixingBehavior</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1InterruptModel.html</anchorfile>
      <anchor>afd8c92d1a0e64f6f54a9ec210c12e2ed</anchor>
      <arglist>(const std::string &amp;lowPriorityChannel, ContentType lowPriorityContentType, const std::string &amp;highPriorityChannel, ContentType highPriorityContentType) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; InterruptModel &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1InterruptModel.html</anchorfile>
      <anchor>a672c82dd4d94f88492e6a3e874b67c2c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::ListeningHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1ListeningHandlerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ListeningHandlerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1ListeningHandlerInterface.html</anchorfile>
      <anchor>aec3fe69fd7b54e9db9898b1cf9280480</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onStartListening</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1ListeningHandlerInterface.html</anchorfile>
      <anchor>aa4dd6722b9704b3a1db4b6d1da525520</anchor>
      <arglist>(std::shared_ptr&lt; DialogControllerInterface &gt; controller, std::set&lt; multiAgentExperience::control::ControlType &gt; controls)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onStopListening</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1ListeningHandlerInterface.html</anchorfile>
      <anchor>aac019fe744622710cab536a8e9b21380</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::utils::Log</name>
    <filename>classmultiAgentExperience_1_1utils_1_1Log.html</filename>
    <class kind="struct">multiAgentExperience::utils::Log::LogEntryMetadata</class>
    <member kind="enumeration">
      <type></type>
      <name>Level</name>
      <anchorfile>classmultiAgentExperience_1_1utils_1_1Log.html</anchorfile>
      <anchor>a1d261502cd7cf4420f79199fb6816522</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::utils::Log::LogEntryMetadata</name>
    <filename>structmultiAgentExperience_1_1utils_1_1Log_1_1LogEntryMetadata.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::utils::logger::Logger</name>
    <filename>classmultiAgentExperience_1_1library_1_1utils_1_1logger_1_1Logger.html</filename>
    <base>multiAgentExperience::utils::Log</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::LoggingActivityTracker</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1LoggingActivityTracker.html</filename>
    <base>multiAgentExperience::library::activity::ActivityTrackerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>notifyOfActivityUpdates</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1LoggingActivityTracker.html</anchorfile>
      <anchor>aebc2a533e045da2b789e348877cf0ce4</anchor>
      <arglist>(const std::vector&lt; Channel::State &gt; &amp;channelStates) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>notifyOfActivityUpdates</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1activity_1_1LoggingActivityTracker.html</anchorfile>
      <anchor>aebc2a533e045da2b789e348877cf0ce4</anchor>
      <arglist>(const std::vector&lt; Channel::State &gt; &amp;channelStates) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::application::MAX</name>
    <filename>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</filename>
    <base>multiAgentExperience::application::MAXInterface</base>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::agent::AgentManagerInterface &gt;</type>
      <name>getAgentManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>acce43dfcbf700a392c10caad45794711</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::experience::ExperienceManagerInterface &gt;</type>
      <name>getExperienceManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a04e5ef03f4f849b848cf4f72dcd67db3</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::application::WakeWordObserverInterface &gt;</type>
      <name>getWakewordObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a2481ff0a25fcb79673ccf3411f4ba435</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::activity::ActivityManagerInterface &gt;</type>
      <name>getActivityManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>ab858da2cb4503ada1171148f034a35ab</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::control::ControlManagerInterface &gt;</type>
      <name>getControlManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a58381be7fe487a8dd96fa37f432e6e7d</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::control::ControlInvokerInterface &gt;</type>
      <name>getControlInvoker</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>abeb4ed89d48744fbc8b1174da95a4990</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLogLevel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a5b591e20fc3176eea49e53824ca9663c</anchor>
      <arglist>(multiAgentExperience::utils::Log::Level level) override</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; MAX &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a645c59f5f109b58c881e461000151362</anchor>
      <arglist>(const actor::ActorId integratorActorId)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::agent::AgentManagerInterface &gt;</type>
      <name>getAgentManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>acce43dfcbf700a392c10caad45794711</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::experience::ExperienceManagerInterface &gt;</type>
      <name>getExperienceManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a04e5ef03f4f849b848cf4f72dcd67db3</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::application::WakeWordObserverInterface &gt;</type>
      <name>getWakewordObserver</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a2481ff0a25fcb79673ccf3411f4ba435</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::activity::ActivityManagerInterface &gt;</type>
      <name>getActivityManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>ab858da2cb4503ada1171148f034a35ab</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::control::ControlManagerInterface &gt;</type>
      <name>getControlManager</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a58381be7fe487a8dd96fa37f432e6e7d</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; multiAgentExperience::control::ControlInvokerInterface &gt;</type>
      <name>getControlInvoker</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>abeb4ed89d48744fbc8b1174da95a4990</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLogLevel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1application_1_1MAX.html</anchorfile>
      <anchor>a5b591e20fc3176eea49e53824ca9663c</anchor>
      <arglist>(multiAgentExperience::utils::Log::Level level) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::application::MAXFactory</name>
    <filename>classmultiAgentExperience_1_1application_1_1MAXFactory.html</filename>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; multiAgentExperience::application::MAXInterface &gt;</type>
      <name>create</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXFactory.html</anchorfile>
      <anchor>a21f330b56c04bf7ae893d905bfc24eec</anchor>
      <arglist>(const actor::ActorId integratorActorId=DEFAULT_INTEGRATOR_ACTOR_ID, std::shared_ptr&lt; multiAgentExperience::utils::Log &gt; logger=nullptr, const std::string &amp;logComponentName=&quot;MAX_LIB&quot;)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const actor::ActorId</type>
      <name>DEFAULT_INTEGRATOR_ACTOR_ID</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXFactory.html</anchorfile>
      <anchor>a0b5d8d0f0fe9a7c03700aff94465b547</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::application::MAXInterface</name>
    <filename>classmultiAgentExperience_1_1application_1_1MAXInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MAXInterface</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXInterface.html</anchorfile>
      <anchor>a7a66cb6a94854ca45bcaae3d3a386159</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::shared_ptr&lt; multiAgentExperience::agent::AgentManagerInterface &gt;</type>
      <name>getAgentManager</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXInterface.html</anchorfile>
      <anchor>aa2ed32de592d6e08aed08f528e16f384</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::shared_ptr&lt; multiAgentExperience::application::WakeWordObserverInterface &gt;</type>
      <name>getWakewordObserver</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXInterface.html</anchorfile>
      <anchor>a1e4dc24f4fd12d7c5defee5026766c17</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::shared_ptr&lt; multiAgentExperience::experience::ExperienceManagerInterface &gt;</type>
      <name>getExperienceManager</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXInterface.html</anchorfile>
      <anchor>a6d8c9149052df815f843e097be380431</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::shared_ptr&lt; multiAgentExperience::activity::ActivityManagerInterface &gt;</type>
      <name>getActivityManager</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXInterface.html</anchorfile>
      <anchor>a6e3889b1e8b3b86f910996326741c5d1</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::shared_ptr&lt; multiAgentExperience::control::ControlManagerInterface &gt;</type>
      <name>getControlManager</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXInterface.html</anchorfile>
      <anchor>a425f00e093dadc77ab3a705fbdfe6217</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::shared_ptr&lt; multiAgentExperience::control::ControlInvokerInterface &gt;</type>
      <name>getControlInvoker</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXInterface.html</anchorfile>
      <anchor>ac54a9cf1c4d098ace66e21a5cb04634c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setLogLevel</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1MAXInterface.html</anchorfile>
      <anchor>ac7e73b36908a876661d22e69fe9b4d74</anchor>
      <arglist>(multiAgentExperience::utils::Log::Level level)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::MockActivity</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1MockActivity.html</filename>
    <base>multiAgentExperience::library::activity::Activity</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::MockActivityChannels</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1MockActivityChannels.html</filename>
    <base>multiAgentExperience::library::activity::ActivityChannels</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::activity::test::MockActivityControllerInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1activity_1_1test_1_1MockActivityControllerInterface.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::MockActivityHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1MockActivityHandlerInterface.html</filename>
    <base>multiAgentExperience::activity::ActivityHandlerInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::MockActivityRequest</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1MockActivityRequest.html</filename>
    <base>multiAgentExperience::library::activity::ActivityRequest</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::MockAgentStoreInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1MockAgentStoreInterface.html</filename>
    <base>multiAgentExperience::library::core::transformer::AgentStoreInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::MockCombinedDialogStateHandlersLifecycleFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1MockCombinedDialogStateHandlersLifecycleFactory.html</filename>
    <base>multiAgentExperience::library::core::transformer::CombinedDialogStateHandlersLifecycleFactory</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::MockControlInvoker</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1MockControlInvoker.html</filename>
    <base>multiAgentExperience::library::control::ControlInvoker</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::MockControlInvokerFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1MockControlInvokerFactory.html</filename>
    <base>multiAgentExperience::library::control::ControlInvokerFactory</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::MockControlObserverInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1MockControlObserverInterface.html</filename>
    <base>multiAgentExperience::control::ControlObserverInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::MockControlRegistry</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1MockControlRegistry.html</filename>
    <base>multiAgentExperience::library::control::ControlRegistry</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::MockControlRegistryFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1MockControlRegistryFactory.html</filename>
    <base>multiAgentExperience::library::control::ControlRegistryFactory</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::control::test::MockControlRegistryInterface</name>
    <filename>classmultiAgentExperience_1_1control_1_1test_1_1MockControlRegistryInterface.html</filename>
    <base>multiAgentExperience::control::ControlRegistryInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::MockControlStore</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1MockControlStore.html</filename>
    <base>multiAgentExperience::library::control::ControlStore</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::MockControlStoreObserver</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1MockControlStoreObserver.html</filename>
    <base>multiAgentExperience::library::control::ControlStoreObserverInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::MockCurrentActivityRequests</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1MockCurrentActivityRequests.html</filename>
    <base>multiAgentExperience::library::activity::CurrentActivityRequests</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::control::test::MockCurrentControls</name>
    <filename>classmultiAgentExperience_1_1library_1_1control_1_1test_1_1MockCurrentControls.html</filename>
    <base>multiAgentExperience::library::control::CurrentControls</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::MockDialog</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1MockDialog.html</filename>
    <base>multiAgentExperience::library::dialog::Dialog</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::test::MockDialogControllerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1test_1_1MockDialogControllerInterface.html</filename>
    <base>multiAgentExperience::dialog::DialogControllerInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::MockDialogControllerTransformerFactory</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1MockDialogControllerTransformerFactory.html</filename>
    <base>multiAgentExperience::library::core::transformer::DialogControllerTransformerFactory</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::MockDialogLifecycle</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1MockDialogLifecycle.html</filename>
    <base>multiAgentExperience::library::dialog::DialogLifecycle</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::MockDialogRequest</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1MockDialogRequest.html</filename>
    <base>multiAgentExperience::library::dialog::DialogRequest</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::test::MockDialogRequestInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1test_1_1MockDialogRequestInterface.html</filename>
    <base>multiAgentExperience::dialog::DialogRequestInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::experience::test::MockExperienceControlInterface</name>
    <filename>classmultiAgentExperience_1_1experience_1_1test_1_1MockExperienceControlInterface.html</filename>
    <base>multiAgentExperience::experience::ExperienceControllerInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::experience::test::MockExperienceManager</name>
    <filename>classmultiAgentExperience_1_1experience_1_1test_1_1MockExperienceManager.html</filename>
    <base>multiAgentExperience::library::experience::ExperienceManager</base>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::experience::test::MockExperienceObserver</name>
    <filename>structmultiAgentExperience_1_1experience_1_1test_1_1MockExperienceObserver.html</filename>
    <base>multiAgentExperience::experience::ExperienceObserverInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::MockInternalDialogController</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1MockInternalDialogController.html</filename>
    <base>multiAgentExperience::library::dialog::DialogController</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::test::MockListeningHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1test_1_1MockListeningHandlerInterface.html</filename>
    <base>multiAgentExperience::dialog::ListeningHandlerInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::test::MockSpeakingHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1test_1_1MockSpeakingHandlerInterface.html</filename>
    <base>multiAgentExperience::dialog::SpeakingHandlerInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::test::MockThinkingHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1test_1_1MockThinkingHandlerInterface.html</filename>
    <base>multiAgentExperience::dialog::ThinkingHandlerInterface</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::OtherStateVerifier</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1OtherStateVerifier.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::SpeakingHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1SpeakingHandlerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SpeakingHandlerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1SpeakingHandlerInterface.html</anchorfile>
      <anchor>a13bff1fe2b78a687c16b7772ed664053</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onStartSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1SpeakingHandlerInterface.html</anchorfile>
      <anchor>ab000526182fb3947987fbbba10c1ca92</anchor>
      <arglist>(std::shared_ptr&lt; DialogControllerInterface &gt; controller, std::shared_ptr&lt; multiAgentExperience::experience::ExperienceControllerInterface &gt; experienceController, std::shared_ptr&lt; multiAgentExperience::control::ControlRegistryInterface &gt; controlRegistry)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onStopSpeaking</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1SpeakingHandlerInterface.html</anchorfile>
      <anchor>ad2cb6ce06411996a27e03dceaaa58388</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiAgentExperience::library::activity::Channel::State</name>
    <filename>structmultiAgentExperience_1_1library_1_1activity_1_1Channel_1_1State.html</filename>
    <member kind="function">
      <type></type>
      <name>State</name>
      <anchorfile>structmultiAgentExperience_1_1library_1_1activity_1_1Channel_1_1State.html</anchorfile>
      <anchor>afa27ecb2689d1f8ca92a69991ab6beab</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>State</name>
      <anchorfile>structmultiAgentExperience_1_1library_1_1activity_1_1Channel_1_1State.html</anchorfile>
      <anchor>ac457dd8b7e03ac1603937524bfa1d752</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>FocusState</type>
      <name>focusState</name>
      <anchorfile>structmultiAgentExperience_1_1library_1_1activity_1_1Channel_1_1State.html</anchorfile>
      <anchor>abe697eaad46ea50ed741cef14597f6b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>interfaceName</name>
      <anchorfile>structmultiAgentExperience_1_1library_1_1activity_1_1Channel_1_1State.html</anchorfile>
      <anchor>a0df217a8c5245d33736829519b67dbee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::chrono::steady_clock::time_point</type>
      <name>timeAtIdle</name>
      <anchorfile>structmultiAgentExperience_1_1library_1_1activity_1_1Channel_1_1State.html</anchorfile>
      <anchor>a985833d3941cec58150ce875ba63656d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::activity::test::StoresSomeControlsActivity</name>
    <filename>classmultiAgentExperience_1_1library_1_1activity_1_1test_1_1StoresSomeControlsActivity.html</filename>
    <base>multiAgentExperience::library::activity::Activity</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::utils::StrongTypeWrapper</name>
    <filename>classmultiAgentExperience_1_1utils_1_1StrongTypeWrapper.html</filename>
    <templarg>T</templarg>
    <templarg>Tag</templarg>
  </compound>
  <compound kind="class">
    <name>StrongTypeWrapper&lt; std::string, struct ActorIdTag &gt;</name>
    <filename>classmultiAgentExperience_1_1utils_1_1StrongTypeWrapper.html</filename>
  </compound>
  <compound kind="class">
    <name>StrongTypeWrapper&lt; std::string, struct ExperienceIdTag &gt;</name>
    <filename>classmultiAgentExperience_1_1utils_1_1StrongTypeWrapper.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::utils::threading::TaskThread</name>
    <filename>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1TaskThread.html</filename>
    <member kind="function">
      <type></type>
      <name>TaskThread</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1TaskThread.html</anchorfile>
      <anchor>aa100abd88e0df1f616132a22195c8f18</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TaskThread</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1TaskThread.html</anchorfile>
      <anchor>a9f3ab51d50dadd5e911ab7369398e7f5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>start</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1TaskThread.html</anchorfile>
      <anchor>a1e65d7936ced672a3ceb50da7c5631ea</anchor>
      <arglist>(std::function&lt; bool()&gt; jobRunner)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::test::TestActivityHandler</name>
    <filename>classmultiAgentExperience_1_1library_1_1test_1_1TestActivityHandler.html</filename>
    <base>multiAgentExperience::activity::ActivityHandlerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>onDenied</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestActivityHandler.html</anchorfile>
      <anchor>a13c3bf42105d0df0b3c083219fbe843f</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onReady</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestActivityHandler.html</anchorfile>
      <anchor>aab7b8bf14135b1296e1e96c48d497d24</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::activity::ActivityControllerInterface &gt; activityController, multiAgentExperience::activity::ActivityFocus focus, std::shared_ptr&lt; control::ControlRegistryInterface &gt; controlRegistry, std::shared_ptr&lt; experience::ExperienceControllerInterface &gt; experienceControl) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onFocusStateChange</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestActivityHandler.html</anchorfile>
      <anchor>ab3eaf8417510886fe1dedec4b80f21d6</anchor>
      <arglist>(multiAgentExperience::activity::ActivityFocus focus) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onStop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestActivityHandler.html</anchorfile>
      <anchor>a9d5e1250a1e6c14116d00a1cfafece5d</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::dialog::test::TestActivityRequest</name>
    <filename>classmultiAgentExperience_1_1library_1_1dialog_1_1test_1_1TestActivityRequest.html</filename>
    <base>multiAgentExperience::library::activity::ActivityRequest</base>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::test::TestAgent</name>
    <filename>classmultiAgentExperience_1_1library_1_1test_1_1TestAgent.html</filename>
    <base>multiAgentExperience::agent::Agent</base>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handleOnWakeWordDetected</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestAgent.html</anchorfile>
      <anchor>a5a4c7b6deb9f7698646abf6639cdd6c9</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handleOnTapDetected</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestAgent.html</anchorfile>
      <anchor>a87af1f979e0c88344a31e186f0bc3292</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handleOnAgentTransfer</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestAgent.html</anchorfile>
      <anchor>acb773693e82ed258a2b8f091fcfae06b</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>onInitialized</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestAgent.html</anchorfile>
      <anchor>aedf0bcc2c357948135b5dc1c42f00dd1</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::test::TestControlWrapper</name>
    <filename>classmultiAgentExperience_1_1library_1_1test_1_1TestControlWrapper.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::test::TestDialog</name>
    <filename>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</filename>
    <base>multiAgentExperience::dialog::DialogRequestInterface</base>
    <base>multiAgentExperience::dialog::ListeningHandlerInterface</base>
    <base>multiAgentExperience::dialog::ThinkingHandlerInterface</base>
    <member kind="function">
      <type>void</type>
      <name>onDenied</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</anchorfile>
      <anchor>a8719f8a62ad77792bfcaa758d9311fb4</anchor>
      <arglist>(const std::string &amp;denialMessage) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onDialogStarted</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</anchorfile>
      <anchor>a70783ae1709d07172a91469f9f64b50f</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::DialogControllerInterface &gt; controller) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onError</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</anchorfile>
      <anchor>a13dc2bcc6ffd2746f170b9bf3e4541df</anchor>
      <arglist>(const std::string &amp;errorMessage) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onDialogStopped</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</anchorfile>
      <anchor>a3e305df1e2d614b9467c9c90db69cb41</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onStartListening</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</anchorfile>
      <anchor>aeffb3de2fae117eaf4dc36db338b440f</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::DialogControllerInterface &gt; controller, std::set&lt; multiAgentExperience::control::ControlType &gt; controls) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onStopListening</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</anchorfile>
      <anchor>ae1d0a4a10b91151f9b658eda997d2af3</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onStartThinking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</anchorfile>
      <anchor>a784dcc81ae3b14e314b8f5362a7f51d2</anchor>
      <arglist>(std::shared_ptr&lt; multiAgentExperience::dialog::DialogControllerInterface &gt; controller) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>onStopThinking</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1test_1_1TestDialog.html</anchorfile>
      <anchor>a69b1a6aa7a4e12d8f223f19f07bfebed</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::dialog::ThinkingHandlerInterface</name>
    <filename>classmultiAgentExperience_1_1dialog_1_1ThinkingHandlerInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ThinkingHandlerInterface</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1ThinkingHandlerInterface.html</anchorfile>
      <anchor>a8c9848b1ac4862e4ef4b5e4fd0ffb3ed</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onStartThinking</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1ThinkingHandlerInterface.html</anchorfile>
      <anchor>a9de617f7e7ab548280036976673abd38</anchor>
      <arglist>(std::shared_ptr&lt; DialogControllerInterface &gt; controller)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onStopThinking</name>
      <anchorfile>classmultiAgentExperience_1_1dialog_1_1ThinkingHandlerInterface.html</anchorfile>
      <anchor>a1a7d824755a6a1ead40ccfa156756282</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::utils::threading::ThreadPool</name>
    <filename>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</filename>
    <member kind="function">
      <type></type>
      <name>ThreadPool</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</anchorfile>
      <anchor>a788146cad005164a3b45a5924d9f68f0</anchor>
      <arglist>(size_t maxThreads=DEFAULT_MAX_THREAD_POOL_THREADS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ThreadPool</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</anchorfile>
      <anchor>af73378bc6180682c7c4cddb70ed221c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::unique_ptr&lt; WorkerThread &gt;</type>
      <name>obtainWorker</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</anchorfile>
      <anchor>a5579d6204b8d0038a8ed3200aeba506a</anchor>
      <arglist>(std::string optionalMoniker=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>releaseWorker</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</anchorfile>
      <anchor>ae12f0f13bacdcb6fb76f8e4f707843a9</anchor>
      <arglist>(std::unique_ptr&lt; WorkerThread &gt; workerThread)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMaxThreads</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</anchorfile>
      <anchor>ae1ac1b92508681962420d38e658c34e7</anchor>
      <arglist>(size_t maxThreads)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>getMaxThreads</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</anchorfile>
      <anchor>a0abeb32666d4d697ae43363fb84f596a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getStats</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</anchorfile>
      <anchor>aa5f76bee1995c4561cee4a933b855515</anchor>
      <arglist>(uint64_t &amp;threadsCreated, uint64_t &amp;threadsObtained, uint64_t &amp;threadsReleasedToPool, uint64_t &amp;threadsReleasedFromPool)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; ThreadPool &gt;</type>
      <name>getDefaultThreadPool</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1ThreadPool.html</anchorfile>
      <anchor>a9b260d1b8b1749b2c1f318db5f256f8e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::utils::timing::Timer</name>
    <filename>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>PeriodType</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>a4729909011daa5aab0ff67a524c66631</anchor>
      <arglist></arglist>
      <enumvalue file="classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html" anchor="a4729909011daa5aab0ff67a524c66631a3a0bc063b6db8cae0361657958be836f">ABSOLUTE</enumvalue>
      <enumvalue file="classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html" anchor="a4729909011daa5aab0ff67a524c66631ac3cb497d8ec3c88b9024774b775358e2">RELATIVE</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>Timer</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>a608dbe1c41a7165bff3b6fcfb5d2974c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Timer</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>a4d24c985f029a9769f9ec60aa0c27336</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>start</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>af8b02a1f4bf9300c0f95fddf3d66227e</anchor>
      <arglist>(const std::chrono::duration&lt; Rep, Period &gt; &amp;delay, const std::chrono::duration&lt; Rep, Period &gt; &amp;period, PeriodType periodType, size_t maxCount, Task task, Args &amp;&amp;... args)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>start</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>a1e02a4093b3183742386d0edd6d5b6fa</anchor>
      <arglist>(const std::chrono::duration&lt; Rep, Period &gt; &amp;period, PeriodType periodType, size_t maxCount, Task task, Args &amp;&amp;... args)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>start</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>aeb76c7a37dc1815961a9b56e442df7d0</anchor>
      <arglist>(const std::chrono::duration&lt; Rep, Period &gt; &amp;delay, Task task, Args &amp;&amp;... args) -&gt; std::future&lt; decltype(task(args...))&gt;</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>a2a45d30a4b874d44eeee4ef3efaf940e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isActive</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>a6914eae99483e135f99a5a049f44226d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static size_t</type>
      <name>getForever</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>a59cc027fce333814767102501850c348</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>getTag</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>ac55bc84989887d6ef4a4998d38cf6642</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const size_t</type>
      <name>FOREVER</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1timing_1_1Timer.html</anchorfile>
      <anchor>a7c028ca440e098b76456242d4be26634</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::TransformedRequestStore</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1TransformedRequestStore.html</filename>
    <templarg>Request</templarg>
    <templarg>TransformedRequest</templarg>
    <templarg>Identifier</templarg>
  </compound>
  <compound kind="class">
    <name>TransformedRequestStore&lt; multiAgentExperience::activity::ActivityRequestInterface, multiAgentExperience::library::core::transformer::ActivityRequestTransformer, multiAgentExperience::library::activity::ActivityRequestID &gt;</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1TransformedRequestStore.html</filename>
  </compound>
  <compound kind="class">
    <name>TransformedRequestStore&lt; multiAgentExperience::dialog::DialogRequestInterface, multiAgentExperience::library::core::transformer::DialogRequestTransformer, multiAgentExperience::library::dialog::DialogRequestID &gt;</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1TransformedRequestStore.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::test::TransformerDialogRequestLifecycleTest</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1test_1_1TransformerDialogRequestLifecycleTest.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::TransformerUtils</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1TransformerUtils.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::test::UniversalDeviceCommandIntegrationTests</name>
    <filename>classmultiAgentExperience_1_1library_1_1test_1_1UniversalDeviceCommandIntegrationTests.html</filename>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::application::WakeWordObserverInterface</name>
    <filename>classmultiAgentExperience_1_1application_1_1WakeWordObserverInterface.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~WakeWordObserverInterface</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1WakeWordObserverInterface.html</anchorfile>
      <anchor>a7730e9badb792ce0e209a805bfb4f059</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>onWakeWordDetected</name>
      <anchorfile>classmultiAgentExperience_1_1application_1_1WakeWordObserverInterface.html</anchorfile>
      <anchor>a008d40ee9e0debd1c10d0de8e3d7fee9</anchor>
      <arglist>(const std::string &amp;wakeword)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::utils::threading::WorkerThread</name>
    <filename>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1WorkerThread.html</filename>
    <member kind="function">
      <type></type>
      <name>WorkerThread</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1WorkerThread.html</anchorfile>
      <anchor>a758d1dfa299f40d7d26a13d18493490f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~WorkerThread</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1WorkerThread.html</anchorfile>
      <anchor>a8e98ae4ac39d5fe12294449737fcc4a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1WorkerThread.html</anchorfile>
      <anchor>a46f088b9318493e1af02a92810e23d0b</anchor>
      <arglist>(std::function&lt; bool()&gt; workFunc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cancel</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1WorkerThread.html</anchorfile>
      <anchor>ad7e57ab87296b70392b2a72acca8aa3d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getMoniker</name>
      <anchorfile>classmultiAgentExperience_1_1library_1_1utils_1_1threading_1_1WorkerThread.html</anchorfile>
      <anchor>a6d0fec75c04e6f56d839b00be866331c</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>multiAgentExperience::library::core::transformer::WrappedWeakReferenceBrokenCallbackInterface</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1WrappedWeakReferenceBrokenCallbackInterface.html</filename>
    <templarg>T</templarg>
  </compound>
  <compound kind="class">
    <name>WrappedWeakReferenceBrokenCallbackInterface&lt; ControlStoreObserverTransformer &gt;</name>
    <filename>classmultiAgentExperience_1_1library_1_1core_1_1transformer_1_1WrappedWeakReferenceBrokenCallbackInterface.html</filename>
  </compound>
  <compound kind="namespace">
    <name>multiAgentExperience</name>
    <filename>namespacemultiAgentExperience.html</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>MAX Library</title>
    <filename>index</filename>
  </compound>
</tagfile>
