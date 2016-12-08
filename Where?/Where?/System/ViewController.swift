//
//  ViewController.swift
//  Where?
//
//  Created by Nero on 10/10/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        //初始化地图view，并启用高德地图服务
        MapManager.sharedInstance().initMapServices(view.bounds)
        MapManager.sharedInstance().showTraffic = true
        MapManager.sharedInstance().showUserLocation(true)
        //初始化地理信息搜索API
        SearchManager.sharedInstance().initSearchService()
        
        view.addSubview(MapManager.sharedInstance().mapView!)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}

