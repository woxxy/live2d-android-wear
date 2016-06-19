package jp.live2d.sample;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;

public class SampleGLRenderer implements Renderer {
    private final String TAG = "Renderer";

	@Override
	public void onDrawFrame(GL10 gl) {
        JniBridge.nativeOnDrawFrame();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		JniBridge.nativeOnSurfaceChanged(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        JniBridge.nativeOnSurfaceCreated();
	}
}
