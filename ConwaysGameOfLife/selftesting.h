#ifndef SELFTESTING_H
#define SELFTESTING_H

#include <QDialog>
#include <QtTest>

namespace Ui {
class SelfTesting;
}

class SelfTesting : public QDialog
{
    Q_OBJECT

public:
    explicit SelfTesting(QWidget *parent = nullptr);
    ~SelfTesting();    

private:
    Ui::SelfTesting *ui;
    QString testsResultFileName = "QTestString_log.txt";

    void loadTestResults();

    void runTests();

public slots:
/*
 * private slots are "reserved" for tests, so use public ;(
*/
    void on_btnRunTests_clicked();    

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

#include "selftesting.moc"

#endif // SELFTESTING_H
