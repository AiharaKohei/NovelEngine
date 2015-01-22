#include "PlayScene.h"


USING_NS_CC;

Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    isFirstText = true;
    
    if (GameManager::getInstance()->isLoadGame) {
        sceneCount = UserDefault::getInstance()->getIntegerForKey("sceneNum");
        cutCount = UserDefault::getInstance()->getIntegerForKey("cutNum");
    } else {
        sceneCount = 0;
        cutCount = 0;
    }
    
    
    LayerColor *back = LayerColor::create(Color4B(150, 150, 150, 80), winSize.width, winSize.height);
    back->setPosition(Point(0, 0));
    this->addChild(back, 2);
    
    auto taplistener = EventListenerTouchAllAtOnce::create();
    taplistener->onTouchesBegan = CC_CALLBACK_2(PlayScene::onTouchesBegan, this);
    taplistener->onTouchesMoved = CC_CALLBACK_2(PlayScene::onTouchesMoved, this);
    taplistener->onTouchesEnded = CC_CALLBACK_2(PlayScene::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(taplistener, -128);
    
    pTextNode = TextNode::create();
    pTextNode->setOriginalPosition(Point(80, winSize.height- 80));
    pTextNode->setInterval(0.01);
    pTextNode->setDelegate(this);
    this->addChild(pTextNode, 3);

    this->setDefaults();
    
    return true;
}

void PlayScene::setDefaults(){
    // defaultsPlist取得
    ValueMap defaultsPlist = FileUtils::getInstance()->getValueMapFromFile("res/defaults.plist");
    
    fontSize = defaultsPlist.at("textSize").asFloat();
    textDimention = defaultsPlist.at("textDimention").asFloat();
    fontName = defaultsPlist.at("fontName").asString();
    
    background = Sprite::create(StringUtils::format("res/bg/%s.png", defaultsPlist.at("bg").asString().c_str()));
    if (background) {
        background->setPosition(Point(winSize.width/2, winSize.height/2));
        this->addChild(background, 1);
    }

    //最初のplist取得
    std::string path = StringUtils::format("res/scene/Scene1.plist");
    plistMap = FileUtils::getInstance()->getValueMapFromFile(path.c_str());
    sceneVector.clear();
    sceneVector = plistMap.at("scene").asValueVector();
    
    this->setCut();
}


void PlayScene::setScene(){
    log("set scene");
    
    //分岐だったら
    ValueMap::iterator it2 = plistMap.find("fork");
    if (it2 != plistMap.end()) {
        ValueMap map = plistMap.at("fork").asValueMap();
        pTextNode->addButton(map.at("textA").asString(),
                             map.at("textB").asString(),
                             map.at("nextSceneNameA").asString(),
                             map.at("nextSceneNameB").asString()
                             );
    }
    log("add button");
    return;
    
    
    //分岐じゃなかったら
    ValueMap::iterator it = plistMap.find("nextSceneName");
    //plist名を探す
    if (it != plistMap.end()) {
        std::string path = StringUtils::format("res/scene/%s",plistMap.at("nextSceneName").asString().c_str());
        plistMap.clear();
        plistMap = FileUtils::getInstance()->getValueMapFromFile(path.c_str());
        //存在しないplist名だったら
        if (plistMap.empty()){
            auto *scene = EndScene::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        //次のSceneに移行
        else{
            sceneVector.clear();
            sceneVector = plistMap.at("scene").asValueVector();
            this->setCut();
        }
    }
    log("next scene");
    return;
}

void PlayScene::setSceneFromFork(std::string plistName){
    std::string path = StringUtils::format("res/scene/%s",plistName.c_str());
    plistMap = FileUtils::getInstance()->getValueMapFromFile(path.c_str());
    //存在しないplist名だったら
    if (plistMap.empty())
    {
        auto *scene = EndScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    //次のSceneに移行
    else
    {
        sceneVector.clear();
        cutCount = 0;
        sceneVector = plistMap.at("scene").asValueVector();
        this->setCut();
    }

}


void PlayScene::setCut(){
    log("set cut");
    cutMap.clear();
    if (static_cast<int>(sceneVector.size()) > cutCount) {
        cutMap = sceneVector.at(cutCount).asValueMap();
        std::string text = cutMap.at("text").asString();
        
        this->divideText(text);
        this->setBg();
        this->setBGM();
        this->setSE();
    } else {
        
        sceneCount++;
        cutCount = 0;
        this->setScene();
    }
}

void PlayScene::divideText(std::string &totalText){
    isContinue = false;
    
    textVector.clear();
    //改行を検知してテキストを分割する
    while (!totalText.empty()) {
        bool isNextContinue = false;
        
        int textSize = static_cast<int>(totalText.size());
        int indexBackSlashN = static_cast<int >(totalText.find("\n"));
        if (indexBackSlashN <= 0)
            indexBackSlashN = 9999;
        int indexTwoBackSlash = static_cast<int >(totalText.find("\\"));
        if (indexTwoBackSlash <= 0)
            indexTwoBackSlash = 9999;
        int indexPeriod = static_cast<int >(totalText.find("。"));
        if (indexPeriod <= 0){
            indexPeriod = 9999;
        } else {
            indexPeriod += 3;
            int indexParentheses = static_cast<int >(totalText.find("」"));
            if (indexPeriod == indexParentheses)
                indexPeriod += 3;
        }
                
        int endIndex = MIN(MIN(textSize, indexBackSlashN), MIN(indexTwoBackSlash, indexPeriod));
        if (endIndex == indexTwoBackSlash | endIndex == indexPeriod)
            isNextContinue = true;
        if (endIndex == indexPeriod && indexPeriod == indexBackSlashN)
            isNextContinue = false;
        
        const std::string oneWordText = std::string(totalText.c_str(), 0, endIndex);
        if (endIndex == indexTwoBackSlash) {
            totalText = totalText.erase(0, endIndex+2);
        } else {
            totalText = totalText.erase(0, isNextContinue == true ? endIndex : endIndex+1);
        }
        
        textParameter tParam = {oneWordText, isContinue};
        textVector.push_back(tParam);
        
        isContinue = isNextContinue;
    }
    this->setText();
}

int PlayScene::findIndexFromText(std::string &text){
    
    return 0;
}

void PlayScene::setText(){
    log("set text");
    if (!textVector.empty()) {
        textParameter tParam = textVector.front();
        textVector.erase(textVector.begin());
        pTextNode->setText(tParam.text, tParam.isContinue, textVector.front().isContinue);
        if (isFirstText) {
            pTextNode->run();
            isFirstText = false;
        }
    } else {
        cutCount++;
        this->setCut();
        pTextNode->removeAllText();
    }
}

void PlayScene::setBg(){
    ValueMap::iterator it = cutMap.find("bg");
    if (it != cutMap.end()) {
        std::string bgPlistName = cutMap.at("bg").asString();
        std::string bgPath = StringUtils::format("res/bg/%s", bgPlistName.c_str());
        background->setTexture(bgPath.c_str());
    }
}

void PlayScene::setSE(){
    ValueMap::iterator it = cutMap.find("se");
    if (it != cutMap.end()) {
        std::string sePlistName = cutMap.at("se").asString();
        std::string sePath = StringUtils::format("res/se/%s", sePlistName.c_str());
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(sePath.c_str());
    }
}

void PlayScene::setBGM(){
    ValueMap::iterator it = cutMap.find("bgm");
    if (it != cutMap.end()) {
        std::string bgmPlistName = cutMap.at("bgm").asString();
        std::string bgmPath = StringUtils::format("res/bgm/%s", bgmPlistName.c_str());
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmPath.c_str());
    }
}

void PlayScene::onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event){
    
}
void PlayScene::onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event){
    
}
void PlayScene::onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event)
{
    if (!pTextNode->getDidTextDisplay()) return;
    if (pTextNode->getIsShowButton()) return;
    
    this->setText();
    this->storeCurrentPage();
    pTextNode->run();
    
}

void PlayScene::storeCurrentPage(){
    UserDefault::getInstance()->setIntegerForKey("sceneNum", sceneCount);
    UserDefault::getInstance()->setIntegerForKey("cutNum", cutCount);
    UserDefault::getInstance()->flush();
}

