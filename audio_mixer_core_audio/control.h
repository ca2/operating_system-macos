#pragma once


#include "app-core/multimedia/audio_mixer/control.h"


namespace multimedia
{


   namespace audio_mixer_core_audio
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO control :
         virtual public ::multimedia::audio_mixer::control
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

         //using ::multimedia::audio_mixer::user::control_ptr_array::add;
         virtual iptr add(::multimedia::audio_mixer::user::control * pcontrol) override;

         bool control_type(::multimedia::audio_mixer::e_control econtrol) const override;
         //bool OnCommand(WPARAM wParam, LPARAM lParam);
         __pointer(::multimedia::audio_mixer::control_data) GetWindowDataByDlgCtrlID(uint32_t nID) override;
         __pointer(::multimedia::audio_mixer::user::control) GetControlByDlgCtrlID(uint32_t nID) override;
         //   bool OnNotify(uint32_t nID, LPNMHDR lpnmhdr);
         void OnVHScroll(uint32_t nSBCode, uint32_t nPos, ::user::interaction * pScrollBar);
         __pointer(::multimedia::audio_mixer::control_data) GetWindowData(int32_t iType) override;
         void OnMixerControlChange() override;
         __pointer(::multimedia::audio_mixer::user::control) GetControl(int32_t iType) override;
         __pointer(::multimedia::audio_mixer::user::control) GetControlByIndex(::index iIndex) override;
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


} // namespace multimedia




