#pragma once


#include "audio-system/audio_mixer/control.h"

//
//namespace multimedia
//{


   namespace audio_mixer_core_audio
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO control :
         virtual public ::audio_mixer::control
      {
      public:


         enum Styles
         {
            StyleV001 = 1
         };


         //MIXERCONTROL                     m_mixercontrol;
         //MIXERCONTROLDETAILS              m_mixercontroldetails;


         control();
         control(control & control);
          ~control() override;

         //using ::audio_mixer::user::control_ptr_array::add;
//         virtual iptr add(::audio_mixer::user::control * pcontrol) override;

         bool control_type(::audio_mixer::e_control econtrol) const override;
         //bool OnCommand(WPARAM wParam, LPARAM lParam);
         ::pointer < ::audio_mixer::control_data > GetWindowDataByDlgCtrlID(uint32_t nID) override;
//         ::pointer < ::audio_mixer::user::control > GetControlByDlgCtrlID(uint32_t nID) override;
         //   bool OnNotify(uint32_t nID, LPNMHDR lpnmhdr);
         void OnVHScroll(uint32_t nSBCode, uint32_t nPos, ::user::interaction * pScrollBar);
         ::pointer < ::audio_mixer::control_data > GetWindowData(int32_t iType) override;
         void OnMixerControlChange() override;
//         ::pointer < ::audio_mixer::user::control > GetControl(int32_t iType) override;
//         ::pointer < ::audio_mixer::user::control > GetControlByIndex(::collection::index iIndex) override;
         void Prepare() override;
         bool CreateWindowsVolumeV001(::user::interaction * pParent, uint32_t nStartID, uint32_t * nNextID);

         //  bool _001CreateMuteControl(sp(::user::interaction) pParent, CRuntimeClass * pruntimeclassMuteControl, uint32_t nStartID, uint32_t * nNextID);
         bool _001CreateMuteControl(::user::interaction * pParent, uint32_t nStartID, uint32_t * nNextID);

         bool CreateWindows(::user::interaction * pParent, int32_t iStyle);

         control & operator =(const control & control);


         //MIXERCONTROL & GetMixerControl();
         //MIXERCONTROLDETAILS & GetMixerControlDetails();


      };


   } // namespace audio_mixer_core_audio

//
//} // namespace multimedia
//
//
//
//
