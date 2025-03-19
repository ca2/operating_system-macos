//
//  macOSControlBox.mm
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2025-03-19.
//  Copyright © 2025 ca2 Software Development. All rights reserved.
//

#include "framework.h"
#include "_mm.h"
#include "macOSControlBox.h"
#include "macOSImpact.h"
@implementation macOSControlBox
-(void)init:(macOSImpact*)pmacosimpact
{
   m_pmacosimpact = pmacosimpact;
   m_ptrackingareaControlBox = nullptr;

   
      m_leftControlBox = 5;
      m_topControlBox = 5;
      m_wControlBoxButton = 12;
      m_hControlBoxButton = 12;
      m_rightControlBox = m_leftControlBox + 12 + 10 + 12 + 10 + 12;
      m_bottomControlBox = m_topControlBox + 12;
      m_paddingControlBox = 6;

   NSRect frame = m_pmacosimpact.frame;
      //CGFloat y = frame.size.height - buttonSize - padding;
      CGFloat y = m_topControlBox;
      CGFloat x = m_leftControlBox;
      m_pnsimageNotKey = ns_image_from_file("matter://macos/not_key.png");

      m_pnsimageNormalClose = ns_image_from_file("matter://macos/close_normal.png");
      m_pnsimageNormalMinimize = ns_image_from_file("matter://macos/minimize_normal.png");
      m_pnsimageNormalZoom = ns_image_from_file("matter://macos/zoom_normal.png");
      m_pnsimageHoverClose = ns_image_from_file("matter://macos/close_hover.png");
      m_pnsimageHoverMinimize = ns_image_from_file("matter://macos/minimize_hover.png");
      m_pnsimageHoverZoom = ns_image_from_file("matter://macos/zoom_hover.png");
      
      
      // Create Close Button
      m_pnsbuttonClose = [[NSButton alloc] initWithFrame:NSMakeRect(x, y, m_wControlBoxButton, m_hControlBoxButton)];
      m_pnsbuttonClose.bezelStyle = NSBezelStyleCircular;
      m_pnsbuttonClose.buttonType = NSButtonTypeMomentaryPushIn;
      m_pnsbuttonClose.bordered = NO;
      m_pnsbuttonClose.wantsLayer = YES;
      //closeButton.layer.backgroundColor = [[NSColor redColor] CGColor];
      m_pnsbuttonClose.target = self;
      
      m_pnsbuttonClose.imageScaling = NSImageScaleNone; // Prevent automatic resizing
      m_pnsbuttonClose.action = @selector(on_control_box_close:);
      
   //   {
   //      NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:m_pnsbuttonClose.bounds
   //                                                                  options:(NSTrackingMouseEnteredAndExited | NSTrackingActiveInKeyWindow)
   //                                                                    owner:self
   //                                                                 userInfo:@{@"button": m_pnsbuttonClose}];
   //      [m_pnsbuttonClose addTrackingArea:trackingArea];
   //
   //   }
      // Create Minimize Button
      m_pnsbuttonMinimize = [[NSButton alloc] initWithFrame:NSMakeRect(x + m_pnsbuttonClose.frame.size.width + m_paddingControlBox, y, m_wControlBoxButton, m_hControlBoxButton)];
      m_pnsbuttonMinimize.bezelStyle = NSBezelStyleCircular;
      m_pnsbuttonMinimize.buttonType = NSButtonTypeMomentaryPushIn;
      m_pnsbuttonMinimize.bordered = NO;
      m_pnsbuttonMinimize.wantsLayer = YES;
      //minimizeButton.layer.backgroundColor = [[NSColor yellowColor] CGColor];
      m_pnsbuttonMinimize.imageScaling = NSImageScaleNone; // Prevent automatic resizing
      
      m_pnsbuttonMinimize.target = self;
      m_pnsbuttonMinimize.action = @selector(on_control_box_minimize:);
      
   //   {
   //   NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:m_pnsbuttonMinimize.bounds
   //                                                               options:(NSTrackingMouseEnteredAndExited | NSTrackingActiveInKeyWindow)
   //                                                                 owner:self
   //                                                              userInfo:@{@"button": m_pnsbuttonMinimize}];
   //   [m_pnsbuttonMinimize addTrackingArea:trackingArea];
   //
   //}
       // Create Maximize Button
      m_pnsbuttonZoom = [[NSButton alloc] initWithFrame:NSMakeRect(x + m_pnsbuttonClose.frame.size.width + m_paddingControlBox+m_pnsbuttonMinimize.frame.size.width + m_paddingControlBox
                                                                   , y, m_wControlBoxButton, m_hControlBoxButton)];
      m_pnsbuttonZoom.bezelStyle = NSBezelStyleCircular;
      m_pnsbuttonZoom.buttonType = NSButtonTypeMomentaryPushIn;
      m_pnsbuttonZoom.bordered = NO;
      m_pnsbuttonZoom.wantsLayer = YES;
      

       //zoomButton.layer.backgroundColor = [[NSColor greenColor] CGColor];
      m_pnsbuttonZoom.target = self;
      m_pnsbuttonZoom.action = @selector(on_control_box_zoom:);
      m_pnsbuttonZoom.imageScaling = NSImageScaleNone; // Prevent automatic resizing
      
   //   {
   //      NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:m_pnsbuttonZoom.bounds
   //                                                                  options:(NSTrackingMouseEnteredAndExited | NSTrackingActiveInKeyWindow)
   //                                                                    owner:self
   //                                                                 userInfo:@{@"button": m_pnsbuttonZoom}];
   //      [m_pnsbuttonZoom addTrackingArea:trackingArea];
   //
   //   }
      

      // Add a single tracking area
      [self layout ];
      
      [self set_not_key];
      
      // Add buttons to the window's content view
      [m_pmacosimpact addSubview:m_pnsbuttonClose];
      
      [m_pmacosimpact addSubview:m_pnsbuttonMinimize];
      
   [m_pmacosimpact addSubview:m_pnsbuttonZoom];
      
   
   
}
- (void)set_not_key
{
   m_pnsbuttonClose.image = m_pnsimageNotKey;
   m_pnsbuttonMinimize.image = m_pnsimageNotKey;
   m_pnsbuttonZoom.image = m_pnsimageNotKey;
}



- (void)set_normal {
   m_pnsbuttonClose.image = m_pnsimageNormalClose;
   m_pnsbuttonMinimize.image = m_pnsimageNormalMinimize;
   m_pnsbuttonZoom.image = m_pnsimageNormalZoom;
}



- (void)set_hover {
   m_pnsbuttonClose.image = m_pnsimageHoverClose;
   m_pnsbuttonMinimize.image = m_pnsimageHoverMinimize;
   m_pnsbuttonZoom.image = m_pnsimageHoverZoom;
}

- (void)layout {
   
   
    //NSButton *closeButton = [self standardWindowButton:NSWindowCloseButton];
    //NSButton *minimizeButton = [self standardWindowButton:NSWindowMiniaturizeButton];
    //NSButton *zoomButton = [self standardWindowButton:NSWindowZoomButton];

   NSRect frame = m_pmacosimpact.frame;
   CGFloat y = m_topControlBox;
   CGFloat x = m_leftControlBox;

   m_pnsbuttonClose.frame = NSMakeRect(x, y, m_pnsbuttonClose.frame.size.width, m_pnsbuttonClose.frame.size.height);
   m_pnsbuttonMinimize.frame = NSMakeRect(x + m_pnsbuttonClose.frame.size.width + m_paddingControlBox, y, m_pnsbuttonMinimize.frame.size.width, m_pnsbuttonMinimize.frame.size.height);
   m_pnsbuttonZoom.frame = NSMakeRect(x + m_pnsbuttonClose.frame.size.width + m_paddingControlBox
                                      + m_pnsbuttonMinimize.frame.size.width + m_paddingControlBox, y, m_pnsbuttonMinimize.frame.size.width, m_pnsbuttonMinimize.frame.size.height);
   
   
   m_rightControlBox = x + m_pnsbuttonClose.frame.size.width + m_paddingControlBox + m_pnsbuttonMinimize.frame.size.width + m_paddingControlBox + m_pnsbuttonZoom.frame.size.width;
   m_bottomControlBox = y + maximum(m_pnsbuttonClose.frame.size.height, maximum(m_pnsbuttonMinimize.frame.size.height, m_pnsbuttonZoom.frame.size.height));

   if(m_ptrackingareaControlBox)
   {

      [m_pmacosimpact removeTrackingArea:m_ptrackingareaControlBox];
    
      m_ptrackingareaControlBox = nil;

   }
 
   // Get the bounding rect of all buttons combined
   NSRect trackingRect = NSUnionRect(NSUnionRect(m_pnsbuttonClose.frame, m_pnsbuttonMinimize.frame), m_pnsbuttonZoom.frame);
    
    // Convert to view coordinates
   //trackingRect = [self convertRect:trackingRect fromView:m_pnsbuttonClose.superview];

   m_ptrackingareaControlBox = [[NSTrackingArea alloc] initWithRect:trackingRect
                                                                options:(NSTrackingMouseEnteredAndExited| NSTrackingActiveInKeyWindow)
                                                                  owner:self userInfo: @{@"name": @"control_box"}];
    
   [m_pmacosimpact addTrackingArea:m_ptrackingareaControlBox]; // Add to the parent view

}



- (void)mouseEntered:(NSEvent *)event
{
   
   if( event.trackingArea == m_ptrackingareaControlBox)
   {
      
      [ self set_hover ];
      
   }
   
}


- (void)mouseExited:(NSEvent *)event
{
   

   if(event.trackingArea == m_ptrackingareaControlBox)
   {

      [ self set_normal ];
      
   }

   //[ super mouseExited: event ];

}



- (void) on_control_box_close:(id)sender
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pmacosimpact->m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
     
   if(p == NULL)
   {
      
      return;
      
   }
   
   p->on_control_box_close();

}


- (void) on_control_box_minimize:(id)sender
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pmacosimpact->m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
     
   if(p == NULL)
   {
      
      return;
      
   }
   
   p->on_control_box_minimize();

}


- (void) on_control_box_zoom:(id)sender
{
   
   auto pnsmacoswindow = (macOSWindow *) m_pmacosimpact->m_pnsacmewindow;

   macos_window * p = pnsmacoswindow->m_pmacoswindow;
     
   if(p == NULL)
   {
      
      return;
      
   }
   
   p->on_control_box_zoom();

}

@end

