//
//  GameManager.h
//  NovelEngine
//
//  Created by aiharakohei on 2014/06/01.
//
//

#ifndef __NovelEngine__GameManager__
#define __NovelEngine__GameManager__

#include "cocos2d.h"

using namespace cocos2d;

class GameManager
{
private:
    static GameManager* m_mySingleton;
    
public:
    GameManager();
    ~GameManager();
    static GameManager* getInstance();
    
    bool isLoadGame;
};
#endif /* defined(__NovelEngine__GameManager__) */
