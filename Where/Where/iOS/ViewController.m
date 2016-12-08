//
//  ViewController.m
//  Where
//
//  Created by Nero on 10/8/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import "ViewController.h"
#import "MapManager.h"
#import "SearchManager.h"
#import "QuickUI.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
}

-(void) viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    //启动高德地图
    [[MapManager sharedInstance] initManagerSize:self.view.bounds];
    
    [[MapManager sharedInstance] showTraffic:YES];
    [[MapManager sharedInstance] setMapType:TYPE_DRAW];
    [[MapManager sharedInstance] followUserLocation:YES];
    
    [self.view addSubview:[MapManager sharedInstance].mapView];
    
    //启动地图数据搜索服务
    [[SearchManager sharedInstance] initSearchService];
    
    //添加ui层
    QuickUI* view = [QuickUI addViewWithFrame:CGRectMake(0,0,CGRectGetWidth(self.view.bounds),CGRectGetHeight(self.view.bounds))];
    [self.view addSubview:view];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
