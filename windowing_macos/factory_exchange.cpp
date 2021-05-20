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
   
   
}




