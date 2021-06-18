#include "framework.h"


static ::user::notify_icon * g_pnotifyiconLast = nullptr;


namespace windowing_macos
{


   notify_icon::notify_icon()
   {

      g_pnotifyiconLast = this;

      m_bCreated = false;
      
   }


   notify_icon::~notify_icon()
   {

      DestroyWindow();

      if(g_pnotifyiconLast== this)
      {

         g_pnotifyiconLast = nullptr;

      }

   }


bool notify_icon::create_notify_icon(::u32 uId, ::user::notify_icon_listener * plistener, ::windowing::icon * pvisualicon)
   {

      if(m_bCreated)
      {

         return false;

      }
      
      m_strId.Format("notify_icon_%d", uId);

      m_strId = "ca2-" + pvisualicon->get_tray_icon_name() + "-" + m_strId;

      m_uiId                     = uId;

      m_plistener                = plistener;

      m_pnotifyiconbridge        = plistener;

//      string strFolder;
//
//      string str1 = pvisualicon->m_strAppTrayIcon;
//
//      str1.replace("-", "_");
//
//      str1.replace("/", "_");
//
//      str1.replace("\\", "_");
//
//      string str(str1);
//
//      if(::str::begins_eat_ci(str, "app_veriwell_"))
//      {
//
//         strFolder+="app-veriwell";
//
//      }
//      else if(::str::begins_eat_ci(str, "app_core_"))
//      {
//
//         strFolder+="app-core";
//
//      }
//      else
//      {
//
//         strFolder+="app";
//
//      }
//
//      //str
//
//      strFolder+= "/appmatter/" + str;
//
//      strFolder += "/_std/_std/main/";
//
//      string strFile = "menubar-icon-22.png";
//
//      string strUrl = "https://server.ca2.software/matter/" + strFolder + strFile;
//
//      strFile = Context.dir().appdata() / strFolder / strFile;
//
//      int iRetry = 3;
//
//      while(iRetry >= 0 && (!Context.file().exists(strFile) || Context.file().length(strFile) <= 0))
//      {
//
//         ::property_set set;
//
//         set["raw_http"] = true;
//         set["disable_common_name_cert_check"] = true;
//
//         Context.http().download(strUrl, strFile, set);
//
//         iRetry--;
//
//      }

      auto pcontext = m_pcontext->m_papexcontext;

      auto pathFile = pcontext->defer_process_matter_path("matter://main/menubar-icon-22.png");

      notify_icon_mm_initialize(pathFile);

      m_bCreated = true;

      return true;

   }


   bool notify_icon::ModifyIcon(__pointer(::draw2d::icon) hicon, bool bForce)
   {

      if(!m_bCreated)
      {

         return false;

      }

      if (!bForce && hicon == m_piconCurrent)
      {

         return true;

      }

//#ifdef WINDOWS_DESKTOP
//
//      m_nid.hIcon       = (HICON) *hicon;
//
//      m_nid.uFlags      = NIF_ICON;
//
//      if(!Shell_NotifyIcon(NIM_MODIFY, &m_nid))
//      {
//
//         return false;
//
//      }
//
//      m_piconCurrent = hicon;
//
//      return true;
//
//#else

      __throw(todo);

//#endif


   }


   void notify_icon::AddHiddenWindow(__pointer(::user::interaction) pwnd)
   {

      m_wndptraHidden.add_unique(pwnd);

   }


#ifdef WINDOWS_DESKTOP


   void notify_icon::destroy_window()
   {

      m_nid.uFlags = 0;

      if (!Shell_NotifyIcon(NIM_DELETE, &m_nid))
      {

         //return false;

      }

      ::user::interaction::destroy_window();

   }


   void notify_icon::remove_all_routes()
   {

      ::user::interaction::remove_all_routes();

   }


   void notify_icon::PostNcDestroy()
   {

      ::user::interaction::PostNcDestroy();


   }

#endif // defined(WINDOWS_DESKTOP)


   bool notify_icon::DestroyWindow()
   {

      if(!m_bCreated)
      {

         return false;

      }

      m_bCreated = false;

      notify_icon_mm_finalize();

      return true;

   }


//   void notify_icon::_001OnDestroy(::message::message* pmessage)
//   {
//
//      output_debug_string("notify_icon::_001OnDestroy");
//
//   }
//
//
//   void notify_icon::_001OnNotifyIconMessage(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::base, pbase, pmessage);
//
//      if (pbase->m_lparam == e_message_left_button_down)
//      {
//
//         while (m_wndptraHidden.get_size() > 0)
//         {
//
//            try
//            {
//
//               __pointer(::user::interaction) pframe = (m_wndptraHidden.element_at(0));
//
//               if (pframe != nullptr)
//               {
//
//                  pframe->display(e_display_normal);
//
//               }
//               else
//               {
//
//                  m_wndptraHidden.element_at(0)->display(e_display_normal);
//
//               }
//
//            }
//            catch (...)
//            {
//
//            }
//
//            m_wndptraHidden.remove_at(0);
//
//         }
//
//      }
//
//      m_plistener->OnNotifyIconMessage(m_uiId, (::u32) pbase->m_lparam);
//
//   }


//   void notify_icon::notify_icon_play(const char * action)
//   {
//
//
//   }


   ::e_status notify_icon::step()
   {

#if defined(LINUX)

//      main_async([&]
//      {
//
//         linux_g_direct_app_indicator_step(m_pindicator);
//
//      });

#endif
      
      return ::success;

   }


//#if defined(LINUX) || defined(MACOS)
//
//
//   int notify_icon::_get_notification_area_action_count()
//   {
//
//      return m_plistener->_get_notification_area_action_count();
//
//   }
//
//
//   const char * notify_icon::_get_notification_area_action_name(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_name(iIndex);
//
//   }
//
//
//   const char * notify_icon::_get_notification_area_action_id(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_id(iIndex);
//
//   }
//
//
//   const char * notify_icon::_get_notification_area_action_label(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_label(iIndex);
//
//   }
//
//
//   const char * notify_icon::_get_notification_area_action_accelerator(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_accelerator(iIndex);
//
//   }
//
//
//   const char * notify_icon::_get_notification_area_action_description(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_description(iIndex);
//
//   }
//
//
//   void notify_icon::call_notification_area_action(const char * pszId)
//   {
//
//      m_plistener->call_notification_area_action(pszId);
//
//   }
//
//
//#endif


} // namespace windowing_macos



