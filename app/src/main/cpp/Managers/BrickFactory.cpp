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
            PlaceBrick<Brick3Lives>(curPosition, brickSize);
        }
    }
    else if(_parameters->_rows==2)
    {
        for(int i =0;i<_parameters->_rows;i++) {
            for (int j = 0; j < _parameters->_columns; j++) {
                Vector2 curPosition = Vector2(rowOffset * ((float) j + 0.5f),
                                              columnOffset * ((float) i + 0.5f));
                if(i==0)
                    PlaceBrick<Brick3Lives>(curPosition, brickSize);
                else
                    PlaceBrick<Brick2Lives>(curPosition, brickSize);
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
                    PlaceBrick<Brick3Lives>(curPosition, brickSize);
                else if(i<2*modifiedCount)
                    PlaceBrick<Brick2Lives>(curPosition, brickSize);
                else
                    PlaceBrick<Brick>(curPosition, brickSize);
            }
        }

    }
}
template<typename T>
void BrickFactory::PlaceBrick(Vector2 position, Vector2 size) {

    Brick* brick = nullptr;
    brick=GetBrickOfTypeFromPool<T>();
    if(brick==nullptr)
    {
        brick=CreateBrickOfType<T>(position, size);
        _pooledBricks.push_back(brick);
    };
    brick->SetPosition(position);
    brick->OnDeactivation.Subscribe([this](Brick* brick) {
        RemoveBrickFromBricks(brick);
    });
    _activeBricks.push_back(brick);

    OnBrickCreation.Invoke(brick);
}

template<typename T>
Brick* BrickFactory::GetBrickOfTypeFromPool() {
    static_assert(std::is_base_of<Brick, T>::value, "T must be derived from Brick");

    for(Brick* pooledBrick:_pooledBricks)
    {
        T* typedBrick = dynamic_cast<T*>(pooledBrick);
        if (typedBrick != nullptr && !typedBrick->IsActive()) {
            typedBrick->ResetBrick();
            return pooledBrick;
        }
    }
    return nullptr;
}
template<typename T>
Brick* BrickFactory::CreateBrickOfType(Vector2 position, Vector2 size) {
    static_assert(std::is_base_of<Brick, T>::value, "T must be derived from Brick");
    return new T(_javaCppAdapter, _gameManager, _parameters,
                         _gameManager->CreateObjectId(),
                         position, size);
}


void BrickFactory::RemoveBrickFromBricks(Brick* brick)
{
    auto it = std::find(_activeBricks.begin(), _activeBricks.end(), brick);
    if (it != _activeBricks.end()) {
        _activeBricks.erase(std::remove(_activeBricks.begin(), _activeBricks.end(), brick), _activeBricks.end());
    }
}

void BrickFactory::Clear() {
    while(!_activeBricks.empty())
    {
        auto brick=_activeBricks.back();
        _activeBricks.pop_back();
        brick->SetActive(false);
    }
}





