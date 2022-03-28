#pragma once


namespace multimedia
{


   namespace audio_mixer_core_audio
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO source :
         virtual public ::multimedia::audio_mixer::source
      {
      public:


//         MIXERLINE                     m_mixerline;
//         MIXERLINECONTROLS             m_mixerlinecontrols;


         source();
         source(source & source);
         ~source() override;


         void mixerGetLineInfo(uint32_t dwSource, uint32_t dwDestination, uint32_t fdwInfo) override;
         void mixerGetLineInfo(uint32_t dwSource, ::multimedia::audio_mixer::destination * pdestination) override;

         ::atom GetLineID() override;
         const char * GetSZName();
         void update_all_controls() override;
         //MIXERLINECONTROLS & get_mixer_line_controls();
         //MIXERLINE & get_mixer_line();
         ::multimedia::audio_mixer::control_array & get_control_array() override;

         ::multimedia::audio_mixer::device * get_device() override;

         void SetDestination(::multimedia::audio_mixer::destination * pdestination) override;
         ::multimedia::audio_mixer::destination * get_destination() override;

         void OnMixerLineChange() override;
         //void OnArrayReallocation(void *pNewPointer);
         //::multimedia::e_result GetControl(uint32_t dwControlType, uint32_t dwControlFlags, ::multimedia::audio_mixer::control ** ppControl);
         void GetLineControls() override;

         bool HasV001Controls() override;
         source & operator = (const source & source);


      };


   } // namespace audio_mixer_core_audio


} // namespace multimedia



