//
//  RoundWindowApp.m
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 27/09/14.
//
//
#include "framework.h"
#include "macos_app.h"
#include "acme/constant/id.h"
#include "acme/operating_system/argcargv.h"
#include "acme/platform/application_menu.h"
#include "acme/handler/command_handler.h"
#include <Foundation/Foundation.h>


NSString * __nsstring(const char * psz);


void ns_main_send(dispatch_block_t block);
void ns_main_post(dispatch_block_t block);

void os_system_start();

void application_handle_command(::platform::application * papplication, const char * pszCommand, ::user::activation_token * puseractivationtoken);

::platform::system * application_system(::platform::application * papplication);

void system_id_update(::platform::system * psystem, int iUpdate, long long iPayload);

void node_will_finish_launching(::platform::system * psystem);
void node_did_finish_launching(::platform::system * psystem);
void system_on_open_untitled_file(::platform::system * psystem);
void system_on_open_file(::platform::system * psystem, const char * pszFile);

void macos_on_app_changed_occlusion_state();

void set_apex_system_as_thread();

NSMenu * ns_create_menu(::application_menu * papplicationmenu, bool bMainMenu);

void ns_create_menu(NSMenu * menu, ::application_menu * papplicationmenu, bool bMainMenu);

void ns_apple_set_application_delegate(::platform::application * papplication, macos_app * pappdelegate);
void * apple_get_application_delegate(::platform::application * papplication);

void acme_defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::command_handler * pcommandhandler)
{
   
   macos_app * pappdelegate = (__bridge macos_app *) apple_get_application_delegate(papplication);
   
   if(pappdelegate == nullptr)
   {
      
      pappdelegate = [ [ macos_app alloc] initWithApplicationMenu: papplicationmenu andCommandHandler: pcommandhandler];
      
      ns_apple_set_application_delegate(papplication, pappdelegate);
      
   }
   
}


@implementation macos_app


- (id)initWithApplicationMenu:(::application_menu *) papplicationmenu andCommandHandler:(::command_handler *)pcommandhandler
{

   [NSApplication sharedApplication];

   //self = [super init];
   

   
   m_windowcontrollera = [ [ NSMutableArray alloc ] init ];
   
   [[[NSWorkspace sharedWorkspace] notificationCenter]
       addObserver:self
       selector:@selector(applicationActivity:)
       name:NSWorkspaceActiveSpaceDidChangeNotification
       object:nil];

   [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

   ns_main_post(^{
           [NSApp activateIgnoringOtherApps:YES];
      
      [NSMenu setMenuBarVisible: true];

       });

   m_papplicationmenu = papplicationmenu;
   
   m_pcommandhandler = pcommandhandler;
   
   [self application_menu_update];

   
   //[ self application_menu_update ];
   


//
//   [[[NSWorkspace sharedWorkspace] notificationCenter]
//    addObserver:self
//    selector:@selector(applicationDidChangeOcclusionState:)
//    name:NSApplicationDidChangeOcclusionStateNotification
//    object:nil];
   return self;
}



//- (id)init
//{
//
//   [NSApplication sharedApplication];
//
//   self = [super init];
//   
//   [self application_menu_update];
//
//   
//   m_windowcontrollera = [ [ NSMutableArray alloc ] init ];
//   
//   [[[NSWorkspace sharedWorkspace] notificationCenter]
//       addObserver:self
//       selector:@selector(applicationActivity:)
//       name:NSWorkspaceActiveSpaceDidChangeNotification
//       object:nil];
//
//   [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
//
//   ns_main_post(^{
//           [NSApp activateIgnoringOtherApps:YES];
//      
//      [NSMenu setMenuBarVisible: true];
//
//       });
//
//   return self;
//   
//}


-(void)dealloc
{
   
   
}


-(void)continueInitialization
{
   
}


-(void)applicationActivity:(NSNotification *)notification
{
   
   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
   
   NSString * strName = app.localizedName;
   //if([ isEqualToString:@"ScreenSaverEngine"])
   {
      printf("NOTIFICATION: %s", [strName UTF8String]);

      // Your code here
   }
}



-(NSWindowController *) addWindow:(NSWindow*)window
{
   
   NSWindowController * pwindowcontroller = [ [ NSWindowController alloc ] initWithWindow : window ];
   
   [ m_windowcontrollera addObject : pwindowcontroller ];
   
   return pwindowcontroller;
   
}

-(void) removeWindowController:(NSWindowController*)pwindowcontroller
{
   

   
   [ m_windowcontrollera removeObject : pwindowcontroller ];
   
}

//-(void) removeWindowController:(NSWindowController*)pwindowcontroller
//{
//   
//   [ m_windowcontrollera removeObject : pwindowcontroller ];
//   
//}


//- (void)on_os_menu_item:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   for(int i = 0; i < [m_menuitema count]; i++)
//   {
//      
//      if(pitem == [m_menuitema objectAtIndex:i])
//      {
//         
//         const char * psz = [[m_menuida objectAtIndex:i] UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         application_on_menu_action(m_papplication, psz);
//         
//         return;
//         
//      }
//      
//   }
//   
//}

//- (void)on_command:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   NSString * str = (NSString *)[pitem representedObject];
//if(str != nil)
//{
//         const char * psz = [str UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         application_on_menu_action(m_papplication, psz);
//         
//         return;
//         
//      //}
//      
//   }
//   
//}


-(void)show_about_box
{
   
   application_handle_command(m_papplication, "show_about_box", nullptr);
   
}


-(void)try_close_application
{
   
   application_handle_command(m_papplication, "try_close_application", nullptr);
   
}


//-(void)application_menu_update
//{
//   
//   //m_menu = [ NSApp mainMenu ];
//   
////   auto m = [[NSMenu alloc] init];
////   
////   [ m removeAllItems ];
//   
//   //if (![ NSApp mainMenu ])
//   //{
//      
//     // [ NSApplication sharedApplication ];
//      
//      id appName = [ [ NSProcessInfo processInfo ] processName ];
//      
//      id menubar = [ NSMenu new ];
//      id appMenuItem = [ NSMenuItem new ];
//      [ menubar addItem : appMenuItem ];
//      
//      id appMenu = [ NSMenu new ] ;
//      id aboutTitle = [ @"About " stringByAppendingString : appName];
//      id aboutMenuItem = [ [ NSMenuItem alloc ] initWithTitle : aboutTitle action: @selector(show_about_box) keyEquivalent: @"a" ];
//   [aboutMenuItem setTarget:self];
//      [ appMenu addItem : aboutMenuItem ];
//      [ appMenu addItem : [ NSMenuItem separatorItem]];
//      id quitTitle = [ @"Quit " stringByAppendingString : appName];
//      id quitMenuItem = [ [ NSMenuItem alloc ] initWithTitle : quitTitle action: @selector(try_close_application) keyEquivalent: @"q" ];
//   [quitMenuItem setTarget:self];
//
//      [ appMenu addItem : quitMenuItem ];
//      [ appMenuItem setSubmenu : appMenu ];
//   
//   
//      
//   [[ NSApplication sharedApplication] setMainMenu : menubar ];
//      
//   //}
//   //[ NSApp setMainMenu: m];
//   
////   m_menu = [[NSMenu alloc] initWithTitle:@"menubar_menu"];
////   m_menuitema = [[NSMutableArray alloc] init];
////
////   m_menuida = [[NSMutableArray alloc] init];
////
////   // Monitor menu/dock theme changes...
////   //   [NSDistributedNotificationCenter.defaultCenter addObserver:self selector:@selector(themeChanged:) name:@"AppleInterfaceThemeChangedNotification" object: nil];
////
////   //int iCount = pbridge->_get_notification_area_action_count();
////
////   //int iCount = 1;
////
////   for(int i = 0; i < m_papplicationmenu->get_count(); i++)
////   {
////
////      //      char * pszName = NULL;
////      //      char * pszId = NULL;
////      //      char * pszLabel = NULL;
////      //      char * pszAccelerator = NULL;
////      //      char * pszDescription = NULL;
////      //
////      //      pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);
////
////      auto & menuitem = m_papplicationmenu->element_at(i);
////
////      char * pszName = strdup(menuitem.m_strName);
////      char * pszId = strdup(menuitem.m_strId);
////      char * pszLabel = strdup(menuitem.m_strName);
////      char * pszAccelerator = strdup(menuitem.m_strMacosAccelerator);
////      char * pszDescription = strdup(menuitem.m_strDescription);
////      NSString * strTitle = NULL;
////
////      NSString * strId = NULL;
////
////      NSMenuItem * item = NULL;
////
////      if(strcasecmp(pszName, "separator") == 0)
////      {
////
////         strTitle = [[NSString alloc] initWithUTF8String: pszName];
////
////         strId = [[NSString alloc] initWithUTF8String: pszName];
////
////         item = [NSMenuItem separatorItem];
////
////      }
////      else
////      {
////
////         strTitle = [[NSString alloc] initWithUTF8String: pszName];
////
////         strId = [[NSString alloc] initWithUTF8String: pszId];
////
////         item = [[NSMenuItem alloc] initWithTitle:  strTitle action: @selector(on_os_menu_item:) keyEquivalent:@"" ];
////
////      }
////
////      [item setTarget:self];
////
////      [m_menu addItem:item];
////
////      [m_menuitema addObject: item];
////
////      [m_menuida addObject: strId];
////
////      if(pszName) free(pszName);
////      if(pszId) free(pszId);
////      if(pszLabel) free(pszLabel);
////      if(pszAccelerator) free(pszAccelerator);
////      if(pszDescription) free(pszDescription);
////   }
////
////   [m_menu setDelegate:self];
////
////   [ NSApp setMainMenu: m_menu];
//
//}



- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
   
   //macos_calc_dark_mode();
   
   //[ NSApp setActivationPolicy:NSApplicationActivationPolicyRegular ];

   //[ self application_menu_update ];
   
   m_pacmenotificationcallback = [ [ acme_notification_callback alloc ]  init ];
   
   m_pacmenotificationcallback->m_papplication = m_papplication;
  
   [m_pacmenotificationcallback fetch_dark_mode];
   
   node_will_finish_launching(application_system(m_papplication));

   NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];

   [appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
   
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
   
   //[self application_menu_update];
   
   node_did_finish_launching(application_system(m_papplication));

   
   //set_apex_system_as_thread();
   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
   
   //defer_run_system();
   
}


- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
   
   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", e_message_box_ok);
   
   system_id_update(application_system(m_papplication), id_app_activated, 0);

   return NO;
   
}

- (void)applicationDidChangeOcclusionState:(NSNotification *)notification
{
   
   //macos_on_app_changed_occlusion_state();
   
}


- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
{
   
   //file_put_contents("/eco/001.txt", "applicationOpenUntitledFile");
   
   system_on_open_untitled_file(application_system(m_papplication));
   
   return YES;
   
}



- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
{
   
   //file_put_contents("/eco/002.txt", "applicationOpenFile");
   //file_put_contents("/eco/003.txt", [filename UTF8String]);

   system_on_open_file(application_system(m_papplication), [filename UTF8String]);
   
   return true;
   
}



- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
{
   
   unsigned long ulCount = [filenames count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   //char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      const char * psz = [[filenames objectAtIndex:ul] UTF8String];
      
      system_on_open_file(application_system(m_papplication), psz);
      
      //psza[ul] = psz;
      
   }
   
//   defer_run_system(psza, (int) ulCount);
//
//
}


- (void)application:(NSApplication *)application open:(NSURL * )url
{
   //file_put_contents("/eco/006.txt", "open");
   //file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_papplication), [[url absoluteString] UTF8String]);
   
}


- (BOOL)application:(id)sender
  openFileWithoutUI:(NSString *)filename;
{
   //file_put_contents("/eco/007.txt", "openFileWithoutUI");
   //file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_papplication), [filename UTF8String]);
   
   return TRUE;
   
}


- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
{
   unsigned long ulCount = [urls count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   //[NSThread sleepForTimeInterval:30.0];
   
   //char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      const char * psz = [[[urls objectAtIndex:ul] absoluteString] UTF8String];
      
      //psza[ul] = psz;
      
      system_on_open_file(application_system(m_papplication), psz);
      
      //free
      
   }
   
   //defer_run_system(psza, (int) ulCount);

}



- (void)applicationWillTerminate:(NSNotification *)notification
{
   
   
   
}



//- (void)sendEvent:(NSEvent *)theEvent
//{
//
//   /*
//
//   char szEvent[128];
//
//   ·zero(szEvent);
//
//   if([theEvent type] == NSLeftMouseDown)
//   {
//
//      strcpy(szEvent, "NSLeftMouseDown");
//
//   }
//   else if([theEvent type] == NSLeftMouseUp)
//   {
//
//      strcpy(szEvent, "NSLeftMouseUp");
//
//   }
//
//   if(strlen(szEvent) > 0)
//   {
//
//      char szEventCopy[128];
//
//      strcpy(szEventCopy, szEvent);
//
//      printf("\n%s", szEventCopy);
//
//   }
//
//   */
//
//   [super sendEvent:theEvent];
//
//}
- (void)handleGetURLEvent:(NSAppleEventDescriptor *)event
           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
   
   // Extract the URL from the Apple event and handle it here.
   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
   
   system_on_open_file(application_system(m_papplication), [url UTF8String]);
   
}


//-(NSMenu *) applicationDockMenu:(NSApplication*)sender
//{
//
//   return m_menu;
//   
//}


//- (void) ns_add_menu :(NSMenu *) menuParent withParent: (const char *) pszParent  withSharedMenu : (menu_shared *) pmenushared
//{
//
//   if(!pmenushared)
//   {
//
//      return;
//
//   }
//
//      for(int i = 0; i < pmenushared->m_iCount; i++)
//      {
//
//         if(!strcmp("separator", pmenushared->m_ppszId[i]))
//         {
//
//            NSMenuItem * menuitem = [NSMenuItem separatorItem];
//
//            [menuParent addItem: menuitem];
//
//         }
//         else if(!strcmp(pszParent, pmenushared->m_ppszParent[i]))
//         {
//
//            NSString * strTitle = [[NSString alloc] initWithUTF8String:pmenushared->m_ppszMenu[i]];
//
//            NSMenuItem * menuitem = [[NSMenuItem alloc] initWithTitle:strTitle action:@selector(on_command:) keyEquivalent:@""];
//
//            NSString * strId = [[NSString alloc] initWithUTF8String:pmenushared->m_ppszId[i]];
//
//            pmenushared->m_ositema[i] = (__bridge void * )menuitem;
//
//            [menuitem setTarget: self];
//
//            [menuitem setRepresentedObject: strId];
//
//            [menuParent addItem: menuitem];
//
//         }
//
//      }
//
//
//}

//
//- (void)play:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   for(int i = 0; i < [m_menuitema count]; i++)
//   {
//      
//      if(pitem == [m_menuitema objectAtIndex:i])
//      {
//         
//         const char * psz = [[m_menuida objectAtIndex:i] UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         application_on_menu_action(m_papplication, psz);
//         
//         return;
//         
//      }
//      
//   }
//   
//}
//

-(void)application_handle: (long long) l withPointer :(void *) p
{
   
   if(l == id_application_menu_update)
   {
      
      [self application_menu_update ];
      
   }
   
}



-(void)application_menu_update
{
   
   //m_menu = [ NSApp mainMenu ];
   
   auto m = [[NSMenu alloc] init];
   
   [ m removeAllItems ];
   
   ns_create_menu(m, m_papplicationmenu, true);
      
   [ NSApp setMainMenu: m];
   
//   m_menu = [[NSMenu alloc] initWithTitle:@"menubar_menu"];
//   m_menuitema = [[NSMutableArray alloc] init];
//
//   m_menuida = [[NSMutableArray alloc] init];
//
//   // Monitor menu/dock theme changes...
//   //   [NSDistributedNotificationCenter.defaultCenter addObserver:self selector:@selector(themeChanged:) name:@"AppleInterfaceThemeChangedNotification" object: nil];
//
//   //int iCount = pbridge->_get_notification_area_action_count();
//
//   //int iCount = 1;
//
//   for(int i = 0; i < m_papplicationmenu->get_count(); i++)
//   {
//
//      //      char * pszName = NULL;
//      //      char * pszId = NULL;
//      //      char * pszLabel = NULL;
//      //      char * pszAccelerator = NULL;
//      //      char * pszDescription = NULL;
//      //
//      //      pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);
//
//      auto & menuitem = m_papplicationmenu->element_at(i);
//
//      char * pszName = strdup(menuitem.m_strName);
//      char * pszId = strdup(menuitem.m_strId);
//      char * pszLabel = strdup(menuitem.m_strName);
//      char * pszAccelerator = strdup(menuitem.m_strMacosAccelerator);
//      char * pszDescription = strdup(menuitem.m_strDescription);
//      NSString * strTitle = NULL;
//
//      NSString * strId = NULL;
//
//      NSMenuItem * item = NULL;
//
//      if(strcasecmp(pszName, "separator") == 0)
//      {
//
//         strTitle = [[NSString alloc] initWithUTF8String: pszName];
//
//         strId = [[NSString alloc] initWithUTF8String: pszName];
//
//         item = [NSMenuItem separatorItem];
//
//      }
//      else
//      {
//
//         strTitle = [[NSString alloc] initWithUTF8String: pszName];
//
//         strId = [[NSString alloc] initWithUTF8String: pszId];
//
//         item = [[NSMenuItem alloc] initWithTitle:  strTitle action: @selector(on_os_menu_item:) keyEquivalent:@"" ];
//
//      }
//
//      [item setTarget:self];
//
//      [m_menu addItem:item];
//
//      [m_menuitema addObject: item];
//
//      [m_menuida addObject: strId];
//
//      if(pszName) free(pszName);
//      if(pszId) free(pszId);
//      if(pszLabel) free(pszLabel);
//      if(pszAccelerator) free(pszAccelerator);
//      if(pszDescription) free(pszDescription);
//   }
//
//   [m_menu setDelegate:self];
//
//   [ NSApp setMainMenu: m_menu];

}




- (void)on_application_menu_action:(id)sender
//{
//
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//
//   NSString * str = (NSString *)[pitem representedObject];
//
//   if(str != nil)
//   {
//
//      const char * psz = [str UTF8String];
//
//      application_on_menu_action(m_papplication, psz);
//
//   }
//
//}
{
   
   NSMenuItem * pitem = (NSMenuItem *) sender;
   
//   if(m_papplicationmenu == NULL)
//   {
//
//      return;
//
//   }
   
   NSString * prefixToRemove = @"menu_item_";
   
   NSString * strId = [pitem.representedObject copy];
   
   if ([strId hasPrefix:prefixToRemove])
   {
      
      strId = [strId substringFromIndex:[prefixToRemove length]];
   
      const char * psz = [strId UTF8String];
         
      m_pcommandhandler->handle_command(psz, nullptr);
         
      return;
      
   }
   
}


@end



void os_menu_item_enable(void * pitem, bool bEnable)
{

   NSMenuItem * pmenuitem = (__bridge NSMenuItem *) pitem;

   ns_main_post(^()
   {

      [pmenuitem setEnabled: bEnable];

   });

}


void os_menu_item_check(void * pitem, bool bCheck)
{

   NSMenuItem * pmenuitem = (__bridge NSMenuItem *) pitem;

   ns_main_post(^()
   {
      
      if(bCheck)
      {

         [pmenuitem setState: NSOnState];
         
      }
      else
      {
         
         [pmenuitem setState: NSOffState];
         
      }

   });

}

//
//void ns_create_main_menu(menu_shared * pmenushared)
//{
//
//   if(pmenushared)
//   {
//
//      menu_shared_increment_reference_count(pmenushared);
//
//   }
//
//   ns_main_post(^{
//   id menuMain = [NSMenu alloc];
//
//   macOSApp * papp = (macOSApp *) [[NSApplication sharedApplication] delegate ];
//
//   {
//
//      id menuitemApp = [NSMenuItem alloc];
//
//      [menuMain addItem: menuitemApp];
//
//      id menuApp = [NSMenu alloc];
//
//      [menuitemApp setSubmenu: menuApp];
//
//      id strAppName = [[NSProcessInfo processInfo] processName];
//
//      id strQuitTitle = [[_("Quit") stringByAppendingString: @" "] stringByAppendingString: strAppName];
//
//      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
//                                                   action:@selector(terminate:) keyEquivalent:@"q"];
//
//      if(pmenushared)
//      {
//      [ papp ns_add_menu : menuApp withParent: "" withSharedMenu: pmenushared];
//
//      }
//
//      [menuApp addItem: menuitemQuit];
//
//   }
//
//
//   {
//
//      id menuitemView = [NSMenuItem alloc];
//
//      [menuMain addItem: menuitemView];
//
//      id menuView = [[NSMenu alloc] initWithTitle:_("View")];
//
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//
//      [menuitemView setSubmenu: menuView];
//
//      id strFxxTitle = _("Transparent Frame");
//
//      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
//                                                            action:@selector(on_command:) keyEquivalent:@"f"];
//
//      if(pmenushared)
//      {
//      [ papp ns_add_menu : menuView withParent: "view" withSharedMenu: pmenushared];
//
//      }
//      [menuitemFxx setRepresentedObject: @"transparent_frame"];
//
//      [menuView addItem: menuitemFxx];
//
//   }
//
//   [NSApp setMainMenu:menuMain];
//
//      if(pmenushared)
//      {
//
//         menu_shared_release(pmenushared);
//
//      }
//
//   });
//
//
//
//}
//
//
void os_begin_system();



void apple_set_application_delegate(::platform::application * papplication, void * pDelegate);

void ns_apple_set_application_delegate(::platform::application * papplication, macos_app * pappdelegate)
{
   
   ns_main_send(^
                {
      
      NSApplication * application = [NSApplication sharedApplication];
      
      pappdelegate->m_papplication = papplication;
      
      [ application setDelegate: pappdelegate ];
      
      apple_set_application_delegate(papplication, (__bridge void *) pappdelegate);
      
      [ pappdelegate continueInitialization ];
      
      //[m_statusitem setEnabled:YES];
      
      [NSApplication sharedApplication];
      
      //   bool bNoDock = argcargv_contains_parameter(argc, argv, "no_dock");
      
   });
   
}


void * apple_get_application_delegate(::platform::application * papplication);


//void defer_create_acme_application_delegate(::platform::application * papplication)
//{
//   
//   macos_app * pappdelegate = (__bridge macos_app *) apple_get_application_delegate(papplication);
//
//   if(pappdelegate == nullptr)
//   {
//      
//      pappdelegate = [ [ macos_app alloc ] init ];
//      
//      ns_apple_set_application_delegate(papplication, pappdelegate);
//      
//   }
//   
//}


//
//
//void acme_macos_application_init(::platform::application * papplication, int argc, char *argv[])
//{
//
////   auto argc = psystem->m_psubsystem->m_argc;
////
////   auto argv = psystem->m_psubsystem->m_argv;
////
////   auto papp = psystem->m_pacmeapplication;
////
////   ::platform::application * papplication = (void *) (::acme::application *) papp;
////
//////      acme_macos_application_main(pApplication, argc, argv);
////
////      //return psystem->m_estatus;
////
//////   }
//   ///
//   ///
//   ///
//   defer_create_acme_application_delegate(pApplication);
//
//
//   macos_app * pappdelegate = (macos_app *) apple_get_application_delegate(pApplication);
//
//
//   void apple_set_application_delegate(::platform::application * papplication, void * pDelegate)
//
//
//   NSApplication * application = [NSApplication sharedApplication];
//
//   pmacosapp->m_papplication = pApplication;
//
//   [application setDelegate: pmacosapp];
//
//   [appDelegate fetch_dark_mode];
//
//   //[m_statusitem setEnabled:YES];
//
//   [NSApplication sharedApplication];
//
//   bool bNoDock = argcargv_contains_parameter(argc, argv, "no_dock");
//
//}


//
//void acme_macos_application_init(::platform::application * papplication, int argc, char *argv[])
//{
//
//   //   auto argc = psystem->m_psubsystem->m_argc;
//   //
//   //   auto argv = psystem->m_psubsystem->m_argv;
//   //
//   //   auto papp = psystem->m_pacmeapplication;
//   //
//   //   ::platform::application * papplication = (void *) (::acme::application *) papp;
//   //
//   ////      acme_macos_application_main(pApplication, argc, argv);
//   //
//   //      //return psystem->m_estatus;
//   //
//   ////   }
//   ///
//   ///void defer_create_macos_app()
//
//   macos_app * pmacosapp = [[macos_app alloc] init];
//
//   acme_macos_application_prepare(pmacosapp, pApplication, argc, argv);
//
//}


void acme_macos_application_main(::platform::application * papplication, int argc, char *argv[])
{
   
//
//   if(bNoDock)
//   {
//      
//      nsapp_activation_policy_accessory();
//      
//   }

   [NSApp activateIgnoringOtherApps:YES];
   
   [NSApp run];
   
}


//-(void)applicationActivity:(NSNotification *)notification
//{
//   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
//   
//   NSString * strName = app.localizedName;
//   //if([ isEqualToString:@"ScreenSaverEngine"])
//   {
//      printf("NOTIFICATION: %s", [strName UTF8String]);
//
//      // Your code here
//   }
//}
//
//
//
//- (void)on_command:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   NSString * str = (NSString *)[pitem representedObject];
//if(str != nil)
//{
//         const char * psz = [str UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         on_application_menu_action(psz);
//         
//         return;
//         
//      //}
//      
//   }
//   
//}
//- (void)applicationWillFinishLaunching:(NSNotification *)notification
//{
//NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];// 1
//[appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
//   
//}
//
//- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
//{
//   
//   set_apex_system_as_thread();
//   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
//   
//   defer_run_system();
//   
//}
//
//
//- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
//{
//   
//   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", e_message_box_ok);
//   
//   system_call_update_app_activated();
//
//   return NO;
//   
//}
//
//- (void)applicationDidChangeOcclusionState:(NSNotification *)notification
//{
//   
//   //macos_on_app_changed_occlusion_state();
//   
//}
//
//
//- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
//{
//   
//   file_put_contents("/eco/001.txt", "applicationOpenUntitledFile");
//   //MessageBox(NULL, "applicationOpenUntitledFile", "applicationOpenUntitledFile", e_message_box_ok);
//   
//   defer_run_system();
//   
//   //__start_system_with_file(NULL);
//   
//   return YES;
//   
//}
//
//
//
//- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
//{
//   
//   file_put_contents("/eco/002.txt", "applicationOpenFile");
//   file_put_contents("/eco/003.txt", [filename UTF8String]);
//
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([filename UTF8String]);
//   
//   return true;
//   
//}
//
//
//
//- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
//{
//   
//   unsigned long ulCount = [filenames count];
//   
//   if(ulCount <= 0)
//   {
//      
//      return;
//      
//   }
//   
//   char ** psza = (char **) malloc(ulCount * sizeof(char*));
//   
//   for(unsigned long ul = 0; ul < ulCount; ul++)
//   {
//      
//      char * psz = strdup([[filenames objectAtIndex:ul] UTF8String]);
//      
//      psza[ul] = psz;
//      
//   }
//   
//   defer_run_system(psza, (int) ulCount);
//   
//   
//}
//- (void)application:(NSApplication *)application open:(NSURL * )url
//{
//   file_put_contents("/eco/006.txt", "open");
//   file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
//   
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([[url absoluteString] UTF8String]);
//}
//
//- (BOOL)application:(id)sender
//  openFileWithoutUI:(NSString *)filename;
//{
//   file_put_contents("/eco/007.txt", "openFileWithoutUI");
//   file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
//   
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([filename UTF8String]);
//}
//
//- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
//{
//   unsigned long ulCount = [urls count];
//   
//   if(ulCount <= 0)
//   {
//      
//      return;
//      
//   }
//   
//   char ** psza = (char **) malloc(ulCount * sizeof(char*));
//   
//   for(unsigned long ul = 0; ul < ulCount; ul++)
//   {
//      
//      char * psz = strdup([[[urls objectAtIndex:ul] absoluteString] UTF8String]);
//      
//      psza[ul] = psz;
//      
//   }
//   
//   defer_run_system(psza, (int) ulCount);
//   
//   
//
//}
//
//
////- (void)sendEvent:(NSEvent *)theEvent
////{
////
////   /*
////   
////   char szEvent[128];
////   
////   ·zero(szEvent);
////   
////   if([theEvent type] == NSLeftMouseDown)
////   {
////   
////      strcpy(szEvent, "NSLeftMouseDown");
////      
////   }
////   else if([theEvent type] == NSLeftMouseUp)
////   {
////     
////      strcpy(szEvent, "NSLeftMouseUp");
////      
////   }
////   
////   if(strlen(szEvent) > 0)
////   {
////   
////      char szEventCopy[128];
////   
////      strcpy(szEventCopy, szEvent);
////      
////      printf("\n%s", szEventCopy);
////      
////   }
////   
////   */
////   
////   [super sendEvent:theEvent];
////   
////}
//- (void)handleGetURLEvent:(NSAppleEventDescriptor *)event
//           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
//   
//   // Extract the URL from the Apple event and handle it here.
//   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
//   
//   defer_run_system([url UTF8String]);
//   
//}
//-(NSMenu *) applicationDockMenu:(NSApplication*)sender
//{
//
//   
//   return m_menu;
//   
//}
//
////[appDelegate->m_menu setDelegate:NSApp];
//
//
//@end

//
//void ns_create_main_menu()
//{
//   
//   
//   id menuMain = [NSMenu alloc];
//   
//   {
//      
//      id menuitemApp = [NSMenuItem alloc];
//      
//      [menuMain addItem: menuitemApp];
//      
//      id menuApp = [NSMenu alloc];
//      
//      [menuitemApp setSubmenu: menuApp];
//      
//      id strAppName = [[NSProcessInfo processInfo] processName];
//      
//      id strQuitTitle = [[_("Quit") stringByAppendingString: @" "] stringByAppendingString: strAppName];
//      
//      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
//                                                   action:@selector(terminate:) keyEquivalent:@"q"];
//      
//      [menuApp addItem: menuitemQuit];
//      
//   }
//   
//   {
//      
//      id menuitemView = [NSMenuItem alloc];
//      
//      [menuMain addItem: menuitemView];
//      
//      id menuView = [[NSMenu alloc] initWithTitle:_("View")];
//      
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//      
//      [menuitemView setSubmenu: menuView];
//      
//      id strFxxTitle = _("Trasparentt(snowballeffect_smallerror>>>)Fxx");
//      
//      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
//                                                            action:@selector(on_command:) keyEquivalent:@"f"];
//      
//      [menuitemFxx setRepresentedObject: @"transparent_frame"];
//      
//      [menuView addItem: menuitemFxx];
//      
//   }
//   
//   [NSApp setMainMenu:menuMain];
//   
//   
//}




//void apex_application_main(int argc, char *argv[])
//{
//
//   NSApplication * application = [NSApplication sharedApplication];
//
//   macOSApp * appDelegate = [[macOSApp alloc] init];
//
//   [application setDelegate:appDelegate];
//
//   [NSApplication sharedApplication];
//
//   bool bNoDock = argcargv_contains_paramater(argc, argv, "no_dock");
//
//   if(bNoDock)
//   {
//
//      nsapp_activation_policy_accessory();
//
//   }
////   else
////   {
////
////      nsapp_activation_policy_regular();
////
////   }
//
//
//   [NSApp activateIgnoringOtherApps:YES];
//
//   [NSApp run];
//
//}
//
//
//


//
//namespace user
//{
//
//
//
//
//   bool is_dark_mode()
//   {
//      
//         
//      return g_bMacosDarkMode;
//      
//   }
//
//
//} // namespace user


CLASS_DECL_ACME void ns_get_main_screen_size(int & cx, int & cy)
{
   
   auto frame = [[NSScreen mainScreen] frame];
   
   cx = frame.size.width;
   
   cy = frame.size.height;
   
}


bool g_bNsAppRunning = false;


void ns_app_set_running(bool bRunning)
{
   
   g_bNsAppRunning = bRunning;
   
}


bool ns_app_is_running()
{
   
   return g_bNsAppRunning;
   
}


void ns_app_run()
{
   
   ns_app_set_running(true);
   
   [ [ NSApplication sharedApplication ] run ];
   
   ns_app_set_running(false);
   
}


void ns_app_post_quit()
{
   
   ns_main_post(^()
                {
      
      [ [ NSApplication sharedApplication ] stop:nil ];
      //   NSEvent* event = [NSEvent otherEventWithType: NSApplicationDefined
      //                                                        location: NSMakePoint(0,0)
      //                                                  modifierFlags: 0
      //                                                      timestamp: 0.0
      //                                                   windowNumber: 0
      //                                                        context: nil
      //                                                        subtype: 0
      //                                                          data1: 0
      //                                                          data2: 0];
      //                   [[ NSApplication sharedApplication ] postEvent: event atStart: FALSE];
      
   });
}



// https://stackoverflow.com/questions/48020222/how-to-make-nsapp-run-not-block
void ns_app_do_tasks()
{
   
   //auto prun = [ NSRunLoop mainRunLoop ];
   
   //auto runloop = [ prun getCFRunLoop ];
   
   ///CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0., false);
   
   //NSLog(@"123");
   //[ prun run ];
   
//
//   while(true)
//   {
//   
//      NSEvent * pevent =
//         [ NSApp nextEventMatchingMask : NSEventMaskAny
//                              untilDate : [ NSDate distantPast ]
//                              inMode : NSDefaultRunLoopMode
//                              dequeue : YES ];
//      if (!pevent)
//      {
//         
//         break;
//         
//      }
//
//      [ NSApp sendEvent : pevent ];
//      
//    }

}


NSMenu * ns_create_menu(::application_menu * papplicationmenu, bool bMainMenu)
{
   
   NSMenu * menu = nil;
   
   if(papplicationmenu->m_strName.has_character())
   {
      
      menu = [ [ NSMenu alloc ] initWithTitle:__nsstring(papplicationmenu->m_strName)];
      
   }
   else
   {
      
      menu = [ NSMenu alloc ];
      
   }
   
   ns_create_menu(menu, papplicationmenu, bMainMenu);
   
   return menu;
   
}


void ns_create_menu(NSMenu * menu, ::application_menu * papplicationmenu, bool bMainMenu)
{
   
//   if(bMainMenu)
//   {
//
//      ensure_edit_menu(pmenu);
//
//   }
   
   for(auto pitem : *papplicationmenu)
   {
      
      NSMenuItem * menuitem = nil;
      
      if(pitem->is_popup())
      {
         
         menuitem = [ NSMenuItem alloc ];
         
         id menuSub = ns_create_menu(pitem, false);
       
         [ menuSub setDelegate: [ [NSApplication sharedApplication] delegate ] ];
         
         [ menuitem setSubmenu: menuSub];

      }
      else if(pitem->is_separator())
      {
         
         menuitem = [NSMenuItem separatorItem];
         
      }
      else
      {
         
         id strTitle = __nsstring(pitem->m_strName);
         id strAcc = __nsstring(pitem->m_strAccelerator);
         
         ::string strMenuItemId;
         
         strMenuItemId = "menu_item_" + pitem->m_atomMenu.as_string();
         
         id strId = __nsstring(strMenuItemId);
         
         menuitem = [[NSMenuItem alloc] initWithTitle:strTitle
                                                            action:@selector(on_application_menu_action:) keyEquivalent:strAcc];
         
         [ menuitem setTarget: [ [NSApplication sharedApplication] delegate ] ];

         [ menuitem setRepresentedObject: strId ];
         
      }

      [menu addItem: menuitem];

   }
   
}



void ensure_edit_menu(::application_menu * papplicationmenu)
{
   
   auto iEdit = papplicationmenu->find_child_with_name("Edit");
   
   if(iEdit >= 0)
   {
    
      return;
      
   }

   auto iFile = papplicationmenu->find_child_with_name("File");
   
   if(iFile >= 0)
   {
      
      iEdit = iFile + 1;
      
   }
   else if(papplicationmenu->has_element())
   {
      
      iEdit = 1;
      
   }
   else
   {
    
      iEdit = 0;
      
   }
    
   papplicationmenu->popup_at(iEdit, "Edit");
      
}




void ns_application_handle(long long l, void * p)
{
   
   ns_main_post(^{

      macos_app * papp = nullptr;
      
      papp = (macos_app *) [ [NSApplication sharedApplication] delegate ] ;
      
      [papp application_handle: l withPointer:p];

   });
   
}
