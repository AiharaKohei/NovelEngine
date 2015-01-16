#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "TextNode.h"
#include "SimpleAudioEngine.h"
#include "EndScene.h"
#include "GameManager.h"

using namespace cocos2d;

struct textParameter {
    std::string text;
    bool isContinue;
};


class PlayScene : public cocos2d::Layer, ForkButtonDelefate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
    
    void setDefaults();
    void setScene();
    void setCut();
    void setText();
    void setBg();
    void setSE();
    void setBGM();
    
    void divideText(std::string &totalText);
    
    void storeCurrentPage();
    
    virtual void setSceneFromFork(std::string plistName);
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);

    
private:
    
    Sprite *background;
    
    float fontSize;
    float textDimention;
    std::string fontName;
    
    ValueMap plistMap;
    ValueVector sceneVector;
    ValueMap cutMap;
    TextNode *pTextNode;
    
    int sceneCount;
    int cutCount;
    std::string nextSceneName;
    
    std::vector<textParameter> textVector;
    
    Size winSize;
    
    bool isFirstText;
    
    int findIndexFromText(std::string &text);
    
    bool isContinue;
};

#endif // __HELLOWORLD_SCENE_H__
