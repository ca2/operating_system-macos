//
//  _mm.h
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 02:49 BRT <3ThomasBS_!!
//
#pragma once


#include "aura_macos/_mm.h"


#import "macos/macOSWindow.h"


#include "macos/macos_window.h"


//#if defined(__OBJECTIVE_CPP__)

//#import <Cocoa/Cocoa.h>

void ns_screen_translate(CGRect * prect, int iIndex = -1);

void ns_main_monitor_cgrect(CGRect * prect);

//#endif


void * new_macos_window(macos_window * papexwindow, CGRect rectangle, unsigned int uStyle);


#import "notify_icon_mm.h"


#import "notify_icon_mm_bridge.h"


#import "macos/macOSImpact.h"


#import "macos/macOSApp.h"


#import "macos/macOSWindowController.h"



