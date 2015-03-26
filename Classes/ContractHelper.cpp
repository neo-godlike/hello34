//  
//  
//  Created by liqing on 2015-Mar-18.  
//  
//  
#include "cocos2d.h"  
#include "ContractHelper.h"  

USING_NS_CC;  

void ContractHelper::choosePhoneCallback(const char* num,const char* name)
{
    std::string str = std::string(name)+" "+std::string(num);
    EventCustom event("desai.phone");
    event.setUserData((void*)str.c_str());
    log("dispatchEvent desai.phone %s",str.c_str());
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"  
  
void ContractHelper::callChoosePhone()  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "openChoosePhone", "()V");  
      
    CCASSERT(isHave, "jni org/cocos2dx/cpp/AppActivity openChoosePhone not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);  
    }  
      
}  


#else

void ContractHelper::callChoosePhone()
{
}

#endif
