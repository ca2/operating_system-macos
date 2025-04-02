//
//  user_notify_icon_mm.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


#include <AppKit/AppKit.h>
//#import <Foundation/Foundation.h>
//#import <Cocoa/Cocoa.h>
//#import <ApplicationServices/ApplicationServices.h>
//#include "apex/user/user/notify_icon_bridge.h"


class application_menu;
class command_handler;


@interface user_notify_icon :  NSObject < NSMenuDelegate> {
@public
   
   
   ::application_menu *                m_papplicationmenu;
   ::command_handler *                 m_pcommandhandler;
   
   
   // http://stackoverflow.com/questions/3409985/how-to-create-a-menubar-application-for-mac
   // Flycut/AppController.h
   NSMenu *                m_menu;
   NSStatusItem *          m_statusitem;
   NSMutableArray *        m_menuitema;
   NSMutableArray *        m_menuida;
   
}

- (id) initWithIconImageFileData:(const void *) pdata size: (int) size applicationMenu: (::application_menu *) papplicationmenu andCommandHandler: (::command_handler *) pcommandhandler;

- (id)initWithIconImage:(NSImage *)pimage applicationMenu: (::application_menu *) papplicationmenu andCommandHandler: (::command_handler *) pcommandhandler;


- (void) on_application_menu_action : (id)sender;


- (void) close;


@end


