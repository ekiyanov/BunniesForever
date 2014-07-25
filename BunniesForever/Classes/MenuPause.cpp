//
//  MenuPause.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "MenuPause.h"
#include "cocos-ext.h"
#include "PlatformParams.h"
using namespace extension;
void MenuPause::draw( Renderer* renderer, const kmMat4 &transform, bool transformUpdated)
{
    renderer->render();
    
    DrawPrimitives::drawSolidRect(Point::ZERO,
                                  Point(getContentSize().width,
                                        getContentSize().height),
                                  Color4F(1,1,1,0.75));
}

bool MenuPause::init()
{
    Layer::init();
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);

    Label* title= Label::createWithTTF("PAUSE", "fonts/victor-pixel.ttf",
                                              PPIntForKey("fontsize"));
    title->setColor(Color3B(63,63,63));
    addChild(title);
    title->setPosition(Point(getContentSize().width/2,
                             getContentSize().height*0.8));
    
    Scale9Sprite * btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.5,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithTTF("RESUME", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(11,197,243));
    }
    
    MenuItemLabel* resume = MenuItemLabel::create(btnBg,
                                                  [](Ref*){
                                                  
                                                      NotificationCenter::getInstance()->postNotification("onResume");
                                                  });
    
    btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.5,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithTTF("RESTART", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(11,197,243));
    }
    
    MenuItemLabel* restart = MenuItemLabel::create(btnBg,
                                                  [](Ref*){
                                                       NotificationCenter::getInstance()->postNotification("onRestart");
                                                  });
    
    Menu* menu = Menu::create();
    menu->addChild(resume);
    menu->addChild(restart);
    
    menu->alignItemsVertically();
    
    addChild(menu);
    
    return true;
}

