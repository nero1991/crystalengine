//
//  SearchManager.h
//  Where
//
//  Created by Nero on 10/9/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AMapSearchKit/AMapSearchKit.h>

@interface SearchManager : NSObject

@property (strong,readonly,nonatomic) AMapSearchAPI* search;

+ (SearchManager*) sharedInstance;

- (void) initSearchService;

//--- 用户数据类

- (BOOL) searchUserLocationInfo;

@end
