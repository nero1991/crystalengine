//
//  MainScene.h
//  carsystem
//
//  Created by Nero on 7/29/15.
//
//

#ifndef __carsystem__MainScene__
#define __carsystem__MainScene__

#include <cocos2d.h>

class MainScene : public cocos2d::Layer
{
    enum CHILD_TAG
    {
        TAG_BEGIN,
        TAG_BG,
        TAG_SPEEDDIAL,
        TAG_ROTATEDIAL,
        TAG_SIMULATE,
    };
public:
    CREATE_FUNC(MainScene);
    
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    virtual void onEnter() override;
    
private:
    void createMapView();
    void createSimulate();
    void createSpeedDial();
    void createRotateDial();
};

#endif /* defined(__carsystem__MainScene__) */
