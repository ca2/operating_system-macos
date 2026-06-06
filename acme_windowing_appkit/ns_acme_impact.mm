//
//  nsview.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/02/22.
//  09:10
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
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
#include "acme_window_bridge.h"
#include "ns_acme_window.h"
#include "ns_acme_impact.h"
#include "acme/operating_system/macos/keyboard.h"
#include "acme/operating_system/winpr_input.h"
#include "acme/constant/user_key.h"
#include <Carbon/Carbon.h>


NSCursor * e_cursor_to_ns_cursor(::enum_cursor ecursor);

::user::enum_key key_code_to_user_key(unsigned int keyCode);
::user::e_key_state ns_pressed_buttons_to_e_button_state(unsigned int pressedButtons);

@implementation ns_acme_impact


- (id) initWithFrame: (NSRect) frame andBridge: (::appkit::acme_window_bridge *) pacmewindowbridge
{
   
   m_pnscursorImpact    = nil;

   self                 = [super initWithFrame:frame];
   
   
   m_pacmewindowbridgeImpact  = pacmewindowbridge;
   
   m_bLShift            = false;
   m_bRShift            = false;
   m_bLControl          = false;
   m_bRControl          = false;
   m_bLAlt              = false;
   m_bRAlt              = false;
   m_bLCommand          = false;
   m_bRCommand          = false;
   m_bOnCreate          = false;
   
   m_pnscursorImpact = [ NSCursor arrowCursor ];
   
   if (self)
   {
      
      m_ptrackingarea = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                                  options: (NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInKeyWindow )
                                                    owner:self userInfo:nil];
      [self addTrackingArea:m_ptrackingarea];
      
   }
   
   
   // Step 1: Enable notifications on the target view
   [self setPostsFrameChangedNotifications:YES];

   // Step 2: Register for the notification
   [[NSNotificationCenter defaultCenter] addObserver:self
                                            selector:@selector(viewDidResizeNotification:)
                                                name:NSViewFrameDidChangeNotification
                                              object:self];


   return self;
   
}

// Step 4: Don't forget to unregister in dealloc
- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

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



// Step 3: Handle the notification
- (void)viewDidResizeNotification:(NSNotification *)notification {
    NSView *view = (NSView *)notification.object;
    NSSize newSize = view.frame.size;
    NSLog(@"View frame changed: %f x %f", newSize.width, newSize.height);
   
   
   if(m_pacmewindowbridgeImpact)
   {
      
      m_pacmewindowbridgeImpact->on_size(newSize.width, newSize.height);
      
   }
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

   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
   if(p == NULL)
   {
      
      return;
      
   }

   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;
   
   auto pressedButtons = [ NSEvent pressedMouseButtons ];
   
   auto ebuttonstate = ns_pressed_buttons_to_e_button_state(pressedButtons);
 
   p->on_left_button_up(ebuttonstate, xHost, yHost, xAbsolute, yAbsolute);
   
}


//- (void)resetCursorRects
//{
//   
//   [super resetCursorRects];
//   
//   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
//   
//   if(p == NULL)
//   {
//      
//      return;
//      
//   }
//   
//   p->on_set_cursor_rectangles();
//
////   auto invisibleCursor =CreateInvisibleCursor();
////   
////   
////    [self addCursorRect:self.bounds
////                 cursor: invisibleCursor];
//}

- (void) mouseMoved: (NSEvent *) event
{

   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;
   
   NSLog(@"mouse move %d, %d", xHost, yHost);

   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;
   
   auto pressedButtons = [ NSEvent pressedMouseButtons ];
   
   auto ebuttonstate = ns_pressed_buttons_to_e_button_state(pressedButtons);

   p->on_mouse_move(ebuttonstate, xHost, yHost, xAbsolute, yAbsolute);
   
   if(m_pnscursorImpact)
   {
      
      [ m_pnscursorImpact set ];
      
   }
   
   return;
   
}


- (void) setMouseCursor : (::enum_cursor) ecursor
{
   
   auto pnscursor = e_cursor_to_ns_cursor(ecursor);
   
   m_pnscursorImpact = pnscursor;
   
}


- (void) mouseDragged: (NSEvent *) event
{

   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
   if(p == NULL)
   {

      return;
      
   }
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;

   auto pressedButtons = [ NSEvent pressedMouseButtons ];
   
   auto ebuttonstate = ns_pressed_buttons_to_e_button_state(pressedButtons);

   p->on_mouse_move(ebuttonstate, xHost, yHost, xAbsolute, yAbsolute);
   
}


- (void) mouseDown: (NSEvent *) event
{
   
   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;
   
   NSUInteger buttons =
       [NSEvent pressedMouseButtons];
   
   auto pressedButtons = [ NSEvent pressedMouseButtons ];
   
   auto ebuttonstate = ns_pressed_buttons_to_e_button_state(pressedButtons);

   p->on_left_button_down(ebuttonstate, xHost, yHost, xAbsolute, yAbsolute);
   
}


- (void) rightMouseUp: (NSEvent *) event
{

   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
   if(p == NULL)
   {
      
      return;
      
   }
    
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;

   auto pressedButtons = [ NSEvent pressedMouseButtons ];
   
   auto ebuttonstate = ns_pressed_buttons_to_e_button_state(pressedButtons);

   p->on_right_button_up(ebuttonstate, xHost, yHost, xAbsolute, yAbsolute);
   
}


- (void) rightMouseDown: (NSEvent *) event
{
   
   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   NSPoint pointHost = [self flippedLocationInWindow: event];
   
   int xHost = pointHost.x;
   
   int yHost = pointHost.y;

   NSPoint pointAbsolute = [self screenLocationEx: event];
   
   int xAbsolute = pointAbsolute.x;
   
   int yAbsolute = pointAbsolute.y;

   auto pressedButtons = [ NSEvent pressedMouseButtons ];
   
   auto ebuttonstate = ns_pressed_buttons_to_e_button_state(pressedButtons);

   p->on_right_button_down(ebuttonstate, xHost, yHost, xAbsolute, yAbsolute);
   
}


- (BOOL) isFlipped
{
   
   return YES;
   
}


- (BOOL) isOpaque
{
   
   return NO;
   
}



#define WINDOW_FRAME_PADDING 32

#define REDRAW_HINTING
#undef REDRAW_HINTING
//#define REDRAW_HINTING1
//#define REDRAW_HINTING2


- (void) drawRect: (NSRect) rect
{

   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   CGContextRef cgc = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];

#ifdef REDRAW_HINTING1
   
   {
      
      CGContextSetBlendMode(cgc, kCGBlendModeCopy);
      
      CGContextSetRGBFillColor(cgc, 10.f / 255.0f, 160.f / 255.0f, 255.f / 255.0f, 255.f / 255.0f);
      
      auto rectArtifact1 = rect;
      
      //rectArtifact1.size.width /= 4;
      
      //rectArtifact1.size.height /= 4;
      
      CGContextFillRect(cgc, rectArtifact1);
      
   }
   
#endif
   
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
   
   //auto rectFrame = [self frame];
   
   //p->_on_draw_frame(cgc, rectFrame.size);
   p->_on_draw_frame(cgc, rect);
   
#ifdef REDRAW_HINTING
   
   {
   
      CGContextSetBlendMode(cgc, kCGBlendModeCopy);

      CGContextSetRGBFillColor(cgc, 255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 155 / 255.0f);
      
      auto rectArtifact2 = rect;
      
      rectArtifact2.size.width /= 4;
      
      rectArtifact2.size.height /= 4;
      
      rectArtifact2.origin.x = rect.size.width - rectArtifact2.size.width;
      
      rectArtifact2.origin.y = rect.size.height - rectArtifact2.size.height;

      CGContextFillRect(cgc, rectArtifact2);
      
   }
   
#endif
   
#ifdef REDRAW_HINTING2
   
   {
      
      CGContextSetBlendMode(cgc, kCGBlendModeCopy);
      
      CGContextSetRGBFillColor(cgc, 10.f / 255.0f, 255.f / 255.0f, 160.f / 255.0f, 155.f / 255.0f);
      
      auto rectArtifact1 = rect;
      
      //rectArtifact1.size.width /= 4;
      
      //rectArtifact1.size.height /= 4;
      
      CGContextFillRect(cgc, rectArtifact1);
      
   }
   
#endif

   
}


- (BOOL)acceptsFirstResponder
{

   return TRUE;

}


- (BOOL) acceptsFirstMouse:(NSEvent *)theEvent
{
   
   if(![NSApp isActive])
   {
      
   }
   
//   if(![m_pacmewindowbridge isKeyWindow])
//   {
//      
//      [m_pacmewindowbridge makeKeyWindow];
//      
//   }
   
   return YES;
   
}


- (BOOL) mouseDownCanMoveWindow
{

   return NO;

}

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

   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
     
   if(p == NULL)
   {
      
      return;
      
   }
   
   if(event.isARepeat)
   {
      
      return;
      
   }
   
   const char * pszUtf8 = nullptr;
   
   if([[event characters] length ] > 0)
   {
   
      pszUtf8 = [[event characters] UTF8String];
   
   }
   
   NSEventModifierFlags flags =
           [event modifierFlags];

       bool ctrl =
           (flags & NSEventModifierFlagControl) != 0;

       bool alt =
           (flags & NSEventModifierFlagOption) != 0;

       bool shift =
           (flags & NSEventModifierFlagShift) != 0;

       bool fKey =
           (event.keyCode == kVK_ANSI_F);

       if (ctrl && alt && shift && fKey)
   //if (fKey)
       {
          p->toggle_fullscreen();
       }
   
   auto keyCode = [event keyCode];
   
   auto euserkey = key_code_to_user_key(keyCode);

//   if(keyCode == 0 && pszUtf8)
//   {
//      if(pszUtf8[0] >= 'a' && pszUtf8[0] <= 'z')
//      {
//         euserkey = (::user::enum_key) (::user::e_key_a + (pszUtf8[0] - 'a'));
//      }
//      else if(pszUtf8[0] >= '0' && pszUtf8[0] <= '9')
//      {
//         euserkey = (::user::enum_key) (::user::e_key_0 + (pszUtf8[0] - '0'));
//      }
//   }
   
   p->on_key_down(euserkey);
   
//
//   
//   DWORD keyCode;
//   
//   DWORD keyFlags = 0;
//   
//   DWORD vkcode;
//   
//   DWORD scancode;
   
//   keyCode = [event keyCode];
//   
//   vkcode = keyCode;
//      
//   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);
//
//   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
//   
//   char * pszUtf8 = nullptr;
//   
//   if(!apple_is_action_key(keyCode) && !(kbdModFlags &(NSControlKeyMask | NSCommandKeyMask|NSAlternateKeyMask)))
//   {
//   
//      if([[event characters] length ] > 0)
//      {
//      
//         pszUtf8 = strdup([[event characters] UTF8String]);
//      
//      }
//      else if(keyCode == kVK_Space)
//      {
//       
//         pszUtf8=strdup(" ");
//         
//      }
//      
//   }
//   else if(keyCode == kVK_Tab)
//   {
//    
//      pszUtf8 = strdup("\t");
//      
//   }
//   else if(keyCode == kVK_Return)
//   {
//    
//      pszUtf8 = strdup("\r");
//      
//   }
//   
//   if(pszUtf8)
//   {
//
//      int iUni = *pszUtf8;
//      
//      p->on_char(iUni);
//      
//      free(pszUtf8);
//      
//   }
   
}


- (void)keyUp:(NSEvent *)event
{
   
//   DWORD keyCode;
//   
//   DWORD keyFlags = 0;
//   
//   DWORD vkcode;
//   
//   DWORD scancode;
//   
//   NSString * characters;
   
   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   //keyCode = [event keyCode];
   
   const char * pszUtf8 = nullptr;
   
   if([[event characters] length ] > 0)
   {
   
      pszUtf8 = [[event characters] UTF8String];
   
   }

   auto keyCode = [event keyCode];
   ::user::e_key euserkey = ::user::e_key_none;
   
   if(keyCode == 0 && pszUtf8)
   {
      if(pszUtf8[0] >= 'a' && pszUtf8[0] <= 'z')
      {
         euserkey = (::user::e_key_a + (pszUtf8[0] - 'a'));
      }
      else if(pszUtf8[0] >= '0' && pszUtf8[0] <= '9')
      {
         euserkey = (::user::e_key_0 + (pszUtf8[0] - '0'));
      }
   }
   p->on_key_up(euserkey);

   
//   characters = [event charactersIgnoringModifiers];
//
//   vkcode = keyCode;
//
//   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);
//
//   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   
}


- (void)flagsChanged:(NSEvent *)event
{

   ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
   
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
   
   modFlags = [event modifierFlags] & NSDeviceIndependentModifierFlagsMask;
   
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
   
   kbdModFlags = modFlags;

}


- (void)viewWillMoveToWindow:(NSWindow *)newWindow
{
   
   if(!m_bOnCreate)
   {
      
      m_bOnCreate =true;
      
      ::appkit::acme_window_bridge * p = m_pacmewindowbridgeImpact;
        
      if(p == NULL)
      {
         
         return;
         
      }
      
      p->on_create();

      
   }
   
   NSTrackingArea *const trackingArea = [[NSTrackingArea alloc] initWithRect:NSZeroRect options:(NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveAlways | NSTrackingInVisibleRect) owner:self userInfo:nil];
   
   [self addTrackingArea:trackingArea];
   
   [self.window invalidateCursorRectsForView:self];
   
}


- (void)mouseEntered:(NSEvent *)theEvent
{

   [super mouseEntered:theEvent];

}


- (void)mouseExited:(NSEvent *)theEvent
{

   [super mouseExited:theEvent];

}


@end


unsigned int event_num_pad_key_code(NSEvent * event)
{

   NSString * arrow = [event charactersIgnoringModifiers];
   
   if([arrow length] == 1)
   {
      
      unichar key = [arrow characterAtIndex:0];
      
      if(key == NSLeftArrowFunctionKey)
      {
         
         return VK_LEFT; //::user::key_left;
         
      }
      else if(key == NSRightArrowFunctionKey)
      {
         
         return VK_RIGHT; //::user::key_right;
         
      }
      else if(key == NSUpArrowFunctionKey)
      {
         
         return VK_UP; // ::user::key_up;
         
      }
      else if(key == NSDownArrowFunctionKey)
      {
         
         return VK_DOWN; // ::user::key_down;
         
      }
      else if(key >= L'0' && key <= L'9')
      {
         
         //return 3000 + key - L'0';
         
         return 0;
         
      }
      
   }
   
   return 0;

}


unsigned int event_key_code(NSEvent * event)
{

   unsigned int uiModifierFlags = (unsigned int) [event modifierFlags];

   if(uiModifierFlags & NSNumericPadKeyMask)
   {

      return event_num_pad_key_code(event);
   
   }
   
   unsigned int uiKeyCode = [event keyCode];
 
   return uiKeyCode;
   
}



::user::enum_key key_code_to_user_key(unsigned int keyCode)
{
   
   ::user::enum_key euserkey = ::user::e_key_none;

   if(keyCode == kVK_ANSI_A)
   {
      
      euserkey = ::user::e_key_a;
      
   }
   else if(keyCode == kVK_ANSI_B)
   {
      
      euserkey = ::user::e_key_b;
      
   }
   else if(keyCode == kVK_ANSI_C)
   {
      
      euserkey = ::user::e_key_c;
      
   }
   else if(keyCode == kVK_ANSI_D)
   {
      
      euserkey = ::user::e_key_d;
      
   }
   else if(keyCode == kVK_ANSI_E)
   {
      
      euserkey = ::user::e_key_e;
      
   }
   else if(keyCode == kVK_ANSI_F)
   {
      
      euserkey = ::user::e_key_f;
      
   }
   else if(keyCode == kVK_ANSI_G)
   {
      
      euserkey = ::user::e_key_g;
      
   }
   else if(keyCode == kVK_ANSI_H)
   {
      
      euserkey = ::user::e_key_h;
      
   }
   else if(keyCode == kVK_ANSI_I)
   {
      
      euserkey = ::user::e_key_i;
      
   }
   else if(keyCode == kVK_ANSI_J)
   {
      
      euserkey = ::user::e_key_j;
      
   }
   else if(keyCode == kVK_ANSI_K)
   {
      
      euserkey = ::user::e_key_k;
      
   }
   else if(keyCode == kVK_ANSI_L)
   {
      
      euserkey = ::user::e_key_l;
      
   }
   else if(keyCode == kVK_ANSI_M)
   {
      
      euserkey = ::user::e_key_m;
      
   }
   else if(keyCode == kVK_ANSI_N)
   {
      
      euserkey = ::user::e_key_n;
      
   }
   else if(keyCode == kVK_ANSI_O)
   {
      
      euserkey = ::user::e_key_o;
      
   }
   else if(keyCode == kVK_ANSI_P)
   {
      
      euserkey = ::user::e_key_p;
      
   }
   else if(keyCode == kVK_ANSI_Q)
   {
      
      euserkey = ::user::e_key_q;
      
   }
   else if(keyCode == kVK_ANSI_R)
   {
      
      euserkey = ::user::e_key_r;
      
   }
   else if(keyCode == kVK_ANSI_S)
   {
      
      euserkey = ::user::e_key_s;
      
   }
   else if(keyCode == kVK_ANSI_T)
   {
      
      euserkey = ::user::e_key_t;
      
   }
   else if(keyCode == kVK_ANSI_U)
   {
      
      euserkey = ::user::e_key_u;
      
   }
   else if(keyCode == kVK_ANSI_V)
   {
      
      euserkey = ::user::e_key_v;
      
   }
   else if(keyCode == kVK_ANSI_W)
   {
      
      euserkey = ::user::e_key_w;
      
   }
   else if(keyCode == kVK_ANSI_X)
   {
      
      euserkey = ::user::e_key_x;
      
   }
   else if(keyCode == kVK_ANSI_Y)
   {
      
      euserkey = ::user::e_key_y;
      
   }
   else if(keyCode == kVK_ANSI_Z)
   {
      
      euserkey = ::user::e_key_z;
      
   }
   else if(keyCode == kVK_ANSI_0)
   {
      
      euserkey = ::user::e_key_0;
      
   }
   else if(keyCode == kVK_ANSI_1)
   {
      
      euserkey = ::user::e_key_1;
      
   }
   else if(keyCode == kVK_ANSI_2)
   {
      
      euserkey = ::user::e_key_2;
      
   }
   else if(keyCode == kVK_ANSI_3)
   {
      
      euserkey = ::user::e_key_3;
      
   }
   else if(keyCode == kVK_ANSI_4)
   {
      
      euserkey = ::user::e_key_4;
      
   }
   else if(keyCode == kVK_ANSI_5)
   {
      
      euserkey = ::user::e_key_5;
      
   }
   else if(keyCode == kVK_ANSI_6)
   {
      
      euserkey = ::user::e_key_6;
      
   }
   else if(keyCode == kVK_ANSI_7)
   {
      
      euserkey = ::user::e_key_7;
      
   }
   else if(keyCode == kVK_ANSI_8)
   {
      
      euserkey = ::user::e_key_8;
      
   }
   else if(keyCode == kVK_ANSI_9)
   {
      
      euserkey = ::user::e_key_9;
      
   }
   else if(keyCode == kVK_ANSI_Equal)
   {
      
      euserkey = ::user::e_key_equal;
      
   }
   else if(keyCode == kVK_ANSI_Minus)
   {
      
      euserkey = ::user::e_key_hyphen;
      
   }
   else if(keyCode == kVK_ANSI_RightBracket)
   {
      
      euserkey = ::user::e_key_right_bracket;
      
   }
   else if(keyCode == kVK_ANSI_LeftBracket)
   {
      
      euserkey = ::user::e_key_left_bracket;
      
   }
   else if(keyCode == kVK_ANSI_Quote)
   {
      
      euserkey = ::user::e_key_apostrophe;
      
   }
   else if(keyCode == kVK_ANSI_Semicolon)
   {
      
      euserkey = ::user::e_key_semicolon;
      
   }
   else if(keyCode == kVK_ANSI_Backslash)
   {
      
      euserkey = ::user::e_key_backslash;
      
   }
   else if(keyCode == kVK_ANSI_Comma)
   {
      
      euserkey = ::user::e_key_comma;
      
   }
   else if(keyCode == kVK_ANSI_Slash)
   {
      
      euserkey = ::user::e_key_slash;
      
   }
   else if(keyCode == kVK_ANSI_Period)
   {
      
      euserkey = ::user::e_key_slash;
      
   }
   else if(keyCode == kVK_ANSI_Slash)
   {
      
      euserkey = ::user::e_key_slash;
      
   }
   else if(keyCode == kVK_ANSI_Period)
   {
      
      euserkey = ::user::e_key_dot;
      
   }
   else if(keyCode == kVK_ANSI_Grave)
   {
      
      euserkey = ::user::e_key_grave;
      
   }
   else if(keyCode == kVK_Delete)
   {
      
      euserkey = ::user::e_key_back;
      
   }
   else if(keyCode == kVK_Return)
   {
      
      euserkey = ::user::e_key_return;
      
   }
   else if(keyCode == kVK_Escape)
   {
      
      euserkey = ::user::e_key_escape;
      
   }
   else if(keyCode == kVK_Tab)
   {
      
      euserkey = ::user::e_key_tab;
      
   }
   else
   {
    
      throw ::exception(error_unexpected_situation);
      
   }

   return euserkey;
   
}


NSCursor* CreateInvisibleCursor()
{
    NSImage* image =
        [[NSImage alloc]
            initWithSize:NSMakeSize(16, 16)];

    return [[NSCursor alloc]
        initWithImage:image
              hotSpot:NSZeroPoint];
}


NSCursor * g_pnscursorInvisible = nil;

NSCursor * e_cursor_to_ns_cursor(::enum_cursor ecursor)
{
   
   if(ecursor == e_cursor_none)
   {
      
      if(g_pnscursorInvisible == nil)
      {
         
         g_pnscursorInvisible = CreateInvisibleCursor();
         
      }
      
      return g_pnscursorInvisible;
      
   }
   else if(ecursor == e_cursor_arrow)
   {
    
      return [ NSCursor arrowCursor ];
      
   }
   else
   {
    
      return nil;
      
   }
   
}



