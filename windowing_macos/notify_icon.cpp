#include "framework.h"
#include "acme/platform/system.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#include "aura/_defer.h"
#endif
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"
#include "acme/platform/application.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/context.h"


static ::user::notify_icon * g_pnotifyiconLast = nullptr;


namespace windowing_macos
{


   notify_icon::notify_icon()
   {

      g_pnotifyiconLast = this;

      m_bCreated = false;
      
      //m_pnotifyiconbridge = this;
      
   }


   notify_icon::~notify_icon()
   {

      DestroyWindow();

      if(g_pnotifyiconLast== this)
      {

         g_pnotifyiconLast = nullptr;

      }

   }

::application_menu * notify_icon::menu()
{
 
   return ::user::notify_icon::menu();
   
}


::application_menu_callback * notify_icon::callback()
{
   
   return this;
   
}

   void notify_icon::create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * pwindowingicon)
   {

      if(m_bCreated)
      {

         //return ::success_none;
         
         return;

      }
      
      m_strId = "notify_icon_" + atom;

      m_strId = "ca2-" + pwindowingicon->get_tray_icon_name() + "-" + m_strId;

      m_atom                       = atom;

      m_puserinteractionNotify   = puserinteractionNotify;

      //m_pnotifyiconbridge        = plistener;

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
//      if(::str::case_insensitive_begins_eat(str, "app_veriwell_"))
//      {
//
//         strFolder+="app-veriwell";
//
//      }
//      else if(::str::case_insensitive_begins_eat(str, "app_core_"))
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
   
   
       ::file::path pathFolder = system()->directory_system()->ca2roaming() / "matter/icon/128";

      string strIconName = application()->m_strAppId;

      strIconName.find_replace("/", "_");
      strIconName.find_replace("-", "_");

      auto pcontext = application();

      auto memoryIconImage = pcontext->file()->safe_get_memory("matter://main/menubar-icon-22.png");
      
      
      //auto pimage = m_psystem->context_image()->get_image(pathFile);
   
      //auto pathFile = pwindowingicon->m_strTrayIconName;
   
      //auto pathFile = pathFolder / ( strIconName + ".png" );

      notify_icon_mm_initialize(memoryIconImage.data(), (int) memoryIconImage.size());

      m_bCreated = true;

      //return true;

   }


   bool notify_icon::ModifyIcon(::pointer < ::image::icon > hicon, bool bForce)
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

      throw ::exception(todo);

//#endif


   }


   void notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      //auto estatus =
      
      ::user::notify_icon::add_hidden_window(puserinteraction);
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

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
//               ::pointer < ::user::interaction > pframe = (m_wndptraHidden.element_at(0));
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
//      m_plistener->OnNotifyIconMessage(m_uiId, (unsigned int) pbase->m_lparam);
//
//   }


//   void notify_icon::notify_icon_play(const char * action)
//   {
//
//
//   }


   bool notify_icon::notify_icon_step()
   {

#if defined(LINUX)

//      main_async([&]
//      {
//
//         linux_g_direct_app_indicator_step(m_pindicator);
//
//      });

#endif
      
      //return ::success;
      
      return true;

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



