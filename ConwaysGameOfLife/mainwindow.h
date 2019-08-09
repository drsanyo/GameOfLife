#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <gameoflife.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    QTimer *timer;

    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void on_btnStart_clicked();

    void on_sbScale_valueChanged(int arg1);

    void OnTimerEvent();

    void on_sbMapSize_valueChanged(int arg1);

    void on_hsSpeed_valueChanged(int value);

    void on_btnRecreateMap_clicked();

private:
    Ui::MainWindow *ui;

    GameOfLife gameOfLife;
    uint scale = 7;
    uint border = 20;

    void RefreshSpeedValue();
    void StartTimerAtCurrentSpeed();
    QPoint MousePositionToMapPosition(QPoint p);
    void InvertMapCell(QPoint p);
};





#endif // MAINWINDOW_H
