//
//  __impact.mm
//  innate_ui_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-09-20 16:57
//
#include "framework.h"
#import <AppKit/AppKit.h>
#include "__text_field.h"


namespace innate_ui_appkit
{
   

//   void window::createø()
//   {
//
//      // m_hwnd = CreateWindowW(_get_class_name(), L"", WS_DLGFRAME | WS_CAPTION | WS_POPUPWINDOW,
//      //         CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, (HINSTANCE) ::platform::get()->m_hinstanceThis,
//      //         nullptr);
//
//      // m_pgtkwidget = gtk_dialog_new_with_buttons("Custom Dialog",
//      //                                              NULL,
//      //                                              GTK_DIALOG_DESTROY_WITH_PARENT,
//      //                                              NULL);
//
//
//      NSRect frame = NSMakeRect(0, 0, 300, 300);
//            NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
//                                                           styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
//                                                             backing:NSBackingStoreBuffered
//                                                               defer:NO];
//            [window setTitle:@"Custom Dialog"];
//
//            // Create the label
////            NSTextField *label = [[NSTextField alloc] initWithFrame:NSMakeRect(100, 80, 200, 24)];
////            [label setStringValue:@"This is a custom message"];
////            [label setBezeled:NO];
////            [label setDrawsBackground:NO];
////            [label setEditable:NO];
////            [label setSelectable:NO];
////            [[window contentView] addSubview:label];
//
//            // Create the button
////            NSButton *button = [[NSButton alloc] initWithFrame:NSMakeRect(110, 20, 80, 24)];
////            [button setTitle:@"OK"];
////            [button setTarget:window]; // Close window when clicked
////            [button setAction:@selector(close)];
////            [[window contentView] addSubview:button];
//
//            // Add an icon
////            NSImageView *iconView = [[NSImageView alloc] initWithFrame:NSMakeRect(20, 60, 64, 64)];
////            NSImage *icon = [NSImage imageNamed:NSImageNameCaution]; // Change to your preferred icon
////            [iconView setImage:icon];
////            [[window contentView] addSubview:iconView];
//
//            // Center the window on the screen
//            ///[window center];
//
//            // Show the window without blocking other UI interactions
//            ///[window makeKeyAndOrderFront:nil];
//
//            // Ensure the application stays running while the window is open
//            //[NSApp activateIgnoringOtherApps:YES];
//
//      m_pnsobject = window;
//
//      //m_pqwidget = new QDialog();
//
//
//      //m_pgtkwidgetFixed = gtk_fixed_new();
//
//      //gtk_window_set_child(GTK_WINDOW(m_pgtkwidget), m_pgtkwidgetFixed);
//      //gtk_widget_set_parent(m_pgtkwidget, nullptr);
//      ///GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(m_pgtkwidget));
//      //m_fixed = gtk_fixed_new();
//      //gtk_box_append(content_area, m_fixed);
//
//   }

void __text_field::__create_still()
{
   
   NSTextField *label = [[NSTextField alloc] initWithFrame:NSMakeRect(100, 80, 200, 24)];
   [label setBezeled:NO];
   [label setDrawsBackground:NO];
   [label setEditable:NO];
   //[label setSelectable:NO];

   m_pNSTextField = (__bridge_retained void *) label;

}

void __text_field::__show()
{
   
}

void __text_field::__set_text(const char *psz)
{
   
   auto pnstextfield = (__bridge  NSTextField *)m_pNSTextField;
   
   NSString * pstr = [[NSString alloc] initWithUTF8String:psz];
   
   [pnstextfield setStringValue:pstr];
}


void __text_field::__set_font_size(double dSizeEm)
{
   
   auto pnstextfield = (__bridge  NSTextField *)m_pNSTextField;
   
   if(pnstextfield == nil || !(dSizeEm > 0.0))
   {
      
      return;
      
   }
   
   NSFont * pfontCurrent = [pnstextfield font];
   
   if(pfontCurrent == nil)
   {
      
      pfontCurrent = [NSFont systemFontOfSize:[NSFont systemFontSize]];
      
   }
   
   CGFloat pointSize = [NSFont systemFontSize] * (CGFloat)dSizeEm;
   
   NSFont * pfont = [NSFont fontWithDescriptor:[pfontCurrent fontDescriptor]
                                          size:pointSize];
   
   if(pfont != nil)
   {
      
      [pnstextfield setFont:pfont];
      
   }
   
}


static NSFontWeight ns_font_weight_from_css_weight(int iFontWeight)
{
   
   if(iFontWeight <= 100)
   {
      
      return NSFontWeightUltraLight;
      
   }
   else if(iFontWeight <= 200)
   {
      
      return NSFontWeightThin;
      
   }
   else if(iFontWeight <= 300)
   {
      
      return NSFontWeightLight;
      
   }
   else if(iFontWeight <= 400)
   {
      
      return NSFontWeightRegular;
      
   }
   else if(iFontWeight <= 500)
   {
      
      return NSFontWeightMedium;
      
   }
   else if(iFontWeight <= 600)
   {
      
      return NSFontWeightSemibold;
      
   }
   else if(iFontWeight <= 700)
   {
      
      return NSFontWeightBold;
      
   }
   else if(iFontWeight <= 800)
   {
      
      return NSFontWeightHeavy;
      
   }
   else
   {
      
      return NSFontWeightBlack;
      
   }
   
}


void __text_field::__set_font_weight(int iFontWeight)
{
   
   auto pnstextfield = (__bridge  NSTextField *)m_pNSTextField;
   
   if(pnstextfield == nil || iFontWeight <= 0)
   {
      
      return;
      
   }
   
   NSFont * pfontCurrent = [pnstextfield font];
   
   if(pfontCurrent == nil)
   {
      
      pfontCurrent = [NSFont systemFontOfSize:[NSFont systemFontSize]];
      
   }
   
   NSFontDescriptor * pdescriptor = [pfontCurrent fontDescriptor];
   NSDictionary * ptraitsCurrent = [pdescriptor objectForKey:NSFontTraitsAttribute];
   NSMutableDictionary * ptraits =
      ptraitsCurrent ? [ptraitsCurrent mutableCopy] : [[NSMutableDictionary alloc] init];
   
   ptraits[NSFontWeightTrait] = @(ns_font_weight_from_css_weight(iFontWeight));
   
   NSFontDescriptor * pdescriptorWeighted =
      [pdescriptor fontDescriptorByAddingAttributes:@{NSFontTraitsAttribute: ptraits}];
   
   NSFont * pfont = [NSFont fontWithDescriptor:pdescriptorWeighted
                                          size:[pfontCurrent pointSize]];
   
   if(pfont != nil)
   {
      
      [pnstextfield setFont:pfont];
      
   }
   
}


void __text_field::__set_position(int x, int y)
{
   
   NSPoint point;
   
   point.x = x;
   auto pnstextfield = (__bridge  NSTextField *)m_pNSTextField;
//   if([m_pnsview isFlipped])
//   {
//      
//      point .y =  y;
//
//   }
//   else
   {
      
      int superHeight =[[pnstextfield superview] frame].size.height ;
      
      int height =[pnstextfield frame].size.height;
      
      int offset = superHeight - height;
      
      int y2 = offset - y;
      point .y =y2 ;
   }
   
   
   [pnstextfield setFrameOrigin:point];
   
}
void __text_field::__set_size(int cx, int cy)
{
   
   NSSize size;
   
   size.width = cx;
   
   size.height= cy;
   
   auto pnstextfield = (__bridge  NSTextField *)m_pNSTextField;
   [pnstextfield setFrameSize:size];
   
}

void __text_field::__impact_release()
{
 
   auto pnstextfield = (__bridge_transfer  NSTextField *)m_pNSTextField;
   //m_pnsview = nil;
   
}


void __text_field::__get_fitting_size(int & cx, int & cy)
{
   auto field = (__bridge NSTextField *)m_pNSTextField;

   if(field == nil)
   {
      cx = 0;
      cy = 0;
      return;
   }

   NSSize size = [field fittingSize];

   cx = (int)ceil(size.width);
   cy = (int)ceil(size.height);
}

} // namespace innate_ui_appkit
