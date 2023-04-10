#pragma once


#include "audio-system/audio_mixer/source.h"

//
//namespace multimedia
//{


   namespace audio_mixer_core_audio
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO source :
         virtual public ::audio_mixer::source
      {
      public:


//         MIXERLINE                     m_mixerline;
//         MIXERLINECONTROLS             m_mixerlinecontrols;


         source();
         source(source & source);
         ~source() override;


         void get_line_info(uint32_t dwSource, uint32_t dwDestination, uint32_t fdwInfo) override;
         void get_line_info(uint32_t dwSource, ::audio_mixer::destination * pdestination) override;

         ::atom GetLineID() override;
         const char * GetSZName();
         void update_all_controls() override;
         //MIXERLINECONTROLS & get_mixer_line_controls();
         //MIXERLINE & get_mixer_line();
         ::audio_mixer::control_array & get_control_array() override;

         ::audio_mixer::device * get_device() override;

         void SetDestination(::audio_mixer::destination * pdestination) override;
         ::audio_mixer::destination * get_destination() override;

         void OnMixerLineChange() override;
         //void OnArrayReallocation(void *pNewPointer);
         //::multimedia::e_result GetControl(uint32_t dwControlType, uint32_t dwControlFlags, ::audio_mixer::control ** ppControl);
         void GetLineControls() override;

         bool HasV001Controls() override;
         source & operator = (const source & source);


      };


   } // namespace audio_mixer_core_audio

//
//} // namespace multimedia
//
//
//
