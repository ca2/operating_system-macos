//
//  macos_file.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 03/05/18.
//
#import "_mm.h"

//enum_status ns_create_alias(const char * pszTarget, const char * pszSource)
//{
//   
//   NSString * strTarget = [[NSString alloc]initWithUTF8String:pszTarget];
//   
//   NSString * strSource = [[NSString alloc]initWithUTF8String:pszSource];
//   
//   NSError * error = nullptr;
//   if([[NSFileManager defaultManager ] createSymbolicLinkAtPath: strTarget withDestinationPath: strSource error:&error] == NO)
//   {
//      
//      if([error code] == NSFileWriteFileExistsError)
//      {
//         
//         return error_already_exists;
//         
//      }
//      
//      return error_failed;
//      
//   }
//   
//   return ::success;
//   
//}
//
//enum_status ns_symbolic_link_destination(char ** ppszDestination, const char * pszLink)
//{
//   
//  
//   NSString * strLink = [[NSString alloc]initWithUTF8String:pszLink];
//   
//   NSError * error = nullptr;
//   
//   NSString * strDestination = [[NSFileManager defaultManager ] destinationOfSymbolicLinkAtPath:strLink error:&error];
//   
//   if(strDestination == nullptr)
//   {
//      
//      return error_failed;
//      
//   }
//   
//   if(ppszDestination)
//   {
//   
//      *ppszDestination = __strdup(strDestination);
//      
//   }
//   
//   return success;
//   
//}
//
//
//
//char * ns_user_local_folder(NSSearchPathDirectory e)
//{
//   
//   NSArray < NSURL * > * pa = [[NSFileManager defaultManager ] URLsForDirectory:e inDomains:NSLocalDomainMask| NSUserDomainMask];
//   
//   if(pa == NULL || [pa count] <= 0)
//   {
//      
//      return NULL;
//      
//   }
//   
//   return __strdup([[pa objectAtIndex:0] path]);
//   
//}
//
//
//
//char * ns_user_local_desktop_folder()
//{
//   
//   return ns_user_local_folder(NSDesktopDirectory);
//   
//}
//
//
//char * ns_user_local_documents_folder()
//{
//   
//   return ns_user_local_folder(NSDocumentDirectory);
//   
//}
//
//char * ns_user_local_downloads_folder()
//{
//   
//   return ns_user_local_folder(NSDownloadsDirectory);
//   
//}
//
//
//char * ns_user_local_music_folder()
//{
//   
//   return ns_user_local_folder(NSMusicDirectory);
//   
//}
//
//
//char * ns_user_local_image_folder()
//{
//   
//   return ns_user_local_folder(NSPicturesDirectory);
//   
//}
//
//char * ns_user_local_video_folder()
//{
//   
//   return ns_user_local_folder(NSMoviesDirectory);
//   
//}
//
//
////char * ns_resolve_alias(const char * psz, bool bNoUI = false, bool bNoMount = false)
////{
////   
////   NSString * str = [[NSString alloc] initWithUTF8String: psz];
////   
////   NSURL * url = [NSURL fileURLWithPath: str];
////   
////   NSNumber * aliasFlag = nil;
////   
////   [url getResourceValue:&aliasFlag forKey: NSURLIsAliasFileKey error: nil];
////   
////   if(!aliasFlag.boolValue)
////   {
////   
////      return NULL;
////   
////   }
////   
////   NSURLBookmarkResolutionOptions options = 0;
////   
////   options |= bNoUI ? NSURLBookmarkResolutionWithoutUI : 0;
////   
////   options |= bNoMount ? NSURLBookmarkResolutionWithoutMounting : 0;
////   
////   //NSError * perror = NULL;
////   
////   //NSURL * urlTarget = [NSURL URLByResolvingAliasFileAtURL: url options: options error: &perror];
////   NSString * strTarget = nullptr;
////   if (@available(macOS 10.10, *)) {
////      NSURL * urlTarget = [NSURL URLByResolvingAliasFileAtURL: url options: options error: nil];
////      
////       strTarget = [urlTarget absoluteString];
////   } else {
////      // Fallback on earlier versions
////      strTarget = str;
////   }
////   
////   return __strdup(strTarget);
////
////}
//
//
////bool os_is_alias(const char * psz)
////{
////   
////   NSString * str = [[NSString alloc] initWithUTF8String: psz];
////   
////   NSURL * url = [NSURL fileURLWithPath: str];
////   
////   NSNumber * aliasFlag = nil;
////   
////   [url getResourceValue:&aliasFlag forKey:NSURLIsAliasFileKey error: nil];
////   
////   return aliasFlag.boolValue;
////   
////}
////
//
//
//
//
//
////
////void ns_create_alias(const char * pszTarget, const char * pszSource)
////{
////   NSString * strTarget = [[NSString alloc]initWithUTF8String:pszTarget];
////   NSString * strSource = [[NSString alloc]initWithUTF8String:pszSource];
////
////   [[NSFileManager defaultManager ] createSymbolicLinkAtPath: strTarget withDestinationPath: strSource error:nil];
////}
////

char * ns_resource_folder()
{
   
   NSString * resourcePath = [ [ NSBundle mainBundle ] resourcePath ];
   
   return __strdup(resourcePath);
   
}


//char * ns_user_local_folder(NSSearchPathDirectory e)
//{
//
//   NSArray < NSURL * > * pa = [[NSFileManager defaultManager ] URLsForDirectory:e inDomains:NSLocalDomainMask| NSUserDomainMask];
//
//   if(pa == NULL || [pa count] <= 0)
//   {
//
//      return NULL;
//
//   }
//
//   return __strdup([[pa objectAtIndex:0] path]);
//
//}
//
//
//
//char * ns_user_local_desktop_folder()
//{
//
//   return ns_user_local_folder(NSDesktopDirectory);
//
//}
//
//
//char * ns_user_local_documents_folder()
//{
//
//   return ns_user_local_folder(NSDocumentDirectory);
//
//}
//
//char * ns_user_local_downloads_folder()
//{
//
//   return ns_user_local_folder(NSDownloadsDirectory);
//
//}
//
//
//char * ns_user_local_music_folder()
//{
//
//   return ns_user_local_folder(NSMusicDirectory);
//
//}
//
//
//char * ns_user_local_image_folder()
//{
//
//   return ns_user_local_folder(NSPicturesDirectory);
//
//}
//
//char * ns_user_local_video_folder()
//{
//
//   return ns_user_local_folder(NSMoviesDirectory);
//
//}
//
//
////char * ns_resolve_alias(const char * psz, bool bNoUI = false, bool bNoMount = false)
////{
////
////   NSString * str = [[NSString alloc] initWithUTF8String: psz];
////
////   NSURL * url = [NSURL fileURLWithPath: str];
////
////   NSNumber * aliasFlag = nil;
////
////   [url getResourceValue:&aliasFlag forKey: NSURLIsAliasFileKey error: nil];
////
////   if(!aliasFlag.boolValue)
////   {
////
////      return NULL;
////
////   }
////
////   NSURLBookmarkResolutionOptions options = 0;
////
////   options |= bNoUI ? NSURLBookmarkResolutionWithoutUI : 0;
////
////   options |= bNoMount ? NSURLBookmarkResolutionWithoutMounting : 0;
////
////   //NSError * perror = NULL;
////
////   //NSURL * urlTarget = [NSURL URLByResolvingAliasFileAtURL: url options: options error: &perror];
////
////   NSURL * urlTarget = [NSURL URLByResolvingAliasFileAtURL: url options: options error: nil];
////
////   NSString * strTarget = [urlTarget absoluteString];
////
////   return __strdup(strTarget);
////
////}
//
////
////bool os_is_alias(const char * psz)
////{
////
////   NSString * str = [[NSString alloc] initWithUTF8String: psz];
////
////   NSURL * url = [NSURL fileURLWithPath: str];
////
////   NSNumber * aliasFlag = nil;
////
////   [url getResourceValue:&aliasFlag forKey:NSURLIsAliasFileKey error: nil];
////
////   return aliasFlag.boolValue;
////
////}
////
//
//
