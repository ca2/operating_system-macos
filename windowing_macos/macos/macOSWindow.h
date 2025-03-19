//
//  RoundWindow.h
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


#import <Cocoa/Cocoa.h>
#include "macOSWindowController.h"
#include "acme_windowing_appkit/ns_acme_window.h"

unsigned int event_key_code(NSEvent * event);


class macos_window;
@class macOSImpact;


@interface macOSWindow : ns_acme_window
{
@public
   
   
   bool                    m_bNoActivate;
   macos_window *          m_pmacoswindow;
   
   
   //macOSImpact *           m_pimpactChildContent;
   NSWindowController *    m_pwindowcontroller;
  
}

-(void)dealloc;

-(void)windowDidExpose:(NSNotification*)notification;

-(void)windowWillClose:(NSNotification*)notification;

-(int) control_box_right_when_at_left;

@end
