//
// Created by taren on 26.03.2024.
//

#include "BrickFactory.h"


BrickFactory::BrickFactory(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters,Vector2* fieldSize):
        Manager(adapter,gameManager,parameters)
{
    _fieldSize=fieldSize;
    OnBrickCreation = GenericEvent<Brick*>();
    _gameManager->OnNewRound.Subscribe([this]() {
        Generate();
    });
    _gameManager->OnGameOver.Subscribe([this]() {
        Clear();
    });

}
void BrickFactory::Generate()
{
    float rowOffset=_fieldSize->x/(float)_parameters->_columns;
    float columnOffset = rowOffset/_parameters->_brickWidthToHeight;
    Vector2 brickSize=Vector2(rowOffset,columnOffset)*_parameters->_brickDecreasingCoef;
    for(int i =0;i<_parameters->_rows;i++)
        for(int j=0;j<_parameters->_columns;j++)
        {
            Vector2 curPosition=Vector2(rowOffset*((float)i+0.5f),columnOffset*((float)j+0.5f));
            auto brick=CreateBrick(curPosition,brickSize);
            _bricks.push_back(brick);

            OnBrickCreation.Invoke(brick);
        }
}
Brick* BrickFactory::CreateBrick(Vector2 position, Vector2 size) {
    auto brickID=_gameManager->CreateObjectId();
    auto brickShape = Shapes::RECTANGLE;

    Brick* brick = new Brick(_javaCppAdapter, _gameManager, _parameters,_gameManager->CreateObjectId(),
                             position, size
                             );
    brick->OnDestroy.Subscribe([this](Brick* brick) {
        _bricks.erase(std::remove(_bricks.begin(), _bricks.end(), brick), _bricks.end());
    });
    return brick;
}

void BrickFactory::Clear() {
    while(!_bricks.empty())
    {
        _bricks.back()->Destroy();
    }
}



