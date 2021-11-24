//
//  _factory.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-20 01:19 <3ThomasBS_!!
//
#include "framework.h"


extern "C"
void aura_macos_factory(::factory::factory * pfactory);


extern "C"
void windowing_macos_factory(::factory::factory * pfactory)
{
   

   aura_macos_factory(pfactory);

   
   pfactory->add_factory_item < windowing_macos::windowing, ::windowing::windowing > ();


   pfactory->add_factory_item < windowing_macos::window, ::windowing::window > ();

   pfactory->add_factory_item < windowing_macos::node, ::acme::node > ();
   pfactory->add_factory_item < windowing_macos::display, ::windowing::display > ();
   pfactory->add_factory_item < windowing_macos::monitor, ::windowing::monitor > ();
   pfactory->add_factory_item < windowing_macos::cursor, ::windowing::cursor > ();
   pfactory->add_factory_item < windowing_macos::notify_icon, ::user::notify_icon > ();
   pfactory->add_factory_item < windowing_macos::icon, ::windowing::icon > ();

   pfactory->add_factory_item < ::imm_client, ::user::text_composition_client > ();

   pfactory->add_factory_item < windowing_macos::keyboard, ::windowing::keyboard > ();

   pfactory->add_factory_item < windowing_macos::copydesk, ::user::copydesk > ();

}



