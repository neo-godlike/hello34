//  
//  
//  Created by try on 14-10-3.  
//  
//  
  
#ifndef __UseJni__JniMethod__  
#define __UseJni__JniMethod__  
  
#include <stdio.h>  
  
#if defined(ANDROID)  
  
class JniMethod  
{  
public:  
    static void callAndroidFunc1();  
    static void callAndroidFunc2(float number);  
    static void callAndroidFunc3(std::string name);  
    static void callAndroidFunc4(std::string name, int age);  
    static int  callAndroidFunc5(bool flag);  
    static void callAndroidFunc6(std::vector<int> arr);  
    static std::vector<int> callAndroidFunc7();  


    static void callGotoActivity();
};  
  
#endif  
#endif /* defined(__UseJni__JniMethod__) */  
