#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <math.h>
#include <iostream>
#include "signal.h"

float alpha;
float beta;
float gamma;
double cX;
double cY;
int keyPressed;
double scaleArray[]{};
QPoint mousePoint = QPoint(1,1);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mousePoint = QPoint(this->width(),this->height());
    setMouseTracking(true);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
   this->setMouseTracking(true);
   mousePoint = event->pos();
   cX =  mousePoint.x()/ ((double)this->width());
   cY =  mousePoint.y() / ((double)this->height());
   update();
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
    if (event->delta() > 0 && keyPressed == Qt::Key_Shift)
    {
        alpha += 1 - cX;
    }
    else if (event->delta() < 0 && keyPressed == Qt::Key_Shift)
    {
        alpha -= 1 - cX;
    }
    else if (event->delta() > 0 && keyPressed == Qt::Key_Control)
    {
        gamma += cX;
    }
    else if (event->delta() < 0 && keyPressed == Qt::Key_Control)
    {
        gamma -= cX;
    }
    else if (event->delta() > 0)
    {
         beta += 1 + cY;
    }
    else if (event->delta() < 0)
    {
        beta -= 1 - cY;
    }
    this->update();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    keyPressed = event->key();
    this->update();
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    keyPressed = Qt::Key_unknown;
    this->update();
}

void MainWindow::graph()
{
    auto signal = new Signal(500);
        signal->generate_sine(100.0, 2.0);
        auto scaleArray = signal->values;
    if (alpha == 0)
        alpha = this->width() / signal->signal_size;
    if (beta == 0)
        beta = 120;
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(50 + gamma * 5,this->height() - 50,50 + gamma * 5,50);
    painter.drawLine(50 + gamma * 5,this->height() / 2,this->width()- 50,this->height()  /2);
    for (int i = 50; i < this->width(); i += alpha)
    {
        if (alpha < 3)
        {
            alpha = 3;
        }
        if (i < this->width() - 50)
        {
            auto y1 = this->height() / 2 + 5 ;
            auto y2 = this->height() / 2 - 5 ;
            if (i > 50)
            {
              painter.drawLine(i + gamma * 5, y1, i + gamma * 5, y2);
            }
        }
    }
    for (int i = this -> height() / 2 - beta; i > 50; i -= beta )
    {
        auto index = i;
        painter.drawLine(45 + gamma * 5, index, 55 +gamma * 5,index);
    }
    for (int i = this->height() / 2 + beta; i < this->height(); i += beta )
    {
       auto indexer = i ;
       painter.drawLine(45 + gamma * 5 ,indexer ,55 + gamma * 5,indexer);
    }
    for (int i = 0; i < signal->signal_size - 1; i++)
    {
        auto eWidth = 8;
        painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(50 + i * alpha + gamma * 5,this->height() / 2 - scaleArray[i] * beta,50 + (i + 1) * alpha + gamma * 5,this->height() / 2 - scaleArray[i+1] * beta);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(50 + i * alpha + gamma * 5 - eWidth/2,this->height() / 2 - scaleArray[i] * beta   - eWidth/2,eWidth,eWidth);
    }
    for (int i = 0; i < signal->signal_size - 1; i+= 5)
    {
        auto eWidth = 8;
        painter.setPen(QPen(Qt::gray, 1, Qt::DotLine, Qt::FlatCap));
        painter.drawLine(50 + i * alpha + gamma * 5,this->height() / 2 - scaleArray[i] * beta,50 + i * alpha + gamma * 5,this->height() / 2);
        painter.setPen(QPen(Qt::darkMagenta, 1, Qt::SolidLine, Qt::FlatCap));
        if(i != 0) painter.drawText(50 + i * alpha + gamma * 5,this->height() / 2 +50,QString::number(i));
    }
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawEllipse(mousePoint,2,2);
}

void MainWindow::paintEvent(QPaintEvent*)
{
    graph();
}
