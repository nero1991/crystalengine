//
//  CallBackManager.h
//  Where
//
//  Created by Nero on 10/9/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CallBackInfo : NSObject
@property (strong,readwrite,nonatomic) id obj;
@property (readwrite,nonatomic) SEL method;

- (id) initWithObj : (id) obj Selector : (SEL) method;

@end

@interface CallBackManager : NSObject

+ (CallBackManager*) sharedInstance;

- (id) init;

- (void) deleteCallBackInfo : (int) idNumber;

- (CallBackInfo*) getCallBackInfo : (int) idNumber;

- (int) saveCallBackInfo : (id) obj Selector : (SEL) method;

@end
