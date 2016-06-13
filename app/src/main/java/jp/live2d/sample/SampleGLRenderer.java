package jp.live2d.sample;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

import jp.live2d.sample.support.BitmapLoader;

public class SampleGLRenderer implements Renderer {
    private final String TAG = "Renderer";

	private Context context;

	private final String MODEL_PATH = "haru/haru.moc" ;
	private final String TEXTURE_PATHS[] =
		{
			"haru/haru.1024/texture_00.png" ,
			"haru/haru.1024/texture_01.png" ,
			"haru/haru.1024/texture_02.png"
		} ;

	public void setContext(Context c) {
		context = c;
	}

	@Override
	public void onDrawFrame(GL10 gl) {
       // Log.d(TAG, "onDrawFrame");
        JniBridge.nativeOnDrawFrame();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.d(TAG, "onSurfaceChanged");
		JniBridge.nativeOnSurfaceChanged(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Log.d(TAG, "onSurfaceCreated");

        JniBridge.nativeOnSurfaceCreated();
		JniBridge.nativeLoadLive2DModel(getFilePath(R.raw.haru, "haru.moc"));
		JniBridge.nativeLoadTexture(0, getFilePath(R.raw.texture_00, "texture_00.png"), new BitmapLoader(context.getAssets()));
		JniBridge.nativeLoadTexture(1, getFilePath(R.raw.texture_01, "texture_01.png"), new BitmapLoader(context.getAssets()));
		JniBridge.nativeLoadTexture(2, getFilePath(R.raw.texture_02, "texture_02.png"), new BitmapLoader(context.getAssets()));
	}

	protected String getFilePath(int resource, String outFilename) {
		String outPath = context.getApplicationInfo().dataDir;
		String outFile = outPath + "/" + outFilename;
		Log.d("blah", outFile);
		try (InputStream in = context.getResources().openRawResource(resource); FileOutputStream out = new FileOutputStream(outFile)) {
			byte[] buff = new byte[1024];
			int read = 0;

			while ((read = in.read(buff)) > 0) {
				out.write(buff, 0, read);
			}

			return outFile;
		} catch (IOException e) {
			e.printStackTrace();
		}

		return "";
	}
}
