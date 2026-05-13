//
//  _mm.h
//  appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#pragma once


#include "operating_system-apple/core_graphics/_mm.h"
#include "_struct.h"

using namespace appkit;

void ns_window_release(ns_window_t & nswindow);

void ns_image_release(ns_image_t & nsimage);


cg_image_t ns_image_get_cg_image(ns_image_t nsimage);



