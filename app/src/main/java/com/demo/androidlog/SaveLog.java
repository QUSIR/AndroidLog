package com.demo.androidlog;

import android.content.Context;
import android.os.Environment;
import android.util.Log;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class SaveLog {
    static {
        System.loadLibrary("native-lib");
    }
    public native static void savelog(byte[] data,int len);
    private static final String TAG="SaveLog";
    public static final SaveLog sManager = new SaveLog();

    public static SaveLog instance() {
        return sManager;
    }
    private static String MYLOG_PATH_SDCARD_DIR = "/sdcard/SaveLog";

    public static void log(String tag, String msg) {
        String msgdata="";
        msgdata=tag+" "+msg;
        createDir(MYLOG_PATH_SDCARD_DIR);
        savelog(msgdata.getBytes(),msgdata.length());
    }
    private static void createDir (String dirPath) {
        File dir = new File(dirPath);
        if (dir.exists()) {
            return;
        }
        if (!dirPath.endsWith(File.separator)) {
            dirPath = dirPath + File.separator;
        }
        if (dir.mkdirs()) {
            Log.d(TAG,"create directory [ "+ dirPath + " ] success");
        }
    }
}
