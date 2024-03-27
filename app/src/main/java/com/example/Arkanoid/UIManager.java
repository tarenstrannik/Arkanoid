package com.example.Arkanoid;
import android.app.Dialog;
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
    private Dialog _gameOverDialog;
    private TextView _livesText,_scoreText;
    public UIManager(Context context,TextView livesText, TextView scoreText)
    {
        _main=(MainActivity) context;
        _context=context;
        _livesText=livesText;
        _scoreText=scoreText;
        _gameOverDialog = new Dialog(context);
        _gameOverDialog.setContentView(R.layout.game_over_layout);
        _gameOverDialog.getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        _restartButton = _gameOverDialog.findViewById(R.id.restart_button);
        _restartButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                _main.AdapterRestartGame();
                _gameOverDialog.hide();
            }
        });

        _exitButton = _gameOverDialog.findViewById(R.id.exit_button);
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

    public void DisplayGameOverScreen(int score){
        TextView scoreValueTextView = _gameOverDialog.findViewById(R.id.GameOverScoreValue);
        scoreValueTextView.setText(String.valueOf(score));

        _gameOverDialog.show();
    }
}
