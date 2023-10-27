//
//  keyboard_hook.h
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/09/21.
//  22:30 BRT
#pragma once

//
//namespace keyboard_hook
//{
//
//   
//   ::e_status install(::particle * pparticleListener);
//
//   ::e_status uninstall(::particle * pparticleListener);
//
//   ::e_status is_enabled(bool bPrompt);
//
//
//} // keyboard_hook
//

// Merge from app_core_auratype by camilo 2021-09-12 16:31 BRT <3ThomasBS_!! 2023-10-27 17:19
#pragma once


#include "acme/_operating_system.h"
#include "apex/input/keyboard_hook.h"


namespace input_appkit
{


   class keyboard_hook :
      virtual public ::particle,
      virtual public ::input::keyboard_hook
   {
   public:


      static bool                s_bKeyboardHook;
      static ::task_pointer      s_ptaskKeyboard;

      keyboard_hook();
      ~keyboard_hook() override;


      virtual void install_keyboard_hook();

      virtual void uninstall_keyboard_hook();

      virtual bool is_keyboard_hook_installed();

      virtual void _keyboard_hook_task();


//      static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

      void keyboard_proc(enum_message emessage, int iVirtualKeyCode, int iScanCode) override;


   };


} // namespace input_appkit




