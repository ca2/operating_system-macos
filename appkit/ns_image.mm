//
//  ns_image.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#include <AppKit/AppKit.h>
#include "_mm.h"

void ns_image_release(ns_image_t & nsimage)
{
 
   if(nsimage.is_null())
   {
      
      return;
      
   }
   
   // Transfers ownership to ARC. ARC will release 'pns' when this function exits.
   NSImage * pns = (__bridge_transfer NSImage *)nsimage.m_p;
   
   // Clear the original pointer so the caller knows it's gone
   nsimage.clear();
   
}



cg_image_t ns_image_get_cg_image(ns_image_t nsimage)
{
   NSImage * image = (__bridge NSImage *)nsimage.m_p;
 
   CGImageRef cgImage = [image CGImageForProposedRect:NULL
                                              context:nil
                                                hints:nil];

   //w  = (::i32) CGImageGetWidth(cgImage);
   //h = (::i32) CGImageGetHeight(cgImage);
   return {(::uptr) cgImage};
}


//
//void ns_image_get_size(void * pNS, ::i32 & w,::i32 & h)
//{
//   NSImage * image = (__bridge NSImage *)pNS;
// 
//   CGImageRef cgImage = [image CGImageForProposedRect:NULL
//                                              context:nil
//                                                hints:nil];
//
//   w  = (::i32) CGImageGetWidth(cgImage);
//   h = (::i32) CGImageGetHeight(cgImage);
//   
//}
