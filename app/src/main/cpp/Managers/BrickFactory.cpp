//
// Created by taren on 26.03.2024.
//

#include "BrickFactory.h"
#include "GameManager.h"

BrickFactory::BrickFactory(JavaCppAdapter* adapter, GameManager* gameManager, Vector2 fieldSize, int rows, int columns)
{
    _javaCppAdapter=adapter;
    _gameManager=gameManager;
    _fieldSize=fieldSize;
    _rows=rows;
    _columns=columns;

    OnFigureCreation = GenericEvent<Figure*>();
    _gameManager->OnNewRound.Subscribe([this]() {
        Clear();
        Generate();
    });

}
void BrickFactory::Generate()
{
    float rowOffset=_fieldSize.x/(float)_columns;
    float columnOffset = rowOffset/_brickWidthToHeight;
    Vector2 brickSize=Vector2(rowOffset,columnOffset)*_brickDecreasingCoef;
    for(int i =0;i<_rows;i++)
        for(int j=0;j<_columns;j++)
        {
            Vector2 curPosition=Vector2(rowOffset*((float)i+0.5f),columnOffset*((float)j+0.5f));
            auto brick=CreateBrick(curPosition,brickSize,_color,_price,_price);
            _bricks.push_back(brick);
            OnFigureCreation.Invoke(brick);
        }
}
Figure *BrickFactory::CreateBrick(Vector2 position, Vector2 size, Color color,int price,int lives) {
    auto brickID=_gameManager->CreateObjectId();
    auto brickShape = Shapes::RECTANGLE;

    Brick* brick = new Brick(_javaCppAdapter, _gameManager, _gameManager->CreateObjectId(),
                             brickShape, position, size,
                             color, false, price, lives);
    brick->OnDestroy.Subscribe([this](Figure* figure) {
        _bricks.remove(figure);
    });
    return brick;
}

void BrickFactory::Clear() {
    for(Figure* brick: _bricks)
    {
        delete brick;
    }
}



