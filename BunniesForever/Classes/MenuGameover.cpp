//
//  MenuGameover.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "MenuGameover.h"
#include "cocos-ext.h"
using namespace extension;
void MenuGameover::draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
{
    renderer->render();
    
    DrawPrimitives::drawSolidRect(Point::ZERO,
                                  Point(getContentSize().width,
                                        getContentSize().height),
                                  Color4F(1,1,1,0.75));
}

bool MenuGameover::init()
{
    Layer::init();
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
    
    Label* title= Label::createWithSystemFont("GAME OVER", "HelveticaNeue",
                                              40);
    addChild(title);
    title->setPosition(Point(getContentSize().width/2,
                             getContentSize().height*0.8));
    
    Scale9Sprite * btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.5,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithSystemFont("SHARE", "Arial", 40);
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(233,143,11));
    }
    
    MenuItemLabel* share = MenuItemLabel::create(btnBg,
                                                  [](Ref*){
                                                      NotificationCenter::getInstance()->postNotification("onShare");
                                                  });
    
    btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.5,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithSystemFont("SHARE", "Arial", 40);
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(233,143,11));
    }

    
    MenuItemLabel* restart = MenuItemLabel::create(btnBg,
                                                   [](Ref*){
                                                       NotificationCenter::getInstance()->postNotification("onRestart");
                                                   });
    
    Menu* menu = Menu::create();
    menu->addChild(share);
    menu->addChild(restart);
    
    menu->alignItemsVertically();
    
    addChild(menu);
    
    return true;
}

