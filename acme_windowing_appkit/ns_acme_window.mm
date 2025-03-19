//
//  nswindow.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/02/22.
//  23:25
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include <Foundation/Foundation.h>
#include <AppKit/AppKit.h>
#include <Carbon/Carbon.h>
#include "ns_acme_window.h"
#include "acme_window_bridge.h"
#include "ns_acme_impact.h"
#import "macos_app.h"


void ns_main_post(dispatch_block_t block);

bool ns_app_is_running();
void ns_main_post(dispatch_block_t block);

void ns_main_send(dispatch_block_t block);

 
@implementation ns_acme_window : NSWindow


// rectangle.origin.x = left of rectangle
// rectangle.origin.y = bottom of rectangle
// origin of screen is at the bottom of screen
// top of rectangle is bigger numerically than the bottom
// and grows bigger from bottom as farther from bottom of screen.


- (id)initWithContentRect: (NSRect) rectangle styleMask: (NSUInteger) windowStyle backing:(NSBackingStoreType) bufferingType defer: (BOOL) deferCreation

{
   
   self = [ super
      initWithContentRect : rectangle
      styleMask : windowStyle // it was 0
      backing : bufferingType // it was  NSBackingStoreBuffered
      defer : deferCreation ]; // it was YES
   
   if(!self)
   {
      
      return nil;
      
   }
   
   [ self setOpaque : NO ];
   
   [ self setBackgroundColor: [ NSColor clearColor ] ];
      
   [ self setAcceptsMouseMovedEvents : YES ];
   
   [ self setLevel : NSNormalWindowLevel ];
   
   [ self setReleasedWhenClosed : NO ];
   
   [ self setIgnoresMouseEvents : NO ];
   
//   macos_app * papp = (macos_app *) [ [ NSApplication sharedApplication ] delegate ];
//   
//   m_pwindowcontroller = [ papp addWindow: self ];

   [ [ NSNotificationCenter defaultCenter ] addObserver: self selector: @selector(windowDidMove:) name: NSWindowDidMoveNotification object: self];

   [ [ NSNotificationCenter defaultCenter ] addObserver: self selector: @selector(windowDidResize:) name: NSWindowDidResizeNotification object: self];
   
   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidBecomeMain:) name: NSWindowDidBecomeMainNotification object: self];
   
   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidResignMain:) name: NSWindowDidResignMainNotification object: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidBecomeKey:) name: NSWindowDidBecomeKeyNotification object: self];
   
   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidResignKey:) name: NSWindowDidResignKeyNotification object: self];

   [ self create_impact ];
   
   return self;
   
}

-(void)setBridge:(::appkit::acme_window_bridge * ) pacmewindowbridge
{
 
   m_pacmewindowbridge = pacmewindowbridge;
   
}

-(void)dealloc
{
   
   m_pnsacmeimpact = nil;
   
   [ [ NSNotificationCenter defaultCenter ] removeObserver: self];

}
//
//- (BOOL)windowShouldClose:(NSWindow *)sender
//{
//   
//   return TRUE;
//   
//}

- (void)windowDidMove:(NSNotification *)notification
{
   
   NSRect rectFrame = [ self frame ];
   
   int x = rectFrame.origin.x;
   
   int y = (int) [[NSScreen mainScreen] frame].size.height - rectFrame.origin.y - rectFrame.size.height;
   
   int w = rectFrame.size.width;
   
   int h = rectFrame.size.height;
   
   m_pacmewindowbridge->on_layout(x, y, w, h);
   
}


- (void)windowDidResize:(NSNotification *)notification
{
   
   NSRect rectFrame = [ self frame ];
   
   int x = rectFrame.origin.x;
   
   int y = (int) [[NSScreen mainScreen] frame].size.height - rectFrame.origin.y - rectFrame.size.height;
   
   int w = rectFrame.size.width;
   
   int h = rectFrame.size.height;
   
   m_pacmewindowbridge->on_layout(x, y, w, h);
   
}


- (void)windowDidBecomeMain:(NSNotification *)aNotification
{
   
   printf("windowDidBecomeMain\n");
   
   m_pacmewindowbridge->macos_window_become_main();
   
}


- (void)windowDidResignMain:(NSNotification *)aNotification
{
   
   printf("windowDidResignMain\n");
   
   if(m_pacmewindowbridge)
   {
      
      m_pacmewindowbridge->macos_window_resign_main();
      
   }
   
}


- (void)windowDidBecomeKey:(NSNotification *)aNotification
{
   
   printf("windowDidBecomeKey\n");
   
   m_pacmewindowbridge->macos_window_become_key();
   
}


- (void)windowDidResignKey:(NSNotification *)aNotification
{
   
   printf("windowDidResignKey\n");
   
   if(m_pacmewindowbridge)
   {
      
      m_pacmewindowbridge->macos_window_resign_key();
      
   }
   
}


- (BOOL) canBecomeKeyWindow
{
   
   return YES;
   
}


- (BOOL) canBecomeMainWindow
{
   
   return YES;
   
}


- (BOOL) acceptsFirstResponder
{
   
   return YES;
   
}


- (BOOL) canBecomeFirstResponder
{
   
   return YES;
   
}


- (BOOL) resignFirstResponder
{
   
   return YES;
   
}


- (void)create_impact
{

   NSRect bounds = [ self frame ];
   
   bounds.origin = NSZeroPoint;

   m_pnsacmeimpact = [ [ ns_acme_impact alloc ] initWithFrame: bounds andWindow:self ];
   
   //m_pimpactChild = pimpact;
   
   [ super setContentView: m_pnsacmeimpact ];
   
   [ m_pnsacmeimpact setFrame: bounds ];
   
   [ m_pnsacmeimpact setAutoresizingMask: 0 ];
   
   //[ m_pnsacmeimpact display ];
   
}


-(int) control_box_right_when_at_left
{
   
   return -1;
   
}

@end



void * __nsacmewindow_osdata(CFTypeRef typeref)
{
 
   ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) typeref;
   
   NSWindow * pnswindow = (NSWindow *) pnsacmewindow;
   
   void * posdata = (__bridge_retained void *) pnswindow;
   
   return posdata;
   
}

