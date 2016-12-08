//
//  MainScene.cpp
//  carsystem
//
//  Created by Nero on 7/29/15.
//
//

#include "MainScene.h"
#include "Instrument.h"
#include "InstrumentDial.h"
#include <CocosGUI.h>
#include <UIWebView.h>
#include "Simulation.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    bool result = Layer::init();
    scheduleUpdate();
    return result;
}

void MainScene::onEnter()
{
    createSpeedDial();
    createRotateDial();
    createMapView();
    createSimulate();
    Layer::onEnter();
}

void MainScene::createMapView()
{
    removeChildByTag(CHILD_TAG::TAG_BG);
    auto map = Sprite::create("res/map.png");
    map->setAnchorPoint(Vec2(0.5f, 0.5f));
    map->ignoreAnchorPointForPosition(false);
    map->setPosition(getContentSize().width / 2, getContentSize().height / 2);
    addChild(map,TAG_BG,TAG_BG);
    
//    auto webView = experimental::ui::WebView::create();
//    webView->setContentSize(getContentSize());
//    webView->setPosition(Vec2::ZERO);
//    webView->setAnchorPoint(Vec2::ZERO);
//    webView->ignoreAnchorPointForPosition(false);
//    addChild(webView, 0.0f, CHILD_TAG::TAG_BG);
//    webView->loadURL("http://map.baidu.com");
//    webView->setTouchEnabled(false);
//    webView->setScalesPageToFit(true);
}

void MainScene::createSimulate()
{
    removeChildByTag(TAG_SIMULATE);
    auto simulate = Simulation::create(dynamic_cast<InstrumentDial*>(getChildByTag(TAG_SPEEDDIAL)),
                                       dynamic_cast<InstrumentDial*>(getChildByTag(TAG_ROTATEDIAL)));
    simulate->ignoreAnchorPointForPosition(false);
    simulate->setAnchorPoint(Vec2(0.5f, 0.5f));
    simulate->setPosition((getContentSize().width - simulate->getContentSize().width) / 2.0f,
                          (getContentSize().height - simulate->getContentSize().height) / 2.0f);
    
    simulate->setSimulateInfo(280.0f, 9000.0f);

    simulate->addSimulateLv(6.0f, 30.0f);
    simulate->addSimulateLv(5.0f, 50.0f);
    simulate->addSimulateLv(4.0f, 70.0f);
    simulate->addSimulateLv(3.0f, 80.0f);
    simulate->addSimulateLv(2.0f, 120.0f);
    simulate->addSimulateLv(1.0f, 240.0f);

    
    addChild(simulate, TAG_SIMULATE, TAG_SIMULATE);
}

void MainScene::createSpeedDial()
{
    removeChildByTag(TAG_SPEEDDIAL);
    auto dial = InstrumentDial::create();
    dial->setInstrumentSize(Size(getContentSize().width / 3.0f,getContentSize().width / 3.0f));
    dial->setPosition(Vec2(dial->getInstrumentSize().width / 2.0f,
                           dial->getInstrumentSize().height));
    dial->setValueRange(0.0f, 280.0f);
    dial->setValue(120.0f);
    addChild(dial,TAG_SPEEDDIAL,TAG_SPEEDDIAL);
}

void MainScene::createRotateDial()
{
    removeChildByTag(TAG_ROTATEDIAL);
    auto dial = InstrumentDial::create();
    dial->setInstrumentSize(Size(getContentSize().width / 3.0f,getContentSize().width / 3.0f));
    dial->setPosition(Vec2(getContentSize().width - dial->getInstrumentSize().width / 2.0f,
                           dial->getInstrumentSize().height));
    dial->setValueRange(0.0f, 8000.0f);
    dial->setValue(2121.0f);
    addChild(dial,TAG_ROTATEDIAL,TAG_ROTATEDIAL);
}