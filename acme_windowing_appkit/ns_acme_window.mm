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

NSCursor* CreateInvisibleCursor();

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


- (id)initWithContentRect: (NSRect) rectangle styleMask: (NSUInteger) windowStyle backing:(NSBackingStoreType) bufferingType defer: (BOOL) deferCreation moreNative:(bool)bMoreNative

{
   
   m_bSavedFullscreen = false;
   
   self = [ super
      initWithContentRect : rectangle
      styleMask : windowStyle // it was 0
      backing : bufferingType // it was  NSBackingStoreBuffered
      defer : deferCreation ]; // it was YES
   
   if(!self)
   {
      
      return nil;
      
   }
   
   if(!bMoreNative)
   {
      
      [ self setOpaque : NO ];
      
      [ self setBackgroundColor: [ NSColor clearColor ] ];
      
   }
   
   self.styleMask |= NSWindowStyleMaskMiniaturizable;
      
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

   //[ self create_impact ];
   
   return self;
   
}

-(void)setBridge:(::appkit::acme_window_bridge * ) pacmewindowbridge
{
 
   m_pacmewindowbridge = pacmewindowbridge;
   
   // Get the window number (NSInteger) from the NSWindow object.
   NSWindow * pnswindow = self;

   // Cast the NSInteger to CGWindowID.
   auto p = (__bridge void *) pnswindow;
   
   m_pacmewindowbridge->set_ns_window_uptr((::uptr) p);
   
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
   
   //int w = rectFrame.size.width;
   
   //int h = rectFrame.size.height;
   
   //m_pacmewindowbridge->on_layout(x, y, w, h);
   
   m_pacmewindowbridge->on_move(x, y);
   
}


- (void)windowDidResize:(NSNotification *)notification
{
   
   NSRect rectFrame = [ self frame ];
   
   //int x = rectFrame.origin.x;
   
   //int y = (int) [[NSScreen mainScreen] frame].size.height - rectFrame.origin.y - rectFrame.size.height;
   
   int w = rectFrame.size.width;
   
   int h = rectFrame.size.height;
   
   //m_pacmewindowbridge->on_layout(x, y, w, h);
   
   m_pacmewindowbridge->on_size(w, h);
   
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

   m_pnsacmeimpact = [ [ ns_acme_impact alloc ] initWithFrame: bounds andBridge:m_pacmewindowbridge ];
   
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

-(void) enterImmersiveFullscreen
{
   
   if(m_bSavedFullscreen)
   {
    
      return;
      
   }
   m_bSavedFullscreen = true;
   m_savedStyleMask = [self styleMask];
   m_savedFrame = [self frame];
   m_savedLevel = [self level];
   
   NSRect screenRect =
       [[NSScreen mainScreen] frame];
   //screenRect.size.width /=2;
   //screenRect.size.height /=2;

   [self setStyleMask:
       NSWindowStyleMaskBorderless];

   [self setFrame:screenRect
            display:YES];

   //[self setLevel:NSMainMenuWindowLevel + 1];
   [self setLevel:NSNormalWindowLevel];
   
//#if !_DEBUG
   [NSApp setPresentationOptions:
       NSApplicationPresentationHideDock |
       NSApplicationPresentationHideMenuBar];
///#endif

   
}

-(void) exitImmersiveFullscreen
{
   
   if(!m_bSavedFullscreen)
   {
    
      return;
      
   }
   m_bSavedFullscreen = false;
   [self setStyleMask:
       m_savedStyleMask];

   [self setLevel:
       m_savedLevel];

   [self setFrame:
       m_savedFrame
            display:YES];
   [NSApp setPresentationOptions:
       NSApplicationPresentationDefault];
   

}
-(bool) isInImmersiveFullscreen
{
   
   return m_bSavedFullscreen;
   
}

-(void) toggleImmersiveFullscreen
{
   
   if(m_bSavedFullscreen)
   {
      
      [self exitImmersiveFullscreen];
      
   }
   else
   {
    
      [ self enterImmersiveFullscreen];
      
   
   }
   
}

//-(void) add_cursor_rectangle:(NSRect)rect withCursor:(enum_cursor)ecursor
//{
//   
//   auto pimpact = [self contentView];
//   
//   if(pimpact)
//   {
//      
//      NSCursor * pnscursor = nil;
//      
//      if(ecursor == ::e_cursor_none)
//      {
//      
//         pnscursor = CreateInvisibleCursor();
//      
//      }
//      else if(ecursor == ::e_cursor_arrow)
//      {
//         
//         pnscursor = [NSCursor arrowCursor];
//         
//      }
//      
//      if(pnscursor)
//      {
//         
////         NSRect nsrect;
////         
////         nsrect.origin.x = cgrect.left;
////         nsrect.origin.y = r.top;
////         nsrect.size.width = r.width();
////         nsrect.size.height = r.height();
//         
//         [pimpact addCursorRect:rect cursor: pnscursor];
//         
//      }
//      
//   }
//
//}

- (void)minimizeWindowInstantly{
   
   NSWindow * window = self;
//    // 1. Store the original animation behavior configuration
//    NSWindowAnimationBehavior originalBehavior = window.animationBehavior;
//    
//    // 2. Kill the animations for this window
//    window.animationBehavior = NSWindowAnimationBehaviorNone;
    
    // 3. Minimize the window to the Dock instantly
    //[window orderOut:nil];
   [NSApp hide:nil];
    
    // 4. Restore original animation behavior for future window restorations
    //window.animationBehavior = originalBehavior;
}


@end



void * __nsacmewindow_osdata(CFTypeRef typeref)
{
 
   ns_acme_window * pnsacmewindow = (__bridge ns_acme_window *) typeref;
   
   NSWindow * pnswindow = (NSWindow *) pnsacmewindow;
   
   void * posdata = (__bridge_retained void *) pnswindow;
   
   return posdata;
   
}

