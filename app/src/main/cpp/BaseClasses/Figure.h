//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_FIGURE_H
#define ARKANOID_FIGURE_H
#include "GameSceneObject.h"
#include "../Structures/Vector2.h"
#include "../Structures/Color.h"
#include "../Enums/Shapes.h"


class Figure: public GameSceneObject {
    protected:
        int _id;
        Shapes _shape;
        Vector2 _position;
        Vector2 _startPosition;
        Vector2 _size;
        Color _color;
        bool _registerTouch;
        void FixedUpdate() override;
        virtual void SetPosition(Vector2 position);
        virtual Vector2 GetPosition();
        virtual Vector2 GetVisualPosition(Vector2 position);
        virtual void ConstraintRestrictions();

    public:
        Figure(JavaCppAdapter* adapter,
               int id,
                Shapes shape = Shapes::RECTANGLE,
                Vector2 position=Vector2(0,0),
                Vector2 size=Vector2(0,0),
                Color color=Color(0,0,0),
                bool registerTouch=false);
        ~Figure();
        virtual float GetTopBorder();
        virtual float GetBottomBorder();
        virtual float GetLeftBorder();
        virtual float GetRightBorder();
};

#endif //ARKANOID_FIGURE_H
