//
//  TextNode.cpp
//  NovelEngine
//
//  Created by aiharakohei on 2014/05/06.
//
//

#include "TextNode.h"
USING_NS_CC;
#define BTN_TAG 1

TextNode::TextNode(){
    
}

TextNode::~TextNode(){
    
}

bool TextNode::init(){
    
    if ( !Node::init() )
    {
        return false;
    }
    
    didTextDisplay = true;
    isShowButton = false;
    isContinuePrevLabel_ = false;
        
    return true;
}

void TextNode::addLabel(){
    
    Label *label = Label::createWithSystemFont("a", "AmericanTypewriter-Bold", 32);
    label->setPosition(Point(originalPoint_.x, originalPoint_.y - ((int)labelVector_.size() * (label->getContentSize().height + 13))));
    label->setString("");
    label->enableOutline(Color4B(0, 0, 0, 0.5), 1);
    this->addChild(label);

    labelVector_.pushBack(label);
    
    nowLabel_ = label;
}

void TextNode::setText(const std::string &text, bool isContinuePrevLabel){
    
    isContinuePrevLabel_ = isContinuePrevLabel;

    if (isContinuePrevLabel_) {
        nowLabelText_ += text;
    } else {
        strLengthEnd_ = 0;
        strLengthBegin_ = 0;
        nowLabelText_ = text;
    }
}

void TextNode::setInterval(float interval){
    interval_ = interval;
}

void TextNode::removeAllText(){
    for (int i = 0; i < (int)labelVector_.size(); i++) {
        this->removeChild(labelVector_.at(i));
    }
    labelVector_.clear();
//    this->addLabel();
}

void TextNode::run(){
    if (!didTextDisplay) return;
    
    didTextDisplay = false;
    
    if (!isContinuePrevLabel_)
        this->addLabel();
    
    this->schedule(schedule_selector(TextNode::renewTextLabel), interval_);
}

void TextNode::renewTextLabel(float dt){
    
    if (strLengthEnd_ + strLengthBegin_ >= nowLabelText_.length()) {
        this->unschedule(schedule_selector(TextNode::renewTextLabel));
        didTextDisplay = true;
    } else {
        int charSize = Utils::conversionCharBytesFromCharCode(this->nowLabelText_[strLengthEnd_]);
        strLengthEnd_ += charSize;
        
        std::string str(this->nowLabelText_, strLengthBegin_, strLengthEnd_);
        nowLabel_->setString(str);
        
        nowLabel_->setPosition(Point(originalPoint_.x + nowLabel_->getSystemFontSize() / 2 + nowLabel_->getContentSize().width / 2, nowLabel_->getPositionY()));
    }
    if (nowLabel_->getContentSize().width >= 920) {
        
        strLengthBegin_ += strLengthEnd_;
        strLengthEnd_ = 0;
        this->addLabel();
    }

}

void TextNode::addButton(std::string textA, std::string textB, std::string nextSceneNameA, std::string nextSceneNameB){
    
    std::string formatedTextA = StringUtils::format("A : %s", textA.c_str());
    Label *labelA = Label::createWithSystemFont(formatedTextA.c_str(), "AmericanTypewriter-Bold", 32);
    MenuItemLabel *btnA = MenuItemLabel::create(labelA, CC_CALLBACK_1(TextNode::pressForkButton, this));
    btnA->setTag(0);
    btnA->setPosition(Point(originalPoint_.x + btnA->getContentSize().width/2, originalPoint_.y));
    
    std::string formatedTextB = StringUtils::format("B : %s", textB.c_str());
    Label *labelB = Label::createWithSystemFont(formatedTextB.c_str(), "AmericanTypewriter-Bold", 32);
    labelB->setDimensions(920, 0);
    MenuItemLabel *btnB = MenuItemLabel::create(labelB, CC_CALLBACK_1(TextNode::pressForkButton, this));
    btnB->setTag(1);
    btnB->setPosition(Point(originalPoint_.x + btnB->getContentSize().width/2, btnA->getPositionY()- btnB->getContentSize().height - 20));
    
    Menu *menu = Menu::create(btnA, btnB, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 10, BTN_TAG);
    nextSceneNameA_ = nextSceneNameA;
    nextSceneNameB_ = nextSceneNameB;
    
    isShowButton = true;

}

void TextNode::setDelegate(ForkButtonDelefate *delegate) {
    delegate_ = delegate;
}

void TextNode::pressForkButton(cocos2d::Ref *obj){
    labelVector_.clear();

    this->removeChildByTag(BTN_TAG);
    MenuItemLabel *btn = (MenuItemLabel*)obj;
    std::string plsitName = btn->getTag() == 0 ? nextSceneNameA_ : nextSceneNameB_;
    delegate_->setSceneFromFork(plsitName);
    
    isShowButton = false;
}
