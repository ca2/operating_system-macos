//
//  _windowing_macos.h
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 04:23 BRT <3ThomasBS_!!
//
#pragma once


#include "aura_macos/_library.h"


#include "macos/macos_window.h"


rectangle_i32_array cg_get_window_rect_list_intersect_above(CGWindowID windowid);
CGWindowID ns_get_window_id(void * pnswindow);


#include "display.h"


#include "imm_client.h"


#include "keyboard.h"


#include "monitor.h"


#include "notify_icon_mm_bridge.h"


#include "notify_icon.h"


#include "icon.h"


#include "cursor.h"


#include "window.h"


#include "copydesk.h"


#include "windowing.h"


#include "node.h"



