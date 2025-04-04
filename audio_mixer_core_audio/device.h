#pragma once


#include "audio-system/audio_mixer/device.h"
//
//
//namespace multimedia
//{


   namespace audio_mixer_core_audio
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO device :
         virtual public ::audio_mixer::device
      {
      public:


         //HMIXER                        m_hMixer;
         //MIXERCAPS                     m_mixercaps;


         device();
         ~device() override;

         virtual bool initialize(::audio_mixer::audio_mixer * pmixer);

         ::audio_mixer::audio_mixer * get_mixer() override;
         const char * GetSZPName();
         //bool OnCommand(WPARAM wparam, LPARAM lparam);
         void close() override;
         void MapDlgCtrlIDToLineControls(::audio_mixer::source * pSource) override;
         void MapDlgCtrlIDToControls() override;
         void MapLineControls(::audio_mixer::source * pSource) override;
         void OnMixerControlChange(uint32_t dwControlID) override;
         void OnMixerLineChange(uint32_t dwLineID) override;
         void map_lines() override;
         void map_controls() override;
         void get_destination(::audio_mixer::e_destination edestination, ::audio_mixer::destination ** ppDestination);
         void initialize_destinations() override;
         void initialize_capabilities() override;
         void open(uint32_t uiMixerId, uint32_t dwCallback, uint32_t dwInstance, uint32_t fdwOpen);


      };


   } // namespace audio_mixer_core_audio

//
//} // namespace multimedia
//
//
//
//
//
