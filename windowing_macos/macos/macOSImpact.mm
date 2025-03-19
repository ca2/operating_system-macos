//
//  RoundWindowFrameView.m
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
#include "framework.h"
#include "macOSImpact.h"
#include "macOSWindow.h"
#include "macOSControlBox.h"
#include "macos_window.h"
#include "macOSWindow.h"
#include <Carbon/Carbon.h>
#include "acme/operating_system/macos/keyboard.h"
#import "acme/operating_system/winpr_input.h"

//NSCursor * g_pcurrentNscursor = nullptr;
NSImage * ns_image_from_file(const char * pszMatter);
@implementation macOSImpact


- (id) initWithFrame: (NSRect) frame andWindow: (ns_acme_window *) pnsacmewindow
{
   m_pmacoscontrolbox = nullptr;
   m_ptrackingarea = nullptr;
   self                 = [super initWithFrame:frame andWindow:pnsacmewindow];
   
   //[self setWantsLayer : YES];
   //[self setLayerContentsRedrawPolicy: NSViewLayerContentsRedrawOnSetNeedsDisplay];
   
//   appleKeyboardType    = mac_detect_keyboard_type();
   
   //pnsmacoswindow          = (macOSWindow *) pnsacmewindow;
   
   m_bLShift            = false;
   m_bRShift            = false;
   m_bLControl          = false;
   m_bRControl          = false;
   m_bLAlt              = false;
   m_bRAlt              = false;
   m_bLCommand          = false;
   m_bRCommand          = false;
//   if (self) {
//      m_ptrackingarea = [[NSTrackingArea alloc] initWithRect:[self bounds]
//                                                  options: (NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInKeyWindow )
//                                                    owner:self userInfo:@{@"name": @"entire_client_area"}];
//      [self addTrackingArea:m_ptrackingarea];
//   }
//
   
   if(pnsacmewindow->m_pacmewindowbridge->should_use_desktop_ambient_like_control_box())
   {
      
      m_pmacoscontrolbox = [macOSControlBox alloc];
      
      [m_pmacoscontrolbox init: self];
      
   }

   //[ self createControlBoxButtons ];
   
   return self;
   
}



//
// resizeRect
//
// Returns the bounds of the resize box.
//
- (NSRect) resizeRect
{
   
	const CGFloat resizeBoxSize = 16.0;
   
	const CGFloat contentViewPadding = 5.5;
	
	NSRect contentViewRect = [[self window] contentRectForFrameRect:[[self window] frame]];
   
	NSRect resizeRect = NSMakeRect(
		NSMaxX(contentViewRect) + contentViewPadding,
		NSMinY(contentViewRect) - resizeBoxSize - contentViewPadding,
		resizeBoxSize,
		resizeBoxSize);
	
	return resizeRect;
   
}
- (NSPoint) screenLocationEx: (NSEvent *) event
{
   
   NSPoint point = [event locationInWindow];
   
   if([event window] != nil)
   {
      
      CGRect rectWindow = [[event window] frame];
      
      point.x += rectWindow.origin.x;
      
      point.y += rectWindow.origin.y;
      
   }
   
   point.y = (int) [[NSScreen mainScreen] frame].size.height - point.y;

   return point;
   
}


- (NSPoint) flippedLocationInWindow: (NSEvent *) event
{
   
   NSPoint point = [event locationInWindow];
   
   if([event window] != nil)
   {
      
      CGRect rectWindow = [[event window] frame];
      
      point.y = rectWindow.size.height - point.y - 1;
      
   }
   
   //point.y = (int) [[NSScreen mainScreen] frame].size.height - point.y;

   return point;
   
}


- (void) mouseUp: (NSEvent *) event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
      return;
    
   //NSPoint point = [event locationInWindow];
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;

   // Left Button
   
   int iButton = 0;
   
   NSInteger i = [event clickCount];
   
   if(i == 2)
   {

      p->macos_window_double_click(iButton, xHost, yHost, xAbsolute, yAbsolute);
      
   }
   
   p->macos_window_mouse_up(iButton, xHost, yHost, xAbsolute, yAbsolute);
   
}

-(void) resizeWithOldSuperviewSize:(NSSize)oldSize
{
   
   [super resizeWithOldSuperviewSize:oldSize];
   
   if(m_pmacoscontrolbox)
   {
      [m_pmacoscontrolbox layout];
      
   }
   

   
}

- (void) mouseMoved: (NSEvent *) event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
      return;
   
   //NSPoint point = [event locationInWindow];
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;
   
   p->macos_window_mouse_repositioned(xHost, yHost, xAbsolute, yAbsolute, [NSEvent pressedMouseButtons]);
   
   return;
   
}


- (void) mouseDragged: (NSEvent *) event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
      return;
   
   //NSPoint point = [event locationInWindow];
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;

   p->macos_window_mouse_dragged(xHost, yHost, xAbsolute, yAbsolute, [NSEvent pressedMouseButtons]);
   
}


//
// mouseDown:
//
// Handles mouse clicks in our frame. Two actions:
//	- click in the resize box should resize the window
//	- click anywhere else will drag the window.
//

///////////////////////////////
//
//   Left click only
//
- (void) mouseDown: (NSEvent *) event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;
   
   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
      return;
   
   //NSPoint point = [event locationInWindow];
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;
   // Left Button
   
   int iButton = 0;
   
   p->macos_window_mouse_down(iButton, xHost, yHost, xAbsolute, yAbsolute);
   
}


- (void)rightMouseUp:(NSEvent *)event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;
   
   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
      return;
   
   //NSPoint point = [event locationInWindow];
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;

   // Right Button
   
   int iButton = 1;
   
   p->macos_window_mouse_up(iButton, xHost, yHost, xAbsolute, yAbsolute);
   
}


- (void)rightMouseDown:(NSEvent *)event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;
   
   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
      return;
   
   //NSPoint point = [event locationInWindow];
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;
   // Right Button
   
   int iButton = 1;
   
   p->macos_window_mouse_down(iButton, xHost, yHost, xAbsolute, yAbsolute);
   
}


- (void)scrollWheel:(NSEvent *)event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;
   
   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   //NSPoint point = [event locationInWindow];
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;
   
   double delta = event.deltaY;
   
   p->macos_window_mouse_wheel(delta, xHost, yHost, xAbsolute, yAbsolute);
   
}


- (BOOL) isFlipped
{
   
   return YES;
   
}


- (BOOL) isOpaque
{
   
   return NO;
   
}


//- (BOOL) wantsUpdateLayer
//{
//
//   return YES;
//
//}



#define WINDOW_FRAME_PADDING 32

- (void)drawDebugRect:(NSRect)rect
{
   
   /*
    
    //   [super drawRect:rect];
    
    // return;
    
    BOOL bWindowVisible = [m_pmacoswindow isVisible];
    
    BOOL bViewHidden = [self isHidden];
    
    NSRect e = [m_pmacoswindow frame];
    
    NSRect e2 = [[NSScreen mainScreen] frame];
    
    double a = [m_pmacoswindow alphaValue];
    
    CGContextRef cgc1 = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];
    
    COLORREF cr = argb(255, 0, 0, 0);
    
    CGContextSetBlendMode(cgc1, kCGBlendModeCopy);
    
    CGContextSetRGBFillColor(cgc1, argb_get_r_value(cr) / 255.0f, argb_get_g_value(cr) / 255.0f, argb_get_b_value(cr) / 255.0f, argb_get_a_value(cr) / 255.0f);
    
    CGContextFillRect(cgc1, rect);
    
    //   [[NSColor greenColor] set];
    
    //   NSRectFill(rect);
    
    return;
    
    */
   
   /*
    
    [[NSColor clearColor] set];
    
    NSRectFill(rect);
    
    NSBezierPath * rectPath = [NSBezierPath bezierPathWithRect : [self bounds]];
    
    NSGradient * gradient = [[NSGradient alloc] initWithColorsAndLocations : [NSColor whiteColor], (CGFloat) 0.0, [NSColor lightGrayColor], (CGFloat)1.0, nil];
    
    [gradient drawInBezierPath : rectPath angle:90];
    
    [[NSColor whiteColor] set];
    [rectPath stroke];
    
    NSRect resizeRect = [self resizeRect];
    NSBezierPath *resizePath = [NSBezierPath bezierPathWithRect:resizeRect];
    
    [[NSColor lightGrayColor] set];
    [resizePath fill];
    
    [[NSColor darkGrayColor] set];
    [resizePath stroke];
    
    
    [[NSColor blackColor] set];
    NSString *windowTitle = [[self window] title];
    NSRect titleRect = [self bounds];
    titleRect.origin.y = titleRect.size.height - (WINDOW_FRAME_PADDING - 7);
    titleRect.size.height = (WINDOW_FRAME_PADDING - 7);
    NSMutableParagraphStyle *paragraphStyle =
    [[NSMutableParagraphStyle alloc] init];
    [paragraphStyle setAlignment:NSCenterTextAlignment];
    [windowTitle
    drawWithRect:titleRect
    options:0
    attributes:[NSDictionary
    dictionaryWithObjectsAndKeys:
				paragraphStyle, NSParagraphStyleAttributeName,
				[NSFont systemFontOfSize:14], NSFontAttributeName,
    nil]];
    
    
    return; */

}

//- (void) updateLayer
//{
//
//
//}


//
// drawRect:
//
// Draws the frame of the window.
//

#define REDRAW_HINTING
#undef REDRAW_HINTING

- (void) drawRect: (NSRect) rect
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   p->profiling_on_start_draw_rectangle();
//#define REDRAW_HINTING
   CGContextRef cgc = nullptr;
   if (@available(macOS 10.10, *))
   {
         cgc = (CGContextRef) [[NSGraphicsContext currentContext] CGContext];
      
   }
   else
   {
      cgc = (__bridge_retained CGContextRef) [NSGraphicsContext currentContext];

   }
      
#ifdef REDRAW_HINTING
      
      {
         
         CGContextSetBlendMode(cgc, kCGBlendModeCopy);
         
         CGContextSetRGBFillColor(cgc, 255 / 255.0f, 200 / 255.0f, 0 / 255.0f, 155 / 255.0f);
         
         auto rectArtifact1 = rect;
         
         rectArtifact1.size.width /= 4;
         
         rectArtifact1.size.height /= 4;
         
         CGContextFillRect(cgc, rectArtifact1);
         
      }
      
#endif
      
      auto rectFrame = [self frame];
      
      p->macos_window_draw(cgc, rectFrame.size);

   
   p->profiling_on_end_draw_rectangle();
   
#ifdef REDRAW_HINTING
   
   {
   
      CGContextSetBlendMode(cgc, kCGBlendModeCopy);

      CGContextSetRGBFillColor(cgc, 255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 155 / 255.0f);
      
      auto rectArtifact2 = rect;
      
      rectArtifact2.size.width /= 4;
      
      rectArtifact2.size.height /= 4;
      
      //rectArtifact2.origin.x = rect.size.width - rectArtifact2.size.width;
      
      rectArtifact2.origin.y = rect.size.height - rectArtifact2.size.height;

      CGContextFillRect(cgc, rectArtifact2);
      
   }
    {
    
       CGContextSetBlendMode(cgc, kCGBlendModeCopy);

       CGContextSetRGBFillColor(cgc, 0.4f, 0.f, 0.f, 8.f / 255.f);
       
       auto rectArtifact2 = rect;
       
       rectArtifact2.size.width /= 4;
       
       rectArtifact2.size.height /= 4;
       
       rectArtifact2.origin.x = rect.size.width - rectArtifact2.size.width;
       
       rectArtifact2.origin.y = rect.size.height - rectArtifact2.size.height;

       CGContextFillRect(cgc, rectArtifact2);
       
    }

#endif
   
   [ super drawRect : rect ];
   
}


- (BOOL)acceptsFirstResponder
{

   return TRUE;

}


- (BOOL) acceptsFirstMouse:(NSEvent *)theEvent
{

//printf("\nacceptsFirstMouse\n");
   
   if(![NSApp isActive])
   {
      
      //[NSApp ];
      
   }
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;
   
   if(![pnsmacoswindow isKeyWindow])
   {
      
      [pnsmacoswindow makeKeyWindow];
      
   }
   
//   if(![m_pmacoswindow isMainWindow])
//   {
//
//      [m_pmacoswindow makeMainWindow];
//
//   }
//   
//   if([[NSApp orderedWindows] firstObject] != m_pmacoswindow)
//   {
//   
//      [m_pmacoswindow orderFront:self];
//      
//   }

   return YES;
   
}


- (BOOL) mouseDownCanMoveWindow
{

   return NO;

}

//
//// from RoundWindow.mm
//
///*- (BOOL) acceptsFirstResponder
//{
//   if(m_bNoActivate)
//      return NO;
//   else
//      return YES;
//}*/
//
//- (BOOL) becomeFirstResponder
//{
//   return YES;
//}
////   if(m_bNoActivate)
//  //    return NO;
//  // else
//  // {
//      
//      //      m_pmacoswindow->macos_window_on_become_first_responder();
//      
//    //  return YES;
//      
//  // }
////}
//
////- (BOOL) resignFirstResponder
////{
////   return YES;
////   //if(m_bNoActivate)
////     // return YES;
////   //else
////  //    return YES;
////   
////}
//

#define DO_FLAG(m_f, p, now, key) \
if(m_f) \
{ \
if(!now) \
{ \
p->macos_window_key_up(key); \
m_f = false; \
} \
} \
else \
{ \
if(now) \
{ \
p->macos_window_key_down(key); \
m_f = true; \
} \
}

- (void)keyDown:(NSEvent *)event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
     
   if(p == NULL)
   {
      
      return;
      
   }
   
   if(event.isARepeat)
   {
      
      return;
      
   }
   
   DWORD keyCode;
   
   DWORD keyFlags = 0;
   
   DWORD vkcode;
   
   DWORD scancode;
   
   //unichar keyChar;
   
   keyCode = [event keyCode];
   
   
//   char sz[1024];
//   char szFormat[1024];
//
//   strcpy(sz, "");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "-----------------------------------------------------------------------------\n");
//   sprintf(szFormat, "RoundWindowFrameView::keyDown : %s\n", [characters UTF8String]);
//   ansi_concatenate(sz, szFormat);
//   ansi_concatenate(sz, "-----------------------------------------------------------------------------\n");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "\n");
//
//   printf("%s", sz);
   
//   if ([characters length] > 0)
//   {
//
//      keyChar = [characters characterAtIndex:0];
//
//      keyCode = fixKeyCode(keyCode, keyChar, appleKeyboardType);
//
//   }
   
   //vkcode = GetVirtualKeyCodeFromKeycode(keyCode + 8, KEYCODE_TYPE_APPLE);
   
   vkcode = keyCode;
      
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);

   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   
   char * pszUtf8 = nullptr;
   
   if(!apple_is_action_key(keyCode) && !(kbdModFlags &(NSEventModifierFlagControl | NSEventModifierFlagCommand|NSEventModifierFlagOption)))
   {
   
      if([[event characters] length ] > 0)
      {
      
         pszUtf8 = strdup([[event characters] UTF8String]);
      
      }
      else if(keyCode == kVK_Space)
      {
       
         pszUtf8=strdup(" ");
         
      }
      
      
   }
   
   //bool bRet = p->macos_window_key_down(vkcode, scancode, pszUtf8);
   
   p->macos_window_key_down(vkcode, scancode, pszUtf8);
   
   if(pszUtf8)
   {
      
      free(pszUtf8);
      
   }
   
}


- (void)keyUp:(NSEvent *)event
{
   
   DWORD keyCode;
   
   DWORD keyFlags = 0;
   
   DWORD vkcode;
   
   DWORD scancode;
   
   //unichar keyChar;
   
   NSString * characters;
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;
   
   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   keyCode = [event keyCode];
   
   characters = [event charactersIgnoringModifiers];
   
//   char sz[1024];
//   char szFormat[1024];
//
//   strcpy(sz, "");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "-----------------------------------------------------------------------------\n");
//   sprintf(szFormat, "RoundWindowFrameView::keyUp : %s\n", [characters UTF8String]);
//   ansi_concatenate(sz, szFormat);
//   ansi_concatenate(sz, "-----------------------------------------------------------------------------\n");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "\n");
//
//   printf("%s", sz);
   
//   if ([characters length] > 0)
//   {
//      
//      keyChar = [characters characterAtIndex:0];
//      
//      keyCode = fixKeyCode(keyCode, keyChar, appleKeyboardType);
//      
//   }
   
   //vkcode = GetVirtualKeyCodeFromKeycode(keyCode + 8, KEYCODE_TYPE_APPLE);
   
   vkcode = keyCode;
      
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);

   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   
   //bool bRet = p->macos_window_key_up(vkcode, scancode);
   
   p->macos_window_key_up(vkcode, scancode);

}


- (void)flagsChanged:(NSEvent *)event
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
   
   if(p == NULL)
   {
      
      printf("flags_changed(0)\n");
      
      [super flagsChanged:event];
      
      return;
      
   }
   
   int key;
   
   DWORD keyFlags = 0;
   
   DWORD vkcode;
   
   DWORD scancode;
   
   DWORD modFlags;
   
   key = [event keyCode] + 8;
   
   modFlags = [event modifierFlags] & NSEventModifierFlagDeviceIndependentFlagsMask;
   
   vkcode = GetVirtualKeyCodeFromKeycode(key, KEYCODE_TYPE_APPLE);
   
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);
   
   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   
   scancode &= 0xFF;
   
   vkcode &= 0xFF;
   
#if 0
   
   if (modFlags & NSAlphaShiftKeyMask)
      printf("NSAlphaShiftKeyMask");
   
   if (modFlags & NSShiftKeyMask)
      printf("NSShiftKeyMask");
   
   if (modFlags & NSControlKeyMask)
      printf("NSControlKeyMask");
   
   if (modFlags & NSAlternateKeyMask)
      printf("NSAlternateKeyMask");
   
   if (modFlags & NSCommandKeyMask)
      printf("NSCommandKeyMask");
   
   if (modFlags & NSNumericPadKeyMask)
      printf("NSNumericPadKeyMask");
   
   if (modFlags & NSHelpKeyMask)
      printf("NSHelpKeyMask");
   
#endif
   
//   const char * pszUtf8 = nullptr;
//
//   if(event.characters && event.characters.length > 0)
//   {
//
//      pszUtf8 = [[event characters] UTF8String];
//
//   }

   if ((modFlags & NSEventModifierFlagCapsLock) && !(kbdModFlags & NSEventModifierFlagCapsLock))
      p->macos_window_key_down(vkcode, scancode, nullptr);
   else if (!(modFlags & NSEventModifierFlagCapsLock) && (kbdModFlags & NSEventModifierFlagCapsLock))
      p->macos_window_key_up(vkcode, scancode);
   
   if ((modFlags & NSEventModifierFlagShift) && !(kbdModFlags & NSEventModifierFlagShift))
      p->macos_window_key_down(kVK_Shift, scancode, nullptr);
   else if (!(modFlags & NSEventModifierFlagShift) && (kbdModFlags & NSEventModifierFlagShift))
      p->macos_window_key_up(kVK_Shift, scancode);
   
   if ((modFlags & NSEventModifierFlagControl) && !(kbdModFlags & NSEventModifierFlagControl))
      p->macos_window_key_down(kVK_Control, scancode, nullptr);
   else if (!(modFlags & NSEventModifierFlagControl) && (kbdModFlags & NSEventModifierFlagControl))
      p->macos_window_key_up(kVK_Control, scancode);
   
   if ((modFlags & NSEventModifierFlagOption) && !(kbdModFlags & NSEventModifierFlagOption))
      p->macos_window_key_down(kVK_Option, scancode, nullptr);
   else if (!(modFlags & NSEventModifierFlagOption) && (kbdModFlags & NSEventModifierFlagOption))
      p->macos_window_key_up(kVK_Option, scancode);
   
   if ((modFlags & NSEventModifierFlagCommand) && !(kbdModFlags & NSEventModifierFlagCommand))
      p->macos_window_key_down(kVK_Command, scancode, nullptr);
   else if (!(modFlags & NSEventModifierFlagCommand) && (kbdModFlags & NSEventModifierFlagCommand))
      p->macos_window_key_up(kVK_Command, scancode);
   
   if ((modFlags & NSEventModifierFlagNumericPad) && !(kbdModFlags & NSEventModifierFlagNumericPad))
      p->macos_window_key_down(vkcode, scancode, nullptr);
   else if (!(modFlags & NSEventModifierFlagNumericPad) && (kbdModFlags & NSEventModifierFlagNumericPad))
      p->macos_window_key_up(vkcode, scancode);
   
   if ((modFlags & NSEventModifierFlagHelp) && !(kbdModFlags & NSEventModifierFlagHelp))
      p->macos_window_key_down(vkcode, scancode, nullptr);
   else if (!(modFlags & NSEventModifierFlagHelp) && (kbdModFlags & NSEventModifierFlagHelp))
      p->macos_window_key_up(vkcode, scancode);
   
   kbdModFlags = modFlags;

   // [super flagsChanged:event];
   
}

- (void)viewWillMoveToWindow:(NSWindow *)newWindow
{
   
   if(m_ptrackingarea)
   {
      
      [ self removeTrackingArea : m_ptrackingarea ];
      
      m_ptrackingarea = nil;
      
   }
   
   m_ptrackingarea = [ [NSTrackingArea alloc] initWithRect:NSZeroRect options:(NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveAlways | NSTrackingInVisibleRect) owner:self userInfo:nil];
   
   [ self addTrackingArea : m_ptrackingarea ];
   
   [ self.window invalidateCursorRectsForView : self ];
   
}


- (void)resetCursorRects
{

   [super resetCursorRects];
   
   NSCursor * pcursor = nullptr;
   
   auto pnsmacoswindow = (macOSWindow *) m_pnsacmewindow;
   
   if(pnsmacoswindow)
   {
      
      auto pmacoswindow = pnsmacoswindow->m_pmacoswindow;
      
      if(pmacoswindow)
      {
         
         pcursor = (__bridge NSCursor *) pmacoswindow->macos_window_get_mouse_cursor();
         
      }
      
   }
   
   [self addCursorRect:self.bounds cursor: pcursor ];
   
}


- (void)mouseEntered:(NSEvent *)event
{
   
   if(m_pmacoscontrolbox)
   {
      
      if( event.trackingArea == m_pmacoscontrolbox->m_ptrackingareaControlBox)
      {
         
         [ m_pmacoscontrolbox set_hover ];
         
      }
      
   }

   [super mouseEntered:event];

}


- (void)mouseExited:(NSEvent *)event
{
   
   //[g_pcurrentNscursor pop];
//   if(m_pmacoscontrolbox)
//   {
//      
//
//   if(event.trackingArea == m_ptrackingareaControlBox)
//   {
//
//      [ self setControlBoxNormalImages ];
//      
//   }

   [ super mouseExited: event ];

}
-(int) control_box_right_when_at_left
{
   
   if(!m_pmacoscontrolbox)
   {
      
      return -1;
      
   }
   
   return m_pmacoscontrolbox->m_rightControlBox;
   
}
-(macOSControlBox*)control_box
{
   
   return m_pmacoscontrolbox;
   
}

-(void)window_did_become_key :(macOSWindow *) pmacoswindow withNotification:(NSNotification*) notification
{
   if(m_pmacoscontrolbox)
   {
    
      [ m_pmacoscontrolbox set_normal ];
      
   }
   
}

-(void)window_did_resign_key :(macOSWindow *) pmacoswindow withNotification:(NSNotification*) notification
{
   if(m_pmacoscontrolbox)
   {
    
      [ m_pmacoscontrolbox set_not_key ];
      
   }
   
}

@end

