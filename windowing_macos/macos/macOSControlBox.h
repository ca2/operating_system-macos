//
//  macOSControlBox.h
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2025-03-19.
//  Copyright © 2025 ca2 Software Development. All rights reserved.
//
#import <Cocoa/Cocoa.h>
@class macOSImpact;

@interface macOSControlBox : NSObject
{
@public
   
   
   macOSImpact * m_pmacosimpact;
   
   NSTrackingArea *        m_ptrackingareaControlBox;

   NSButton *              m_pnsbuttonClose;
   NSButton *              m_pnsbuttonMinimize;
   NSButton *              m_pnsbuttonZoom;
   
   NSImage *               m_pnsimageNotKey;
   
   NSImage *               m_pnsimageNormalClose;
   NSImage *               m_pnsimageNormalMinimize;
   NSImage *               m_pnsimageNormalZoom;

   NSImage *               m_pnsimageHoverClose;
   NSImage *               m_pnsimageHoverMinimize;
   NSImage *               m_pnsimageHoverZoom;
   
   int m_leftControlBox;
   int m_topControlBox;
   int m_wControlBoxButton;
   int m_hControlBoxButton;
   int m_rightControlBox;
   int m_bottomControlBox;
   int m_paddingControlBox;
}
-(void)init: (macOSImpact *)pmacosimpact;
-(void)set_normal;
-(void)set_not_key;
-(void)set_hover;
-(void)layout;
-(void)on_control_box_close:(id)sender;
-(void)on_control_box_minimize:(id)sender;
-(void)on_control_box_zoom:(id)sender;
@end
