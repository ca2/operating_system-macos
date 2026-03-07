//
//  _mm_cpp.h
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/03/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once



struct keyboard_layout_change_t
{
 
   virtual void on_keyboard_layout_change(const char * pszKeyboardLayoutId) = 0;
   


};


void run_keyboard_layout_observer(keyboard_layout_change_t * p);
