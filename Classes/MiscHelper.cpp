//  
//  
//  Created by liqing on 2015-Apr-13.  
//  
//  
#include "cocos2d.h"  
#include "MiscHelper.h"  
  
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"  
  
USING_NS_CC;  

 
void MiscHelper::vibrate(long long millisecond)
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/MiscHelper/MiscHelper", "vibrate", "(J)V");  
      
    CCASSERT(isHave, "jni com/desai/MiscHelper/MiscHelper vibrate not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, millisecond);  
    }  
      
}  

#else
void MiscHelper::vibrate(long millisecond){
}
#endif
