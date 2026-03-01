//
//  display.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:43 BRT <3ThomasBS_!!
//
#pragma once


#include "acme/windowing/display.h"
#include "acme/prototype/geometry2d/size.h"


namespace appkit
{

namespace acme
{

namespace windowing
{


class CLASS_DECL_ACME_WINDOWING_APPKIT display :
virtual public ::acme::windowing::display
{
public:
   
   
   display();
   ~display() override;
   
   
   ::int_size get_main_screen_size() override;
   float get_main_screen_scaling_factor() override;
    
    bool is_display_opened() const override;
    
};

} // namespace windowing

}// namespace acme

} // namespace appkit



