#include "HelloWorldScene.h"

#include "audio/include/AudioEngine.h"

#include "JniMethod.h"
#include "AudioRecord.h"
#include "GalleryCamera.h"
#include "ContractHelper.h"
#include "WeChatHelper.h"
#include "MiscHelper.h"



USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocos2d::experimental;
using namespace cocos2d::ui;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
    for (int i = 0; i<(int)searchPaths.size(); i++)
    {
        log("SEARCH PATH: %s",searchPaths[i].c_str());
    }

    std::string manifestUrl = "project.manifest";
    std::string storagePath = FileUtils::getInstance()->getWritablePath() + "HotUpdate/";
    //std::vector<std::string>::iterator iter = searchPaths.begin();
    //searchPaths.insert(iter, storagePath);
    //FileUtils::getInstance()->setSearchPaths(searchPaths);
    _am = AssetsManagerEx::create(manifestUrl, storagePath);
    _am->retain();

    log("*****************************************");
    searchPaths = FileUtils::getInstance()->getSearchPaths();
    for (int i = 0; i<(int)searchPaths.size(); i++)
    {
        log("SEARCH PATH: %s",searchPaths[i].c_str());
    }

    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                            origin.y + closeItem->getContentSize().height/2));

    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    auto item1 = MenuItemFont::create( "Test JNI", CC_CALLBACK_1(HelloWorld::onTestJni, this));
    auto item2 = MenuItemFont::create( "Start record", CC_CALLBACK_1(HelloWorld::onRecordStart, this));
    auto item3 = MenuItemFont::create( "Stop record", CC_CALLBACK_1(HelloWorld::onRecordStop, this));
    auto item4 = MenuItemFont::create( "Play record", CC_CALLBACK_1(HelloWorld::onRecordPlay, this));
    auto item5 = MenuItemFont::create( "Play music", CC_CALLBACK_1(HelloWorld::onMusicPlay, this));
    auto item6 = MenuItemFont::create( "Goto Activity", CC_CALLBACK_1(HelloWorld::onGotoActivity, this));
    auto item7 = MenuItemFont::create( "Image Choose", CC_CALLBACK_1(HelloWorld::onImageChoose, this));
    auto item8 = MenuItemFont::create( "Open Camera", CC_CALLBACK_1(HelloWorld::onOpenCamera, this));
    auto item9 = MenuItemFont::create( "Scan Barcode", CC_CALLBACK_1(HelloWorld::onScanBarcode, this));
    auto item10 = MenuItemFont::create( "Choose Mobbile", CC_CALLBACK_1(HelloWorld::onChoosePhone, this));
    auto item11 = MenuItemFont::create( "WeChat to Friend", CC_CALLBACK_1(HelloWorld::onWeChatToFriend, this));
    auto item12 = MenuItemFont::create( "WeChat to Timeline", CC_CALLBACK_1(HelloWorld::onWeChatToTimeline, this));
    auto item13 = MenuItemFont::create( "Update Res", CC_CALLBACK_1(HelloWorld::onUpdateRes, this));
    auto item14 = MenuItemFont::create( "Vibrate", CC_CALLBACK_1(HelloWorld::onVibrate, this));

    // create menu, it's an autorelease object
    auto menu = Menu::create(item1, item2,item3,item4,item5,item6,item7,item8,item9,item10,item11,item12,item13,item14,closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    menu->alignItemsVertically();
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //label = Label::createWithTTF("Hello World 你好世界", "fonts/Marker Felt.ttf", 24);
    label = LabelTTF::create("Hello World 你好世界", "fonts/Marker Felt.ttf", 30);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto welcome_sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    welcome_sprite->setPosition(Vec2(visibleSize.width/4 + origin.x, visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(welcome_sprite, 0);


    sprite = Sprite::create("speak.png");
    sprite->setPosition(Vec2(visibleSize.width/4*3 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setVisible(false);
    this->addChild(sprite, 0);

    Button* press_speak = Button::create("press_speak_n.png","press_speak_p.png");
    press_speak->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchEvent, this));

    //auto press_speak = Sprite::create("press_speak.png");
    press_speak->setPosition(Vec2(visibleSize.width/4*3 + origin.x, origin.y + press_speak->getContentSize().height));
    this->addChild(press_speak, 0);

    auto dispatcher = Director::getInstance()->getEventDispatcher();  
    //auto listener = EventListenerTouchOneByOne::create();
    //listener->onTouchBegan = [&](Touch* touch, Event* event){
        //log("HelloWorld::onTouchBegan");
    //};
    //listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);  
    //listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved,press_speak);  
    //listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded,this);  
    //listener->setSwallowTouches(true);//不向下传递触摸  
    //dispatcher->addEventListenerWithSceneGraphPriority(listener,press_speak);


    auto customListener1 = EventListenerCustom::create("desai.pic", CC_CALLBACK_1(HelloWorld::onCustomEvent, this));
    auto customListener2 = EventListenerCustom::create("desai.qrcode", CC_CALLBACK_1(HelloWorld::onCustomEvent, this));
    auto customListener3 = EventListenerCustom::create("desai.start", CC_CALLBACK_1(HelloWorld::onCustomEvent, this));
    auto customListener4 = EventListenerCustom::create("desai.phone", CC_CALLBACK_1(HelloWorld::onCustomEvent, this));
     
    //添加自定义事件监听器，优先权为1
    dispatcher->addEventListenerWithFixedPriority(customListener1, 1);
    dispatcher->addEventListenerWithFixedPriority(customListener2, 1);
    dispatcher->addEventListenerWithFixedPriority(customListener3, 1);
    dispatcher->addEventListenerWithFixedPriority(customListener4, 1);
    
    CCASSERT(AudioEngine::lazyInit(),"Fail to initialize AudioEngine!");
    log("AudioEngine::lazyInit");



    EventListenerAssetsManagerEx* _amListener = EventListenerAssetsManagerEx::create(_am, [this](EventAssetsManagerEx* event){
            log("Assets Manager Event %d %s",(int)(event->getEventCode()),event->getMessage().c_str());
            switch(event->getEventCode())
            {
                case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
                {
                    log("ERROR_NO_LOCAL_MANIFEST");
                    break;
                }
                case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
                {
                    log("ERROR_DOWNLOAD_MANIFEST");
                    break;
                }
                case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
                {
                    log("ERROR_PARSE_MANIFEST");
                    break;
                }
                case EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:
                {
                    log("NEW_VERSION_FOUND %s",this->_am->getRemoteManifest()->getVersion().c_str());
                    break;
                }
                case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
                {
                    log("ALREADY_UP_TO_DATE");
                    break;
                }
                case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
                {
                    std::string assetId = event->getAssetId();
                    float percent = event->getPercent();
                    log("UPDATE_PROGRESSION %s %f",assetId.c_str(),percent);
                    break;
                }
                case EventAssetsManagerEx::EventCode::ASSET_UPDATED:
                {
                    log("ASSET_UPDATED %s", event->getAssetId().c_str());
                    break;
                }
                case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
                {
                    log("ERROR_UPDATING %s", event->getAssetId().c_str());
                    break;
                }
                case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
                {
                    log("UPDATE_FINISHED");
                    auto searchPaths = FileUtils::getInstance()->getSearchPaths();
                    for (int i = 0; i<(int)searchPaths.size(); i++)
                    {
                        log("SEARCH PATH: %s",searchPaths[i].c_str());
                    }
                    break;
                }
                case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
                {
                    log("UPDATE_FAILED");
                    break;
                }
                case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
                {
                    log("ERROR_DECOMPRESS");
                    break;
                }
                default:
                    log("err assets manager evnet");
                    break;
            }
    });
    dispatcher->addEventListenerWithFixedPriority(_amListener, 1);


    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased =[&](EventKeyboard::KeyCode keyCode, Event* event)
    {
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            log("***********************BACK CLICKED*******************");
            setLabel("Back Clicked!!");

        } 
        else if (keyCode == EventKeyboard::KeyCode::KEY_MENU)     
        {              
            log("***********************MENU CLICKED*******************");
            setLabel("Menu Clicked!!");
            
        } 
    };
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

void HelloWorld::onCustomEvent(EventCustom* event)
{
    // 获取消息传递的数据
    char* data = (char*)event->getUserData();
    log("onCustomEvent %s data = %s",event->getEventName().c_str(), data);
    label->setString(data);
}


void HelloWorld::setLabel(std::string str){
    label->setString(str);
}

void HelloWorld::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    static std::string filename = FileUtils::getInstance()->getWritablePath() + "test.arm";
    int audioId;

    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            AudioRecord::callRecordStart(filename);
            label->setString("Please Speak!!请说话");
            sprite->setVisible(true);
            break;
            
        case Widget::TouchEventType::MOVED:
            break;
            
        case Widget::TouchEventType::ENDED:
            label->setString("Speak End!!已录制");
            sprite->setVisible(false);
            AudioRecord::callRecordStop();
            audioId = AudioEngine::play2d(filename);
            AudioEngine::setFinishCallback(audioId, [&](int id, const std::string& filePath){
                label->setString("Play End!!播放完毕");
            });

            break;
            
        case Widget::TouchEventType::CANCELED:
            label->setString("Speak Canceled!!已取消");
            sprite->setVisible(false);
            AudioRecord::callRecordStop();
            break;
            
        default:
            break;
    }

}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event){
    log("HelloWorld::onTouchBegan");
    std::string filename = FileUtils::getInstance()->getWritablePath() + "test.arm";
    AudioRecord::callRecordStart(filename);
    label->setString("Please Speak!!说话");
    sprite->setVisible(true);
}
//void HelloWorld::onTouchMoved(Touch* touch, Event* event){
    //log("HelloWorld::onTouchMoved");
//}
void HelloWorld::onTouchEnded(Touch* touch, Event* event){
    log("HelloWorld::onTouchEnded");
    label->setString("Speak End!!");
    sprite->setVisible(false);
    AudioRecord::callRecordStop();
    std::string filename = FileUtils::getInstance()->getWritablePath() + "test.arm";
    int audioId = AudioEngine::play2d(filename);
    AudioEngine::setFinishCallback(audioId, [&](int id, const std::string& filePath){
        label->setString("Play End!!");
    });
}

void HelloWorld::onTestJni(Ref* pSender){
    //jnitest
    #if defined(ANDROID)  
      
    JniMethod::callAndroidFunc1();  
    JniMethod::callAndroidFunc2(3.14f);  
    JniMethod::callAndroidFunc3("hello");  
    JniMethod::callAndroidFunc4("hello", 3);  
          
    int ret = JniMethod::callAndroidFunc5(true);  
    log("callAndroidFunc5: %d", ret);  
      
    std::vector<int> arr6;  
    arr6.push_back(1);  
    arr6.push_back(20);  
    arr6.push_back(300);  
    JniMethod::callAndroidFunc6(arr6);  
      
    std::vector<int> arr7 = JniMethod::callAndroidFunc7();  
    for (int i : arr7)  
    {  
        log("callAndroidFunc7: %i", i);  
    }  
      
    #endif  
}
void HelloWorld::onRecordStart(Ref* pSender){
    std::string filename = FileUtils::getInstance()->getWritablePath() + "test.arm";
    AudioRecord::callRecordStart(filename);
    log("record start %s",filename.c_str());
}
void HelloWorld::onRecordStop(Ref* pSender){
    AudioRecord::callRecordStop();
    log("record end");
}
void HelloWorld::onRecordPlay(Ref* pSender){
    std::string filename = FileUtils::getInstance()->getWritablePath() + "test.arm";
    int ret = AudioEngine::play2d(filename);
    log("record play %s %d",filename.c_str(),ret);
}
void HelloWorld::onMusicPlay(Ref* pSender){
    int ret = AudioEngine::play2d("/backgroun.mp3");
    log("music play %d",ret);
}
void HelloWorld::onGotoActivity(Ref* pSender){
    JniMethod::callGotoActivity();
    log("JniMethod::callGotoActivity");
}
void HelloWorld::onChoosePhone(Ref* pSender){
    ContractHelper::callChoosePhone();
    log("ContractHelper::callChoosePhone");
}
void HelloWorld::onImageChoose(Ref* pSender){
    GalleryCamera::callOpenImageChoose();
    log("GalleryCamera::callOpenImageChoose");
}
void HelloWorld::onOpenCamera(Ref* pSender){
    GalleryCamera::callOpenCamera();
    log("GalleryCamera::callOpenCamera");
}
void HelloWorld::onScanBarcode(Ref* pSender){
    GalleryCamera::callScanBarcode();
    log("GalleryCamera::callScanbarcode");
}
void HelloWorld::onWeChatToFriend(Ref* pSender){
    WeChatHelper::sendToFriend("老虎队");
    log("WeChatHelper::sendToFriend");
}
void HelloWorld::onWeChatToTimeline(Ref* pSender){
    WeChatHelper::sendToTimeline("老虎队");
    log("WeChatHelper::sendToTimeline");
}
void HelloWorld::onUpdateRes(Ref* pSender){
    if(!_am->getLocalManifest()->isLoaded())
    {
        log("get local manifest error.");
    }
    else
    {
        log("get local manifest ok ver:%s", _am->getLocalManifest()->getVersion().c_str());
        _am->update();
    }
}
void HelloWorld::onVibrate(Ref* pSender){
    MiscHelper::vibrate(1000);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
