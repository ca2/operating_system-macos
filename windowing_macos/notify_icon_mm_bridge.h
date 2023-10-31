//
//  user_notify_icon_mm_bridge.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
//
#pragma once


class application_menu;
class application_menu_callback;


class user_notify_icon_mm_bridge
{
public:


   void *                              m_pnotifyicon;
   //::user_notify_icon_bridge *         m_pnotifyiconbridge;
   

   //virtual void notify_icon_mm_initialize(const void * pdata, int cx, int cy, int scan);
   
   virtual void notify_icon_mm_initialize(const void * pdataImageFile, int size);
   
   
   virtual ::application_menu * menu() = 0;
   
   virtual ::application_menu_callback * callback() = 0;
   
   virtual void notify_icon_mm_finalize();


};



