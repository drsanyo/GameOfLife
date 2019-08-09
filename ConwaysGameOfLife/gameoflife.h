#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H
#include <cstdint>
#include <vector>

class GameOfLife
{
private:
    std::vector<std::vector<uint8_t>> _mapNew;

    uint16_t _mapSize = 100;    

    void createMapArrays();
    void deleteMapArrays();

public:
    GameOfLife();
    GameOfLife(uint16_t newMapSize);
    ~GameOfLife();
    std::vector<std::vector<uint8_t>> Map;

    uint16_t mapSize() { return _mapSize; }
    void mapSize(const uint16_t& mapSize) {
        deleteMapArrays();
        _mapSize = mapSize;
        createMapArrays();
    }

    uint8_t countNeighbors(uint16_t width, uint16_t height);
    uint8_t lieveOrDieRule(uint8_t neighborsCount, uint8_t previousValue);
    void calculateNewGeneration();
    void initialiseGameMap();
};

#endif // GAMEOFLIFE_H
