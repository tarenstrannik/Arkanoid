package com.example.Arkanoid;

import androidx.appcompat.app.AppCompatActivity;

import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.graphics.Point;
import android.media.MediaPlayer;
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
    private boolean _isGameWindowActive = true; // Флаг, указывающий на активность окна игры
    private MediaPlayer _mediaPlayer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        getSupportActionBar().hide();

        com.example.Arkanoid.databinding.ActivityMainBinding _binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(_binding.getRoot());
        _mediaPlayer = MediaPlayer.create(this, R.raw.beep);
        FrameLayout gameArea = findViewById(R.id.GameArea);
        FrameLayout gameOver = findViewById(R.id.GameOverDialog);
        _visualManager = new VisualManager( this, gameArea);
        _uiManager = new UIManager(this,_binding.LivesValue, _binding.ScoreValue,gameOver,_binding.StartGameText);
        Point viewAreaSize = DisplayUtils.GetScreenSize(this);
        AdapterInitiateJavaCppAdapter();
        float deltaTime= (float) _updateCycleDelayMs /1000;
        AdapterInitiateCPPGameManager(viewAreaSize.x,viewAreaSize.y,deltaTime);
        StartUpdateCycle(_updateCycleDelayMs);
    }
    private void StartUpdateCycle(int updateCycleDelay)
    {
        _handler = new Handler();
        _updateRunnable = new Runnable() {
            @Override
            public void run() {
                if(_isGameWindowActive)
                    AdapterFixedUpdate();

                _handler.postDelayed(this, updateCycleDelay);
            }
        };

        _handler.postDelayed(_updateRunnable, updateCycleDelay);
    }

    @Override
    protected void onResume() {
        super.onResume();
        _isGameWindowActive = true;
    }

    @Override
    protected void onPause() {
        super.onPause();
        _isGameWindowActive = false;
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        _handler.removeCallbacks(_updateRunnable);
        if (_mediaPlayer != null) {
            _mediaPlayer.release();
            _mediaPlayer = null;
        }
    }

    public void NativeUpdateScore(int score)
    {
        _uiManager.UpdateScore(score);
    }
    public void NativeUpdateLives(int lives)
    {
        _uiManager.UpdateLives(lives);
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
    public void NativeHideInstructions() {
        _uiManager.HideInstruction();
    }
    public void NativeSetFigureColor(int id, int colorR,int colorG,int colorB)
    {
        _visualManager.SetFigureColor(id,Color.rgb(colorR,colorG,colorB));
    }
    public void NativeSetFigureActive(int id, boolean value)
    {
        _visualManager.SetFigureActive(id,value);
    }
    public void NativeDestroyFigure(int id)
    {
        _visualManager.DestroyFigure(id);
    }
    public void NativeSetPosition(int id, int positionX, int positionY)
    {
        _visualManager.SetFigurePosition(id, new Point(positionX,positionY));
    }
    public void NativePlaySound() {
        _mediaPlayer.start();
    }
    public void NativeGameOver(int score)
    {
        _uiManager.DisplayGameOverScreen(score);
    };
    public void NativeExitGame()
    {
        finish();
    };
    public native void AdapterInitiateJavaCppAdapter();
    public native void AdapterInitiateCPPGameManager(int width, int height, float deltaTime);
    public native void AdapterFixedUpdate();
    public native void AdapterProcessTouch(int x, int y);
    public native void AdapterRestartGame();
}