//
//  MAMapManager.h
//  Where
//
//  Created by Nero on 10/8/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import <MAMapKit/MAMapKit.h>
#import <Foundation/Foundation.h>

enum MAPTYPE {
    TYPE_ERROR,
    TYPE_REAL,
    TYPE_DRAW,
};

@interface MapManager : NSObject
{
    CLLocationManager * locationManager;
}

@property (strong,readonly,nonatomic) MAMapView* mapView;

+ (MapManager*) sharedInstance;

- (BOOL) initManagerSize : (CGRect) rect;

//基本地图功能接口

//--- 变更地图显示类型
- (enum MAPTYPE) mapType;

- (void) setMapType : (enum MAPTYPE) type;

//--- 设置交通状态显示

- (BOOL) isShowTraffic;

- (void) showTraffic : (BOOL) show;

//--- 定位系统

- (BOOL) isEnableLocation;

- (void) enableLocation : (BOOL) enable;

- (void) followUserLocation : (BOOL) follow;

@end
