//
//  UserPathDataManager.swift
//  Where?
//
//  Created by Nero on 10/13/15.
//  Copyright © 2015 Nero. All rights reserved.
//

import Foundation

class UserPathDataManager {
    private static var instance : UserPathDataManager? = nil
    
    class func sharedInstance()->UserPathDataManager! {
        if (nil == instance) {
            instance = UserPathDataManager()
        }
        return instance
    }
}