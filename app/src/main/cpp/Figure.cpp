//
// Created by taren on 23.03.2024.
//

#include "Figure.h"

Figure::Figure(JavaCppAdapter* adapter, int id,
               Shapes shape,
               Vector2 position,
               Vector2 size,
               Color color,
               bool registerTouch) : GameSceneObject(adapter)
{
    _id=id;
    _shape=shape;
    _position=position;
    _size=size;
    _color=color;
    _registerTouch=registerTouch;
    auto visualX=Figure::GetVisualPosition(position).x;
    auto visualY=Figure::GetVisualPosition(position).y;
    _javaCppAdapter-> CreateFigure(id,static_cast<int>(shape),visualX,visualY,
                                   size.x,size.y,color.r,color.g,color.b,
                                   registerTouch);
}

void Figure::FixedUpdate()
{
    GameSceneObject::FixedUpdate();
}

void Figure::SetPosition(Vector2 position)
{
    _position=position;

    _javaCppAdapter->SetPosition(_id,GetVisualPosition(position));
}
Vector2 Figure::GetVisualPosition(Vector2 position)
{
    return Vector2(position.x-_size.x/2,position.y-_size.y/2);
}

Vector2 Figure::GetPosition() {
    return _position;
}
