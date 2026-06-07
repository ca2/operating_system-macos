//
//  NotifyIcon.mm
//  innate_subsystem_macos
//
#include "framework.h"
#include "acme/platform/system.h"
#include "NotifyIcon.h"
#include "drawing/Icon.h"
#include "operating_system-macos/appkit/ns_image.h"

#import <AppKit/AppKit.h>


@interface innate_subsystem_macos_notify_icon_target : NSObject

@property(nonatomic, assign) innate_subsystem_macos::NotifyIcon * notifyIcon;

- (void)onStatusItem:(id)sender;

@end


@implementation innate_subsystem_macos_notify_icon_target

- (void)onStatusItem:(id)sender
{
   NSEventType type = NSApp.currentEvent.type;

   if (type == NSEventTypeRightMouseUp || type == NSEventTypeRightMouseDown)
   {
      _notifyIcon->on_native_right_button_up();
   }
   else
   {
      _notifyIcon->on_native_left_button_down();
   }
}

@end


namespace innate_subsystem_macos
{


   void NotifyIcon::__create_status_item()
   {
      if (m_pStatusItem)
      {
         return;
      }

      NSStatusItem * statusItem =
         [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
      innate_subsystem_macos_notify_icon_target * target =
         [[innate_subsystem_macos_notify_icon_target alloc] init];

      target.notifyIcon = this;
      statusItem.button.target = target;
      statusItem.button.action = @selector(onStatusItem:);
      [statusItem.button sendActionOn:NSEventMaskLeftMouseDown | NSEventMaskRightMouseUp];
      statusItem.button.enabled = YES;

      m_pStatusItem = (__bridge_retained void *) statusItem;
      m_pStatusItemTarget = (__bridge_retained void *) target;

      __set_icon();
      __set_text(m_strText);
   }


   void NotifyIcon::__destroy_status_item()
   {
      if (m_pStatusItem)
      {
         NSStatusItem * statusItem = (__bridge_transfer NSStatusItem *) m_pStatusItem;
         [[NSStatusBar systemStatusBar] removeStatusItem:statusItem];
         m_pStatusItem = nullptr;
      }

      if (m_pStatusItemTarget)
      {
         innate_subsystem_macos_notify_icon_target * target =
            (__bridge_transfer innate_subsystem_macos_notify_icon_target *) m_pStatusItemTarget;
         target.notifyIcon = nullptr;
         m_pStatusItemTarget = nullptr;
      }
   }


   void NotifyIcon::__set_icon()
   {
      if (!m_pStatusItem)
      {
         return;
      }

      NSStatusItem * statusItem = (__bridge NSStatusItem *) m_pStatusItem;
      NSImage * image = nil;

      if (m_picon)
      {
         auto picon = m_picon->impl<::innate_subsystem_macos::Icon>();

         if (picon && picon->m_pnsimage)
         {
            image = (__bridge NSImage *) picon->m_pnsimage->m_nsimage.m_p;
         }
      }

      if (!image)
      {
         image = NSApp.applicationIconImage;
      }

      if (image)
      {
         image = [image copy];
         image.size = NSMakeSize(18.0, 18.0);
      }

      statusItem.button.image = image;
   }


   void NotifyIcon::__set_text(const ::scoped_string & scopedstrText)
   {
      if (!m_pStatusItem)
      {
         return;
      }

      ::string strText(scopedstrText);
      NSStatusItem * statusItem = (__bridge NSStatusItem *) m_pStatusItem;
      statusItem.button.toolTip = [NSString stringWithUTF8String:strText.c_str()];
   }


   void NotifyIcon::__show_balloon(const ::scoped_string & scopedstrMessage,
                                   const ::scoped_string & scopedstrCaption)
   {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
      ::string strMessage(scopedstrMessage);
      ::string strCaption(scopedstrCaption);
      NSUserNotification * notification = [[NSUserNotification alloc] init];
      notification.title = [NSString stringWithUTF8String:strCaption.c_str()];
      notification.informativeText = [NSString stringWithUTF8String:strMessage.c_str()];
      [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:notification];
#pragma clang diagnostic pop
   }


} // namespace innate_subsystem_macos
