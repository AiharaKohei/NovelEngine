//
//  TItleScene.cpp
//  NovelEngine
//
//  Created by aiharakohei on 2014/05/27.
//
//

#include "TItleScene.h"
USING_NS_CC;


using namespace ui;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite *bg = Sprite::create("res/titleScene/bg.png");
    bg->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(bg);
    
    Label *labelA = Label::createWithSystemFont("始めから", "AmericanTypewriter-Bold", 32);
    labelA->setColor(Color3B(0, 0, 0));
    MenuItemLabel *newBtn = MenuItemLabel::create(labelA, CC_CALLBACK_1(TitleScene::pressForkButton, this));
    newBtn->setPosition(Point(winSize.width/2, winSize.height/2 - 50));
    newBtn->setTag(newBtnTag);
    
    
    Label *labelB = Label::createWithSystemFont("続きから", "AmericanTypewriter-Bold", 32);
    labelB->setColor(Color3B(0, 0, 0));
    MenuItemLabel *loadBtn = MenuItemLabel::create(labelB, CC_CALLBACK_1(TitleScene::pressForkButton, this));
    loadBtn->setPosition(Point(winSize.width/2, winSize.height/2 - 180));
    loadBtn->setTag(loadBtnTag);
    
    Menu *menu = Menu::create(newBtn, loadBtn, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    
    return true;
}

void TitleScene::pressForkButton(cocos2d::Ref *obj){
    MenuItemLabel *btn = (MenuItemLabel*)obj;
    switch (btn->getTag()) {
        case newBtnTag:
            GameManager::getInstance()->isLoadGame = false;
            break;
        case loadBtnTag:
            GameManager::getInstance()->isLoadGame = true;
            break;
        default:
            break;
    }
    
    Scene *scene = PlayScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
