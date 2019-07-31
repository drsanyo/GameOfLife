#include <QtTest>
#include <../ConwaysGameOfLife/gameoflife.h>


class GameOfLifeClassTests : public QObject
{
    Q_OBJECT

private slots:
    void countNeighbors_ForEmptyMapShouldReturnZero();
    void countNeighbors_ForAloneCellOnMapShouldReturnZero();
    void countNeighbors_ArroundAloneCellShouldReturnOne();
    void countNeighbors_EmptyCellInTopLeftCornerWithOneNeighborshoulReturnOne();
    void countNeighbors_EmptyCellInBottomRightCornerWithOneNeighborshoulReturnOne();
    void countNeighbors_OutOfMapBoundsShouldReturnZero();

    //void lieveOrDieRule_CCellWithNoNeighborsDies();

};


void GameOfLifeClassTests::countNeighbors_ForEmptyMapShouldReturnZero()
{
    // assign
    uint16_t mapSize = 5;
    GameOfLife game(mapSize);

    // act
    for (uint16_t i = 0; i < mapSize; ++i) {
        for (uint16_t j = 0; j < mapSize; ++j) {
            uint8_t Neighbors = game.countNeighbors(i, j);

            // assert
            QCOMPARE(Neighbors, 0);
        }
    }
}

void GameOfLifeClassTests::countNeighbors_ForAloneCellOnMapShouldReturnZero()
{
    // assign
    uint16_t mapSize = 5;
    GameOfLife game(mapSize);
    game.map()[2][2] = 1;

    // act
    uint8_t Neighbors = game.countNeighbors(2, 2);

    // assert
    QCOMPARE(Neighbors, 0);
}

void GameOfLifeClassTests::countNeighbors_ArroundAloneCellShouldReturnOne()
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
            uint8_t Neighbors = game.countNeighbors(i, j);

            // assert
            if ((i != 2) && (j != 2)){
                QCOMPARE(Neighbors, 1);
            }
        }
    }
}

void GameOfLifeClassTests::countNeighbors_EmptyCellInTopLeftCornerWithOneNeighborshoulReturnOne()
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
    uint8_t Neighbors = game.countNeighbors(testCellX, testCellY);

    // assert
    QCOMPARE(Neighbors, 1);
}

void GameOfLifeClassTests::countNeighbors_EmptyCellInBottomRightCornerWithOneNeighborshoulReturnOne()
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
    uint8_t Neighbors = game.countNeighbors(testCellX, testCellY);

    // assert
    QCOMPARE(Neighbors, 1);
}

void GameOfLifeClassTests::countNeighbors_OutOfMapBoundsShouldReturnZero()
{
    // assign
    uint16_t mapSize = 5;
    GameOfLife game(mapSize);

    // act
    uint8_t Neighbors = game.countNeighbors(5, 5);

    // assert
    QCOMPARE(Neighbors, 0);
}

QTEST_APPLESS_MAIN(GameOfLifeClassTests)

#include "tst_gameoflifeclasstests.moc"
