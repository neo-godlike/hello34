//  
//  
//  Created by liqing on 2015-Apr-13.  
//  
//  
package com.desai.MiscHelper;

import android.os.Vibrator;
import android.content.Context;
import android.util.Log;  

import org.cocos2dx.lib.Cocos2dxHelper;

public class MiscHelper{
    public static void vibrate(long millisecond){
        Vibrator vibrator = (Vibrator) Cocos2dxHelper.getActivity().getSystemService(Context.VIBRATOR_SERVICE);
        Log.d("vibrate","In Java vibrate "+millisecond);
        vibrator.vibrate(millisecond);
    }
}
