#pragma once


#include "audio-system/audio_mixer/line_info.h"


//namespace multimedia
//{


   namespace audio_mixer_core_audio
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO line_info :
         virtual public ::audio_mixer::line_info
      {
      public:


         //MIXERLINE       m_mixerLine;


         line_info();
         ~line_info() override;


      };


   } // namespace audio_mixer_core_audio

//
//} // namespace multimedia
//
//
//
