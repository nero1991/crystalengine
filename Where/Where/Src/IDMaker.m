//
//  IDMaker.m
//  Where
//
//  Created by Nero on 10/9/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import "IDMaker.h"

static IDMaker* _instance = nil;

@interface IDMaker () {
    int idPool;
    NSMutableArray *unUseIDs;
}

@end

@implementation IDMaker

+ (IDMaker*) sharedInstance {
    if (nil == _instance) {
        _instance = [IDMaker new];
    }
    return _instance;
}

- (id) init {
    self = [super init];
    if (nil != self) {
        idPool = 0;
        unUseIDs = [NSMutableArray new];
    }
    return self;
}

- (int) retainID {
    int result = -1;
    if ([unUseIDs count] != 0 && [unUseIDs isKindOfClass:[NSNumber class]] == YES ) {
        result = [unUseIDs.lastObject intValue];
        [unUseIDs removeLastObject];
    } else {
        result = ++idPool;
    }
    return result;
}

- (void) releaseID : (int) idNumber {
    if (idNumber <= idPool) {
        BOOL allowRelease = YES;
        for (NSNumber* number in unUseIDs) {
            if (idNumber == [number intValue]) {
                allowRelease = NO;
                break;
            }
        }
        if (YES == allowRelease) {
            [unUseIDs addObject:[[NSNumber alloc] initWithInt:idNumber]];
        }
    }
}

@end
