//
//  IngameScene.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "IngameScene.h"
#include "RunRow.h"

static IngameScene* __instance = 0;

Scene* IngameScene::scene()
{
    Scene* sc= Scene::create();
    IngameScene* ingame=new IngameScene();
    ingame->autorelease();
    ingame->init();
    __instance=ingame;
    sc->addChild(ingame);
    return sc;
}

IngameScene* IngameScene::getInstance()
{
    return __instance;
}

float IngameScene::runSpeed()
{
    return -500;
}

void IngameScene::addRow(const Color3B& color)
{
    RunRow* r = new RunRow();
    r->init(color);
    r->autorelease();
    
    float newheight=0;

    
    
    _rows.pushBack(r);
    
    addChild(r);
    
    for (auto it : _rows)
        newheight+=it->getContentSize().height;
    
    float newTopY = getContentSize().height/2+newheight/2;
    
    r->setPosition(Point(getContentSize().width,newTopY-newheight));
    
    for (auto it : _rows)
    {
        newTopY-=it->getContentSize().height;
        it->runAction(MoveTo::create(0.5, Point(0,newTopY)));
        
        it->killAllObjects();
    }
}

bool IngameScene::CanSpawnRows()
{
    return _score>=(pow(2,_rows.size()));
}

void IngameScene::draw(Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
{
    renderer->render();
    
    DrawPrimitives::drawSolidRect(Point::ZERO, Point(getContentSize().width,
                                                     getContentSize().height),
                                  Color4F::WHITE);
}

bool IngameScene::init()
{
    
    Layer::init();

    RunRow* r = new RunRow();
    r->init(Color::RED);
    r->autorelease();
    addChild(r);
    r->setPosition(Point(0,getContentSize().height/2-r->getContentSize().height/2));
    
    _rows.pushBack(r);
    
    MenuItemLabel* pausebtn=    MenuItemLabel::create(Sprite::create("PauseBtn.png"),
                          [](Ref*){
                             // pause menu
                          });
    
    Menu* menu = Menu::create();
    menu->addChild(pausebtn);
    menu->setPosition(Point::ZERO);menu->setAnchorPoint(Point::ZERO);
    pausebtn->setPosition(Point(getContentSize().width-pausebtn->getContentSize().width/2,
                                getContentSize().height-pausebtn->getContentSize().height/2));
    
    Label* score = Label::createWithSystemFont("0", "HelveticaNeue", 20);
    addChild(score);
    score->setPosition(Point(getContentSize().width/2,
                             getContentSize().height-score->getContentSize().height));
    _scoreLabel=score;
    _scoreLabel->setColor(Color3B(63,63,63));
    _score=0;
    
    addChild(menu);
    
    
    return true;
}

void IngameScene::addScore(int score)
{
    _score+=score;
    
    char text[64];sprintf(text, "%i",_score);
    _scoreLabel->setString(text);
}