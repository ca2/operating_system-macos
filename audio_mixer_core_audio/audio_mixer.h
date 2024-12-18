#pragma once


#include "audio-system/audio_mixer/audio_mixer.h"

//
//namespace multimedia
//{


   namespace audio_mixer_core_audio
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO audio_mixer :
         virtual public ::audio_mixer::audio_mixer
      {
      public:

//
//         ::pointer < ::audio_mixer_core_audio::window >            m_pwindow;


         audio_mixer();
         ~audio_mixer() override;



         ::audio_mixer::callback * get_callback();
         void set_callback(::audio_mixer::callback * pcallback);


         void set_new_device(uint32_t uiMixerId) override;


         //bool OnCommand(WPARAM wparam, LPARAM lparam);
         //void OnMixerControlChange(HMIXER hMixer, uint32_t dwControlID);
         //void OnMixerLineChange(HMIXER hMixer, uint32_t dwLineID);


         //static bool get_component_name(LPMIXERLINE pmxl, string & strComponent);
         //static bool get_control_type_name(LPMIXERCONTROL pmxctrl, string & strTypeName);



      };


   } // namespace audio_mixer_core_audio
//
//
//} // namespace multimedia
//
//
//
