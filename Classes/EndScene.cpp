//
//  EndScene.cpp
//  NovelEngine
//
//  Created by aiharakohei on 2014/06/01.
//
//

#include "EndScene.h"
#include "TItleScene.h"
USING_NS_CC;

Scene* EndScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite *bg = Sprite::create("res/endScene/bg.png");
    bg->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(bg);
    
    auto taplistener = EventListenerTouchAllAtOnce::create();
    taplistener->onTouchesBegan = CC_CALLBACK_2(EndScene::onTouchesBegan, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(taplistener, -128);
    
    return true;
}

void EndScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, TitleScene::createScene(), Color3B::WHITE));
    
}

