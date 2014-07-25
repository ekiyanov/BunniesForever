//
//  MenuGameover.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "MenuGameover.h"

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
    
    MenuItemLabel* share = MenuItemLabel::create(Label::createWithSystemFont("SHARE",
                                                                              "HelveticaNeue",
                                                                              20),
                                                  [](Ref*){
                                                      NotificationCenter::getInstance()->postNotification("onShare");
                                                  });
    
    MenuItemLabel* restart = MenuItemLabel::create(Label::createWithSystemFont("RESTART",
                                                                               "HelveticaNeue",
                                                                               20),
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

