#include "framework.h"
#include "acme/constant/id.h"
#import "save_file_dialog_delegate.h"
#include "acme/filesystem/filesystem/file_dialog.h"


NSWindow * g_pnswindow = nullptr;


NSWindow * ns_main_window()
{

   return g_pnswindow;
   
}


void ns_set_main_window(NSWindow * pnswindow)
{
   
   g_pnswindow = pnswindow;
   
}


void millis_sleep(::u64 uMillis);

void system_id_update(void * pSystem, ::i64 iUpdate, ::i64 iPayload);
//void system_call_update_wallpaper_changed();

bool mm2_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);

void * get_system_mmos(void * pSystem);
void set_system_mmos(void * pSystem, void * pmmos);


void init_mmos(void * pSystem)
{

   auto pmmos = ([[mmos alloc] init]);

   set_system_mmos(pSystem, (__bridge_retained void *) pmmos);

   pmmos->m_pSystem = pSystem;
   
   pmmos->theLock = [[NSRecursiveLock alloc] init];
   
   pmmos->m_ppszWallpaper = NULL;
   
   pmmos->m_llWallpaper = 0;
   
   pmmos->m_iIcon = 0;
   
   [pmmos monitorWallpaper];
   
   [pmmos monitorIconForFile];
   
   [[pmmos dd_invokeOnMainThreadAndWaitUntilDone: TRUE] deferWallpaper:NULL];
   
}

void term_mmos(void * pSystem)
{
   
   auto pmmos = (__bridge_transfer mmos *) get_system_mmos(pSystem);
   
   [pmmos dd_fake];
   
}

//
//void ns_main_async(dispatch_block_t block)
//{
//   
//   //   dispatch_block_t block = ^{
//   //      // Code for the method goes here
//   //   };
//   //
//   
//   if ([NSThread isMainThread])
//   {
//      
//      block();
//      
//   }
//   else
//   {
//      
//      dispatch_async(dispatch_get_main_queue(), block);
//      
//   }
//   
//}





@implementation mmos

//-(NSURL *)browse_folder : (NSURL *) directoryURL canCreateDirectories: (bool) bCanCreateDirectories
//{
//
//   NSOpenPanel * panel = [NSOpenPanel openPanel];
//
//   [panel setCanCreateDirectories: bCanCreateDirectories];
//
//   [panel setAllowsMultipleSelection: NO];
//
//   [panel setCanChooseDirectories:YES];
//
//   [panel setCanChooseFiles:NO];
//
//   if(directoryURL != nil)
//   {
//
//      panel.directoryURL = directoryURL;
//
//   }
//
//   if ([panel runModal] != NSModalResponseOK)
//   {
//
//      return NULL;
//
//   }
//
//   return [[panel URLs] lastObject];
//
//}


//-(NSArray < NSURL *> *)browse_file_open : (NSURL **) startDir multi: (bool) b
//{
//
//   NSOpenPanel *panel = [NSOpenPanel openPanel];
//
//      [panel setAllowsMultipleSelection:b];
//
//      [panel setCanChooseDirectories:NO];
//
//      [panel setCanChooseFiles:YES];
//
//      if(startDir != nil && *startDir !=nil)
//      {
//
//         panel.directoryURL= *startDir;
//
//      }
//
//      NSInteger result = [panel runModal];
//
//      if(startDir != nil)
//      {
//
//         *startDir = panel.directoryURL;
//
//      }
//
//      if(result != NSModalResponseOK)
//      {
//
//         return NULL;
//
//      }
//
//
//   return [panel URLs];
//
//}


- (id)get
{
   
//   static mmos * s_mmos = NULL;
//
//   if(s_mmos == NULL)
//   {
//
//      s_mmos = ([[self alloc] init]);
//
//      s_mmos->theLock = [[NSRecursiveLock alloc] init];
//
//      s_mmos->m_ppszWallpaper = NULL;
//
//      s_mmos->m_llWallpaper = 0;
//
//      s_mmos->m_iIcon = 0;
//
//      [s_mmos monitorWallpaper];
//
//      [s_mmos monitorIconForFile];
//
//      [[s_mmos dd_invokeOnMainThreadAndWaitUntilDone: TRUE] deferWallpaper:NULL];
//
//   }
   
   return (__bridge mmos *) get_system_mmos(m_pSystem);
   
}


- (void)get_user_wallpaper:(void **)charpp forScreen:(NSScreen *) s;
{
   
   char ** ppsz = (char **) charpp;
   
   NSURL * purl = [[NSWorkspace sharedWorkspace] desktopImageURLForScreen:s];
   
   if(purl == NULL)
   {
      
      *ppsz = NULL;
      
   }
   else
   {
   
      *ppsz = strdup([[purl absoluteString] UTF8String]);
                     
   }
   
}


- (void)get_user_wallpaper:(void *)charppp getCount:(void *) llp
{

   long long * pll = (long long *) llp;

   NSArray<NSScreen *> * screenArray = [NSScreen screens];

   *pll = [screenArray count];
   
   char ** p = (char **) malloc(*pll * sizeof(char*));
   
   char *** ppsz = (char ***) charppp;
   
   *ppsz = p;

   for (int i = 0; i < *pll; i++)
   {
   
      NSScreen * screen = [screenArray objectAtIndex: i];
      
      [self get_user_wallpaper: (void **)&p[i] forScreen:screen];
   
   }
   
}


- (void)desktopImageChanged:(NSNotification *)notification
{

   system_id_update(m_pSystem, id_wallpaper_changed, 0);

}


-(void)applicationActivity:(NSNotification *)notification
{
   
   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
   
   if([app.localizedName isEqualToString:@"ScreenSaverEngine"])
   {
      
      system_id_update(m_pSystem, id_wallpaper_changed, 0);
      
   }
   
}


-(void)monitorWallpaper
{
   
   NSRunLoop* myRunLoop = [NSRunLoop mainRunLoop];
   
   NSMethodSignature *sgn = [self methodSignatureForSelector:@selector(deferWallpaper:)];
   
   NSInvocation *inv = [NSInvocation invocationWithMethodSignature: sgn];
   
   [inv setTarget: self];
   
   [inv setSelector: @selector(deferWallpaper:)];
   
   NSTimer *t = [NSTimer timerWithTimeInterval: 0.1
                                    invocation:inv
                                       repeats:YES];
   
   [myRunLoop addTimer:t forMode:NSDefaultRunLoopMode];
   
}


-(void)runRunnableOnMainThread:(matter *)prunnable
{
   
   [[self dd_invokeOnMainThread] runRunnable: prunnable];
   
}


-(void)runRunnable:(matter *)prunnable
{
   
   __call(prunnable);
   
}


-(void)deferWallpaper:(NSTimer *)timer
{
   
   char ** ppsz = NULL;
   
   long long ll;
   
   [self get_user_wallpaper: (void *) &ppsz getCount: (void *) &ll];
   
   [self->theLock lock];
   
   char ** ppszOld = self->m_ppszWallpaper;
   
   long long llOld = self->m_llWallpaper;
   
   if(ppsz != NULL)
   {
      
      self->m_ppszWallpaper = ppsz;
      
      self->m_llWallpaper = ll;
      
      for(long long i = 0; i < llOld; i++)
      {
         
         free(ppszOld[i]);
         
      }
      
      free(ppszOld);
      
   }

   [self->theLock unlock];
   
}


-(void)monitorIconForFile
{
   
   NSRunLoop* myRunLoop = [NSRunLoop mainRunLoop];
   
   NSMethodSignature *sgn = [self methodSignatureForSelector:@selector(deferIconForFile:)];

   NSInvocation *inv = [NSInvocation invocationWithMethodSignature: sgn];

   [inv setTarget: self];

   [inv setSelector:@selector(deferIconForFile:)];
   
   NSTimer *t = [NSTimer timerWithTimeInterval: 0.1 invocation:inv repeats:YES];
   
   [myRunLoop addTimer:t forMode:NSDefaultRunLoopMode];
   
}


-(void)deferIconForFile:(NSTimer *)timer
{

   if(self->m_iIcon != 1)
   {
      
      return;
      
   }
      
   if(self->m_pszIcon == NULL)
   {
      
      self->m_iIcon = 0;
      
      return;
      
   }
   
   mm2_get_file_image(self->m_picon, self->m_cxIcon, self->m_cyIcon, self->m_iScanIcon, self->m_pszIcon);
   
   self->m_iIcon = 0;
   
}


@end


bool mm1a_get_file_image(void * pSystem, unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   auto pmmos = (__bridge mmos *) get_system_mmos(pSystem);
   
   if(pmmos->m_iIcon == 0)
   {

      pmmos->m_pszIcon = psz;

      pmmos->m_picon = pcr;

      pmmos->m_cxIcon = cx;

      pmmos->m_cyIcon = cy;

      pmmos->m_iScanIcon = iScan;

      pmmos->m_iIcon = 1;

      while(pmmos->m_iIcon != 0)
      {
         
         millis_sleep(5);
         
      }

   }
   
   return true;
      
}


void ns_set_this_process_binary_default_browser()
{
   
   CFBundleRef bundle = CFBundleGetMainBundle();
   
   CFURLRef url = CFBundleCopyBundleURL(bundle);
   
   LSRegisterURL(url, true);
   
   CFStringRef identifier = CFBundleGetIdentifier(bundle);
   
   LSSetDefaultHandlerForURLScheme(CFSTR("http"), identifier);
   
}


void ns_log(const char * pszLog)
{
 
   NSString * strLog = [[NSString alloc]initWithUTF8String:pszLog];
   
   NSLog(@"%@", strLog);
   
}


void ns_main_async(dispatch_block_t block);


void mm_folder_dialog(::function < void(const char *) > functionParameter, const char * pszStartFolder, bool bCanCreateDirectories)
{
   
   __block auto function = functionParameter;
   
   __block NSString * strStartFolder = nil;
   
   if(pszStartFolder != nullptr)
   {
      
      strStartFolder = [[NSString alloc] initWithUTF8String:pszStartFolder];
      
   }

   ns_main_async(^
   {

      //mmos * pos = (__bridge mmos *) get_system_mmos(pSystem);

      NSURL * urlStartFolder = nil;

      if(strStartFolder != nil)
      {

         urlStartFolder = [[NSURL alloc]initWithString : strStartFolder];

      }

      NSOpenPanel * panel = [NSOpenPanel openPanel];
      
      [panel setCanCreateDirectories: bCanCreateDirectories];

      [panel setAllowsMultipleSelection: NO];
      
      [panel setCanChooseDirectories:YES];
      
      [panel setCanChooseFiles:NO];
      
      if(urlStartFolder != nil)
      {

         panel.directoryURL = urlStartFolder;
      
      }
      
      if ([panel runModal] != NSModalResponseOK)
      {
         
         function({});
         
      }
      else
      {
         
         function([[[[panel URLs] lastObject] absoluteString] UTF8String ]);
         
      }

   });

}


void mm_file_dialog(::file::file_dialog * pdialogParam)
{

   ::pointer < ::file::file_dialog > pdialog(pdialogParam);

   ns_main_async(^()
   {

      NSURL * urlStartFolder = nil;
      
      NSString * strStartFolder=[[NSString alloc] initWithUTF8String: pdialog->m_pathStartFolder.c_str()];

      urlStartFolder = [[NSURL alloc]initWithString : strStartFolder ];
    
      NSSavePanel * psavepanel = nil;
      NSOpenPanel * popenpanel = nil;
      
      if(pdialog->m_bSave)
      {
         
         psavepanel = [ NSSavePanel savePanel ];
         
      }
      else
      {

         popenpanel = [ NSOpenPanel openPanel ];

         [ popenpanel setAllowsMultipleSelection:pdialog->m_bMultiple ];

         [ popenpanel setCanChooseDirectories: NO ];

         [ popenpanel setCanChooseFiles: YES];

         psavepanel = popenpanel;
         
      }

//      auto pdelegate = [save_file_dialog_delegate alloc];
//      
//      pdelegate->m_pdialog = pdialog;
//      
//      [ psavepanel setDelegate : pdelegate ];
      
      if(urlStartFolder != nil)
      {

         psavepanel.directoryURL = urlStartFolder;

      }

      NSModalResponse result = [ psavepanel runModal];
      
      if(result == NSModalResponseOK)
      {
         
         if(pdialog->m_bSave)
         {
            
            pdialog->m_patha.add([ [ [ psavepanel URL] absoluteString ] UTF8String ]);
            
         }
         else
         {

            NSArray < NSURL * > * urla = [ popenpanel URLs ];
            
            for(int i = 0; i < [ urla count]; i++)
            {
               
               pdialog->m_patha.add([ [ [ urla objectAtIndex:i ] absoluteString ] UTF8String ]);
               
            }
            
         }
         
         pdialog->m_function(::transfer(pdialog));
         
      }
      
   });

}


bool ns_is_system_dark_mode()
{
   
   NSString *interfaceStyle = [NSUserDefaults.standardUserDefaults valueForKey:@"AppleInterfaceStyle"];
   
   auto bDark = [interfaceStyle isEqualToString:@"Dark"];
   
   return bDark;
   
}
