#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
//    glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::SHOW_ALL);
    auto s = director->getWinSize();

    std::vector<std::string> searchpath;

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    if (s.width==1024 || s.width==2048)
    {
        searchpath.push_back("ipad");
    }
    if (s.width==2048)
    {
        searchpath.push_back("ipadhd");
    }
    
    if (s.height==320 || s.height==640)
    {
        searchpath.push_back("iphone");
    }
    if(s.height==640)
        searchpath.push_back("iphonehd");
#else
    searchpath.push_back("android");
#endif
    
    searchpath.push_back("shared");
    searchpath.push_back("sounds");

    FileUtils::getInstance()->setSearchPaths(searchpath);
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
