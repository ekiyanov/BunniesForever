#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "IngameScene.h"
#include "cocos-ext.h"
#include "PlatformParams.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "AndroidJNI.h"
#endif

using namespace cocos2d;
using namespace extension;
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
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    hideAdmobJNI();
#endif
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Click2.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Win.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Lose.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("BonusGet.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AchievementGet.mp3");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist");
    
    // create menu, it's an autorelease object
    Menu* pMenu=Menu::create();
    
    Scale9Sprite * btnBg = Scale9Sprite::create("sq100.png");
    btnBg->setContentSize(Size(getContentSize().width*0.5,getContentSize().height*0.1));
    
    {
        Label* lbl = Label::createWithTTF("START", "fonts/victor-pixel.ttf", PPIntForKey("fontsize"));
        lbl->setPosition(Point(btnBg->getContentSize().width/2,
                               btnBg->getContentSize().height/2));
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B(233,143,11));
    }
    
    MenuItemLabel* btnStartSimple = MenuItemLabel::create(btnBg,
                                                          [](Ref*)
                                                          {
                                                              Scene* scene = IngameScene::scene();
                                                              Director::getInstance()->pushScene(scene);
                                                          });
    
    /*
    {
        btnBg = Scale9Sprite::create("sq100.png");
        btnBg->setContentSize(Size(getContentSize().width*0.5,getContentSize().height*0.1));
        
        Label* lbl = Label::createWithSystemFont("Top Scores", "HelveticaNeue", 20);
        btnBg->addChild(lbl);
        btnBg->setColor(Color3B::MAGENTA);
    }
    
    
    MenuItemLabel* btnScores = MenuItemLabel::create(Label::createWithSystemFont("Top Scores", "HelveticaNeue", 20),
                                                     [](Ref*)
                                                     {
                                                         
                                                     });
    
    
    pMenu->addChild(btnScores);
    
    */
    
    pMenu->addChild(btnStartSimple);
    
    pMenu->alignItemsVertically();
    this->addChild(pMenu, 1);
    
    return true;
}