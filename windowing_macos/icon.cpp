// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard S�rensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
// macOS version by Camilo 2021-05-31 14:53
#include "framework.h"
#include "icon.h"


namespace windowing_macos
{


   icon::icon()
   {

   }


   icon::~icon()
   {


   }


//   string icon::get_tray_icon_name() const
//   {
//
//      return m_strTrayIconName;
//
//   }
//
//
//   ::e_status icon::set_tray_icon_name(const ::string & strTrayIconName)
//   {
//
//      m_strTrayIconName = strTrayIconName;
//
//      return ::success;
//
//   }
//
//
//   void * icon::get_os_data(const ::i32_size & size) const
//   {
//
//      return nullptr;
//
//   }
//
//
//   ::e_status icon::load_file(string strPath)
//   {
//
//      throw interface_only();
//
//      return false;
//
//   }
//
//
//   ::e_status icon::load_matter(string strMatter)
//   {
//
//      auto pcontext = get_context();
//
//      string strPath = papplication->dir().matter(strMatter);
//
//      if (!load_file(strPath))
//      {
//
//         return false;
//
//      }
//
////      on_update_icon();
//
//      return true;
//
//   }
//
//
//   ::e_status icon::load_app_tray_icon(string strApp)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      string strMatter = "main/icon.ico";
//
//      if (!load_matter(strMatter))
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      //m_strAppTrayIcon = strApp;
//
//      return true;
//
//#endif
//
//
//   }
//
//
//   image_pointer icon::get_image(const concrete < ::i32_size > & size)
//   {
//
//      throw interface_only();
//
//      return nullptr;
//
//   }
//
//
//   void icon::get_sizes(array < concrete < ::i32_size > > & a)
//   {
//
//
//   }


} // namespace windowing_macos



