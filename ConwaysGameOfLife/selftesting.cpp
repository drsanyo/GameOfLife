#include "selftesting.h"
#include "ui_selftesting.h"
#include "gameoflife.h"

#include <QTableView>
#include <QTest>

SelfTesting::SelfTesting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelfTesting)
{
    ui->setupUi(this);    
}

SelfTesting::~SelfTesting()
{
    delete ui;
}

void SelfTesting::loadTestResults()
{
    QFile file(testsResultFileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream ReadFile(&file);
    ui->txtTestResult->setText(ReadFile.readAll());
    file.close();
}

void SelfTesting::runTests()
{
    QStringList redirectOutputToFile;
    redirectOutputToFile<<" "<<"-o"<<testsResultFileName;
    //redirectOutputToFile<<"-xml";

    /*
     * cannot pass here filename with absolute path
     * so cannot use temporary file (e.g. QTemporaryFile)
    */
    QTest::qExec(this, redirectOutputToFile);
}

void SelfTesting::on_btnRunTests_clicked()
{
    runTests();
    loadTestResults();
    QFile::remove(testsResultFileName);
}


void SelfTesting::countNeighbors_ForEmptyMapShouldReturnZero()
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

void SelfTesting::countNeighbors_ForAloneCellOnMapShouldReturnZero()
{
    // assign
    uint16_t mapSize = 5;
    GameOfLife game(mapSize);
    game.Map[2][2] = 1;

    // act
    uint8_t Neighbors = game.countNeighbors(2, 2);

    // assert
    QCOMPARE(Neighbors, 0);
}

void SelfTesting::countNeighbors_ArroundAloneCellShouldReturnOne()
{
    // assign
    uint16_t mapSize = 5;
    uint16_t cellX = 2;
    uint16_t cellY = 2;

    GameOfLife game(mapSize);
    game.Map[cellY][cellX] = 1;

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

void SelfTesting::countNeighbors_EmptyCellInTopLeftCornerWithOneNeighborshoulReturnOne()
{
    // assign
    uint16_t mapSize = 5;

    uint16_t testCellX = 0;
    uint16_t testCellY = 0;

    uint16_t neighbourX = 1;
    uint16_t neighbourY = 0;

    GameOfLife game(mapSize);
    game.Map[neighbourX][neighbourY] = 1;

    // act
    uint8_t Neighbors = game.countNeighbors(testCellX, testCellY);

    // assert
    QCOMPARE(Neighbors, 1);
}

void SelfTesting::countNeighbors_EmptyCellInBottomRightCornerWithOneNeighborshoulReturnOne()
{
    // assign
    uint16_t mapSize = 5;

    uint16_t testCellX = 4;
    uint16_t testCellY = 4;

    uint16_t neighbourX = 4;
    uint16_t neighbourY = 0;

    GameOfLife game(mapSize);
    game.Map[neighbourX][neighbourY] = 1;

    // act
    uint8_t Neighbors = game.countNeighbors(testCellX, testCellY);

    // assert
    QCOMPARE(Neighbors, 1);
}

void SelfTesting::countNeighbors_OutOfMapBoundsShouldReturnZero()
{
    // assign
    uint16_t mapSize = 5;
    GameOfLife game(mapSize);

    // act
    uint8_t Neighbors = game.countNeighbors(5, 5);

    // assert
    QCOMPARE(Neighbors, 0);
}

void SelfTesting::lieveOrDieRule_CellWithOneOrLessNeighborsShouldDie()
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

void SelfTesting::lieveOrDieRule_CellWithMoreThanThreeNeighborsShouldDie()
{
    // assign
    uint8_t previousCellState = 1;
    GameOfLife game;

    // act
    uint8_t newCellState = game.lieveOrDieRule(4, previousCellState);

    // assert
    QCOMPARE(newCellState , 0);
}

void SelfTesting::lieveOrDieRule_CellWithTwoOrThreeNeighborsShouldSurvive()
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

void SelfTesting::lieveOrDieRule_EmptyCellWithThreeNeighborsShouldBorn()
{
    // assign
    uint8_t previousCellState = 0;
    GameOfLife game;

    // act
    uint8_t newCellState = game.lieveOrDieRule(3, previousCellState);

    // assert
    QCOMPARE(newCellState , 1);
}

void SelfTesting::lieveOrDieRule_EmptyCellWithTwoNeighborsShouldBeEmpty()
{
    // assign
    uint8_t previousCellState = 0;
    GameOfLife game;

    // act
    uint8_t newCellState = game.lieveOrDieRule(2, previousCellState);

    // assert
    QCOMPARE(newCellState, previousCellState);
}

void SelfTesting::calculateNewGeneration_StillLifes_Block()
{
    // assign
    const uint16_t mapSize = 4;
    GameOfLife game(mapSize);
    game.Map[1][1] = 1;
    game.Map[1][2] = 1;
    game.Map[2][1] = 1;
    game.Map[2][2] = 1;

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
    for (uint8_t i = 0; i < mapSize; ++i) {
        for (uint8_t j = 0; j < mapSize; ++j) {
            QCOMPARE(game.Map[i][j], resultArray[i][j]);
        }
    }
}

void SelfTesting::calculateNewGeneration_StillLifes_Tub()
{
    // assign
    const uint16_t mapSize = 5;
    GameOfLife game(mapSize);
    game.Map[2][1] = 1;
    game.Map[2][3] = 1;
    game.Map[1][2] = 1;
    game.Map[3][2] = 1;

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
    for (uint8_t i = 0; i < mapSize; ++i) {
        for (uint8_t j = 0; j < mapSize; ++j) {
            QCOMPARE(game.Map[i][j], resultArray[i][j]);
        }
    }
}

void SelfTesting::calculateNewGeneration_Oscillators_Blinker()
{
    // assign
    const uint16_t mapSize = 5;
    GameOfLife game(mapSize);
    game.Map[2][1] = 1;
    game.Map[2][2] = 1;
    game.Map[2][3] = 1;

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
    for (uint8_t i = 0; i < mapSize; ++i) {
        for (uint8_t j = 0; j < mapSize; ++j) {
            QCOMPARE(game.Map[i][j], resultArray[i][j]);
        }
    }
}

void SelfTesting::calculateNewGeneration_Oscillators_Beacon()
{
    // assign
    const uint16_t mapSize = 6;
    GameOfLife game(mapSize);

    game.Map[1][4] = 1;
    game.Map[1][3] = 1;
    game.Map[2][4] = 1;
    game.Map[2][3] = 1;

    game.Map[3][2] = 1;
    game.Map[3][1] = 1;
    game.Map[4][2] = 1;
    game.Map[4][1] = 1;

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
    for (uint8_t i = 0; i < mapSize; ++i) {
        for (uint8_t j = 0; j < mapSize; ++j) {
            QCOMPARE(game.Map[i][j], resultArray[i][j]);
        }
    }
}

void SelfTesting::calculateNewGeneration_Spaceships_Glinder()
{
    // assign
    const uint16_t mapSize = 5;
    GameOfLife game(mapSize);

    game.Map[1][2] = 1;
    game.Map[2][0] = 1;
    game.Map[2][2] = 1;
    game.Map[3][1] = 1;
    game.Map[3][2] = 1;

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
    for (uint8_t i = 0; i < mapSize; ++i) {
        for (uint8_t j = 0; j < mapSize; ++j) {
            QCOMPARE(game.Map[i][j], resultArray[i][j]);
        }
    }
}
