//
//  app.m
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 16/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#import "framework.h"
#import "NSBundle+OBCodeSigningInfo.h"

bool nsapp_activation_policy_is_regular()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyRegular)
   {
      
      return true;
      
   }
   
   return false;
   
}


int nsapp_activation_policy_is_accessory()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyAccessory)
   {
      
      return true;
      
   }
   
   return false;
   
}


bool nsapp_activation_policy_is_prohibited()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyProhibited)
   {
      
      return true;
      
   }
   
   return false;
   
}


void nsapp_activation_policy_regular()
{
   
   ns_main_post(^{
   
      [NSApp  setActivationPolicy:NSApplicationActivationPolicyRegular];
   
   });
   
}


void nsapp_activation_policy_accessory()
{
   ns_main_post(^{
      
      [NSApp setActivationPolicy:NSApplicationActivationPolicyAccessory];
       
   });
   
}


void nsapp_activation_policy_prohibited()
{
  
   ns_main_post(^{
   
      [NSApp setActivationPolicy:NSApplicationActivationPolicyProhibited];
   
   });
   
}


void nsapp_activate_ignoring_other_apps(int i)
{
   
   ns_main_post(^{
      
      if(i)
      {
      
         [NSApp activateIgnoringOtherApps: YES];
      
      }
      else
      {
      
         [NSApp activateIgnoringOtherApps: NO];
      
      }
                 
   });
   
}


NSAppleScript * ns_get_dark_mode_script()
{
   
   return [[NSAppleScript alloc] initWithSource :@"tell app \"System Events\" to tell appearance preferences to set dark mode to true"];
   
}


NSAppleScript * ns_get_lite_mode_script()
{
   
   return [[NSAppleScript alloc] initWithSource :@"tell app \"System Events\" to tell appearance preferences to set dark mode to false"];
}


// Don't forget to:
// add NSAppleEventsUsageDescription to Info.plist with System Events usage description
// add Apple Events Hardened Runtime entitlement

bool ns_set_dark_mode(bool bDark)
{
   
   NSAppleScript * pscript = nil;
   
   if(bDark)
   {
      
      pscript = ns_get_dark_mode_script();
      
   }
   else
   {
    
      pscript = ns_get_lite_mode_script();
      
   }
   
   NSDictionary *error = nil;
   
   [pscript executeAndReturnError:&error];
   
   return error == nil;
   
}

bool ns_is_sandboxed()
{
   
   return [[NSBundle mainBundle]ob_isSandboxed];
   
}

char * bundleSeedID()
{
    NSString *tempAccountName = @"bundleSeedID";
    NSDictionary *query = @{
        (__bridge NSString *)kSecClass : (__bridge NSString *)kSecClassGenericPassword,
        (__bridge NSString *)kSecAttrAccount : tempAccountName,
        (__bridge NSString *)kSecAttrService : @"",
        (__bridge NSString *)kSecReturnAttributes: (__bridge NSNumber *)kCFBooleanTrue,
    };
    CFDictionaryRef result = nil;
    OSStatus status = SecItemCopyMatching((__bridge CFDictionaryRef)query, (CFTypeRef *)&result);
    if (status == errSecItemNotFound)
        status = SecItemAdd((__bridge CFDictionaryRef)query, (CFTypeRef *)&result);
    if (status != errSecSuccess) {
        return nil;
    }
    status = SecItemDelete((__bridge CFDictionaryRef)query); // remove temp item
    NSDictionary *dict = (__bridge_transfer NSDictionary *)result;
    NSString *accessGroup = dict[(__bridge NSString *)kSecAttrAccessGroup];
    NSArray *components = [accessGroup componentsSeparatedByString:@"."];
    NSString *bundleSeedID = [[components objectEnumerator] nextObject];
    return strdup([bundleSeedID UTF8String]);
}



BOOL macos_launch_on_login()
{
    LSSharedFileListRef loginItemsListRef = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
    CFArrayRef snapshotRef = LSSharedFileListCopySnapshot(loginItemsListRef, NULL);
    NSArray* loginItems = (__bridge_transfer NSArray *)snapshotRef;
    NSURL *bundleURL = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    for (id item in loginItems) {
        LSSharedFileListItemRef itemRef = (__bridge_retained LSSharedFileListItemRef)item;
        CFURLRef itemURLRef;
        if (LSSharedFileListItemResolve(itemRef, 0, &itemURLRef, NULL) == noErr) {
            NSURL *itemURL = (__bridge_transfer NSURL *)itemURLRef;
            if ([itemURL isEqual:bundleURL]) {
                return YES;
            }
        }
    }
    return NO;
}

void macos_set_launch_on_login(int launchOnLogin)
{
    NSURL *bundleURL = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    LSSharedFileListRef loginItemsListRef = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);

    if (launchOnLogin) {
        NSDictionary *properties;
        properties = [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:@"com.apple.loginitem.HideOnLaunch"];
        LSSharedFileListItemRef itemRef = LSSharedFileListInsertItemURL(loginItemsListRef, kLSSharedFileListItemLast, NULL, NULL, (__bridge_retained CFURLRef)bundleURL, (__bridge_retained CFDictionaryRef)properties,NULL);
        if (itemRef) {
            CFRelease(itemRef);
        }
    } else {
        LSSharedFileListRef loginItemsListRef = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
        CFArrayRef snapshotRef = LSSharedFileListCopySnapshot(loginItemsListRef, NULL);
        NSArray* loginItems = (__bridge_transfer NSArray* )snapshotRef;

        for (id item in loginItems) {
            LSSharedFileListItemRef itemRef = (__bridge_retained LSSharedFileListItemRef)item;
            CFURLRef itemURLRef;
            if (LSSharedFileListItemResolve(itemRef, 0, &itemURLRef, NULL) == noErr) {
                NSURL *itemURL = (__bridge_transfer NSURL *)itemURLRef;
                if ([itemURL isEqual:bundleURL]) {
                    LSSharedFileListItemRemove(loginItemsListRef, itemRef);
                }
            }
        }
    }
}
