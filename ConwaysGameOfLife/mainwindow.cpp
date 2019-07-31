#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QTimer>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->installEventFilter(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(OnTimerEvent()));

    gameOfLife.mapSize(uint16_t(ui->sbMapSize->value()));    

    RefreshSpeedValue();
    scale = uint(ui->sbScale->value());
}

MainWindow::~MainWindow()
{
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
    QPainter painter(this);
    for (uint i = 0; i < gameOfLife.mapSize(); ++i)
        for (uint j = 0; j < gameOfLife.mapSize(); ++j){
            if (gameOfLife.map()[i][j] == 1){
                painter.setBrush(Qt::SolidPattern);
            }
            else {
                painter.setBrush(Qt::NoBrush);
            }            
            painter.drawRect(QRect(ui->gbControls->width() + int(border) + int(i) * int(scale), int(border)+int(j)*int(scale), int(scale), int(scale)));
        }
}

void MainWindow::on_sbScale_valueChanged(int arg1)
{
    scale = uint(arg1);
    this->repaint();
}

void MainWindow::OnTimerEvent()
{
    gameOfLife.calculateNewGeneration();
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

void MainWindow::on_hsSpeed_valueChanged(int value)
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
    if (p.x()<gameOfLife.mapSize() && p.y()<gameOfLife.mapSize())
    {
        if (gameOfLife.map()[p.x()][p.y()] == 1) {
            gameOfLife.map()[p.x()][p.y()] = 0;
        }else{
            gameOfLife.map()[p.x()][p.y()] = 1;
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
        (p.y() - int(border)) / int(scale));
    return result;
}

