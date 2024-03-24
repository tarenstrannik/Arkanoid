package com.example.Arkanoid;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.graphics.Point;
import android.os.Bundle;
import android.os.Handler;
import android.widget.FrameLayout;

import com.example.Arkanoid.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'Arkanoid' library on application startup.
    static {
        System.loadLibrary("Arkanoid");
    }
    private Handler _handler;
    private Runnable _updateRunnable;
    private VisualManager _visualManager;
    private UIManager _uiManager;
    private static final int _updateCycleDelayMs=16;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getSupportActionBar().hide();

        com.example.Arkanoid.databinding.ActivityMainBinding _binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(_binding.getRoot());
        FrameLayout _container = findViewById(R.id.GameArea);
        _visualManager = new VisualManager( this, _container);
        _uiManager = new UIManager(_binding.LivesValue, _binding.ScoreValue);
        Point viewAreaSize = DisplayUtils.GetScreenSize(this);
        InitiateJavaCppAdapter();
        InitiateCPPGameManager(viewAreaSize.x,viewAreaSize.y);
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
        _uiManager.UpdateScore(score);
    }
    public void NativeUpdateLives(int lives)
    {
        _uiManager.UpdateScore(lives);
    }
    public void NativeCreateFigure(
            int id,
            int shapeType,
            int positionX,
            int positionY,
            int sizeX,
            int sizeY,
            int colorR,
            int colorG,
            int colorB,
            boolean registerTouch
    )
    {

        _visualManager.CreateFigure(
                id,
                Shapes.values()[shapeType],
                new Point(positionX,positionY),
                new Point (sizeX,sizeY),
                Color.rgb(colorR,colorG,colorB),
                registerTouch);
    }
    public void NativeSetPosition(int id, int positionX, int positionY)
    {
        _visualManager.SetFigurePosition(id, new Point(positionX,positionY));
    }
    public native void InitiateJavaCppAdapter();
    public native void InitiateCPPGameManager(int width, int height);
    public native void FixedUpdate();

    public native void NativeProcessTouch(int x, int y);
}