//
//  image.m
//  acme_macos
//
//  Created by Camilo Sasuke on 29/05/21.
//
#import <AppKit/AppKit.h>


NSImage * nsimage_from_cgimageref(CGImageRef image, int cx, int cy)
{
   
   NSSize sz;
   
   sz.width = cx;
   
   sz.height = cy;
   
   return [[NSImage alloc] initWithCGImage:image size:sz];
   
}

