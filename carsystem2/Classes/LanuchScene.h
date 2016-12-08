//
//  LanuchScene.h
//  carsystem
//
//  Created by Nero on 7/29/15.
//
//

#ifndef __carsystem__LanuchScene__
#define __carsystem__LanuchScene__

#include <cocos2d.h>

class LanuchScene : public cocos2d::Layer
{
    enum CHILD_TAG
    {
        TAG_BEGIN,
        TAG_BG,
    };
public:
    CREATE_FUNC(LanuchScene);
    
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    virtual void onEnter() override;
    
private:
    void showAnimate();
    void createBackgroundImage();
    
    void sceneSwitch();
};

#endif /* defined(__carsystem__LanuchScene__) */
