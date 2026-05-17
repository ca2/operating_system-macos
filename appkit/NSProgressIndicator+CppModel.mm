//
//  NSProgressIndicator+CppModel.mm
//  appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 16/05/26.
//

#import "NSProgressIndicator+CppModel.h"
#import <objc/runtime.h>

static const char *CppModelPointerKey = "CppModelPointerKey";
static const char *CustomTagKey = "CustomTagKey";

@implementation NSProgressIndicator (CppModel)

// C++ Pointer Getter/Setter
- (void)setCppModelPointer:(void *)pointer {
    // NSValue wraps the raw C++ pointer without trying to retain it as an Obj-C object
    NSValue *value = [NSValue valueWithPointer:pointer];
    objc_setAssociatedObject(self, CppModelPointerKey, value, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void *)cppModelPointer {
    NSValue *value = objc_getAssociatedObject(self, CppModelPointerKey);
    return value ? [value pointerValue] : nullptr;
}

// Integer Tag Getter/Setter
- (void)setCustomTag:(NSInteger)tag {
    objc_setAssociatedObject(self, CustomTagKey, @(tag), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSInteger)customTag {
    NSNumber *tagNumber = objc_getAssociatedObject(self, CustomTagKey);
    return tagNumber ? [tagNumber integerValue] : -1;
}

@end
