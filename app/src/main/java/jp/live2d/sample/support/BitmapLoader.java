package jp.live2d.sample.support;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

public class BitmapLoader
{
    public static Bitmap open(String path) {
        try
        {
            return BitmapFactory.decodeFile(path);
        }
        catch (Exception e) { }
        return null;
    }

    public static int getWidth(Bitmap bmp) {
        return bmp.getWidth();
    }

    public static int getHeight(Bitmap bmp) {
        return bmp.getHeight();
    }

    public static void getPixels(Bitmap bmp, int[] pixels) {
        int w = bmp.getWidth();
        int h = bmp.getHeight();
        bmp.getPixels(pixels, 0, w, 0, 0, w, h);
    }

    public static void close(Bitmap bmp) {
        bmp.recycle();
    }
}