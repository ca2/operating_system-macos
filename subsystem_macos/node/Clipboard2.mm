//
//  Clipboard2.mm
//  subsystem_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11
//  <3ThomasBorregaardSørensen!!
//

#import <AppKit/AppKit.h>


bool Clipboard2_writeToClipBoard(const char * pszText)
{
    @autoreleasepool
    {

        NSString* nsString =
            [[NSString alloc]
                initWithUTF8String:pszText];

        if (!nsString)
            return false;

        NSPasteboard* pasteboard =
            [NSPasteboard generalPasteboard];

        [pasteboard clearContents];

        BOOL success =
            [pasteboard setString:
                nsString
                         forType:NSPasteboardTypeString];

        return success == YES;
    }
}

char * Clipboard2_readFromClipBoard()
{

    @autoreleasepool
    {
        NSPasteboard* pasteboard =
            [NSPasteboard generalPasteboard];

        NSString* nsString =
            [pasteboard stringForType:
                NSPasteboardTypeString];

        if (!nsString)
            return nullptr;

        const char* utf8 =
            [nsString UTF8String];

        if (!utf8)
            return nullptr;

        return strdup(utf8);
    }
}

char * Clipboard_getString()
{
   
   
   NSPasteboard *pasteboard =
   [NSPasteboard generalPasteboard];
   
   NSString *nsstring =
   [pasteboard stringForType:NSPasteboardTypeString];
   
   if(nsstring == nil)
   {
      return nullptr;
   }
   
   auto psz = [nsstring UTF8String];
   
   auto p = strdup(psz);
   
   return p;
   
}


bool Clipboard_setString(const char * psz)
{
   
   NSPasteboard *pasteboard =
   [NSPasteboard generalPasteboard];
   
   [pasteboard clearContents];
   
   NSString *nsstring =
   [NSString stringWithUTF8String:
    psz];
   
   if(nsstring == nil)
   {
      return false;
   }
   
   BOOL success =
   [pasteboard setString:
    nsstring
                 forType:NSPasteboardTypeString];
   
   return true;
}
