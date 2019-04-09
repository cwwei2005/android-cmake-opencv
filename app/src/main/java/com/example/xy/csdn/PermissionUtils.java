package com.example.xy.csdn;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;

public class PermissionUtils {
    public static boolean hasPermission(Context ctx, String permission){
        return ContextCompat.checkSelfPermission(ctx, permission) == PackageManager.PERMISSION_GRANTED;
    }

    public static void requestPermissions(Activity activity, String[] permissions, int code){
        ActivityCompat.requestPermissions(activity, permissions, code);
    }
}
