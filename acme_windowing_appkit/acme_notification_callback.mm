//
//  notification_callback.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sorensen on 05/01/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "macos_app.h"
#include "acme/constant/id.h"
#include "acme/operating_system/argcargv.h"
bool ns_get_dark_mode();

//void system_id_update(::platform::system * psystem, int iUpdate, long long iPayload);
long long system_id_topic(::platform::system* psystem, int iId, long long llWparam, long long llLparam);

::platform::system * application_system(::platform::application * papplication);

//#import <Foundation/Foundation.h>
void ns_main_post(dispatch_block_t block);
void ns_main_send(dispatch_block_t block);

@implementation acme_notification_callback


- (id)init
{

//   ns_main_post(^{
      
   [ [ NSDistributedNotificationCenter defaultCenter ] addObserver:self selector:@selector(themeChanged:) name:@"AppleInterfaceThemeChangedNotification" object: nil];
   //});

   return self;
   
}

-(void)dealloc
{
   
   
}

-(void)themeChanged:(NSNotification *) notification
{
 
   NSLog (@"%@", notification);
   
   [self fetch_dark_mode];
   
 
}


-(void)fetch_dark_mode
{
   
   NSString *interfaceStyle = [NSUserDefaults.standardUserDefaults valueForKey:@"AppleInterfaceStyle"];
   
   int iDarkMode = [interfaceStyle isEqualToString:@"Dark"];

   system_id_topic(application_system(m_papplication), id_get_operating_system_dark_mode_reply, iDarkMode, 0);

}




@end



