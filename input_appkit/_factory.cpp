//
//  _factory.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-20 01:19 <3ThomasBS_!!
//
#include "framework.h"
#include "input.h"


extern "C"
void input_appkit_factory(::factory::factory * pfactory)
{
   

   pfactory->add_factory_item < input_appkit::input, ::input::input > ();


}



