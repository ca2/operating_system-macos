//
//  NSProgressIndicator+CppModel.h
//  appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 16/05/26.
//

#import <AppKit/AppKit.h>

@interface NSProgressIndicator (CppModel)
// A raw pointer to your C++ class, struct, or data model
@property (nonatomic, assign) void *cppModelPointer;
// A standard integer tag for classic identification
@property (nonatomic, assign) NSInteger tag;
@end
