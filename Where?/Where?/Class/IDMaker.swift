//
//  IDMaker.swift
//  Where?
//
//  Created by Nero on 10/10/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

import Foundation

class IDMaker {
    //错误的id
    static let nops : Int = -1;
    
    private static var instance : IDMaker? = nil
    
    //当前生成器
    private var idIndex = 0
    
    //获取下一个可用id,当id益处时返回无效id
    private var nextID : Int {
        get {
            if (idIndex < Int.max) {
                return ++idIndex
            } else {
                return IDMaker.nops;
            }
        }
    }
    
    //空闲id池
    private var idPool = [Int]()
    
    class func sharedInstance()->IDMaker! {
        if (nil == instance) {
            instance = IDMaker();
        }
        return instance;
    }
    
    //获取一个没有被使用过的唯一id
    func retainID()->Int {
        if (idPool.count == 0) {
            return nextID;
        } else {
            let id = idPool.last!
            idPool.removeLast()
            return id
        }
    }
    
    //收回一个之前被占用了的id
    func releaseID(id : Int)->Bool {
        if (id < idIndex && ArraySearch(idPool, search: id)) {
            idPool.append(id)
            return true
        } else {
            return false
        }
    }
}