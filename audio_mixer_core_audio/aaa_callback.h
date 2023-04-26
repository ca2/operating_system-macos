#pragma once


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO callback
      {
      public:


         callback();
         virtual ~callback();


         ::pointer < ::audio_mixer::user::level_control > allocate_level_control() override;
         ::pointer < ::audio_mixer::user::toggle_control > allocate_toggle_control() override;
         ::pointer < ::audio_mixer::user::label > allocate_label() override;


      };


   } // namespace audio_mixer_audio_core


} // namespace multimedia



