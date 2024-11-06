//
//  RoundWindowApp.h
//  axis
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 27/09/14.
//
//

//
//  RoundWindowFrameImpact.h
//  RoundWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//
#pragma once


#include "acme_notification_callback.h"


@interface macos_app : NSObject < NSApplicationDelegate >
{
@public

   ::platform::application *              m_papplication;
   
   NSMutableArray *                       m_windowcontrollera;
   
   acme_notification_callback *           m_pacmenotificationcallback;

}

-(void)application_menu_update;
-(NSWindowController *) addWindow:(NSWindow*)window;
-(void) removeWindowController:(NSWindowController*)pwindowcontroller;
-(void) continueInitialization;
-(void) show_about_box;
-(void) try_close_application;

@end
