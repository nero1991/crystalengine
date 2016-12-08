//
//  IDMaker.h
//  Where
//
//  Created by Nero on 10/9/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IDMaker : NSObject

+ (IDMaker*) sharedInstance;

- (id) init;

- (int) retainID;

- (void) releaseID : (int) idNumber;

@end