//
//  ios_media_picker.h
//  media_ios
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-10 01:08 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/_start.h"
#include "acme/_.h"


class macos_window;


#ifdef __OBJECTIVE_CPP__
@class macosMediaPickerViewController;
#endif


struct platform_media_item_t;


class macos_media_picker
{
public:
   
   
#ifdef __OBJECTIVE_CPP__
   macosMediaPickerViewController * m_pmacoscontroller;
#else
   void * m_pMacosController;
#endif
   
   
   macos_media_picker();
   
   virtual void macos_media_picker_pick_media(const char * pszMediaType, macos_window * pmacoswindow);
   virtual void macos_media_picker_did_pick_platform_media_item(platform_media_item_t * pplatformmediaitem) = 0;
   
   
};



