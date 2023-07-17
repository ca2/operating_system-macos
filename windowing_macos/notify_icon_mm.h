//
//  user_notify_icon_mm.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#ifndef user_notify_icon_mm_h
#define user_notify_icon_mm_h


#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <ApplicationServices/ApplicationServices.h>
#include "apex/user/user/notify_icon_bridge.h"


class user_notify_icon_bridge;


@interface user_notify_icon :  NSObject < NSMenuDelegate> {
@public
   
   
   ::user_notify_icon_bridge *   m_pnotifyiconbridge;
   
   
   // http://stackoverflow.com/questions/3409985/how-to-create-a-menubar-application-for-mac
   // Flycut/AppController.h
   NSMenu *             m_menu;
   NSStatusItem *       m_statusitem;
   NSMutableArray *     m_menuitema;
   NSMutableArray *     m_menuida;
   
}

- (id) initIconImageFileData:(const void *) pdata withSize: (int) size withBridge: (::user_notify_icon_bridge *) pbridge;

- (id)initIconImage:(NSImage *)pimage withBridge: (::user_notify_icon_bridge *) pbridge;


- (void) on_item_action : (id)sender;


- (void) close;


@end


#endif /* user_notify_icon_mm_h */
