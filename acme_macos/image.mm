//
//  image.m
//  acme_macos
//
//  Created by Camilo Sasuke on 29/05/21.
//
#import <AppKit/AppKit.h>


void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image);



NSImage * nsimage_from_cgimageref(CGImageRef image, int cx, int cy)
{
   
   NSSize sz;
   
   sz.width = cx;
   
   sz.height = cy;
   
   return [[NSImage alloc] initWithCGImage:image size:sz];
   
}


NSImage * nsimage_from_image_data(const void * pdata, int cx, int cy, int scan)
{

   NSBitmapImageRep * imageRep = [[ NSBitmapImageRep alloc] initWithBitmapDataPlanes: (unsigned char *_Nullable *_Nullable) pdata
          pixelsWide:cx
         pixelsHigh:cy                                  bitsPerSample:8
            samplesPerPixel:4
            hasAlpha:TRUE
               isPlanar: FALSE
               colorSpaceName:NSDeviceRGBColorSpace
               bitmapFormat:0
                                       bytesPerRow:scan
                                      bitsPerPixel:32] ;

   NSSize imageSize = NSMakeSize(cx, cy);

   NSImage * image = [[NSImage alloc] initWithSize:imageSize];
   
   [image addRepresentation:imageRep];

   return image;

}



