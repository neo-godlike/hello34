//  
//  
//  Created by liqing on 2015-Mar-18.  
//  
//  
  
#include "org_cocos2dx_cpp_JniCallCocos.h"  
#include "GalleryCamera.h"
#include "AppDelegate.h"
#include "ContractHelper.h"

USING_NS_CC;  
  
void JNICALL Java_org_cocos2dx_cpp_JniCallCocos_GalleryCameraCallback(JNIEnv * env, jclass jj, jint type, jstring jstr)  
{  
    // 这里只是简单的打印一下日志，表示调用成功  
    // 这里用Cocos2d-x的消息中心发送消息给当前场景还是很方便滴  
    
    const char* str;  
    str = env->GetStringUTFChars(jstr,JNI_FALSE);  
    log("In C++ From Java GalleryCameraCallback %d %s ^_^",type,str);
    
    if((type==1)||(type==2)){
        GalleryCamera::dispatchEvent(type ,str);
    }else if (type==3){
        AppDelegate::startWithUrl(str);
    }

    env->ReleaseStringUTFChars(jstr, str);
}  

void JNICALL Java_org_cocos2dx_cpp_JniCallCocos_StartWithUrlCallback(JNIEnv * env, jclass jj , jstring jstr)
{
    const char* str;  
    str = env->GetStringUTFChars(jstr,JNI_FALSE);  
    log("In C++ From Java StartWithUrlCallback %s ^_^",str);
    AppDelegate::startWithUrl(str);
    env->ReleaseStringUTFChars(jstr, str);

}

void JNICALL Java_org_cocos2dx_cpp_JniCallCocos_ChoosePhoneCallback(JNIEnv * env, jclass jj, jstring num, jstring name)
{
    const char* num_str;
    const char* name_str;
    num_str = env->GetStringUTFChars(num,JNI_FALSE);  
    name_str = env->GetStringUTFChars(name,JNI_FALSE);

    log("In C++ From Java ChoosePhoneCallback %s %s ^_^",num_str,name_str);
    ContractHelper::choosePhoneCallback(num_str,name_str);

    env->ReleaseStringUTFChars(num, num_str);
    env->ReleaseStringUTFChars(name, name_str);


}  
