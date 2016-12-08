//
//  SearchManager.m
//  Where
//
//  Created by Nero on 10/9/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import "appKey.h"
#import "SearchManager.h"
#import "MapManager.h"

static SearchManager* _instance = nil;

@interface SearchManager () <AMapSearchDelegate>

@end

@implementation SearchManager

+ (SearchManager*) sharedInstance {
    if (nil == _instance) {
        _instance = [SearchManager new];
    }
    return _instance;
}

- (void) initSearchService {
    //初始化地图搜索服务
    [AMapSearchServices sharedServices].apiKey = appKey;
    if (nil == _search) {
        _search = [[AMapSearchAPI alloc] init];
        _search.delegate = self;
    }
}

- (BOOL) searchUserLocationInfo {
    MAUserLocation* userLocation = [MapManager sharedInstance].mapView.userLocation;
    if (nil != userLocation) {
        //构造AMapReGeocodeSearchRequest对象
        AMapReGeocodeSearchRequest *regeo = [[AMapReGeocodeSearchRequest alloc] init];
        regeo.location = [AMapGeoPoint locationWithLatitude:userLocation.location.coordinate.latitude
                                                  longitude:userLocation.location.coordinate.longitude];
        regeo.radius = 100;
        regeo.requireExtension = YES;
        
        //发起逆地理编码
        [_search AMapReGoecodeSearch: regeo];
        return YES;
    } else {
        return NO;
    }
}

//--- 搜索功能回调
- (void)AMapSearchRequest:(id)request didFailWithError:(NSError *)error {
    NSLog(@"搜索发生了错误");
}

//实现逆地理编码的回调函数
- (void)onReGeocodeSearchDone:(AMapReGeocodeSearchRequest *)request response:(AMapReGeocodeSearchResponse *)response {
    if(response.regeocode != nil)
    {
        //通过AMapReGeocodeSearchResponse对象处理搜索结果
        NSString *result = [NSString stringWithFormat:@"ReGeocode: %@", response.regeocode];
        NSLog(@"ReGeo: %@", result);
    }
}

@end
