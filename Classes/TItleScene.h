//
//  TItleScene.h
//  NovelEngine
//
//  Created by aiharakohei on 2014/05/27.
//
//

#ifndef __NovelEngine__TItleScene__
#define __NovelEngine__TItleScene__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "GameManager.h"
#include "PlayScene.h"

enum
{
    newBtnTag = 0,
    loadBtnTag,
};

using namespace cocos2d;

class TitleScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
    
    void pressForkButton(cocos2d::Ref *obj);
    
};
#endif /* defined(__NovelEngine__TItleScene__) */
