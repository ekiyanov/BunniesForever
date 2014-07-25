//
//  MenuPause.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "MenuPause.h"

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

    Label* title= Label::createWithSystemFont("PAUSE", "HelveticaNeue",
                                              40);
    addChild(title);
    title->setPosition(Point(getContentSize().width/2,
                             getContentSize().height*0.8));
    
    MenuItemLabel* resume = MenuItemLabel::create(Label::createWithSystemFont("RESUME",
                                                                              "HelveticaNeue",
                                                                              20),
                                                  [](Ref*){
                                                  
                                                      NotificationCenter::getInstance()->postNotification("onResume");
                                                  });
    
    MenuItemLabel* restart = MenuItemLabel::create(Label::createWithSystemFont("RESTART",
                                                                              "HelveticaNeue",
                                                                              20),
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

