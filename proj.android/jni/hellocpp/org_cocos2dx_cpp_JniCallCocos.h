//  
//  
//  Created by liqing on 2015-Mar-18.  
//  
//  
  
#ifndef __UseJni2__com_game_UseJni2_JniCallCocos__  
#define __UseJni2__com_game_UseJni2_JniCallCocos__  
  
#include "cocos2d.h"  
#include <jni.h>  
  
extern "C"  
{  
    /* 
     * Class:     com_game_UseJni2_JniCallCocos 
     * Method:    HelloCocos 
     * Signature: ()V 
     */  
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_JniCallCocos_GalleryCameraCallback(JNIEnv *, jclass, jint, jstring);  
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_JniCallCocos_StartWithUrlCallback(JNIEnv *, jclass , jstring);  
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_JniCallCocos_ChoosePhoneCallback(JNIEnv *, jclass , jstring, jstring);  
}  
  
#endif /* defined(__UseJni2__com_game_UseJni2_JniCallCocos__) */  
