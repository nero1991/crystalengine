//
//  LanuchScene.cpp
//  carsystem
//
//  Created by Nero on 7/29/15.
//
//

#include "LanuchScene.h"
#include "MainScene.h"

USING_NS_CC; 

Scene* LanuchScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LanuchScene::create();
    scene->addChild(layer);
    return scene;
}

bool LanuchScene::init()
{
    bool result = Layer::init();
    return result;
}

void LanuchScene::onEnter()
{
    createBackgroundImage();
    showAnimate();
    Layer::onEnter();
}

void LanuchScene::showAnimate()
{
    auto bg = getChildByTag(CHILD_TAG::TAG_BG);
    if (nullptr != bg) {
        bg->setOpacity(0);
        bg->runAction(Sequence::create(FadeTo::create(0.5f, 255),
                                       CallFunc::create(CC_CALLBACK_0(LanuchScene::sceneSwitch, this)), NULL));
    }
}

void LanuchScene::createBackgroundImage()
{
    if (nullptr == getChildByTag(CHILD_TAG::TAG_BG)) {
        auto background = Sprite::create("res/lanuch.png");
        background->setPosition(Vec2::ZERO);
        background->setAnchorPoint(Vec2::ZERO);
        background->ignoreAnchorPointForPosition(false);
        addChild(background,0,CHILD_TAG::TAG_BG);
    }
}

void LanuchScene::sceneSwitch()
{
    CCLOG("切换到主界面");
    Director::getInstance()->replaceScene(MainScene::createScene());
}