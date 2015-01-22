//
//  TextNode.h
//  NovelEngine
//
//  Created by aiharakohei on 2014/05/06.
//
//

#ifndef __NovelEngine__TextNode__
#define __NovelEngine__TextNode__

#include "cocos2d.h"
#include "Utils.h"

using namespace cocos2d;

class ForkButtonDelefate
{
public:
    virtual void setSceneFromFork(std::string plistName){};
    
};

class TextNode : public cocos2d::Node
{
public:
    
    TextNode();
     ~TextNode();
    virtual bool init();
    
    CREATE_FUNC(TextNode);
    
    
    void setText(const std::string &text, bool isContinuePrevLabel, bool isKeepNowText);
    void setInterval(float interval);
    void setOriginalPosition(cocos2d::Point originalPoint) {
        originalPoint_ = originalPoint;
    };
    void run();
    
    void removeAllText();
    
    void setDelegate(ForkButtonDelefate *delegate);
    void addButton(std::string textA, std::string textB, std::string nextSceneNameA, std::string nextSceneNameB);
    
    bool getDidTextDisplay(){
        return didTextDisplay;
    };
    bool getIsShowButton(){
        return isShowButton;
    };
    void renewTextLabel(float dt);
    void setCursorPosition(bool isKeepNowText);
    
private:
    int strLengthEnd_;
    int strLengthBegin_;
    float interval_;
    std::string nowLabelText_;
    cocos2d::Point originalPoint_;
    cocos2d::Label *nowLabel_;
    cocos2d::Vector<cocos2d::Label*> labelVector_;
    ForkButtonDelefate *delegate_;
    Label *cursorLabel;
    bool isKeepNowText_;
    
    
    void addLabel();
    void pressForkButton(Ref *obj);
    
    std::string nextSceneNameA_;
    std::string nextSceneNameB_;
    
    bool didTextDisplay;
    bool isShowButton;
    bool isContinuePrevLabel_;
    
    
};

#endif /* defined(__NovelEngine__TextNode__) */
