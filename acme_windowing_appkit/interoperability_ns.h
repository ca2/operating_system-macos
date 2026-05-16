//
//  interoperability_ns.h
//  acme_windowing_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on May 2026.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


@interface ComboItem : NSObject<NSCopying>

@property(nonatomic, copy) NSString *title;
@property(nonatomic) uint64_t payload;

- (instancetype)initWithTitle:(NSString *)title
                        payload:(uint64_t)value;

@end
