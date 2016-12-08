//
//  SearchManager.swift
//  Where?
//
//  Created by Nero on 10/10/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

import Foundation

//--- 扩展类型CLLocationCoordinate2D，以支持在Dictionary中使用
extension CLLocationCoordinate2D : Hashable {
    public var hashValue: Int {
        get {
            let value = String(latitude) + String(longitude)
            return value.hashValue
        }
    }
}

public func ==(lhs: CLLocationCoordinate2D, rhs: CLLocationCoordinate2D) -> Bool {
    if (lhs.latitude == rhs.latitude && lhs.longitude == rhs.longitude) {
        return true
    } else {
        return false
    }
}

class SearchManager : NSObject ,AMapSearchDelegate ,MissionCompleteDelegate{
    private static var instance : SearchManager? = nil
    
    private var searchAPI : AMapSearchAPI? = nil
    
    private var searchedInfo : Dictionary<CLLocationCoordinate2D,Int> = Dictionary<CLLocationCoordinate2D,Int>()
    
    class func sharedInstance()->SearchManager! {
        if (nil == instance) {
            instance = SearchManager()
        }
        return instance
    }
    
    //初始化地理位置信息搜索服务
    func initSearchService() {
        AMapSearchServices.sharedServices().apiKey = AppKey.appKey
        if (nil == searchAPI) {
            searchAPI = AMapSearchAPI()
            searchAPI!.delegate = self
        }
    }
    
    //搜索指定地点的详细信息
    func searchLocationInfo (location : CLLocationCoordinate2D,radius : Int) {
        //构造AMapReGeocodeSearchRequest对象
        let regeo = AMapReGeocodeSearchRequest();
        regeo.location = AMapGeoPoint.locationWithLatitude(CGFloat(location.latitude),
                                                           longitude: CGFloat(location.longitude))
        regeo.radius = radius;
        regeo.requireExtension = true;
            
        //发起逆地理编码
        searchAPI!.AMapReGoecodeSearch(regeo)
    }
    
    //搜索用户当前位置的详细信息
    func searchUserLoactionInfo()->Bool {
        let userLocation = MapManager.sharedInstance().mapView?.userLocation
        if (userLocation != nil) {
            let missionID = MissionCenter.sharedInstance().append(self)
            if (IDMaker.nops != missionID && addInfoSearchInfo((userLocation?.location?.coordinate)!, missionID: missionID)) {
                searchLocationInfo((userLocation?.location?.coordinate)!, radius: 10)
            }
            return true
        } else {
            return false
        }
    }
    
//--- 搜索数据回调
    //搜索出现错误的回调
    func AMapSearchRequest(request: AnyObject!, didFailWithError error: NSError!) {
        print("搜索数据出现了错误")
        //TODO::在指定的view上显示失败信息
        //进行错误原因猜测，写入系统日志
    }
    
    //地理逆编码信息查询结果
    func onReGeocodeSearchDone(request: AMapReGeocodeSearchRequest!, response: AMapReGeocodeSearchResponse!) {
        let location = CLLocationCoordinate2D(latitude: CLLocationDegrees(request.location.latitude),
                                              longitude: CLLocationDegrees(request.location.longitude))
        let missionID = searchedInfo[location]
        if (missionID != nil) {
            let callBack = MissionCenter.sharedInstance()[missionID!]
            let location = CLLocationCoordinate2D.init(latitude: CLLocationDegrees(request.location.latitude),
                                                       longitude: CLLocationDegrees(request.location.longitude))
            let info = UserLocationDataManager.AMapAddressComponetToDict(response.regeocode.addressComponent,
                                                                 title: "nil",location: location)
            callBack?.afterComplete(missionID!, isSuccess: true, data: info)
            MissionCenter.sharedInstance().remove(missionID!)
        }
    }

//--- 任务处理回调
    func afterComplete(missionID : Int, isSuccess : Bool, data : Dictionary<String,String>!) {
        print("地理信息逆编码完成")
        //TODO::在指定的view上显示成功信息
        UserLocationDataManager.sharedInstance().appendLocation(data)
    }
    
    //保存地理编码搜索数据的任务号，以及地理位置数据,可以用于任务回调处理
    private func addInfoSearchInfo( location: CLLocationCoordinate2D,missionID : Int)->Bool {
        if (searchedInfo[location] == nil) {
            searchedInfo[location] = missionID
            return true
        } else {
            return false
        }
    }
}