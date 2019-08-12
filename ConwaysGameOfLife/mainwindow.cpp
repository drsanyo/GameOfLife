#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selftesting.h"
#include <string>
#include <QTimer>
#include <QMouseEvent>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->installEventFilter(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(OnTimerEvent()));

    gameOfLife.mapSize(uint16_t(ui->sbMapSize->value()));
    gameOfLife.ConnectCalculationsToThread(calculationThread);
    gameOfLife.moveToThread(&calculationThread);

    RefreshSpeedValue();
    scale = uint(ui->sbScale->value());
}

MainWindow::~MainWindow()
{
    calculationThread.wait();
    delete ui;    
}

void MainWindow::on_btnStart_clicked()
{
    if (ui->btnStart->text() == "Start"){
        StartTimerAtCurrentSpeed();
        ui->btnStart->setText("Stop");
    }
    else {
        timer->stop();
        ui->btnStart->setText("Start");
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    uint16_t mapSize = gameOfLife.mapSize();
    QPainter painter(this);
    for (uint i = 0; i < mapSize; ++i)
        for (uint j = 0; j < mapSize; ++j){
            if (gameOfLife.Map[i][j] == 1){
                painter.setBrush(Qt::SolidPattern);
            }
            else {
                painter.setBrush(Qt::NoBrush);
            }            
            painter.drawRect(QRect(
                                 ui->gbControls->width() + int(border) + int(i) * int(scale),
                                 ui->menuBar->height() + int(border)+int(j)*int(scale),
                                 int(scale),
                                 int(scale)));
        }   
}

void MainWindow::on_sbScale_valueChanged(int arg1)
{
    scale = uint(arg1);
    this->repaint();
}

void MainWindow::OnTimerEvent()
{
    calculationThread.start();
    calculationThread.quit();
    this->repaint();
}

void MainWindow::on_sbMapSize_valueChanged(int arg1)
{
    bool timerOldState= timer->isActive();
    timer->stop();
    gameOfLife.mapSize(uint16_t(arg1));    
    gameOfLife.initialiseGameMap();
    if (timerOldState){
        StartTimerAtCurrentSpeed();
    }
    this->repaint();
}

void MainWindow::on_hsSpeed_valueChanged(int *)
{
    bool timerOldState= timer->isActive();
    timer->stop();
    if (timerOldState){
        StartTimerAtCurrentSpeed();
    }
    RefreshSpeedValue();
}

void MainWindow::on_btnRecreateMap_clicked()
{
    gameOfLife.initialiseGameMap();
    this->repaint();
}

void MainWindow::RefreshSpeedValue()
{
    ui->lbSpeedVisual->setText(QString::number(double(ui->hsSpeed->value()) / double(ui->hsSpeed->maximum()) * 100));
}

void MainWindow::StartTimerAtCurrentSpeed()
{
    timer->start(ui->hsSpeed->maximum()/ui->hsSpeed->value());
}

void MainWindow::InvertMapCell(QPoint p)
{
    if ((p.x()<gameOfLife.mapSize() && p.y()<gameOfLife.mapSize()) && ((p.x() >= 0) && (p.y()>= 0)))
    {
        if (gameOfLife.Map[uint8_t(p.x())][uint8_t(p.y())] == 1) {
            gameOfLife.Map[uint8_t(p.x())][uint8_t(p.y())] = 0;
        }else{
            gameOfLife.Map[uint8_t(p.x())][uint8_t(p.y())] = 1;
        }
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* me = static_cast<QMouseEvent *>( event );
        const QPoint point = MousePositionToMapPosition(me->pos());
        InvertMapCell(point);
        this->repaint();       
    }
    return QMainWindow::eventFilter(watched, event);
}

QPoint MainWindow::MousePositionToMapPosition(QPoint p)
{
    const QPoint result(
        (p.x() - ui->gbControls->width() - int(border)) / int(scale),
        (p.y() - ui->menuBar->height() - int(border)) / int(scale));
    return result;
}


void MainWindow::on_actionSelf_Testing_triggered()
{
    SelfTesting selfTetsingWindow;
    selfTetsingWindow.setModal(true);
    selfTetsingWindow.exec();
}
