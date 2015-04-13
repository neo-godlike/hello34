#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Layer
{
private:
    cocos2d::LabelTTF* label;
    cocos2d::Sprite* sprite;
    cocos2d::extension::AssetsManagerEx* _am;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void setLabel(std::string str);

    void onCustomEvent(cocos2d::EventCustom* event);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onTestJni(cocos2d::Ref* pSender);
    void onRecordStart(cocos2d::Ref* pSender);
    void onRecordStop(cocos2d::Ref* pSender);
    void onRecordPlay(cocos2d::Ref* pSender);
    void onMusicPlay(cocos2d::Ref* pSender);
    void onGotoActivity(cocos2d::Ref* pSender);
    void onChoosePhone(cocos2d::Ref* pSender);
    void onImageChoose(cocos2d::Ref* pSender);
    void onOpenCamera(cocos2d::Ref* pSender);
    void onScanBarcode(cocos2d::Ref* pSender);
    void onWeChatToFriend(cocos2d::Ref* pSender);
    void onWeChatToTimeline(cocos2d::Ref* pSender);
    void onUpdateRes(cocos2d::Ref* pSender);

    void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    //void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
