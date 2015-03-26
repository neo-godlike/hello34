package com.hello34.wxapi;

import org.cocos2dx.cpp.AppActivity;

import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.modelbase.BaseReq;

import android.app.Activity;
import android.widget.Toast;
import android.os.Bundle;
import android.content.Intent;


public class WXEntryActivity extends Activity implements IWXAPIEventHandler{


    @Override  
    public void onCreate(Bundle savedInstanceState) {  
        super.onCreate(savedInstanceState);  

        initData();  
    }  
  
    @Override  
    protected void onNewIntent(Intent intent) {  
        super.onNewIntent(intent);  

        setIntent(intent);  
        initData();  
    }  
  
    private void initData() {  
        AppActivity.api.handleIntent(getIntent(), this);  
    }  

    @Override  
    public void onReq(BaseReq req) {  
    }  

    @Override  
    public void onResp(BaseResp resp) {  
        String result = "";  
          
        switch (resp.errCode) {  
        case BaseResp.ErrCode.ERR_OK:  
            result = "WeChat OK";  
            break;  
        case BaseResp.ErrCode.ERR_USER_CANCEL:  
            result = "WeChat Cancel";  
            break;  
        case BaseResp.ErrCode.ERR_AUTH_DENIED:  
            result = "WeChat Auth Denied";  
            break;  
        default:  
            result = "WeChat Unknown";  
            break;  
        }  
          
        Toast.makeText(this, result, Toast.LENGTH_LONG).show();  

        Intent in = new Intent(this, AppActivity.class);
        this.startActivity(in);
    }
}
