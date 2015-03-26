#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

std::string AppDelegate::start_param = "";

AppDelegate::AppDelegate() {
    log("AppDelegate::AppDelegate()");
    //auto dispatcher = Director::getInstance()->getEventDispatcher();  
    //auto customListener3 = EventListenerCustom::create("desai.start", CC_CALLBACK_1(HelloWorld::onCustomEvent, this));
    //dispatcher->addEventListenerWithFixedPriority(customListener3, 1);
}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    log("before HelloWorld::createScene()");
    auto scene = HelloWorld::createScene();

    // run
    log("before runWithScene");
    director->runWithScene(scene);


    auto customListener = EventListenerCustom::create("desai.start.internal", AppDelegate::onStartWithUrl);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(customListener, 1);

    //如果没有收到消息，开始参数未被清空，则再发消息
    if(!AppDelegate::start_param.empty()){
        EventCustom event("desai.start.internal");
        event.setUserData((void*)(AppDelegate::start_param.c_str()));
        log("dispatch desai.start.internal again");
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }


    return true;
}


void AppDelegate::startWithUrl(const char* str)
{
    EventCustom event("desai.start.internal");
    start_param=std::string(str);
    event.setUserData((void*)str);
    log("in AppDelegate dispatchEvent desai.start.internal %s",str);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void AppDelegate::onStartWithUrl(EventCustom* event)
{
    EventCustom event1("desai.start");
    event1.setUserData(event->getUserData());
    log("redirect desai.start.internal to desai.start");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event1);
    AppDelegate::start_param.clear();
    log("redirected, clear start_param");
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
