//
//  IngameScene.h
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#ifndef __BunniesForever__IngameScene__
#define __BunniesForever__IngameScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class RunRow;
class IngameScene : public Layer
{
    Label* _scoreLabel;
    int _score;
    
    Vector<RunRow*>   _rows;
    
    Node* _PauseMenu;
    Node* _GameoverMenu;
public:
    static Scene* scene();
    static IngameScene* getInstance();
    bool init();
    float runSpeed();
    void addScore(int score);
    void draw(Renderer* renderer, const kmMat4 &transform, bool transformUpdated);
    
    void addRow(const Color3B& color);
    
    bool CanSpawnRows();
    
    void onGameOver(Ref* );
    void onTapPause(Ref* );
    void onRestartGame(Ref*);
    void onResumeGame(Ref*);
};
#endif /* defined(__BunniesForever__IngameScene__) */
