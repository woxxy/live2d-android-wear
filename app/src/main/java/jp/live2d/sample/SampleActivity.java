/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
package jp.live2d.sample;


import android.os.Bundle;
import android.support.wearable.activity.WearableActivity;
import android.util.Log;


public class SampleActivity extends WearableActivity
{
    protected static String TAG = "WAIFU";

    private SampleGLSurfaceView GLView;

    @Override
    public void onCreate(Bundle savedStateInstance)
    {
        super.onCreate(savedStateInstance);

        Log.d(TAG, "create");

        GLView = new SampleGLSurfaceView(this);
        setContentView(GLView) ;
    }

    @Override
    public void onResume()
    {
        Log.d(TAG, "resume");
        super.onResume();
        GLView.onResume();
    }

    @Override
    public void onPause()
    {
        super.onPause();
        GLView.onPause();
        Log.d(TAG, "pause");
    }

    @Override
    public void onStart()
    {
        Log.d(TAG, "start");
        super.onStart();
    }

    @Override
    public void onStop()
    {
        Log.d(TAG, "stop");
        super.onStop();
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "destroy");
        super.onDestroy();  // Always call the superclass
        //System.exit(0);
    }
}
