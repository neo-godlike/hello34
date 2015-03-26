//  
//  
//  Created by liqing on 2015-Mar-18.  
//  
//  
#include "cocos2d.h"  
#include "GalleryCamera.h"  

USING_NS_CC;  

void GalleryCamera::dispatchEvent(int type,const char* str)
{
    std::string name;
    switch(type){
        case 1: name = "desai.pic"; break;
        case 2: name = "desai.qrcode"; break;
        default: return;
    }
    EventCustom event(name);
    event.setUserData((void*)str);
    log("dispatchEvent %s %s",name.c_str(),str);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

  
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"  
  

void GalleryCamera::callOpenImageChoose()  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "openImageChoose", "()V");  
      
    CCASSERT(isHave, "jni org/cocos2dx/cpp/AppActivitycall openImageChoose not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);  
    }  
      
}  
void GalleryCamera::callOpenCamera()  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "openCamera", "()V");  
      
    CCASSERT(isHave, "jni org/cocos2dx/cpp/AppActivitycall openCamera not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);  
    }  
      
}  
void GalleryCamera::callScanBarcode()  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "scanBarcode", "()V");  
      
    CCASSERT(isHave, "jni org/cocos2dx/cpp/AppActivitycall scanBarcode not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);  
    }  
      
}  
#else

void GalleryCamera::callOpenImageChoose(){
} 
void GalleryCamera::callOpenCamera(){
}
void GalleryCamera::callScanBarcode(){
}
#endif
