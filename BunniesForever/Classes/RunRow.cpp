//
//  RunRow.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "RunRow.h"
#include "Character.h"
#include "RowObject.h"
#include "ObjectFactory.h"
#include "IngameScene.h"
#include "PlatformParams.h"

void RunRow::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    renderer->render();
    
    DrawPrimitives::setDrawColor4B(0, 0, 0, 255-63);
    DrawPrimitives::drawLine(Point::ZERO, Point(getContentSize().width,0));
}

bool RunRow::init(const Color3B& color)
{
    setContentSize(Size(Director::getInstance()->getWinSize().width,PPIntForKey("rowheight")));
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
    
    _paused=false;
    
    _boxHeight=PPIntForKey("boxheight");
    _bonusHeight=PPIntForKey("bonusheight");
    
    pCharacter = Character::CharacterWithColor(color);
    
    pCharacter->setPosition(Point(pCharacter->getContentSize().width,0));
    addChild(pCharacter);
    
    scheduleUpdate();
    
    Label* taptojump = Label::createWithTTF("TAP TO JUMP", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
    _taptojump = taptojump;
    addChild(_taptojump);
    _taptojump->setVisible(false);
    _taptojump->setColor(color);
    _taptojump->setAnchorPoint(Point::ANCHOR_MIDDLE);
    
    
    return true;
}

void RunRow::killAllObjects()
{
    for (auto it : _rowObjects)
    {
        it->removeFromGame();
    }
    
    _rowObjects.clear();
}

bool RunRow::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point pt=convertTouchToNodeSpace(touch);
    if (pt.x>0&&pt.y>0&&pt.x<getContentSize().width&&pt.y<getContentSize().height)
    {
        if (_paused)  return false;
        if (_readysetgo)
        {
            _readysetgo=false;
            
            _taptojump->runAction(Sequence::create(FadeOut::create(0.3),
                                                   CallFunc::create([this](){_taptojump->setVisible(false);}),
                                                   NULL));
        }
        
        
        pCharacter->Jump();
        return true;
    }

    return false;
}

void RunRow::update(float dt)
{
    if (_readysetgo)
    {
            _gamet+=dt;
        
        _taptojump->setScale(0.9+0.1*sin(_gamet));
        
    }
    if (_paused || IngameScene::getInstance()->allSetDone()==false) return;
    updateCollision();
    
    updateGeneration(dt);
}

void RunRow::updateGeneration(float dt)
{

    _nextGeneration-=dt;
    
    if (_nextGeneration<=0)
    {
        _nextGeneration=CCRANDOM_0_1()*1+1;
     
        bool terminal = false;
        std::string key =IngameScene::getInstance()->CanSpawnRows()?"rescue":(
                                                                              rand()%5==0?"bonus":"terminal");
        RowObject * rowObject=RowObjectFactory::getInstance()->ObjectForKey(key.c_str()
                                                                            ,
                                                                            "");
        
        terminal = key=="terminal";
        rowObject->setPosition(getContentSize().width,0);
        
        _rowObjects.pushBack(rowObject);

        
        addChild(rowObject);
        
        if (key=="bonus")
        {
            float scale = _bonusHeight/rowObject->getContentSize().height;
            rowObject->setScale(scale);
        }
        
        if (terminal)
        {
            float scale = _boxHeight/rowObject->getContentSize().height;
            rowObject->setScale(scale);
            
            RowObject* obj=RowObjectFactory::getInstance()->ObjectForKey("bonus", "");
            scale = _bonusHeight/obj->getContentSize().height;
            obj->setScale(scale);
            
            obj->setPosition(getContentSize().width,rowObject->getContentSize().height);
            _rowObjects.pushBack(obj);
            addChild(obj);
        }
    }
}

void RunRow::setPaused(bool state)
{
    _paused=state;
    for ( auto it : _rowObjects)
        it->setPaused(_paused);
}

void RunRow::updateCollision()
{
    Rect charRect=pCharacter->getBoundingBox();
    
    Vector<RowObject*> ConsumedObjects;
    
    for (auto it : _rowObjects)
    {
        Rect objRect = it->getBoundingBox();
        
        if (objRect.intersectsRect(charRect))
        {
            if (pCharacter->onCollideWithObject(it))
            {
                ConsumedObjects.pushBack(it);
            }
        }
    }
    
    for (auto it : ConsumedObjects)
    {
        it->removeFromGame();
        _rowObjects.eraseObject(it);
    }
    ConsumedObjects.clear();
    
}


void RunRow::setReadySetGo(bool state)
{
    _taptojump->setVisible(state);
    
    if (state){

     
        _gamet=0;
        
        _taptojump->setOpacity(255);
        _taptojump->setPosition(getContentSize().width+_taptojump->getContentSize().width,
                                _taptojump->getContentSize().height/2);
        _taptojump->runAction(EaseElasticOut::create(MoveTo::create(0.5,
                    Point(getContentSize().width-_taptojump->getContentSize().width/2,
                                                        _taptojump->getContentSize().height/2)),0.5));
        
         _readysetgo=state;
    }
}