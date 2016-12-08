//
//  MapManager.swift
//  Where?
//
//  Created by Nero on 10/10/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

import Foundation

enum MapDisplayType {
    case Undefine
    case Standard
    case Satellite
}

class MapManager : NSObject, MAMapViewDelegate {
    private static var instance : MapManager? = nil
    private(set) var mapView : MAMapView? = nil
    
    //地图显示类型
    var mapType : MapDisplayType {
        get {
            if (nil != mapView) {
                switch (mapView!.mapType) {
                case .Standard:
                    return MapDisplayType.Standard
                case .Satellite:
                    return MapDisplayType.Satellite
                }
            } else {
                return MapDisplayType.Undefine
            }
        }
        
        set (type) {
            if (nil != mapView) {
                switch (type) {
                case .Standard:
                    mapView!.mapType = MAMapType.Standard
                case .Satellite:
                    mapView!.mapType = MAMapType.Satellite
                default:
                    print("undefine map type!")
                }
            }
        }
    }
    
    //交通情况显示
    var showTraffic : Bool {
        get {
            if (nil != mapView) {
                return mapView!.showTraffic
            } else {
                return false
            }
        }
        
        set (isShow) {
            if (nil != mapView) {
                mapView!.showTraffic = isShow
            }
        }
    }
    
    //用户位置定位
    var enableLocation : Bool {
        get {
            if (nil != mapView) {
                return mapView!.showsUserLocation
            } else {
                return false
            }
        }
        
        set (enable) {
            if (nil != mapView) {
                mapView!.showsUserLocation = enable
            }
        }
    }
    
    class func sharedInstance ()-> MapManager! {
        if (nil == MapManager.instance) {
            MapManager.instance = MapManager()
        }
        return MapManager.instance
    }
    
    //初始化地图服务以及地图绘制层
    func initMapServices (size : CGRect)->Bool {
        if (nil == mapView) {
            MAMapServices.sharedServices().apiKey = AppKey.appKey
            mapView = MAMapView(frame: size)
            mapView!.delegate = self
            resetMapElementsLocation()
            return true
        } else {
            return false
        }
    }
    
    //跟踪用户定位(打开用户位置的同时，在地图上显示用户当前位置)
    func showUserLocation (isShow : Bool) {
        if (nil != mapView) {
            if (isShow) {
                enableLocation = true
                mapView!.setUserTrackingMode(MAUserTrackingMode.FollowWithHeading, animated: true)
            } else {
                enableLocation = false
                mapView!.setUserTrackingMode(MAUserTrackingMode.None, animated: false)
            }
        }
    }
    
    //检查用户定位系统是否开启
    private func checkLoactionService () ->Bool {
        switch (CLLocationManager.authorizationStatus()) {
        case .AuthorizedWhenInUse,.AuthorizedAlways:
            return true
        default:
            return false
        }
    }
    
    //重新设置地图辅助元素的显示位置
    private func resetMapElementsLocation() {
        if (nil != mapView) {
            let compassSize = mapView!.compassSize
            mapView!.compassOrigin = CGPointMake(CGRectGetWidth(mapView!.bounds) - compassSize.width,
                                                 CGRectGetHeight(mapView!.bounds) - compassSize.height)
        }
    }
    
//--- 地图数据处理回调
    
    //定位失败回调
    func mapView(mapView: MAMapView!, didFailToLocateUserWithError error: NSError!) {
        switch (error.code) {
        case CLError.Network.rawValue:
            print("网络没有打开")
        case CLError.Denied.rawValue:
            if (checkLoactionService()) {
                print("定位服务由于未知原因被禁用")
            } else {
                let locationManager = CLLocationManager()
                locationManager.requestWhenInUseAuthorization();
            }
        case CLError.LocationUnknown.rawValue:
            print("未知的地理位置")
        default:
            print("定位系统其他错误")
        }
    }
    
    //用户位置更新回调
    func mapView(mapView: MAMapView!, didUpdateUserLocation userLocation: MAUserLocation!, updatingLocation: Bool) {
        //TEST:: 测试地点数据搜索功能
        SearchManager.sharedInstance().searchUserLoactionInfo()
    }
}