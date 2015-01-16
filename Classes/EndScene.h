//
//  EndScene.h
//  NovelEngine
//
//  Created by aiharakohei on 2014/06/01.
//
//

#ifndef __NovelEngine__EndScene__
#define __NovelEngine__EndScene__

#include "cocos2d.h"

using namespace cocos2d;

class EndScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
  
    // implement the "static create()" method manually
    CREATE_FUNC(EndScene);
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
    
};
#endif /* defined(__NovelEngine__EndScene__) */
