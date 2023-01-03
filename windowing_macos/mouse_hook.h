//
//  mouse_hook.h
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/09/21.
//  22:32
//
#pragma once


namespace mouse_hook
{

   
   ::e_status install(::particle * pparticleListener);

   ::e_status uninstall(::particle * pparticleListener);


} // mouse_hook

