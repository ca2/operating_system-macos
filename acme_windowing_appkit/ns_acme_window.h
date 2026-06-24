//
//  nswindow.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 02/02/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#include <Cocoa/Cocoa.h>

namespace appkit
{
class acme_window_bridge;
}
@class ns_acme_impact;


@interface ns_acme_window : NSWindow
{
@public
   
   ::appkit::acme_window_bridge *      m_pacmewindowbridge;
   ns_acme_impact *                    m_pnsacmeimpact;
   //NSWindowController *       m_pwindowcontroller;
   bool m_bSavedFullscreen;
   NSWindowStyleMask m_savedStyleMask;
   NSRect m_savedFrame;
   NSInteger m_savedLevel;
}

//-(instancetype) init: (NSRect) rectangle;
- (id)initWithContentRect: (NSRect) rectangle styleMask: (NSUInteger) windowStyle backing:(NSBackingStoreType) bufferingType defer: (BOOL) deferCreation moreNative:(bool) bMoreNative;

-(void)setBridge:(::appkit::acme_window_bridge *) pacmewindowbridge;
- (void)create_impact;
- (void)windowDidBecomeKey:(NSNotification *)aNotification;
- (void)windowDidResignKey:(NSNotification *)aNotification;
-(int) control_box_right_when_at_left ;
-(void) enterImmersiveFullscreen;
-(void) exitImmersiveFullscreen;
-(bool) isInImmersiveFullscreen;
-(void) toggleImmersiveFullscreen;
- (void)minimizeWindowInstantly;
//-(void) add_cursor_rectangle:(NSRect) rect withCursor: (enum_cursor) ecursor;
@end
 
