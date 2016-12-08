//
//  FileManager.swift
//  Where?
//
//  Created by Nero on 10/12/15.
//  Copyright © 2015 Nero. All rights reserved.
//

import Foundation

class FileManager {
    private static var instance : FileManager? = nil
    
    class func sharedInstance()->FileManager! {
        if (nil == instance) {
            instance = FileManager()
        }
        return instance
    }
    
    func read(fileName : String)->String! {
        var content : String? = String()
        do {
            content = try String.init(contentsOfFile: fullPath(fileName), encoding: NSUTF8StringEncoding)
        } catch {
            
        }
        return content
    }
    
    func write(fileName : String,content : String) {
        do {
            try content.writeToFile(fullPath(fileName), atomically: true, encoding: NSUTF8StringEncoding)
        } catch {
            
        }
    }
    
    func fullPath(fileName : String)->String {
        //获取Document文件夹
        var paths = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory ,
            NSSearchPathDomainMask.UserDomainMask, true);
        let documentsDirectory = paths[0]
        return documentsDirectory + fileName
    }
}