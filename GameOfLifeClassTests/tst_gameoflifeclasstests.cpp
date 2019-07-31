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

    void lieveOrDieRule_CellWithOneOrLessNeighborsShouldDie();
    void lieveOrDieRule_CellWithMoreThanThreeNeighborsShouldDie();
    void lieveOrDieRule_CellWithTwoOrThreeNeighborsShouldSurvive();
    void lieveOrDieRule_EmptyCellWithThreeNeighborsShouldBorn();
    void lieveOrDieRule_EmptyCellWithTwoNeighborsShouldBeEmpty();

    void calculateNewGeneration_StillLifes_Block();
    void calculateNewGeneration_StillLifes_Tub();
    void calculateNewGeneration_Oscillators_Blinker();
    void calculateNewGeneration_Oscillators_Beacon();
    void calculateNewGeneration_Spaceships_Glinder();
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

void GameOfLifeClassTests::lieveOrDieRule_CellWithOneOrLessNeighborsShouldDie()
{
    // assign
    uint8_t previousCellState = 1;
    GameOfLife game;

    // act
    uint8_t newCellState0Neighbors = game.lieveOrDieRule(0, previousCellState);
    uint8_t newCellState1Neighbor = game.lieveOrDieRule(1, previousCellState);

    // assert
    QCOMPARE(newCellState1Neighbor , 0);
    QCOMPARE(newCellState0Neighbors , 0);
}

void GameOfLifeClassTests::lieveOrDieRule_CellWithMoreThanThreeNeighborsShouldDie()
{
    // assign
    uint8_t previousCellState = 1;
    GameOfLife game;

    // act
    uint8_t newCellState = game.lieveOrDieRule(4, previousCellState);

    // assert
    QCOMPARE(newCellState , 0);
}

void GameOfLifeClassTests::lieveOrDieRule_CellWithTwoOrThreeNeighborsShouldSurvive()
{
    // assign
    uint8_t previousCellState = 1;
    GameOfLife game;

    // act
    uint8_t newCellState2Neighbors = game.lieveOrDieRule(2, previousCellState);
    uint8_t newCellState3Neighbors = game.lieveOrDieRule(3, previousCellState);

    // assert
    QCOMPARE(newCellState2Neighbors , previousCellState);
    QCOMPARE(newCellState3Neighbors , previousCellState);
}

void GameOfLifeClassTests::lieveOrDieRule_EmptyCellWithThreeNeighborsShouldBorn()
{
    // assign
    uint8_t previousCellState = 0;
    GameOfLife game;

    // act
    uint8_t newCellState = game.lieveOrDieRule(3, previousCellState);

    // assert
    QCOMPARE(newCellState , 1);
}

void GameOfLifeClassTests::lieveOrDieRule_EmptyCellWithTwoNeighborsShouldBeEmpty()
{
    // assign
    uint8_t previousCellState = 0;
    GameOfLife game;

    // act
    uint8_t newCellState = game.lieveOrDieRule(2, previousCellState);

    // assert
    QCOMPARE(newCellState, previousCellState);
}

void GameOfLifeClassTests::calculateNewGeneration_StillLifes_Block()
{
    // assign
    const uint16_t mapSize = 4;
    GameOfLife game(mapSize);
    game.map()[1][1] = 1;
    game.map()[1][2] = 1;
    game.map()[2][1] = 1;
    game.map()[2][2] = 1;

    int resultArray[mapSize][mapSize] =
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };

    // act
    game.calculateNewGeneration();

    // assert
    for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j) {
            QCOMPARE(game.map()[i][j], resultArray[i][j]);
        }
    }
}

void GameOfLifeClassTests::calculateNewGeneration_StillLifes_Tub()
{
    // assign
    const uint16_t mapSize = 5;
    GameOfLife game(mapSize);
    game.map()[2][1] = 1;
    game.map()[2][3] = 1;
    game.map()[1][2] = 1;
    game.map()[3][2] = 1;

    int resultArray[mapSize][mapSize] =
    {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,1,0,1,0},
        {0,0,1,0,0},
        {0,0,0,0,0}
    };

    // act
    game.calculateNewGeneration();

    // assert
    for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j) {
            QCOMPARE(game.map()[i][j], resultArray[i][j]);
        }
    }
}

void GameOfLifeClassTests::calculateNewGeneration_Oscillators_Blinker()
{
    // assign
    const uint16_t mapSize = 5;
    GameOfLife game(mapSize);
    game.map()[2][1] = 1;
    game.map()[2][2] = 1;
    game.map()[2][3] = 1;

    int resultArray[mapSize][mapSize] =
    {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,0,0,0}
    };

    // act
    game.calculateNewGeneration();

    // assert
    for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j) {
            QCOMPARE(game.map()[i][j], resultArray[i][j]);
        }
    }
}

void GameOfLifeClassTests::calculateNewGeneration_Oscillators_Beacon()
{
    // assign
    const uint16_t mapSize = 6;
    GameOfLife game(mapSize);

    game.map()[1][4] = 1;
    game.map()[1][3] = 1;
    game.map()[2][4] = 1;
    game.map()[2][3] = 1;

    game.map()[3][2] = 1;
    game.map()[3][1] = 1;
    game.map()[4][2] = 1;
    game.map()[4][1] = 1;

    int resultArray[mapSize][mapSize] =
    {
        {0,0,0,0,0,0},
        {0,0,0,1,1,0},
        {0,0,0,0,1,0},
        {0,1,0,0,0,0},
        {0,1,1,0,0,0},
        {0,0,0,0,0,0}
    };

    // act
    game.calculateNewGeneration();

    // assert
    for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j) {
            QCOMPARE(game.map()[i][j], resultArray[i][j]);
        }
    }
}

void GameOfLifeClassTests::calculateNewGeneration_Spaceships_Glinder()
{
    // assign
    const uint16_t mapSize = 5;
    GameOfLife game(mapSize);

    game.map()[1][2] = 1;
    game.map()[2][0] = 1;
    game.map()[2][2] = 1;
    game.map()[3][1] = 1;
    game.map()[3][2] = 1;

    int resultArray[mapSize][mapSize] =
    {
        {0,0,0,0,0},
        {0,1,0,0,0},
        {0,0,1,1,0},
        {0,1,1,0,0},
        {0,0,0,0,0}
    };

    // act
    game.calculateNewGeneration();

    // assert
    for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j) {
            QCOMPARE(game.map()[i][j], resultArray[i][j]);
        }
    }
}

QTEST_APPLESS_MAIN(GameOfLifeClassTests)

#include "tst_gameoflifeclasstests.moc"
