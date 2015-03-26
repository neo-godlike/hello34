//  
//  
//  Created by try on 14-10-3.  
//  
//  
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include "cocos2d.h"  
#include "JniMethod.h"  
  
#if defined(ANDROID)  
#include "platform/android/jni/JniHelper.h"  
  
USING_NS_CC;  
  
  
// 调用android静态方法：没有参数  
void JniMethod::callAndroidFunc1()  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/JniMethod/JniMethod", "AndroidFunc1", "()V");  
      
    CCASSERT(isHave, "jni callAndroidFunc1 not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);  
    }  
      
}  
  
// 调用android静态方法：一个float参数  
void JniMethod::callAndroidFunc2(float number)  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/JniMethod/JniMethod", "AndroidFunc2", "(F)V");  
      
    CCASSERT(isHave, "jni callAndroidFunc1 not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, number);  
    }  
}  
  
// 调用android静态方法：一个string参数  
void JniMethod::callAndroidFunc3(std::string name)  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/JniMethod/JniMethod", "AndroidFunc3", "(Ljava/lang/String;)V");  
  
    CCASSERT(isHave, "jni callAndroidFunc3 not found");  
      
    if (isHave)  
    {  
        jstring jStr = minfo.env->NewStringUTF(name.c_str());  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jStr);  
    }  
}  
  
// 调用android静态方法：多个参数  
void JniMethod::callAndroidFunc4(std::string name, int age)  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/JniMethod/JniMethod", "AndroidFunc4", "(Ljava/lang/String;I)V");  
      
    CCASSERT(isHave, "jni callAndroidFunc4 not found");  
      
    if (isHave)  
    {  
        jstring jName = minfo.env->NewStringUTF(name.c_str());  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jName, age);  
    }  
}  
  
//  
int  JniMethod::callAndroidFunc5(bool flag)  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/JniMethod/JniMethod", "AndroidFunc5", "(Z)I");  
      
    CCASSERT(isHave, "jni callAndroidFunc5 not found");  
      
    if (isHave)  
    {  
        jint num = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, flag);  
        return num;  
    }  
    return -1;  
}  
  
//  
void JniMethod::callAndroidFunc6(std::vector<int> arr)  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/JniMethod/JniMethod", "AndroidFunc6", "([I)V");  
      
    CCASSERT(isHave, "jni callAndroidFunc6 not found");  
      
    if (isHave)  
    {  
        jintArray jarr = minfo.env->NewIntArray(arr.size());  
        jint *intArr = minfo.env->GetIntArrayElements(jarr, NULL);  
        for (int i = 0; i < arr.size(); ++i)  
        {  
            // http://www.2cto.com/kf/201312/268735.html  
            intArr[i] = arr[i];  
        }  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jarr);  
    }  
}  
  
//  
std::vector<int> JniMethod::callAndroidFunc7()  
{  
    std::vector<int> arr;  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/desai/JniMethod/JniMethod", "AndroidFunc7", "()[I");  
      
    CCASSERT(isHave, "jni callAndroidFunc7 not found");  
      
    if (isHave)  
    {  
        jintArray jarr = (jintArray)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  
        jsize len = minfo.env->GetArrayLength(jarr);  
        jint *intArr = minfo.env->GetIntArrayElements(jarr, NULL);  
        for (int i = 0; i < len; ++i)  
        {  
            arr.push_back(intArr[i]);  
        }  
    }  
  
    return arr;  
}  
 void JniMethod::callGotoActivity()  
{  
    JniMethodInfo minfo;  
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "gotoActivity", "()Ljava/lang/Object;");  
      
    CCASSERT(isHave, "jni callAndroidFunc1 not found");  
      
    if (isHave)  
    {  
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);  
    }  
      
}  

#endif  
