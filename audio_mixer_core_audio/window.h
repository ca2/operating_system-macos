#pragma once


namespace multimedia
{


   namespace audio_mixer_core_audio
   {


      class audio_mixer;


      class window : 
         public ::user::interaction
      {
      public:


         __pointer(::multimedia::audio_mixer::audio_mixer)   m_pmixer;


         window();
         ~window() override;


         void install_message_routing(::channel * pchannel) override;


         DECLARE_MESSAGE_HANDLER(_001OnMixerControlChange);
         DECLARE_MESSAGE_HANDLER(_001OnMixerLineChange);


      };


   } // namespace audio_mixer_core_audio


} // namespace multimedia



