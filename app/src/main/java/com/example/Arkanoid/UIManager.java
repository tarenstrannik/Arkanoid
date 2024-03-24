package com.example.Arkanoid;
import android.content.Context;
import android.widget.FrameLayout;
import android.widget.TextView;
public class UIManager {
    private TextView _livesText,_scoreText;
    public UIManager(TextView livesText, TextView scoreText)
    {
        _livesText=livesText;
        _scoreText=scoreText;
    }

    public void UpdateScore(int score)
    {
        _scoreText.setText(String.valueOf(score));
    }
    public void UpdateLives(int lives)
    {
        _livesText.setText(String.valueOf(lives));
    }
}
