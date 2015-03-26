/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import android.content.Intent;
import android.content.DialogInterface;
import android.app.AlertDialog;
import android.provider.MediaStore;
import android.os.Environment;
import android.net.Uri;
import android.app.Activity;
import android.util.Log;  
import android.database.Cursor;
import java.io.File;
import android.os.Bundle;
import android.provider.ContactsContract;

import com.desai.QrcodeScan.MainActivity;
import com.desai.QrcodeScan.MipcaActivityCapture;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.widget.Toast;

import com.hello34.R;
import com.tencent.mm.sdk.modelmsg.SendMessageToWX;
import com.tencent.mm.sdk.modelmsg.WXMediaMessage;
import com.tencent.mm.sdk.modelmsg.WXWebpageObject;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

public class AppActivity extends Cocos2dxActivity {
    private static final String APP_ID = "wxee0d07163b63052a";//AppID
    private static IWXAPI api;//微信API接口
    private static AppActivity instance;//类静态实例，为了方便后面静态函数的调用


	private static final int REQUEST_CODE_GETIMAGE_BYSDCARD = 0;// 从sd卡得到图像的请求码
	private static final int REQUEST_CODE_GETIMAGE_BYCAMERA = 1;// 从相机得到图像的请求码
	private static final int REQUEST_CODE_SCAN_BARCODE = 2;//
	private static final int REQUEST_CODE_GET_MOBILE = 3;//


    @Override  
    public void onCreate(Bundle savedInstanceState) {  
        super.onCreate(savedInstanceState);  
        Intent in = getIntent();
        String s1 = in.toURI();
        String s2 = in.getDataString();  
  
        Log.d("URI: ", s1);  
        if(s2!=null) {
            Log.d("URL: ", s2);  
            JniCallCocos.StartWithUrlCallback(s2);
        }

        instance = this;
        regToWX();
    }  

    private void regToWX(){
        api = WXAPIFactory.createWXAPI(this, APP_ID, true);
        api.registerApp(APP_ID);
    }

    public static void sendMsgToFriend(){
        if(api.openWXApp())
        {
            WXWebpageObject webpage = new WXWebpageObject();
            webpage.webpageUrl = "http://www.desai.com";
            WXMediaMessage msg = new WXMediaMessage(webpage);
            msg.title = "壹德州";
            msg.description = "我邀请您加入XXX俱乐部";
      
            Bitmap thumb = BitmapFactory.decodeResource(instance.getResources(), R.drawable.icon);
            msg.thumbData = Util.bmpToByteArray(thumb, true);
      
            SendMessageToWX.Req req = new SendMessageToWX.Req();
            req.transaction = buildTransaction("webpage");
            req.message = msg;
            req.scene = SendMessageToWX.Req.WXSceneSession;
            api.sendReq(req);
        }
        else
        {
             Toast.makeText(instance, "未安装微信", Toast.LENGTH_SHORT).show();
        }
    }

    public static void sendMsgToTimeLine(){
        if(api.openWXApp())
        {
            if(api.getWXAppSupportAPI() >= 0x21020001)
            {               
                WXWebpageObject webpage = new WXWebpageObject();
                webpage.webpageUrl = "http://www.desai.com";
                WXMediaMessage msg = new WXMediaMessage(webpage);
                msg.title = "壹德州";
                msg.description = "我邀请您加入XXX俱乐部";
      
                Bitmap thumb = BitmapFactory.decodeResource(instance.getResources(), R.drawable.icon);
                msg.thumbData = Util.bmpToByteArray(thumb, true);
      
                SendMessageToWX.Req req = new SendMessageToWX.Req();
                req.transaction = buildTransaction("webpage");
                req.message = msg;
                req.scene = SendMessageToWX.Req.WXSceneTimeline;
                api.sendReq(req);
            }
            else{
                Toast.makeText(instance, "微信版本过低", Toast.LENGTH_SHORT).show();
            }
        }
        else
        {
             Toast.makeText(instance, "未安装微信", Toast.LENGTH_SHORT).show();
        }
    }

    private static String buildTransaction(final String type) {
        return (type == null) ? String.valueOf(System.currentTimeMillis()) : type + System.currentTimeMillis();
    }

    //@Override
    //public void onStart(){
        //super.onStart();
        //Log.d("AppActivity","onStart");
    //}

    //@Override
    //public void onResume(){
        //super.onResume();
        //Log.d("AppActivity","onResume");
    //}

    //@Override 
    //public void onWindowFocusChanged(boolean hasFocus) { 
        //super.onWindowFocusChanged(hasFocus); 
        //Log.d("AppActivity","onWindowFocusChanged");
    //}


    public static Object gotoActivity()
    {
        Intent in = new Intent(AppActivity.getContext(),
                //UserInfoActivity.class);
                MainActivity.class);
        AppActivity.getContext().startActivity(in);
        
        return null;
    }

    public static void openChoosePhone(){
        //Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        //intent.setType("vnd.android.cursor.item/phone");
        //Intent intent = new Intent(Intent.ACTION_PICK, ContactsContract.Contacts.CONTENT_URI);  
        Intent intent = new Intent(Intent.ACTION_PICK, ContactsContract.CommonDataKinds.Phone.CONTENT_URI);  
        ((Activity)(AppActivity.getContext())).startActivityForResult(intent,REQUEST_CODE_GET_MOBILE);
    }


    public static void openImageChoose(){
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("image/*");
        ((Activity)(AppActivity.getContext())).startActivityForResult(intent,REQUEST_CODE_GETIMAGE_BYSDCARD);
    }


    public static void openCamera(){
        Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        intent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(new File(Environment.getExternalStorageDirectory(), "temp.jpg")));
        ((Activity)(AppActivity.getContext())).startActivityForResult(intent, REQUEST_CODE_GETIMAGE_BYCAMERA);
    }

    public static void scanBarcode(){
        Intent intent = new Intent();
        intent.setClass(AppActivity.getContext(), MipcaActivityCapture.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        ((Activity)(AppActivity.getContext())).startActivityForResult(intent, REQUEST_CODE_SCAN_BARCODE);
    }

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == REQUEST_CODE_GETIMAGE_BYSDCARD && resultCode == RESULT_OK && data!=null){
            Uri uri = data.getData();
            Cursor cursor = getContentResolver().query(uri, null, null, null, null);
            cursor.moveToFirst();
            String imgNo = cursor.getString(0); //图片编号
            String imgPath = cursor.getString(1); //图片文件路径
            String imgSize = cursor.getString(2); //图片大小
            String imgName = cursor.getString(3); //图片文件名
            Log.d("choosepic","path:"+imgPath);
            JniCallCocos.GalleryCameraCallback(1,imgPath);
        }else if(requestCode == REQUEST_CODE_GETIMAGE_BYCAMERA && resultCode == RESULT_OK){
            sendBroadcast(new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE,Uri.parse("file://"+Environment.getExternalStorageDirectory()+"/temp.jpg")));
            JniCallCocos.GalleryCameraCallback(1,Environment.getExternalStorageDirectory()+"/temp.jpg");
        }else if(requestCode == REQUEST_CODE_SCAN_BARCODE && resultCode == RESULT_OK && data!=null){
            Bundle bundle = data.getExtras();
            JniCallCocos.GalleryCameraCallback(2,bundle.getString("result"));
        }else if(requestCode == REQUEST_CODE_GET_MOBILE && resultCode ==RESULT_OK && data!=null){
            Uri uri = data.getData();
            Cursor cursor = getContentResolver().query(uri, null, null, null, null);
            cursor.moveToFirst();
            String num = cursor.getString(cursor.getColumnIndexOrThrow(ContactsContract.CommonDataKinds.Phone.NUMBER));
            Log.d("choose-mobile","return: "+num);
            // 获取外键id  
            String contact_id = cursor  
                    .getString(cursor  
                            .getColumnIndexOrThrow(ContactsContract.CommonDataKinds.Phone.CONTACT_ID));
            // 根据外键id获取姓名  
            Cursor namecursor = getContentResolver().query(  
                    ContactsContract.Contacts.CONTENT_URI, null,  
                    ContactsContract.Contacts._ID + "=" + contact_id, null,  
                    null);  
            namecursor.moveToNext();  
            String name = namecursor  
                    .getString(namecursor  
                            .getColumnIndexOrThrow(ContactsContract.Contacts.DISPLAY_NAME));  
            Log.d("choose-mobile","return: "+ name);
            JniCallCocos.ChoosePhoneCallback(num,name);
        }
    }
}
