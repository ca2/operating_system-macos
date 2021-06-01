//
//  factory_exchange.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-20 01:19 <3ThomasBS_!!
//
#include "framework.h"


extern "C"
void aura_macos_factory_exchange(::factory_map * pfactorymap);


extern "C"
void windowing_macos_factory_exchange(::factory_map * pfactorymap)
{
   

   aura_macos_factory_exchange(pfactorymap);

   
   pfactorymap->create_factory < windowing_macos::windowing, ::windowing::windowing > ();


   pfactorymap->create_factory < windowing_macos::window, ::windowing::window > ();

   pfactorymap->create_factory < windowing_macos::node, ::acme::node > ();
   pfactorymap->create_factory < windowing_macos::display, ::windowing::display > ();
   pfactorymap->create_factory < windowing_macos::monitor, ::windowing::monitor > ();
   pfactorymap->create_factory < windowing_macos::cursor, ::windowing::cursor > ();
   pfactorymap->create_factory < windowing_macos::notify_icon, ::user::notify_icon > ();
   pfactorymap->create_factory < windowing_macos::icon, ::windowing::icon > ();

   pfactorymap->create_factory < ::imm_client, ::user::text_composition_client > ();

   pfactorymap->create_factory < windowing_macos::keyboard, ::windowing::keyboard > ();

   
}




