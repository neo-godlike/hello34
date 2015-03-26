//  
//  
//  Created by liqing on 2015-Mar-18.  
//  
//  
#include "cocos2d.h"  
#include "AudioRecord.h"  
  
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"  
  
USING_NS_CC;  

 
void AudioRecord::callRecordStart(std::string filename)  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/AudioRecord/AudioRecord", "start", "(Ljava/lang/String;)V");  
      
    CCASSERT(isHave, "jni com/desai/AudioRecord/AudioRecord start not found");  
      
    if (isHave)  
    {  
        jstring jStr = minfo.env->NewStringUTF(filename.c_str());  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jStr);  
    }  
      
}  

 
void AudioRecord::callRecordStop()  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/AudioRecord/AudioRecord", "stop", "()V");  
      
    CCASSERT(isHave, "jni com/desai/AudioRecord/AudioRecord stop not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);  
    }  
      
}  


#else
void AudioRecord::callRecordStart(std::string filename){
}
void AudioRecord::callRecordStop(){
}
#endif
