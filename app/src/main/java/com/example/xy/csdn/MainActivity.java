package com.example.xy.csdn;

import android.Manifest;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.Environment;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());


        if (!PermissionUtils.hasPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)){
            String[] p = {Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE};
            PermissionUtils.requestPermissions(this, p, 1);
        }

        final ImageView mImageView  = findViewById(R.id.image_view);
        final ImageView mImageView2  = findViewById(R.id.image_view2);
//        Bitmap bitmap = BitmapFactory.decodeFile(Environment.getExternalStorageDirectory()+"/DCIM/Yado/Infrared_20190409_144423.jpg");
//        mImageView.setImageBitmap(bitmap);
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
//                String path = Environment.getExternalStorageDirectory()+"/Huawei/MagazineUnlock/magazine-unlock-05-2.3.1309-_0B9E6BAFA974F39C9B3E7CAF29E1D3A7.jpg";
                String path = Environment.getExternalStorageDirectory()+"/DCIM/Yado/20190403_185017719.png";
                Bitmap bitmap = BitmapFactory.decodeFile(path);
                int w = bitmap.getWidth(), h = bitmap.getHeight();
                Log.e("tag","h "+h);
                Log.e("tag","w "+w);
                int[] pix = new int[w * h];
                bitmap.getPixels(pix, 0, w, 0, 0, w, h);
                int[] resultPixels = blurImage(pix,w,h);
                Bitmap result = Bitmap.createBitmap(w,h, Bitmap.Config.RGB_565);
                result.setPixels(resultPixels, 0, w, 0, 0,w, h);
                mImageView.setImageBitmap(result);
                mImageView2.setImageBitmap(bitmap);
            }
        },500);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int[] getGray(int buf[],int w,int h);
    public native int[] blurImage(int pixels[],int w,int h);
}
