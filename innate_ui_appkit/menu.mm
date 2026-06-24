//
//  menu.mm
//  innate_ui_appkit
//
#include "framework.h"
#include "menu.h"

#import <AppKit/AppKit.h>


@interface innate_ui_appkit_menu_target : NSObject

@property(nonatomic, assign) innate_ui_appkit::menu * menu;

- (void)onMenuItem:(NSMenuItem *)item;

@end


@implementation innate_ui_appkit_menu_target

- (void)onMenuItem:(NSMenuItem *)item
{
   if (_menu)
   {
      _menu->on_action((::i32) item.tag);
   }
}

@end


namespace innate_ui_appkit
{


   void menu::__create_menu()
   {
      if (m_pNSMenu)
      {
         return;
      }

      NSMenu * menu = [[NSMenu alloc] initWithTitle:@""];
      menu.autoenablesItems = NO;

      innate_ui_appkit_menu_target * target = [[innate_ui_appkit_menu_target alloc] init];
      target.menu = this;

      m_pNSMenu = (__bridge_retained void *) menu;
      m_pMenuTarget = (__bridge_retained void *) target;
   }


   void menu::__destroy_menu()
   {
      if (m_pMenuTarget)
      {
         innate_ui_appkit_menu_target * target = (__bridge_transfer innate_ui_appkit_menu_target *) m_pMenuTarget;
         target.menu = nullptr;
         m_pMenuTarget = nullptr;
      }

      if (m_pNSMenu)
      {
         NSMenu * menu = (__bridge_transfer NSMenu *) m_pNSMenu;
         [menu removeAllItems];
         m_pNSMenu = nullptr;
      }
   }


   void menu::__add_item(const ::scoped_string & scopedstr, int iId)
   {
      NSMenu * menu = (__bridge NSMenu *) m_pNSMenu;
      innate_ui_appkit_menu_target * target = (__bridge innate_ui_appkit_menu_target *) m_pMenuTarget;
      ::string strTitle(scopedstr);
      NSString * title = [NSString stringWithUTF8String:strTitle.c_str()];

      NSMenuItem * item = [[NSMenuItem alloc] initWithTitle:title
                                                    action:@selector(onMenuItem:)
                                             keyEquivalent:@""];
      item.target = target;
      item.tag = iId;
      item.enabled = YES;

      [menu addItem:item];
   }


   void menu::__add_separator()
   {
      NSMenu * menu = (__bridge NSMenu *) m_pNSMenu;
      [menu addItem:[NSMenuItem separatorItem]];
   }


   void menu::__erase_menu_item_by_command_id(::i32 iCommandId)
   {
      NSMenu * menu = (__bridge NSMenu *) m_pNSMenu;
      NSMenuItem * item = [menu itemWithTag:iCommandId];

      if (item)
      {
         [menu removeItem:item];
      }
   }


   void menu::__set_default_menu_item_command_id(::i32 iCommandId)
   {
      NSMenu * menu = (__bridge NSMenu *) m_pNSMenu;

      for (NSMenuItem * item in menu.itemArray)
      {
         if ([item isSeparatorItem])
         {
            continue;
         }

         NSDictionary * attributes = nil;

         if (item.tag == iCommandId)
         {
            attributes = @{NSFontAttributeName: [NSFont boldSystemFontOfSize:[NSFont systemFontSize]]};
         }

         item.attributedTitle = [[NSAttributedString alloc] initWithString:item.title attributes:attributes];
      }
   }


   void menu::__track_popup_menu()
   {
      NSMenu * menu = (__bridge NSMenu *) m_pNSMenu;

      if (!menu)
      {
         return;
      }

      // AppKit does not permit the menu-bar root to be populated or tracked as
      // a popup menu. Keep this boundary explicit because a popup requested
      // while a temporary ca2 window is closing can otherwise reach this path
      // with the currently installed main-menu object.
      if (menu == NSApp.mainMenu)
      {
         NSLog(@"Ignoring an attempt to track NSApp.mainMenu as a popup menu.");
         return;
      }

      NSPoint point = [NSEvent mouseLocation];
      [menu popUpMenuPositioningItem:nil atLocation:point inView:nil];
   }


} // namespace innate_ui_appkit
