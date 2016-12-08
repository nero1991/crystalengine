//
//  UserDataManager.swift
//  Where?
//
//  Created by Nero on 10/12/15.
//  Copyright © 2015 Nero. All rights reserved.
//

import Foundation

enum AddressComponent : String {
    case Title = "title"
    case Latitude = "latitude"
    case Longitude = "longitude"
    case Province = "province"
    case City = "city"
    case District = "district"
    case TownShip = "township"
    case Building = "building"
    case StreetNumber = "streetnumber"
    case CityCode = "citycode"
    case Adcode = "adcode"
    case SavedTime = "SaveTime"
}

//TODO::数据的保存与读取
//用户保存地点数据管理
class UserLocationDataManager {
    private static var instance : UserLocationDataManager? = nil
    
    class SavedLocationInfo {
        //已经保存的地点信息 （dic<数据标题，数据值>)
        typealias Data = Dictionary<String,String>
        
        private var info : Data = Data()
        
        subscript (addressComponent : AddressComponent)->String? {
            get {
                return info[addressComponent.rawValue]
            }
            
            set (value) {
                info[addressComponent.rawValue] = value
            }
        }
        
        init() {
            
        }
        
        init(data : Data?) {
            info = data!
        }
    }
    
    enum DataChangeFlag : Int {
        //地点保存数据更新标志
        case LocationDataChange = 0b0001
        //统计信息数据更新标志
        case StatisticsChange   = 0b0010
    }
    
    //地点统计分析结果 (dic<地点名称，对应savedLocationInfos的数据下标>)
    typealias LocationsStatistics = Dictionary<String,Array<Int>>
    
    //数据变更标志保存
    private var dataChangeFlag : Int = 0
    
    //用于保存用户保存的地点统计数据
    private var locationsStatistics : LocationsStatistics = LocationsStatistics()
    
    //用于保存用户地点的详细数据
    private var savedLocationInfos : Array<SavedLocationInfo?> = Array<SavedLocationInfo?>()
    
    class func sharedInstance()->UserLocationDataManager! {
        if (nil == instance) {
            instance = UserLocationDataManager()
        }
        return instance
    }
    
    //获取用户保存地点的数量
    var count : Int {
        get {
            return savedLocationInfos.count
        }
    }
    
    //获取数据变更标志
    subscript (type : DataChangeFlag)->Bool {
        get {
            return dataChangeFlag & type.rawValue != 0
        }
        
        set {
            if (newValue) {
                dataChangeFlag | type.rawValue
            } else {
                dataChangeFlag & (~type.rawValue)
            }
        }
    }
    
    //获取指定下标的用户地点数据
    subscript (index : Int)->SavedLocationInfo? {
        get {
            return savedLocationInfos[index]
        }
    }
    
    //将高德地图返回的数据转化为内部使用的数据类型
    class func AMapAddressComponetToDict(addressInfo : AMapAddressComponent?,
                                         title : String, location :CLLocationCoordinate2D)->Dictionary<String,String>! {
        var info = Dictionary<String,String>()
        if (nil != addressInfo) {
            info[AddressComponent.Title.rawValue] = title
            info[AddressComponent.Latitude.rawValue] = String(location.latitude)
            info[AddressComponent.Longitude.rawValue] = String(location.longitude)
            info[AddressComponent.Province.rawValue] = String(addressInfo?.province)
            info[AddressComponent.City.rawValue] = String(addressInfo?.city)
            info[AddressComponent.District.rawValue] = String(addressInfo?.district)
            info[AddressComponent.TownShip.rawValue] = String(addressInfo?.township)
            info[AddressComponent.Building.rawValue] = String(addressInfo?.building)
            info[AddressComponent.StreetNumber.rawValue] = String(addressInfo?.streetNumber)
            info[AddressComponent.CityCode.rawValue] = String(addressInfo?.citycode)
            info[AddressComponent.Adcode.rawValue] = String(addressInfo?.adcode)
            info[AddressComponent.SavedTime.rawValue] = String(NSDate().timeIntervalSince1970)
        }
        return info
    }
    
    //移除指定的位置纪录
    func removeLocation(index : Int)->Bool {
        if (savedLocationInfos.count > index) {
            savedLocationInfos.removeAtIndex(index)
            //地点保存数据变更标志设置
            self[DataChangeFlag.LocationDataChange] = true
            //重统计信息中移除
            removeLocationsStatistics(index)
            return true
        } else {
            return false
        }
    }
    
    //保存指定的地址信息 (用于地点保存模式的数据记录)
    func appendLocation(info : Dictionary<String,String>? )->Bool {
        if (nil != info) {
            //地点保存数据变更标志设置
            self[DataChangeFlag.LocationDataChange] = true
            savedLocationInfos.append(SavedLocationInfo.init(data: info))
            //将保存的数据加入统计分析
            locationsStatisticsAnalysis(savedLocationInfos.last!, index: savedLocationInfos.count - 1)
            return true
        } else {
            return false
        }
    }
    
    //移除分析纪录
    func removeLocationsStatistics(index : Int) {
        for key in locationsStatistics.keys {
            var needBreak = false
            var array = locationsStatistics[key]!
            for count in 0...array.count {
                if (array[count] == index) {
                    array.removeAtIndex(count)
                    //统计数据变更标志位设置
                    self[DataChangeFlag.StatisticsChange] = true
                    needBreak = true
                    break
                }
            }
            if (needBreak) {
                break
            }
        }
    }
    
    //地点统计信息分析(只分析用户主动保存和智能保存的地点)
    func locationsStatisticsAnalysis(locationInfo : SavedLocationInfo!,index : Int) {
        let address = locationInfo[AddressComponent.Province]! +
                      locationInfo[AddressComponent.City]! +
                      locationInfo[AddressComponent.District]! +
                      locationInfo[AddressComponent.TownShip]!
        var statisticsArray = locationsStatistics[address]
        if (nil == statisticsArray) {
            locationsStatistics[address] = [Int](arrayLiteral: index)
        } else if (!ArraySearch(statisticsArray,search: index)) {
            statisticsArray?.append(index)
        }
        //统计数据变更标志位设置
        self[DataChangeFlag.StatisticsChange] = true
    }
}
