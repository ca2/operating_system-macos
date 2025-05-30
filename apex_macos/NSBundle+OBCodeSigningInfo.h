//
//  NSBundle+OBCodeSigningInfo.h
//  apex_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/11/23.
//
//
//  NSBundle+OBCodeSigningInfo.h
//
//  Created by Ole Begemann on 22.02.12.
//  Copyright (c) 2012 Ole Begemann. All rights reserved.
//
#pragma once


#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, OBCodeSignState) {
  OBCodeSignStateUnsigned = 1,
  OBCodeSignStateSignatureValid,
  OBCodeSignStateSignatureInvalid,
  OBCodeSignStateSignatureNotVerifiable,
  OBCodeSignStateSignatureUnsupported,
  OBCodeSignStateError
};


@interface NSBundle (OBCodeSigningInfo)

- (BOOL)ob_comesFromAppStore;
- (BOOL)ob_isSandboxed;
- (OBCodeSignState)ob_codeSignState;

@end
