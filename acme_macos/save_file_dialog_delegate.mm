//
//  file_dialog_delegate.m
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 24/04/23.
//

#import <Foundation/Foundation.h>
#include "acme/filesystem/filesystem/file_dialog.h"
#include "save_file_dialog_delegate.h"


@implementation save_file_dialog_delegate

//
//- (NSString *)panel:(id)sender
//userEnteredFilename:(NSString *)filename
//          confirmed:(BOOL)okFlag;
//{
//   
//   if(okFlag)
//   {
//      
//      if(m_pdialog->m_bSave)
//      {
//         
//         m_pdialog->m_patha.add([[ [ sender URL] absoluteString ] UTF8String]);
//         
//      }
//      else
//      {
//
//         NSArray < NSURL * > * urla = [sender URLs];
//         
//         for(int i = 0; i < [ urla count]; i++)
//         {
//            
//            m_pdialog->m_patha.add([[ [urla objectAtIndex:i ] absoluteString] UTF8String]);
//            
//         }
//
//      }
//      
//      m_pdialog->m_function(m_pdialog);
//      
//      [ sender stopModalWithCode : NSModalResponseOK ];
//
//   }
//
//   return nil;
//   
//}

@end
