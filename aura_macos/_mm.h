//
//  _mm.h
//  aura_macos
//
//  Created by Camilo Sasuke on 2021-05-18 15:18 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


#include "aura_apple/_mm.h"
#include "apex_macos/_mm.h"


namespace windowing
{


   class window;


} // namespace windowing_window


using oswindow_t = ::windowing::window;


using oswindow = oswindow_t *;


#include "_c_mm.h"


#import "AuraWindow.h"


#include "aura_window.h"


NSWindow * new_aura_window(aura_window * papexwindow, CGRect rectangle, unsigned int uStyle);


#import "AuraWindowFrameView.h"


#import "AuraWindowApp.h"


#import "AuraWindowController.h"



