//
//  MissionCenter.swift
//  Where?
//
//  Created by Nero on 10/10/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

import Foundation

protocol MissionCompleteDelegate {
    func afterComplete(missionID : Int, isSuccess : Bool, data : Dictionary<String,String>!);
}

class MissionCenter {
    typealias Missions = Dictionary<Int,MissionCompleteDelegate?>
    
    private static var instance : MissionCenter? = nil
    
    private var missions : Missions = Missions()
    
    class func sharedInstance()->MissionCenter! {
        if (nil == instance) {
            instance = MissionCenter()
        }
        return instance
    }
    
    subscript (missionID : Int)->MissionCompleteDelegate? {
        get {
            return missions[missionID]!
        }
    }
    
    func append(delegate : MissionCompleteDelegate?)->Int {
        var result = IDMaker.sharedInstance().retainID()
        if (nil != delegate && result != IDMaker.nops && missions[result] == nil) {
            missions[result] = delegate
        } else {
            print("创建回调任务时出现了错误")
            //回收不再使用的id
            IDMaker.sharedInstance().releaseID(result)
            result = IDMaker.nops
        }
        return result
    }
    
    func remove(missionID : Int)->Bool {
        if (missions.removeValueForKey(missionID) != nil) {
            IDMaker.sharedInstance().releaseID(missionID)
            return true
        } else {
            return false
        }
    }
}