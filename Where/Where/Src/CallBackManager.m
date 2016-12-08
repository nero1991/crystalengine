//
//  CallBackManager.m
//  Where
//
//  Created by Nero on 10/9/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import "CallBackManager.h"
#import "IDMaker.h"

@implementation CallBackInfo
@synthesize obj,method;

- (id) initWithObj : (id) o Selector : (SEL) m{
    if (self = [super init],nil != self) {
        obj = o;
        method = m;
    }
    return self;
}

@end

static CallBackManager* _instance = nil;

@interface CallBackManager () {
    NSMutableDictionary* callbackInfos;
}
@end

@implementation CallBackManager

+ (CallBackManager*) sharedInstance {
    if (nil == _instance) {
        _instance = [CallBackManager new];
    }
    return _instance;
}

- (id) init {
    if (self = [super init], nil != self) {
        callbackInfos = [NSMutableDictionary new];
    }
    return self;
}

- (void) deleteCallBackInfo : (int) idNumber {
    [callbackInfos removeObjectForKey:[[NSNumber alloc] initWithInt:idNumber]];
    [[IDMaker sharedInstance] releaseID:idNumber];
}

- (CallBackInfo*) getCallBackInfo : (int) idNumber {
    return [callbackInfos objectForKey:[[NSNumber alloc] initWithInt:idNumber]];
}

- (int) saveCallBackInfo : (id) obj Selector : (SEL) method {
    int getID = 0;
    if (nil != obj) {
        getID = [[IDMaker sharedInstance] retainID];
        if (getID > 0) {
            [callbackInfos setObject: [[CallBackInfo alloc] initWithObj:obj Selector:method]
                              forKey:[[NSNumber alloc] initWithInt:getID]];
        }
    }
    return getID;
}

@end
