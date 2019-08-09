#include "gameoflife.h"

GameOfLife::GameOfLife():GameOfLife(0)
{

}

GameOfLife::GameOfLife(uint16_t newMapSize)
{
    _mapSize = newMapSize;
    createMapArrays();
}

GameOfLife::~GameOfLife()
{
    deleteMapArrays();
}

void  GameOfLife::initialiseGameMap()
{
    for (uint16_t i = 0; i < _mapSize; ++i)
        for (uint16_t j = 0; j < _mapSize; ++j)
            Map[i][j] = std::rand() % ( 1 - 0 + 1 );
}

uint8_t GameOfLife::countNeighbors(uint16_t x, uint16_t y)
{
    if ((x >= _mapSize) || (y >= _mapSize))
        return 0;

    uint8_t sum = 0;           
    for (int8_t i = -1; i <= +1; ++i)
        for (int8_t j = -1; j <= +1; ++j)
        {
            // "wrap aroud" map to join top<->bottom and left<->right
            uint16_t col = (x + i + _mapSize) % _mapSize;
            uint16_t row = (y + j + _mapSize) % _mapSize;
            sum += Map[col][row];
        }
    return sum-Map[x][y];
}

void GameOfLife::calculateNewGeneration()
{
    for (uint16_t i = 0; i < _mapSize; ++i)
        for (uint16_t j = 0; j < _mapSize; ++j)
        {
            uint8_t neighboursCount = countNeighbors(i, j);
            uint8_t result = lieveOrDieRule(neighboursCount, Map[i][j]);
            _mapNew[i][j] = result;
        }
    std::swap(Map, _mapNew);
}

uint8_t GameOfLife::lieveOrDieRule(uint8_t neighboursCount, uint8_t previousValue)
{
    uint8_t result;
    if ((neighboursCount <= 1) || (neighboursCount > 3)){
        result = 0;
    }
    else if (neighboursCount == 3){
        result = 1;
    }
    else {
        result = previousValue;
    }
    return result;
}

void GameOfLife::createMapArrays()
{
    for (int i = 0; i < _mapSize; i++) {
        std::vector<uint8_t> row;
        for (int j = 0; j < _mapSize; j++) {
            row.push_back(0);
        }
        Map.push_back(row);
    }

    for (int i = 0; i < _mapSize; i++) {
        std::vector<uint8_t> row;
        for (int j = 0; j < _mapSize; j++) {
            row.push_back(0);
        }
        _mapNew.push_back(row);
    }
}

void GameOfLife::deleteMapArrays()
{
    Map.clear();
    _mapNew.clear();
}
