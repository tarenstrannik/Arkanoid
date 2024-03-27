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

    if(_parameters->_rows==1)
    {
        for(int i =0;i<_parameters->_columns;i++)
        {
            Vector2 curPosition = Vector2(rowOffset * ((float) i + 0.5f),
                                          columnOffset * ( 0.5f));
            CreateBrickOfType<Brick3Lives>(curPosition, brickSize);
        }
    }
    else if(_parameters->_rows==2)
    {
        for(int i =0;i<_parameters->_rows;i++) {
            for (int j = 0; j < _parameters->_columns; j++) {
                Vector2 curPosition = Vector2(rowOffset * ((float) j + 0.5f),
                                              columnOffset * ((float) i + 0.5f));
                if(i==0)
                    CreateBrickOfType<Brick3Lives>(curPosition, brickSize);
                else
                    CreateBrickOfType<Brick2Lives>(curPosition, brickSize);
            }
        }

    }
    else
    {
        auto modifiedCount=round((float)_parameters->_rows / 3.0f);
        for(int i =0;i<_parameters->_rows;i++)
        {
            for (int j = 0; j < _parameters->_columns; j++)
            {
                Vector2 curPosition = Vector2(rowOffset * ((float) j + 0.5f),
                                              columnOffset * ((float) i + 0.5f));
                if(i<modifiedCount)
                    CreateBrickOfType<Brick3Lives>(curPosition, brickSize);
                else if(i<2*modifiedCount)
                    CreateBrickOfType<Brick2Lives>(curPosition, brickSize);
                else
                    CreateBrickOfType<Brick>(curPosition, brickSize);
            }
        }

    }
}
template<typename T>
void BrickFactory::CreateBrickOfType(Vector2 position, Vector2 size) {
    static_assert(std::is_base_of<Brick, T>::value, "T must be derived from Brick");

    Brick* brick = new T(_javaCppAdapter, _gameManager, _parameters,
                         _gameManager->CreateObjectId(),
                         position, size);
    brick->OnDestroy.Subscribe([this](Brick* brick) {
        RemoveBrickFromBricks(brick);
    });
    _bricks.push_back(brick);

    OnBrickCreation.Invoke(brick);
}
void BrickFactory::RemoveBrickFromBricks(Brick* brick)
{
    auto it = std::find(_bricks.begin(), _bricks.end(), brick);
    if (it != _bricks.end()) {
        _bricks.erase(std::remove(_bricks.begin(), _bricks.end(), brick), _bricks.end());
    }
}

void BrickFactory::Clear() {
    while(!_bricks.empty())
    {
        auto brick=_bricks.back();
        _bricks.pop_back();
        brick->Destroy();
    }
}



