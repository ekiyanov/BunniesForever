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

void RunRow::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    renderer->render();
    
    DrawPrimitives::drawSolidRect(Point::ZERO, Point(getContentSize().width,getContentSize().height),
                                  Color4F(0.8,0.8,0.8,1.0F));
    DrawPrimitives::setDrawColor4B(0, 0, 0, 1);
    DrawPrimitives::drawLine(Point::ZERO, Point(getContentSize().width,0));
}

bool RunRow::init(const Color3B& color)
{
    setContentSize(Size(Director::getInstance()->getWinSize().width,300));
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
    
    pCharacter = Character::CharacterWithColor(color);
    
    pCharacter->setPosition(Point(pCharacter->getContentSize().width,0));
    addChild(pCharacter);
    
    scheduleUpdate();
    
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
        pCharacter->Jump();
        return true;
    }

    return false;
}

void RunRow::update(float dt)
{
    updateCollision();
    
    updateGeneration(dt);
}

void RunRow::updateGeneration(float dt)
{
    _nextGeneration-=dt;
    
    if (_nextGeneration<=0)
    {
        _nextGeneration=CCRANDOM_0_1()*1+1;
     
        RowObject * rowObject=RowObjectFactory::getInstance()->ObjectForKey(
                                                                            IngameScene::getInstance()->CanSpawnRows()?"rescue":(
                                                                            rand()%5==0?"bonus":"terminal"),
                                                                            "");
        rowObject->setPosition(getContentSize().width,0);
        
        _rowObjects.pushBack(rowObject);
        
        addChild(rowObject);
    }
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
