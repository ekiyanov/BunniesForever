#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "IngameScene.h"


using namespace cocos2d;
using namespace CocosDenshion;

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
        return false;
    
    // create menu, it's an autorelease object
    Menu* pMenu=Menu::create();
    
    MenuItemLabel* btnStartSimple = MenuItemLabel::create(Label::createWithSystemFont("Start", "HelveticaNeue", 20),
                                                          [](Ref*)
                                                          {
                                                              Scene* scene = IngameScene::scene();
                                                              Director::getInstance()->pushScene(scene);
                                                          });
    
    
    
    MenuItemLabel* btnScores = MenuItemLabel::create(Label::createWithSystemFont("Top Scores", "HelveticaNeue", 20),
                                                     [](Ref*)
                                                     {
                                                         
                                                     });
    
    pMenu->addChild(btnStartSimple);
    pMenu->addChild(btnScores);
    
    
    pMenu->alignItemsVertically();
    this->addChild(pMenu, 1);
    
    return true;
}