//
//  keyboard_hook.h
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/09/21.
//  22:30 BRT
#pragma once


namespace keyboard_hook
{

   
   ::e_status install(::matter * pmatterListener);

   ::e_status uninstall(::matter * pmatterListener);

   ::e_status is_enabled(bool bPrompt);


} // keyboard_hook




