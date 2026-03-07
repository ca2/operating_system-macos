//
//  KeyboardLayoutObserver.mm
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/03/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "KeyboardLayoutObserver.h"

//bool cpp_task_get_run();
//
//@implementation KeyboardLayoutObserver
//
//- (instancetype)init : (pfn_keyboard_layout_listen_function) pfn withData:(void *)p
//{
//    self = [super init];
//   self->m_pfn = pfn;
//   self->m_p = p;
//    if (self)
//    {
//        [[NSDistributedNotificationCenter defaultCenter] addObserver:self
//                                                             selector:@selector(inputSourceChanged:)
//                                                                 name:(__bridge NSString *)kTISNotifySelectedKeyboardInputSourceChanged
//                                                               object:nil];
//    }
//    return self;
//}
//
//- (void)inputSourceChanged:(NSNotification *)notification
//{
//   TISInputSourceRef source = TISCopyCurrentKeyboardInputSource();
//   
//   NSString *name = (__bridge NSString *)TISGetInputSourceProperty(
//                                                                   source,
//                                                                   kTISPropertyLocalizedName
//                                                                   );
//   
//   NSString *idString = (__bridge NSString *)TISGetInputSourceProperty(
//                                                                       source,
//                                                                       kTISPropertyInputSourceID
//                                                                       );
//   
//   NSLog(@"Keyboard layout changed:");
//   NSLog(@"Name: %@", name);
//   NSLog(@"ID: %@", idString);
//   self->m_pfn([idString UTF8String], self->m_p);
//    if (source)
//        CFRelease(source);
//}
//
//@end
//
//int run_keyboard_layout_observer(pfn_keyboard_layout_listen_function pfn, void * p)
//{
//    @autoreleasepool
//    {
//        KeyboardLayoutObserver *observer = [[KeyboardLayoutObserver alloc] init : pfn withData: p];
//
//        NSLog(@"Listening for keyboard layout changes...");
//
//       
//       while(cpp_task_get_run())
//       {
//          [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1.0]];
//          
//       }
//    }
//}
