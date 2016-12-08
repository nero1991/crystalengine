//
//  MAMapManager.m
//  Where
//
//  Created by Nero on 10/8/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import "MapManager.h"
#import "appKey.h"

static MapManager* _instance = nil;


@interface MapManager () <MAMapViewDelegate>

@end


@implementation MapManager
@synthesize mapView;

+ (MapManager*) sharedInstance {
    if (nil == _instance) {
        _instance = [[MapManager alloc] init];
    }
    return _instance;
}

- (BOOL) initManagerSize : (CGRect) rect {
    //初始化地图服务
    [MAMapServices sharedServices].apiKey = appKey;
    mapView = [[MAMapView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(rect),
                                                                 CGRectGetHeight(rect))];
    mapView.delegate = self;
    
    [self resetMapElementLocation];
        
    return YES;
}

- (enum MAPTYPE) mapType {
    enum MAPTYPE result = TYPE_ERROR;
    if (nil != mapView) {
        switch (mapView.mapType) {
            case MAMapTypeStandard:
                result = TYPE_DRAW;
                break;
            case MAMapTypeSatellite:
                result = TYPE_REAL;
            default:
                break;
        }
    }
    return result;
}

- (void) setMapType : (enum MAPTYPE) type {
    if (nil != mapView) {
        switch (type) {
            case TYPE_DRAW:
                mapView.mapType = MAMapTypeStandard;
                break;
            case TYPE_REAL:
                mapView.mapType = MAMapTypeSatellite;
            default:
                break;
        }
    }
}

- (BOOL) isShowTraffic {
    if (nil != mapView) {
        return mapView.showTraffic;
    } else {
        return NO;
    }
}

- (void) showTraffic : (BOOL) show {
    if (nil != mapView) {
        mapView.showTraffic = show;
    }
}

- (BOOL) isEnableLocation {
    if (nil != mapView) {
        return mapView.showsUserLocation;
    } else {
        return NO;
    }
}

- (void) enableLocation : (BOOL) enable {
    if (nil != mapView) {
        mapView.showsUserLocation = enable;
    }
}

- (void) followUserLocation : (BOOL) follow {
    if (nil != mapView) {
        if (YES == follow) {
            [self enableLocation:YES];
            [mapView setUserTrackingMode:MAUserTrackingModeFollowWithHeading animated:YES];
        } else {
            [self enableLocation:NO];
            [mapView setUserTrackingMode:MAUserTrackingModeNone];
        }
    }
}

//--- 地图功能回调
//定位失败回调
- (void)mapView:(MAMapView *)mapView didFailToLocateUserWithError:(NSError *)error {
    switch (error.code) {
        case kCLErrorNetwork:
            //TODO::网络不好提示
            break;
        case kCLErrorDenied:
            //TODO::定位服务关闭
            if ([self checkLoactionServeice] == NO) {
                //TODO::弹窗提示开启定位服务
            }
            break;
        default:
            //TODO::未知错误提示
            break;
    }
}



//用户位置更新
-(void)mapView:(MAMapView *)mapView didUpdateUserLocation:(MAUserLocation *)userLocation
                                         updatingLocation:(BOOL)updatingLocation {
    if(updatingLocation)
    {
        //取出当前位置的坐标
        NSLog(@"latitude : %f,longitude: %f",userLocation.coordinate.latitude,userLocation.coordinate.longitude);
    }
}

#pragma mark -- private

- (BOOL) checkLoactionServeice {
    BOOL result = NO;
    if (nil == locationManager) {
        locationManager = [[CLLocationManager alloc] init];
    }
    if (nil != locationManager) {
        if ([CLLocationManager authorizationStatus] < kCLAuthorizationStatusAuthorizedAlways) {
            //弹窗请求用户开启定位
            if ([locationManager respondsToSelector:@selector(requestWhenInUseAuthorization)])
            {
                [locationManager performSelector:@selector(requestWhenInUseAuthorization)];
            }
            result = NO;
        } else {
            result = YES;
        }
    }
    return result;
}

- (void) resetMapElementLocation {
    if (nil != mapView) {
        CGSize compassSize = [mapView compassSize];
        [mapView setCompassOrigin:CGPointMake(CGRectGetWidth(mapView.bounds) - compassSize.width,
                                              CGRectGetHeight(mapView.bounds) - compassSize.height)];
    }
}

@end
