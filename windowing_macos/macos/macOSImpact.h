//
//  RoundWindowFrameView.h
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

#include "acme_windowing_appkit/ns_acme_impact.h"
#define NS_ROUND_WINDOW_FRAME_PADDING 0

//#include "keyboard.h"

//struct mf_context
//{
//
////   enum APPLE_KEYBOARD_TYPE appleKeyboardType;
//   
//};
#import <Cocoa/Cocoa.h>


@class macOSWindow;
@class macOSControlBox;


@interface macOSImpact : ns_acme_impact
{
   @public
//   mf_context* mfc;
   //APPLE_KEYBOARD_TYPE appleKeyboardType;
   //macOSWindow * m_pnsmacoswindow;
   //NSTrackingArea * trackingArea;
   //bool m_bLShift;
   //bool m_bRShift;
   //bool m_bLControl;
   //bool m_bRControl;
   //bool m_bLAlt;
   //bool m_bRAlt;
   //bool m_bLCommand; // In Windows, the Windows Key
   //bool m_bRCommand; // In Windows, the Windows Key
   //unsigned int kbdModFlags;
   
   macOSControlBox *       m_pmacoscontrolbox;
}

- (id)initWithFrame:(NSRect)frame andWindow:(ns_acme_window*)pnsacmewindow;
-(int) control_box_right_when_at_left;
-(macOSControlBox*)control_box;
-(void)window_did_become_key :(macOSWindow *) pmacoswindow withNotification:(NSNotification*) notification;
-(void)window_did_resign_key :(macOSWindow *) pmacoswindow withNotification:(NSNotification*) notification;

@end
