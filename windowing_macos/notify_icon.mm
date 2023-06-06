//
//  user_notify_icon.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
#include "apex/user/notify_icon_bridge.h"
#include "notify_icon_mm.h"


NSImage * image_resize(NSImage* sourceImage, NSSize newSize)
{
   //[sourceImage setScalesWhenResized:YES];
   // Report an error if the source isn't a valid image
   if (![sourceImage isValid])
   {
      NSLog(@"Invalid Image");
      return nullptr;
   }
   
   NSImage *newImage = [[NSImage alloc] initWithSize: newSize];
   [newImage lockFocus];
   [sourceImage setSize: newSize];
   [[NSGraphicsContext currentContext] setImageInterpolation:NSImageInterpolationHigh];
   [sourceImage drawAtPoint:NSZeroPoint fromRect:CGRectMake(0, 0, newSize.width, newSize.height) operation:NSCompositingOperationCopy fraction:1.0];
   [newImage unlockFocus];
   return newImage;
   
}


@implementation user_notify_icon


- (id) initIconImageFileData:(const void *) pdata withSize: (int) size withBridge: (::user_notify_icon_bridge *) pbridge
{

   NSData * data = [NSData dataWithBytes:pdata length:size];
   
   if(data == nil)
   {
      
      return NULL;
      
   }
   
   NSImage * pimage = [[NSImage alloc] initWithData: data];

   return [ self initIconImage: pimage withBridge:pbridge ];

}


- (id)initIconImage:(NSImage *)pimage withBridge:(::user_notify_icon_bridge *)pbridge
{
   
   m_pnotifyiconbridge = pbridge;
   
   // http://stackoverflow.com/questions/3409985/how-to-create-a-menubar-application-for-mac
   m_statusitem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
   
   if (@available(macOS 10.10, *)) {
       [ [ [ m_statusitem button ] cell ] setHighlighted: YES];
   } else {
      [ m_statusitem setHighlightMode: YES ];
   }
   
//   auto pimage = [NSImage alloc];
//
//   if([pimage initByReferencingFile:strIconFile])
//   {
      NSSize sizeNotifyIcon;

      sizeNotifyIcon.width = 22;
      sizeNotifyIcon.height = 22;

      if([pimage size].width != sizeNotifyIcon.width
         || [pimage size].height != sizeNotifyIcon.height)
      {

         pimage = image_resize(pimage, sizeNotifyIcon);

      }
   
   if (@available(macOS 10.10, *)) {
          [ [m_statusitem button] setImage: pimage ];
      } else {
         [ m_statusitem setImage: pimage ];
      }
      
//   }
   
   m_menu = [[NSMenu alloc] initWithTitle:@"menubar_menu"];
   
   m_menuitema = [[NSMutableArray alloc] init];
   
   m_menuida = [[NSMutableArray alloc] init];
   
   int iCount = pbridge->_get_notification_area_action_count();
   
   for(int i = 0; i < iCount; i++)
   {
      
      //char * pszName = NULL;
//      char * pszId = NULL;
//      char * pszLabel = NULL;
//      char * pszAccelerator = NULL;
//      char * pszDescription = NULL;
//
//      pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);
      
      auto pszName = pbridge->_get_notification_area_action_name(i);
      
      auto pszId = pbridge->_get_notification_area_action_id(i);
      
      NSString * strTitle = NULL;
      
      NSString * strId = NULL;
      
      NSMenuItem * item = NULL;

      if(strcasecmp(pszName, "separator") == 0)
      {
         
         strTitle = [[NSString alloc] initWithUTF8String: pszName];
         
         strId = [[NSString alloc] initWithUTF8String: pszName];
         
         item = [NSMenuItem separatorItem];
         
      }
      else
      {
         
         strTitle = [[NSString alloc] initWithUTF8String: pszName];
         
         strId = [NSString stringWithFormat:@"menu_item_%s",  pszId];
         
         item = [[NSMenuItem alloc] initWithTitle:  strTitle action: @selector(on_item_action:) keyEquivalent:@"" ];
         
         item.identifier = strId;
         
      }
      
      [item setTarget:self];
      
      [m_menu addItem:item];
      
      //[m_menuitema addObject: item];
      
      //[m_menuida addObject: strId];
      
//      if(pszName) free(pszName);
//      if(pszId) free(pszId);
//      if(pszLabel) free(pszLabel);
//      if(pszAccelerator) free(pszAccelerator);
//      if(pszDescription) free(pszDescription);

   }
   
   [m_menu setDelegate:self];
   
   [m_statusitem setMenu: m_menu];
   
   if (@available(macOS 10.10, *)) {
       [ [ m_statusitem button ] setEnabled:YES];
   } else {
      [ m_statusitem setEnabled:YES];
   }
   
   return self;
   
}


- (void)dealloc
{
   
   m_pnotifyiconbridge = NULL;
   
}


- (void) on_item_action :(id)sender
{
   
   NSMenuItem * pitem = (NSMenuItem *) sender;
   
   if(m_pnotifyiconbridge == NULL)
   {
      
      return;
      
   }
   
   NSString * prefixToRemove = @"menu_item_";
   
   NSString * strId = [pitem.identifier copy];
   
   if ([pitem.identifier hasPrefix:prefixToRemove])
   {
      
      strId = [pitem.identifier substringFromIndex:[prefixToRemove length]];
   
      const char * psz = [strId UTF8String];
         
      m_pnotifyiconbridge->call_notification_area_action(psz);
         
      return;
      
   }
   
}


- (void)close
{
 
   [[NSStatusBar systemStatusBar] removeStatusItem: m_statusitem];
   
}


@end



