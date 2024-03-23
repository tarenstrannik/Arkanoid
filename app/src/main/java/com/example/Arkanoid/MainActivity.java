package com.example.Arkanoid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.widget.TextView;

import com.example.Arkanoid.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'Arkanoid' library on application startup.
    static {
        System.loadLibrary("Arkanoid");
    }

    private ActivityMainBinding _binding;
    private Handler _handler;
    private Runnable _updateRunnable;

    private TextView _tv;
    private static final int _updateCycleDelayMs=16;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        _binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(_binding.getRoot());

        _tv = _binding.sampleText;

        InitiateJavaCppAdapter();

        // Example of a call to a native method
        //TextView tv = binding.sampleText;
        //tv.setText(stringFromJNI("test"));

        StartUpdateCycle(_updateCycleDelayMs);

    }
    private void StartUpdateCycle(int updateCycleDelay)
    {
        _handler = new Handler();
        _updateRunnable = new Runnable() {
            @Override
            public void run() {
                FixedUpdate();

                _handler.postDelayed(this, updateCycleDelay);
            }
        };

        _handler.postDelayed(_updateRunnable, updateCycleDelay);
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        _handler.removeCallbacks(_updateRunnable);
    }

    public void NativeUpdateScore(int score)
    {
        _tv.setText(String.valueOf(score));
    }
    public native String stringFromJNI(String param);
    public native void InitiateJavaCppAdapter();
    public native void FixedUpdate();

}