//
//  QuickUI.m
//  Where
//
//  Created by Nero on 10/9/15.
//  Copyright (c) 2015 Nero. All rights reserved.
//

#import "QuickUI.h"
#import "MapManager.h"
#import "SearchManager.h"

enum UI_TYPE {
    UI_SAVE_BUTTON = 1,
};

@implementation QuickUI

+ (QuickUI*) addViewWithFrame : (CGRect) frame {
    QuickUI* view = [[[NSBundle mainBundle] loadNibNamed:@"QuickUI" owner:self options:nil] lastObject];
    if (nil != view) {
        [view setFrame:frame];
        [view initEventListener];
    }
    return view;
}

- (void) initEventListener {
    id saveButton = [self viewWithTag:UI_SAVE_BUTTON];
    if ([saveButton isKindOfClass:[UIButton class]] == YES) {
        //TODO::添加事件响应
        [saveButton addTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    } else {
        NSLog(@"没有查找到保存按钮！");
    }
}

- (IBAction) action:(id)sender {
    switch ([sender tag]) {
        case UI_SAVE_BUTTON:
        {
            [[SearchManager sharedInstance] searchUserLocationInfo];
            NSLog(@"保存用户位置");
        }
            break;
        default:
            break;
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
