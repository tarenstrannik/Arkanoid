package com.example.Arkanoid;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.View;

public class CircleView extends View {

    private Paint _paint;
    private int _circleColor = Color.BLACK;;
    public CircleView(Context context) {
        super(context);
        _paint = new Paint();
    }

    @Override
    public void setBackgroundColor(int color) {
        _circleColor = color;
        invalidate();
    }
    @Override
    protected void onDraw(Canvas canvas) {
        int width = getWidth();
        int height = getHeight();
        int radius = Math.min(width, height) / 2;
        _paint.setColor(_circleColor);
        canvas.drawCircle(width / 2, height / 2, radius, _paint);
    }
}