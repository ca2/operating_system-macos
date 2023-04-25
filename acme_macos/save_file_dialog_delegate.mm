//
//  file_dialog_delegate.m
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 24/04/23.
//

#import <Foundation/Foundation.h>

#include "file_dialog_template.h"


@implementation save_file_dialog_template


- (NSString *)panel:(id)sender
userEnteredFilename:(NSString *)filename
          confirmed:(BOOL)okFlag;
{
   
   if(okFlag)
   {
      
      if(m_pdialog->m_bSave)
      {
         
         NSURL * url = [sender URL];
         
         int iCount = 1;
         
         char ** pp = (char **)malloc((iCount + 1) * sizeof(char*));
         
         int i = 0;
         
         pp[0] = __strdup([url absoluteString]);
         
         pp[1] = NULL;
         
         function((const char **) pp, [ [ [ panel directoryURL ] absoluteString ] UTF8String]);
         
         i = 0;
         
         while(pp[i] != NULL)
         {
            
            free(pp[i]);
            
            i++;
            
         }
         
         free(pp);
         
      }
      else
      {
         
         NSOpenPanel * popenpanel = panel;

         NSArray < NSURL * > * urla = [sender URLs];

         char ** pp = (char **)malloc((urla.count + 1) * sizeof(char*));

         int i = 0;

         for(; i < urla.count; i++)
         {

            pp[i] = __strdup([[urla objectAtIndex:i] absoluteString]);

         }

         pp[i] = NULL;

         function((const char **) pp, [ [ [ panel directoryURL ] absoluteString ] UTF8String]);

         i = 0;

         while(pp[i] != NULL)
         {

            free(pp[i]);

            i++;

         }

         free(pp);

      }
      
   }

}

@end
