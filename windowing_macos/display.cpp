//
//  display.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:43 BRT <3ThomasBS_!!
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#include "aura/_defer.h"
#endif


bool macos_get_cursor_position(::int_point * ppointCursor);
int ns_monitor_count();
char * ns_get_wallpaper();
void ns_set_wallpaper(const char *psz);


namespace windowing_macos
{


   display::display()
   {
   
      //m_pDisplay2 = this;
   
   }


   display::~display()
   {
      

   }


   ::collection::count display::get_monitor_count()
   {
    
      return ns_monitor_count();
      
   }


   string display::impl_get_wallpaper(::collection::index iScreen)
   {
      
      auto psz = ns_get_wallpaper();
      
      ::string str(psz);
      
      if(psz)
      {
         
         free(psz);
         
      }
      
//      str.case_insensitive_begins_eat("file://");
//      
//      str = ::url::decode(str);
      
      return ::transfer(str);
      
   }


   bool display::impl_set_wallpaper(::collection::index iScreen, string strWallpaper)
   {
      
//      if(!strWallpaper.case_insensitive_begins("file://"))
//      {
//
//         ::string str = ::url::encode(strWallpaper);
//
//         str.find_replace("%2F", "/");
//
//         strWallpaper = "file://" + str;
//
//      }
   
      ns_set_wallpaper(strWallpaper);
      
      return true;
      
   }


   ::int_point display::_get_mouse_cursor_position()
   {
      
      ::int_point p;
      
      macos_get_cursor_position(&p);
      
      return p;
      
   }


} // namespace windowing_macos


