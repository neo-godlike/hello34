//  
//  
//  Created by liqing on 2015-Mar-26.  
//  
//  
#include "cocos2d.h"  
#include "WeChatHelper.h"  
  
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"  
  
USING_NS_CC;  

void WeChatHelper::sendToFriend()
{
    JniMethodInfo minfo;
    
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","sendMsgToFriend", "()V");
    
    if (!isHave) {
        log("jni:sendMsgToFriend is null");
    }else{
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void WeChatHelper::sendToTimeline()
{
    JniMethodInfo minfo;
    
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","sendMsgToTimeLine", "()V");
    
    if (!isHave) {
        log("jni:sendMsgToTimeLine is null");
    }else{
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

#else
void WeChatHelper::sendToFriend()
{
}
void WeChatHelper::sendToTimeline()
{
}
#endif
