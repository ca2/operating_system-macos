//
//  monitor.m
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 20:48 BRT <3ThomasBS_!!
//
#include "framework.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

void ns_main_async(dispatch_block_t block);


void ns_main_sync(dispatch_block_t block);

void ns_monitor_cgrect(int i, CGRect * prect);
void __ns_monitor_cgrect(int i, CGRect * prect);
void __ns_main_monitor_cgrect(CGRect * prect);

int ns_monitor_count()
{
   
   auto screenArray = [NSScreen screens];

   auto count = [screenArray count];

   return (int) count;
   
}


void ns_screen_translate(CGRect * prect, int iIndex)
{
   
   CGRect rectMonitor;

   __ns_monitor_cgrect(iIndex, &rectMonitor);
   
   auto nsBottom = prect->origin.y + prect->size.height;
   
   auto top = rectMonitor.origin.y + rectMonitor.size.height;

   prect->origin.y = top - nsBottom;

}


void ns_monitor_cgrect(int i, CGRect * prect)
{
   
   __ns_monitor_cgrect(i, prect);

   ns_screen_translate(prect, i);
   
}


void ns_main_monitor_cgrect(CGRect * prect)
{
   
   __ns_main_monitor_cgrect(prect);
   
}


void ns_workspace_cgrect(int iIndex, CGRect * prect)
{

   NSScreen * pscreen;
   
   if(iIndex >= 0)
   {
      
      auto screenArray = [NSScreen screens];

      pscreen = [screenArray objectAtIndex:iIndex];
      
   }
   else
   {
      
      pscreen = [NSScreen mainScreen];
      
   }

   *prect = [pscreen visibleFrame];
   
   ns_screen_translate(prect, iIndex);
   
}


void __ns_main_monitor_cgrect(CGRect * prect)
{

   auto pscreen = [NSScreen mainScreen];

   *prect = [pscreen frame];
   
}


void __ns_monitor_cgrect(int iIndex, CGRect * prect)
{

   NSScreen * pscreen;
   
   if(iIndex >= 0)
   {
      
      auto screenArray = [NSScreen screens];

      pscreen = [screenArray objectAtIndex:iIndex];
      
   }
   else
   {
      
      pscreen = [NSScreen mainScreen];
      
   }

   *prect = [pscreen frame];

}



void ns_set_wallpaper(const char * pszUrl)
{
   
   auto p = strdup(pszUrl);
   
   ns_main_async(^()
   {
      
      NSString * strUrl = [ [ NSString alloc ] initWithUTF8String: p ];
      
      NSURL * url = [ NSURL fileURLWithPath: strUrl ];
      
      NSError * error = nil;
      
      NSScreen * pmainscreen = [ NSScreen mainScreen ];
      
      
      NSColor * pcolorFill = nil;
      
      if (@available(macOS 10.10, *)) {
         pcolorFill =[ NSColor systemGrayColor   ];
         
      }
      else
      {
         
         pcolorFill = [ NSColor lightGrayColor];
         
      }

         NSDictionary * options =
         [
            NSDictionary
            
            dictionaryWithObjectsAndKeys:
               
               pcolorFill,
            NSWorkspaceDesktopImageFillColorKey,
            
            [ NSNumber numberWithBool: NO ],
            NSWorkspaceDesktopImageAllowClippingKey,
            
            [ NSNumber numberWithInteger: NSImageScaleNone ],
            NSWorkspaceDesktopImageScalingKey,
            
            nil
            
         ];
         
         const char * pszError = nullptr;
         
         BOOL bOk = [ [ NSWorkspace sharedWorkspace ] setDesktopImageURL: url forScreen: pmainscreen options:options error:&error];
     
      
      if(bOk)
      {
         
         printf("Wallpaper was set to : \"%s\"\n", p);
         
      }
      else
      {
         
         pszError = [ [ error localizedDescription ] UTF8String ];
         
         printf("Wallpaper wasn't set to : \"%s\" Error:%s\n", p, pszError);

         
      }
   
      ::free(p);
      
   });
   
}


char * ns_get_wallpaper()
{
   
   __block char * p = nullptr;
   
   ns_main_sync(^()
   {

      NSScreen * pmainscreen = [ NSScreen mainScreen ];
      
      NSURL * url = [ [ NSWorkspace sharedWorkspace ] desktopImageURLForScreen: pmainscreen];
      
      if(url == nil)
      {
         
         return;
         
      }
      
      NSString * str = [ url absoluteString ];
      
      auto psz = [ str UTF8String ];
      
      p = strdup(psz);
      
   });
 
   return p;
   
}
