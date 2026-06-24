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
class command_handler;

namespace appkit
{

class acme_window_bridge;

} // namespace appkit

@class ns_acme_window;


@interface macos_app : NSObject < NSApplicationDelegate >
{
@public
   
   
   NSMenu *                         m_menu;

   ::platform::application *              m_papplication;
   
   NSMutableArray *                       m_windowcontrollera;
   
   acme_notification_callback *           m_pacmenotificationcallback;
   ::application_menu *                   m_papplicationmenu;
   ::command_handler *                    m_pcommandhandler;
   BOOL                                   m_bApplicationMenuUpdatePending;
   BOOL                                   m_bApplicationDidFinishLaunching;
   NSInteger                              m_iMenuTrackingCount;

}

// A mutable array to manage and retain your active form dialogs
@property (nonatomic, strong) NSMutableArray<NSWindowController *> *activeDialogs;

-(ns_acme_window *) createMainFrame :(NSRect) r styleMask : (NSUInteger) style withAcmeWindowingWindow:(::acme::windowing::window *) pacmewindowingwindow withAcmeWindowBridge:(::appkit::acme_window_bridge*)pacmewindowbridge;
//-(void)application_menu_update;
-(NSWindowController *) addWindow:(NSWindow*)window;
-(::uptr) showDialog:(NSString*)strDialogName withAcmeWindowingWindow:(::acme::windowing::window*)pacmewindowingwindow;
-(::uptr) createOffscreenChildDialog:(NSString*)strDialogName withAcmeWindowingWindow:(::acme::windowing::window*)pacmewindowingwindow;
-(int)doModalDialog:(NSString *)strDialogName withAcmeWindowingWindow:(::acme::windowing::window*)pacmewindowingwindow;
-(void)doAttachedModalDialog:(NSString *)strDialogName
     withAcmeWindowingWindow: (::acme::windowing::window*)pacmewindowingwindow
parentWindow: (NSWindow *) pnswindowParent andCallback: (const ::function< void(int) > &) callback;
-(void) addDialog:(NSWindowController*)pwindowcontrollerDialog;
-(void) removeDialog:(NSWindowController*)pwindowcontrollerDialog;
-(void) addWindowController:(NSWindowController*)pwindowcontroller;
-(void) removeWindowController:(NSWindowController*)pwindowcontroller;
-(void) continueInitialization;
-(void) show_about_box;
-(void) try_close_application;
-(id) initWithApplicationMenu:(::application_menu *) papplicationmenu andCommandHandler: (::command_handler *) pcommandhandler;
-(void) setApplicationMenuNeedsUpdate;
-(void) application_menu_update;
-(void) application_handle: (::i64) l withPointer :(void *) p;

@end
