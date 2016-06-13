package jp.live2d.sample.support;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

public class BitmapLoader
{
    private AssetManager amgr;

    public BitmapLoader(AssetManager tAmgr) {
        amgr = tAmgr;
    }

    public Bitmap open(String path) {
        try
        {
            return BitmapFactory.decodeFile(path);
        }
        catch (Exception e) { }
        return null;
    }

    public int getWidth(Bitmap bmp) {
        return bmp.getWidth();
    }

    public int getHeight(Bitmap bmp) {
        return bmp.getHeight();
    }

    public void getPixels(Bitmap bmp, int[] pixels) {
        int w = bmp.getWidth();
        int h = bmp.getHeight();
        bmp.getPixels(pixels, 0, w, 0, 0, w, h);
    }

    public void close(Bitmap bmp) {
        bmp.recycle();
    }
}