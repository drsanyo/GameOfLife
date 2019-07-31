#include <QtTest>
#include <../ConwaysGameOfLife/gameoflife.h>


class GameOfLifeClassTests : public QObject
{
    Q_OBJECT

private slots:
    void countNeighbours_ForEmptyMapShouldReturnZero();
    void countNeighbours_ForAloneCellOnMapShouldReturnZero();
    void countNeighbours_ArroundAloneCellShouldReturnOne();
    void countNeighbours_EmptyCellInTopLeftCornerWithOneNeighbourShoulReturnOne();
    void countNeighbours_EmptyCellInBottomRightCornerWithOneNeighbourShoulReturnOne();
    void countNeighbours_OutOfMapBoundsShouldReturnZero();

};


void GameOfLifeClassTests::countNeighbours_ForEmptyMapShouldReturnZero()
{
    // assign
    uint16_t mapSize = 5;
    GameOfLife game(mapSize);

    // act
    for (uint16_t i = 0; i < mapSize; ++i) {
        for (uint16_t j = 0; j < mapSize; ++j) {
            uint8_t neighbours = game.countNeighbours(i, j);

            // assert
            QCOMPARE(neighbours, 0);
        }
    }
}

void GameOfLifeClassTests::countNeighbours_ForAloneCellOnMapShouldReturnZero()
{
    // assign
    uint16_t mapSize = 5;
    GameOfLife game(mapSize);
    game.map()[2][2] = 1;

    // act
    uint8_t neighbours = game.countNeighbours(2, 2);

    // assert
    QCOMPARE(neighbours, 0);
}

void GameOfLifeClassTests::countNeighbours_ArroundAloneCellShouldReturnOne()
{
    // assign
    uint16_t mapSize = 5;
    uint16_t cellX = 2;
    uint16_t cellY = 2;

    GameOfLife game(mapSize);
    game.map()[cellY][cellX] = 1;

    // act
    for (uint16_t i = cellX-1; i <= cellX+1; ++i) {
        for (uint16_t j = cellY-1; j <= cellY-1; ++j) {
            uint8_t neighbours = game.countNeighbours(i, j);

            // assert
            if ((i != 2) && (j != 2)){
                QCOMPARE(neighbours, 1);
            }
        }
    }
}

void GameOfLifeClassTests::countNeighbours_EmptyCellInTopLeftCornerWithOneNeighbourShoulReturnOne()
{
    // assign
    uint16_t mapSize = 5;

    uint16_t testCellX = 0;
    uint16_t testCellY = 0;

    uint16_t neighbourX = 1;
    uint16_t neighbourY = 0;

    GameOfLife game(mapSize);
    game.map()[neighbourX][neighbourY] = 1;

    // act
    uint8_t neighbours = game.countNeighbours(testCellX, testCellY);

    // assert
    QCOMPARE(neighbours, 1);
}

void GameOfLifeClassTests::countNeighbours_EmptyCellInBottomRightCornerWithOneNeighbourShoulReturnOne()
{
    // assign
    uint16_t mapSize = 5;

    uint16_t testCellX = 4;
    uint16_t testCellY = 4;

    uint16_t neighbourX = 4;
    uint16_t neighbourY = 0;

    GameOfLife game(mapSize);
    game.map()[neighbourX][neighbourY] = 1;

    // act
    uint8_t neighbours = game.countNeighbours(testCellX, testCellY);

    // assert
    QCOMPARE(neighbours, 1);
}

void GameOfLifeClassTests::countNeighbours_OutOfMapBoundsShouldReturnZero()
{
    // assign
    uint16_t mapSize = 5;
    GameOfLife game(mapSize);

    // act
    uint8_t neighbours = game.countNeighbours(5, 5);

    // assert
    QCOMPARE(neighbours, 0);
}

QTEST_APPLESS_MAIN(GameOfLifeClassTests)

#include "tst_gameoflifeclasstests.moc"
