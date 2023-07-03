package com.mrousavy.camera.example;

import android.media.Image;
import android.util.Log;
import com.facebook.react.bridge.WritableNativeArray;
import com.facebook.react.bridge.WritableNativeMap;
import com.mrousavy.camera.frameprocessor.Frame;
import com.mrousavy.camera.frameprocessor.FrameProcessorPlugin;
import org.jetbrains.annotations.NotNull;

public class ExampleFrameProcessorPlugin extends FrameProcessorPlugin {
    @Override
    public Object callback(@NotNull Frame frame, @NotNull Object[] params) {
        Image image = frame.getImage();
        Log.d("ExamplePlugin", image.getWidth() + " x " + image.getHeight() + " Image with format #" + image.getFormat() + ". Logging " + params.length + " parameters:");

        for (Object param : params) {
            Log.d("ExamplePlugin", "  -> " + (param == null ? "(null)" : param.toString() + " (" + param.getClass().getName() + ")"));
        }

        WritableNativeMap map = new WritableNativeMap();
        map.putString("example_str", "Test");
        map.putBoolean("example_bool", true);
        map.putDouble("example_double", 5.3);

        WritableNativeArray array = new WritableNativeArray();
        array.pushString("Hello!");
        array.pushBoolean(true);
        array.pushDouble(17.38);

        map.putArray("example_array", array);
        return map;
    }

    ExampleFrameProcessorPlugin() {
        super("example_plugin");
    }
}
