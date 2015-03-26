package com.desai.JniMethod;  
import android.util.Log;  
public class JniMethod   
{  
    // 不带参数  
    public static void AndroidFunc1()  
    {  
        Log.d("jni", "AndroidFunc1 called");  
    }  
    // 带一个float参数  
    public static void AndroidFunc2(float number)  
    {  
        Log.d("jni", "AndroidFunc2 called: " + number);  
    }  
    // 带一个String参数  
    public static void AndroidFunc3(String name)  
    {  
        Log.d("jni", "AndroidFunc3 called: " + name);  
    }  
    // 带两个参数  
    public static void AndroidFunc4(String name, int age)  
    {  
        Log.d("jni", "AndroidFunc4 called: " + age);  
    }  
    // 带一个boolean参数，并返回一个int  
    public static int AndroidFunc5(boolean flag)  
    {  
        Log.d("jni", "AndroidFunc5 called");  
        return flag ? 10 : 100;  
    }  
    // 带一个int 数组参数  
    public static void AndroidFunc6(int arr[])  
    {  
        int sum = 0;  
        for (int i : arr)   
        {  
            sum += i;  
        }  
        Log.d("jni", "AndroidFunc6 called: " + sum);  
    }  
    // 返回一个int 数组  
    public static int[] AndroidFunc7()  
    {  
        int arr[] = {10, 20, 30, 40};  
        return arr;  
    }  
}  
