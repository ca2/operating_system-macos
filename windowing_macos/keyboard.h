// created by Camilo 2021-02-04 00:58 BRT CamiloSasuke<3ThomasBorregaardSoerensen
#pragma once


#include "aura/windowing/keyboard.h"


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS keyboard :
      virtual public ::windowing::keyboard
   {
   public:


      keyboard();
      ~keyboard() override;
      
      
      ::user::enum_key wparam_to_userkey(wparam wparam) override;

      void translate_os_key_message(::user::key * pkey) override;
      

   };


} // namespace windowing_macos





