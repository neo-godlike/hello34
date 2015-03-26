package com.desai.AudioRecord;

import android.media.MediaRecorder;
import java.io.IOException;
import android.util.Log;  
//import android.os.Environment;

public class AudioRecord{
    private static MediaRecorder recorder = null;
    public static void start(String filename){
        recorder = new MediaRecorder();// new出MediaRecorder对象  
        recorder.setAudioSource(MediaRecorder.AudioSource.MIC);  
        // 设置MediaRecorder的音频源为麦克风  
        recorder.setOutputFormat(MediaRecorder.OutputFormat.RAW_AMR);  
        // 设置MediaRecorder录制的音频格式  
        recorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);  
        // 设置MediaRecorder录制音频的编码为amr.  
        //String fileBasePath = Environment.getExternalStorageDirectory().getAbsolutePath();
        Log.d("record","filename "+filename);
        recorder.setOutputFile(filename);  
        // 设置录制好的音频文件保存路径  
        try {  
            recorder.prepare();// 准备录制  
            recorder.start();// 开始录制  
        } catch (IllegalStateException e) {  
            e.printStackTrace();  
        } catch (IOException e) {  
            e.printStackTrace();  
        }  
    }

    public static void stop(){
        if(recorder != null){
            recorder.stop();
            recorder.release();
            recorder = null;
        }
    }
}

