/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
package jp.live2d.sample;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class SampleGLSurfaceView extends GLSurfaceView
{
	private SampleGLRenderer renderer;

	public SampleGLSurfaceView(Context context)
	{
		super(context);

		renderer = new SampleGLRenderer() ;
		renderer.setContext(getContext());
		//setDebugFlags(DEBUG_CHECK_GL_ERROR | DEBUG_LOG_GL_CALLS);
		setEGLContextClientVersion(2);

		setRenderer(renderer);
	}

    public void onPause()
    {
        JniBridge.nativeOnSurfaceDestroyed();
        super.onPause();
    }
}