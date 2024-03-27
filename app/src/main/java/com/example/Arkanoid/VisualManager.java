package com.example.Arkanoid;
import android.app.Dialog;
import android.content.Context;
import android.graphics.Color;
import android.graphics.Point;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewTreeObserver;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;

public class VisualManager {

    private MainActivity _main;
    private Context _context;
    private FrameLayout _container;
    private Point _viewAreaSize;
    public VisualManager(Context context, FrameLayout container)
    {
        _main=(MainActivity) context;
        _context=context;
        _container=container;
    }
    public void CreateFigure(int figureId, Shapes shape, Point position, Point size, int color, boolean registerTouch)
    {
        View figure = null;
        switch(shape)
        {
            case RECTANGLE:
                figure = new View(_context);
                break;
            case CIRCLE:
                figure = new CircleView(_context);
                break;
            default:
                figure = new View(_context);
        }

        figure.setLayoutParams(new FrameLayout.LayoutParams(size.x, size.y));
        figure.setBackgroundColor(color);

        figure.setX(position.x);
        figure.setY(position.y);
        figure.setId(figureId);

        if(registerTouch)
            CreateTouchListener(figure);
        _container.addView(figure);
    }
    private void CreateTouchListener(View figure)
    {
        figure.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                int x = (int)event.getX();//relatively to the position of the view
                int y = (int)event.getY();
                v.clearFocus();
                int globalX= (int)v.getX()+x;
                int globalY= (int)v.getY()+y;
                _main.AdapterProcessTouch(globalX,globalY);

                return true;
            }
        });
    }
    public void SetFigurePosition(int figureId, Point position)
    {
        View figure = _container.findViewById(figureId);
        if (figure != null) {
            figure.setX(position.x);
            figure.setY(position.y);
        }
    }
    public void SetFigureColor(int figureId, int color)
    {
        View figure = _container.findViewById(figureId);
        if (figure != null) {
            figure.setBackgroundColor(color);
        }
    }
    public void DestroyFigure(int figureId) {
        View figure = _container.findViewById(figureId);
        if (figure != null) {
            _container.removeView(figure);
        }
    }

}
