//
//  _c_mm.h
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-19 02:44 BRT <3ThomasBS_!!
//
#pragma once


#if defined(__MM)

void ns_screen_translate(CGRect * prect, int iIndex = -1);

void ns_main_monitor_cgrect(CGRect * prect);

#endif



