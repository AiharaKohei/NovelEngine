//
//  GameManager.cpp
//  NovelEngine
//
//  Created by aiharakohei on 2014/06/01.
//
//

#include "GameManager.h"

using namespace cocos2d;

GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager()
{
    isLoadGame = false;
}

GameManager::~GameManager()
{
    
}

GameManager* GameManager::getInstance()
{
    if (NULL == m_mySingleton)
    {
        m_mySingleton = new GameManager();
    }
    return m_mySingleton;
}
