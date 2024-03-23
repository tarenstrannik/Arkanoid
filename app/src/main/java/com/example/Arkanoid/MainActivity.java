package com.example.Arkanoid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.Arkanoid.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'Arkanoid' library on application startup.
    static {
        System.loadLibrary("Arkanoid");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        CreateGameSceneObject(16F);

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI("test"));

    }

    /**
     * A native method that is implemented by the 'Arkanoid' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(String param);
    public native void CreateGameSceneObject(Float jupdateTimer);
}