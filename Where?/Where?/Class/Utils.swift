//
//  Utils.swift
//  Where?
//
//  Created by Nero on 10/10/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

import Foundation

func ArraySearch<T : Comparable> (array : Array<T>!, search : T)->Bool {
    var result = false
    for element in array {
        if (element == search) {
            result = true
            break
        }
    }
    return result
}