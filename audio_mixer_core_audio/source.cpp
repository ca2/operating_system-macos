#include "framework.h"
#include "source.h"
#include "destination.h"

//
//namespace multimedia
//{


   namespace audio_mixer_core_audio
   {


      source::source()
      {
         //m_mixercontrola.set_app(papp);
         m_pdestination = NULL;
         //m_mixerlinecontrols.pamxctrl = NULL;
      }

      source::source(source & source) :
         //::ca2::ca2(source.get_app()),
         ::audio_mixer::source(source)
      {
         operator =(source);
      }

      source::~source()
      {

      }

      void source::GetLineControls()
      {
//         ::multimedia::e_result mmrc;
//         m_bHasV001Controls = false;
//         int32_t iControlCount = m_mixerline.cControls;
//         if (0 == iControlCount)
//         {
//            //        System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
//            //"There are no controls associated with the selected line.");
//            //        EndDialog(oswindow, FALSE);
//            return MMSYSERR_NOERROR;
//         }
//
//         m_mixercontrola.set_size_create(iControlCount);
//
//         if(m_mixerlinecontrols.pamxctrl != NULL)
//            delete[] (MIXERCONTROL *) m_mixerlinecontrols.pamxctrl;
//         m_mixerlinecontrols.cbStruct       = sizeof(MIXERLINECONTROLS);
//         m_mixerlinecontrols.dwLineID       = m_mixerline.dwLineID;
//         ////////////mxlc.dwControlID    = 0;
//         ////////////mxlc.dwControlType  = 0;
//         m_mixerlinecontrols.cControls      = iControlCount;
//         m_mixerlinecontrols.cbmxctrl       = sizeof(*m_mixerlinecontrols.pamxctrl);
//         m_mixerlinecontrols.pamxctrl       = new MIXERCONTROL[m_mixerline.cControls];
//
//         for (int32_t i = 0; i < iControlCount; i++)
//         {
//            m_mixerlinecontrols.pamxctrl[i].cbStruct = sizeof(MIXERCONTROL);
//         }
//
//         sp(::multimedia::audio_mixer_audio_core::device) device = get_device();
//
//         mmrc = mixerGetLineControls(
//            (HMIXEROBJ) device->m_hMixer,
//            &m_mixerlinecontrols,
//            MIXER_GETLINECONTROLSF_ALL);
//         if (MMSYSERR_NOERROR != mmrc)
//         {
//            System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
//               "mixerGetLineControls(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
//               m_mixerline.dwLineID, device->m_hMixer, mmrc);
//         }
//         else
//         {
//            //        char       ach[128];
//            //      char       szControlType[64];
//            //        uint32_t        u;
//            //    int32_t         nIndex;
//            PMIXERCONTROL       pamxctrl;
//            //        LPMIXERCONTROLDETAILS lpmcd;
//            sp(::multimedia::audio_mixer_audio_core::control)     lpMixerControl;
//
//            //        if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
//            //          MixAppDebugLog(NULL);
//
//            for (int32_t i = 0; (uint32_t) i < m_mixerlinecontrols.cControls; i++)
//            {
//               lpMixerControl = m_mixercontrola(i);
//               lpMixerControl->m_pmixersource = this;
//               pamxctrl = &lpMixerControl->GetMixerControl();
//               //m_mixerlinecontrols.pamxctrl = pamxctrl;
//               //*m_mixerlinecontrols.pamxctrl = m_mixerlinecontrols.pamxctrl[i];
//               *pamxctrl = m_mixerlinecontrols.pamxctrl[i];
//               lpMixerControl->Prepare();
//               //            ::audio_mixer::audio_mixer::get_control_type_name(pamxctrl, lpMixerControl->m_strTypeName);
//
//               switch (pamxctrl->dwControlType)
//               {
//                  //            case MIXERCONTROL_CONTROLTYPE_FADER:
//               case MIXERCONTROL_CONTROLTYPE_VOLUME:
//                  //          case MIXERCONTROL_CONTROLTYPE_BASS:
//                  //        case MIXERCONTROL_CONTROLTYPE_TREBLE:
//                  //      case MIXERCONTROL_CONTROLTYPE_EQUALIZER:
//
//                  //    case MIXERCONTROL_CONTROLTYPE_BOOLEAN:
//                  //  case MIXERCONTROL_CONTROLTYPE_ONOFF:
//               case MIXERCONTROL_CONTROLTYPE_MUTE:
//                  //            case MIXERCONTROL_CONTROLTYPE_MONO:
//                  //          case MIXERCONTROL_CONTROLTYPE_LOUDNESS:
//                  //        case MIXERCONTROL_CONTROLTYPE_STEREOENH:
//                  m_bHasV001Controls = true;
//                  break;
//
//               default:;
//               }
//               //
//               //
//               //
//               //            wsprintf(ach, gszLineControlsFormatList,
//               //                  u,
//               //                (LPTSTR)szControlType,
//               //              pamxctrl[u].dwControlID,
//               //            pamxctrl[u].fdwControl,
//               //          pamxctrl[u].cMultipleItems,
//               //        (char *)pamxctrl[u].szName);
//
//               //            if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
//               //          {
//               //            MixAppDebugLog(ach);
//               //          MixAppDebugLog(gszCRLF);
//               //    }
//
//               //            nIndex = ListBox_AddString(ptlb->hlb, ach);
//               //          ListBox_SetItemData(ptlb->hlb, nIndex, pamxctrl[u].dwControlID);
//            }
//
//            //    ListBox_SetCurSel(ptlb->hlb, 0);
//            //  EnableWindow(get_child_by_id(oswindow, IDD_LINECONTROLS_BTN_INFO), TRUE);
//            //EnableWindow(get_child_by_id(oswindow, IDD_LINECONTROLS_BTN_SETTINGS), TRUE);
//         }
//
//         //    SetWindowRedraw(ptlb->hlb, TRUE);
//         //  LocalFree((HLOCAL)pamxctrl);
//         return mmrc;

      }

      /*::multimedia::e_result source::GetControl(uint32_t dwControlType, uint32_t dwControlFlags,  ::audio_mixer::control ** ppControl)
      {
      ::audio_mixer::control_array & controla = m_mixercontrola;
      if(controla.get_size() <= 0)
      GetLineControls();
      if(controla.get_size() <= 0)
      return MMSYSERR_ERROR;
      for(int32_t i = 0; i < controla.get_size(); i++)
      {
      if((dwControlType != 0 && controla[i].GetControlType() == dwControlType)
      || (dwControlType == 0 && ((controla[i].GetControlType() & dwControlFlags) != 0)))
      {
      *ppControl = controla(i);
      return MMSYSERR_NOERROR;
      }
      }
      return MMSYSERR_ERROR;
      }*/

      /*void source::OnArrayReallocation(void *pNewPointer)
      {
      m_pmixerdestination = (::audio_mixer::destination *) pNewPointer;
      }*/

      void source::OnMixerLineChange()
      {

      }



      void source::update_all_controls()
      {
//         ::audio_mixer::control_array & controla = get_control_array();
//         for(int32_t i = 0; i < controla.get_size(); i++)
//         {
//            controla[i].OnMixerControlChange();
//         }
      }

      source & source::operator = (const source & source)
      {
         m_bHasV001Controls = source.m_bHasV001Controls;
         m_pdestination = source.m_pdestination;
         return *this;
      }

      const char * source::GetSZName()
      {
         //return m_mixerline.szName;
         
         return nullptr;
         
      }

      ::atom source::GetLineID()
      {
         //return m_mixerline.dwLineID;
         
         return {};
         
      }


      ::audio_mixer::device * source::get_device()
      {
         return m_pdestination->get_device();
      }

      void source::SetDestination(::audio_mixer::destination * pdestination)
      {
         m_pdestination = pdestination;
      }


      void source::get_line_info(uint32_t dwSource, uint32_t dwDestination, uint32_t fdwInfo)
      {
         
//         m_mixerline.cbStruct       = sizeof(MIXERLINE);
//         m_mixerline.dwDestination  = dwDestination;
//         m_mixerline.dwSource       = dwSource;
//
//
//         sp(::multimedia::audio_mixer_audio_core::device) device = get_device();
//
//         ::multimedia::e_result mmrc = ::mixerGetLineInfo((HMIXEROBJ)device->m_hMixer, &m_mixerline, fdwInfo);
//
//         if (MMSYSERR_NOERROR != mmrc)
//         {
//            System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
//               "mixerGetLineInfo(src=%u) failed on hmx=%.04Xh, mmr=%u!",
//               dwSource, device->m_hMixer, mmrc);
//         }
//
//         return mmrc;


      }

   
      void source::get_line_info(uint32_t dwSource, ::audio_mixer::destination * pdestination)
      {
         
//         sp(::multimedia::audio_mixer_audio_core::destination) destination = pdestination;
//
//         ::multimedia::e_result mmrc = mixerGetLineInfo(dwSource, destination->m_mixerline.dwDestination, MIXER_GETLINEINFOF_SOURCE);
//         SetDestination(pdestination);
//         return mmrc;

      }

      ::audio_mixer::destination * source::get_destination()
      {
         return m_pdestination;
      }

      bool source::HasV001Controls()
      {
         return m_bHasV001Controls;
      }

      ::audio_mixer::control_array & source::get_control_array()
      {
         return m_mixercontrola;
      }

//      MIXERLINE & source::get_mixer_line()
//      {
//         return m_mixerline;
//      }
//
//      MIXERLINECONTROLS & source::get_mixer_line_controls()
//      {
//         return m_mixerlinecontrols;
//      }
//

   } // namespace audio_mixer_core_audio

//
//} // namespace multimedia
//
//
//
