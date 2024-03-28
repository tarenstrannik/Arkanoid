package com.example.Arkanoid;

import android.app.Activity;
import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.TextView;
public class UIManager {
    private MainActivity _main;
    private Context _context;
    private Button _restartButton;
    private Button _exitButton;

    private TextView _livesText,_scoreText,_startGameText;
    private FrameLayout _gameOver;
    public UIManager(Context context,TextView livesText, TextView scoreText,FrameLayout gameOver, TextView startGameText)
    {
        _main=(MainActivity) context;
        _context=context;
        _livesText=livesText;
        _scoreText=scoreText;
        _gameOver=gameOver;
        _startGameText=startGameText;
        _restartButton = gameOver.findViewById(R.id.restart_button);
        _restartButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                _main.AdapterRestartGame();
                gameOver.setVisibility(View.GONE);
            }
        });

        _exitButton = gameOver.findViewById(R.id.exit_button);
        _exitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                _main.NativeExitGame();
            }
        });
    }

    public void UpdateScore(int score)
    {
        _scoreText.setText(String.valueOf(score));
    }
    public void UpdateLives(int lives)
    {
        _livesText.setText(String.valueOf(lives));
    }
    public void HideInstruction()
    {
        FrameLayout frameLayout = ((Activity) _context).findViewById(R.id.GameArea);
        if(_startGameText!=null)
            frameLayout.removeView(_startGameText);
        _startGameText=null;
    }
    public void DisplayGameOverScreen(int score){
        TextView scoreValueTextView = _gameOver.findViewById(R.id.GameOverScoreValue);
        scoreValueTextView.setText(String.valueOf(score));

        _gameOver.setVisibility(View.VISIBLE);
    }
}
