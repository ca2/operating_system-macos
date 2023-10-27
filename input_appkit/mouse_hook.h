//
//  mouse_hook.h
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/09/21.
//  22:32
// Merge from app_core_auraclick by camilo 2021-09-12 16:34 BRT <3ThomasBS_!! 2023-10-27 17:15
//
#pragma once
//
//
//namespace mouse_hook
//{
//
//   
//   ::e_status install(::particle * pparticleListener);
//
//   ::e_status uninstall(::particle * pparticleListener);
//
//
//} // mouse_hook
//
#pragma once


#include "acme/_operating_system.h"
#include "apex/input/mouse_hook.h"


namespace input_appkit
{


   class mouse_hook :
      virtual public ::particle,
      virtual public ::input::mouse_hook
   {
   public:


      static bool                s_bMouseHook;
//      static mouse_hook *        s_pmousehook;
      static ::task_pointer      s_ptaskMouse;
//      static HHOOK               s_hhookMouse;

      
      mouse_hook();
      ~mouse_hook() override;


      virtual void install_mouse_hook();

      virtual void uninstall_mouse_hook();

      virtual bool is_mouse_hook_installed();

      virtual void _mouse_hook_task();

//      static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

      void mouse_proc(enum_message emessage) override;

   };


   ::e_status install_mouse_hook(::input::mouse_hook * pmousehook);


   ::e_status uninstall_mouse_hook(::input::mouse_hook * pmousehook);


} // namespace input_win32
