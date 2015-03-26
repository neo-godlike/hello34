package org.cocos2dx.cpp;

import java.io.ByteArrayOutputStream;
import java.io.File;


import com.hello34.R;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class UserInfoActivity extends Activity {
	private ImageButton user_nan, user_nv;
	private TextView ut_nan, ut_nv,tv_usernumber,tv_jinbi,tv_jindou,tv_zhanji,tv_shenglv;
	private LinearLayout lf;
	private ImageView user_headImage;
	private ImageButton save_bc;
	private static final int REQUEST_CODE_GETIMAGE_BYSDCARD = 0;// 从sd卡得到图像的请求码
	private static final int REQUEST_CODE_GETIMAGE_BYCAMERA = 1;// 从相机得到图像的请求码
	private String thisLarge = null, theSmall = null;
	private byte[] picture2;
	//用户信息
	private EditText editText1;
	private String nowsex="男";
//	private PlayerLoginInfo playerinfo=null;
	
//	PublicUserInfo pui =new PublicUserInfo();
	Thread td_into;
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		// 窗体状态设置-设置为无标题栏状态【全屏】
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		// 强制横屏
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		setContentView(R.layout.userinfo);
//		user_nan = (ImageButton) findViewById(R.id.user_nan);
//		user_nv = (ImageButton) findViewById(R.id.user_nv);
//		ut_nan = (TextView) findViewById(R.id.ut_nan);
//		ut_nv = (TextView) findViewById(R.id.ut_nv);
		user_headImage = (ImageView) findViewById(R.id.user_headimage);
		LinearLayout lf = (LinearLayout) findViewById(R.id.user_headbd);
//		save_bc = (ImageButton) findViewById(R.id.save_bc);
//		editText1 =(EditText) findViewById(R.id.editText1);
		tv_usernumber = (TextView) findViewById(R.id.tv_usernumber);
//		tv_jinbi = (TextView) findViewById(R.id.tv_jinbi);
//		tv_jindou = (TextView) findViewById(R.id.tv_jindou);
//		tv_zhanji = (TextView) findViewById(R.id.tv_zhanji);
//		tv_shenglv = (TextView) findViewById(R.id.tv_shenglv);
		
		
//		playerinfo=GlobalInfo.getPlayerInfo();
//		
//		if(playerinfo!=null)
//		{
//			setbeasUserInfo();
//		}
//		
//		save_bc.setOnClickListener(new OnClickListener() {
//			
//			@Override
//			public void onClick(View v) {
//				// TODO Auto-generated method stub
//				//保存数据，像服务器提交数据
//				saveok();
//				td_into = new Thread() {
//					public void run() {
//						pui.setSET_USERNAME(editText1.getText().toString());
//						pui.setSET_USERSEX(nowsex);
//						if(picture2!=null)
//						{
//						   String faceImg = Base64.encode(picture2);
//						   pui.setSET_SERTIMG(faceImg);
//						}
//						else
//						{
//							pui.setSET_SERTIMG("no");
//						}
//						pui.SaveUserInfo.run();
//						
//						if(pui.getReturnlastok().equals("ok")==true)
//						{
//							finish();
//							
//							
//						}
//						else
//						{
//							
//						}
//						saveno();
//					};
//
//				};
//				td_into.start();
//			}
//		});
//		
		

		
		lf.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				CharSequence[] items = { "手机相册", "手机拍照", "取消" };
				imageChooseItem(items);
			}
		});
	}


//	public void setbeasUserInfo()
//	{
//		editText1.setText(playerinfo.getUserName()+"");
//		tv_usernumber.setText("ID:"+playerinfo.getUsernumber()+"");
//		tv_jinbi.setText(""+playerinfo.getUserJF());
//		tv_jindou.setText(""+playerinfo.getUserGlod());
//		tv_zhanji.setText("战绩:"+playerinfo.getWincount()+"胜/"+playerinfo.getFailcount()+"负");
//		int winc=Integer.valueOf(playerinfo.getWincount());
//		int failc=Integer.valueOf(playerinfo.getFailcount());
//		float i= (winc+failc);
//		float b= (winc/i)*100 ;
//		int lastcount = (int)b;;
//		tv_shenglv.setText("胜率:"+lastcount+"%");
//		setUserHeadImage(ServiceApi.mainServices + GlobalInfo.getPlayerInfo().getUserheadimg());
//	}
//	
//	private void setUserHeadImage(String faceUrl) {
//		LocalCache.getInstance(CacheValue.GameDataPack).useDownloadResource(
//				faceUrl, new Action<CacheResult>() {
//					@Override
//					public void execute(CacheResult cacheResult) {
//						if (cacheResult.isCached()) {
//							String path = cacheResult.getCachedPath();
//							final Bitmap bm = BitmapCache.Instance
//									.getFileImageOrCache(path);
//							runOnUiThread(new Runnable() {
//								@Override
//								public void run() {
//									BitmapDrawable drwawable = new BitmapDrawable(
//											bm);
//									user_headImage.setBackgroundDrawable(drwawable);
//								}
//							});
//						}
//					}
//				});
//	}
//	
	/**
	 * 操作选择
	 * 
	 * @param items
	 */
	public void imageChooseItem(CharSequence[] items) {
		AlertDialog imageDialog = new AlertDialog.Builder(this)
				.setTitle("增加图片")
				.setItems(items, new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int item) {
						if (item == 0) {
							// 手机选图
							Intent intent = new Intent(
									Intent.ACTION_GET_CONTENT);
							intent.setType("image/*");
							startActivityForResult(intent,
									REQUEST_CODE_GETIMAGE_BYSDCARD);
						}
						// 拍照
						else if (item == 1) {
							Intent intentC = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
							intentC.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(new File(
									Environment.getExternalStorageDirectory(), "temp.jpg")));
							startActivityForResult(intentC, REQUEST_CODE_GETIMAGE_BYCAMERA);
						}
					}
				}).create();

		imageDialog.show();
	}

	// 获取图片
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == REQUEST_CODE_GETIMAGE_BYSDCARD) {
			Bitmap bitm = null;
			if (data != null) {
				Uri selectedImage = data.getData();
				// String[] filePathColumn = { MediaStore.Images.Media.DATA };
				//
				// Cursor cursor = getContentResolver().query(selectedImage,
				// filePathColumn, null, null, null);
				// cursor.moveToFirst();
				//
				// int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
				// String picturePath = cursor.getString(columnIndex);
				// cursor.close();
				// bitm = BitmapFactory.decodeFile(picturePath);
				if (selectedImage != null) {

					final Intent intent1 = new Intent(
							"com.android.camera.action.CROP");
					intent1.setDataAndType(selectedImage, "image/*");
					intent1.putExtra("crop", "true");
					intent1.putExtra("aspectX", 1);
					intent1.putExtra("aspectY", 1);
					intent1.putExtra("outputX", 235);
					intent1.putExtra("outputY", 235);
					intent1.putExtra("return-data", true);
					startActivityForResult(intent1, 4);
				}
			}
			 if(bitm!=null){
			 user_headImage
			 .setImageDrawable(new BitmapDrawable(this.getResources(),bitm));
			 }
		}
		// 拍摄图片
		else if (requestCode == REQUEST_CODE_GETIMAGE_BYCAMERA) {
			if (resultCode != RESULT_OK) {
				
				return;
			}
			
			// 设置文件保存路径这里放在跟目录下
			File picture = new File(Environment.getExternalStorageDirectory()
					+ "/temp.jpg");
			startPhotoZoom(Uri.fromFile(picture));
			
		} else if (requestCode == 4) {
			
			if (data != null){
				Bitmap bmp = data.getParcelableExtra("data");
				ByteArrayOutputStream stream = new ByteArrayOutputStream();
				bmp.compress(Bitmap.CompressFormat.JPEG, 75, stream);//
				picture2 = stream.toByteArray();
				user_headImage.setImageDrawable(new BitmapDrawable(this
						.getResources(), bmp));
			}
				
		}
		
        else if (requestCode == 5) {
			
        	Bundle extras = data.getExtras();
			if (extras != null) {
        	    Bitmap bmp = data.getParcelableExtra("data");
				ByteArrayOutputStream stream = new ByteArrayOutputStream();
				bmp.compress(Bitmap.CompressFormat.JPEG, 75, stream);//
				picture2 = stream.toByteArray();
				user_headImage.setImageBitmap(bmp);
			}
				
		}
	}
	public static final String IMAGE_UNSPECIFIED = "image/*";
	public void startPhotoZoom(Uri uri) {
		System.out.println(uri);
		Intent intent = new Intent("com.android.camera.action.CROP");
		intent.setDataAndType(uri, IMAGE_UNSPECIFIED);
		intent.putExtra("crop", "true");
		// aspectX aspectY 是宽高的比例
		intent.putExtra("aspectX", 1);
		intent.putExtra("aspectY", 1);
		// outputX outputY 是裁剪图片宽高
		intent.putExtra("outputX", 235);
		intent.putExtra("outputY", 235);
		intent.putExtra("return-data", true);
		startActivityForResult(intent, 5);
	}

	
	public void saveok() {
		this.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				
			}
		});
	}
	
	public void saveno() {
		this.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				
			}
		});
	}
}
