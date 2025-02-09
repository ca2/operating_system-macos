//
//  RoundWindowApp.m
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 27/09/14.
//
//

#include "framework.h"
#include "macOSApp.h"
#include "acme/constant/id.h"
#include "aura/_.h"
#include "aura_macos/_c_mm.h"
#include "acme/operating_system/argcargv.h"
#import <StoreKit/StoreKit.h>

bool application_get_bool(::platform::application * papplication, const char * pszItem);

void ns_main_post(dispatch_block_t block);



NSString * __nsstring(const char * psz);
//#include "apex/user/menu_shared.h"

//void on_start_system(::platform::system * psystem);

void os_system_start();
int file_put_contents(const char * path, const char * contents);
void file_add_contents_raw(const char * path, const char * psz);

void application_on_menu_action(::platform::application * papplication, const char * pszCommand);
::platform::system * application_system(::platform::application * papplication);


void system_id_update(::platform::system * psystem, long long iUpdate, long long iPayload);


//void ns_application_update(long long iUpdate, void * p);

void node_will_finish_launching(::platform::system * psystem);
void system_on_open_untitled_file(::platform::system * psystem);
void system_on_open_file(::platform::system * psystem, const char * pszFile);


//void system_call_update_app_activated();
void macos_on_app_changed_occlusion_state();

void set_apex_system_as_thread();


@implementation macOSApp


//@synthesize windowcontroller;
- (id)initWithApplicationMenu:(::application_menu *) papplicationmenu andCommandHandler:(::command_handler *)pcommandhandler
{

   self = [super init];
   
   m_papplicationmenu = papplicationmenu;
   
   m_pcommandhandler = pcommandhandler;
   
   //[ self application_menu_update ];
   


//
//   [[[NSWorkspace sharedWorkspace] notificationCenter]
//    addObserver:self
//    selector:@selector(applicationDidChangeOcclusionState:)
//    name:NSApplicationDidChangeOcclusionStateNotification
//    object:nil];
   return self;
}

-(void)dealloc
{
   
   
   
}


//-(void)application_handle: (long long) l withPointer :(void *) p
//{
//   
//   [ super application_handle:l withPointer:<#p#>];
//   
//}


-(void)continueInitialization
{
 
   [ super continueInitialization ];
   
   bool bNoDock = application_get_bool(m_papplication, "no_dock");
   
   if(bNoDock)
   {
      
      nsapp_activation_policy_accessory();
      
   }

   [NSApp activateIgnoringOtherApps:YES];

   
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



- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
   
   [[[NSWorkspace sharedWorkspace] notificationCenter]
       addObserver:self
       selector:@selector(applicationActivity:)
       name:NSWorkspaceActiveSpaceDidChangeNotification
       object:nil];

   [ self application_menu_update ];
   
   [ super applicationWillFinishLaunching: notification];
   
//   node_will_finish_launching(application_system(m_papplication));
//
//   NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];
//
//   [appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
   
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
   
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
   
   //file_put_contents("/Users/camilo/debug/open_file.txt", [filename UTF8String]);

   system_on_open_file(application_system(m_papplication), [filename UTF8String]);
   
   return true;
   
}



- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
{
   
   
   //file_put_contents("/Users/camilo/debug/open_files.txt", "");

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
   
   
   //file_put_contents("/Users/camilo/debug/open(url).txt", [[url absoluteString] UTF8String]);

   //file_put_contents("/eco/006.txt", "open");
   //file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_papplication), [[url absoluteString] UTF8String]);
   
}


- (BOOL)application:(id)sender
  openFileWithoutUI:(NSString *)filename;
{
   
   
   //file_put_contents("/Users/camilo/debug/openFileWithoutUI(url).txt", [filename UTF8String]);

   //file_put_contents("/eco/007.txt", "openFileWithoutUI");
   //file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
   
   
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_papplication), [filename UTF8String]);
   
   return TRUE;
   
}

- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
{
   
   
   //file_put_contents("/Users/camilo/debug/open_urls.txt", "");

   unsigned long ulCount = [urls count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   //char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      const char * psz = [[[urls objectAtIndex:ul] absoluteString] UTF8String];
      
      //psza[ul] = psz;
      
      //file_add_contents_raw("/Users/camilo/debug/open_urls.txt", psz);
      //file_add_contents_raw("/Users/camilo/debug/open_urls.txt", "\n");
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
   
   
   //file_put_contents("/Users/camilo/debug/handleGetURLEvent.txt", [url  UTF8String]);


   system_on_open_file(application_system(m_papplication), [url UTF8String]);
   
}


-(NSMenu *) applicationDockMenu:(NSApplication*)sender
{

   return m_menu;
   
}
//
//
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



- (void)checkStoreKitPermissions {
//  NSString *mg;
//  SKCloudServiceAuthorizationStatus status = SKCloudServiceController.authorizationStatus;
//  switch (status) {
//    case SKCloudServiceAuthorizationStatusNotDetermined:{
//      // Not determined: ask for permission.
//      [SKCloudServiceController requestAuthorization:^(SKCloudServiceAuthorizationStatus status) {
//        [self checkStoreKitPermissions];
//      }];
//      break;
//    }
//    case SKCloudServiceAuthorizationStatusAuthorized:
//      // Authorized: proceed.
//      NSLog(@"YES SUBSCRIBED!!!!");
//      [self getUserStorefrontID];
//      break;
//    default:
//      // Denied or restricted: do not proceed.
//      NSLog(@"NOT SUBSCRIBED!!!!");
////      NSString * strMessage = [NSString stringWithFormat:@"It appears that you are not currently      subscribed to Apple Music.  Please subscribe to Apple Music and then re-open this App.  This App will close when you touch OK."];
////      [self msgOKend:strMessage];
//      break;
//  }
}
//- (void) getUserStorefrontID{
//  SKCloudServiceController *controller = [SKCloudServiceController new];
//  [controller requestStorefrontIdentifierWithCompletionHandler:^(NSString * _Nullable storefrontIdentifier, NSError * _Nullable error) 
//   {
////    if (error != nil) {
////      userStoreFrontID= nil;
////      NSLog(@"ERROR-no storefrontID");
////    } else {
////      userStoreFrontID= storefrontIdentifier;
////      NSLog(@"Got storefrontID = %@ ", userStoreFrontID);
////    }
//  }];
//}
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

         [pmenuitem setState: NSControlStateValueOn];
         
      }
      else
      {
         
         [pmenuitem setState: NSControlStateValueOff];
         
      }

   });

}


//NSMenu * _ns_create_main_menu(menu_shared * pmenushared)
//{
//   
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
//      id strAppName = __nsstring(pmenushared->application_name());
//      
//      id menuApp = [[NSMenu alloc] initWithTitle: strAppName];
//      
//      [menuitemApp setSubmenu: menuApp];
//      
//      id strQuitTitle = __nsstring("Quit " +  pmenushared->application_name());
//      
//      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
//                                                   action:@selector(terminate:) keyEquivalent:@"q"];
//
//      [ papp ns_add_menu : menuApp withParent: "" withSharedMenu: pmenushared];
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
//      id menuView = [[NSMenu alloc] initWithTitle:__nsstring("View")];
//      
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//      
//      [menuitemView setSubmenu: menuView];
//      
//      id strFxxTitle = __nsstring("Transparent Frame");
//      
//      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
//                                                            action:@selector(on_command:) keyEquivalent:@"f"];
//      
//      [ papp ns_add_menu : menuView withParent: "view" withSharedMenu: pmenushared];
//
//      [menuitemFxx setRepresentedObject: @"transparent_frame"];
//      
//      [menuView addItem: menuitemFxx];
//      
//   }
//
//   return menuMain;
//   
//}
//
//
//void ns_create_main_menu(menu_shared * pmenushared)
//{
//
//   menu_shared_increment_reference_count(pmenushared);
//
//   ns_main_post(
//   ^{
//      
//      NSMenu * menuMain = _ns_create_main_menu(pmenushared);
//   
//      [NSApp setMainMenu:menuMain];
//      
//      menu_shared_release(pmenushared);
//      
//   });
//   
//}


void os_begin_system();


void ns_app_run();

void ns_apple_set_application_delegate(::platform::application * papplication, macos_app * pappdelegate);
void * apple_get_application_delegate(::platform::application * papplication);

void aura_defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::command_handler * pcommandhandler)
{
   
   macos_app * pappdelegate = (__bridge macos_app *) apple_get_application_delegate(papplication);
   
   if(pappdelegate == nullptr)
   {
      
      pappdelegate = [ [ macOSApp alloc] initWithApplicationMenu: papplicationmenu andCommandHandler: pcommandhandler];
      
      ns_apple_set_application_delegate(papplication, pappdelegate);
      
   }
   
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



//NSMenu * ns_create_application_menu(application_menu * pmenu)
//{
//   
//   
//   id menu = [NSMenu alloc];
//   
////   {
////      
////      id menuitemApp = [NSMenuItem alloc];
////      
////      [menuMain addItem: menuitemApp];
////      
////      id menuApp = [NSMenu alloc];
////      
////      [menuitemApp setSubmenu: menuApp];
////      
////      id strAppName = [[NSProcessInfo processInfo] processName];
////      
////      id strQuitTitle = __nsstring("Quit " + ::string([strAppName UTF8String]));
////      
////      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
////                                                   action:@selector(terminate:) keyEquivalent:@"q"];
////      
////      [menuApp addItem: menuitemQuit];
////      
////   }
//
//   for(auto & item : *papplicationmenu)
//   {
//      
//      id menuitem = [ NSMenuItem alloc ];
//      
//      [ menu addItem: menuitem];
//      
//      if(item.has_element())
//      {
//      
//         id menuView = [[NSMenu alloc] initWithTitle:__nsstring(item."View")];
//      
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//      
//      [menuitemView setSubmenu: menuView];
//      
//      id strFxxTitle = __nsstring("Trasparentt(snowballeffect_smallerror>>>)Fxx");
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
//      id strQuitTitle = __nsstring("Quit " + ::string([strAppName UTF8String]));
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
//      id menuView = [[NSMenu alloc] initWithTitle:__nsstring("View")];
//      
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//      
//      [menuitemView setSubmenu: menuView];
//      
//      id strFxxTitle = __nsstring("Trasparentt(snowballeffect_smallerror>>>)Fxx");
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
//



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







