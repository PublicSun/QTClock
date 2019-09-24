#include "clockwidget.h"
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include "../../common/comm.h"

ClockWidget::ClockWidget(QWidget *parent) : QWidget(parent){

    QTimer *timer=new QTimer(this);
    timer->start(1000); // 每次发射timeout信号时间间隔为1秒
    connect(timer,SIGNAL(timeout()),this,SLOT(showSS()));
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}
void ClockWidget::showSS(){
    if(StepNum<=354){
        StepNum=StepNum+Needle_Step;
    }else {
        StepNum=6;
        StepMM=StepMM+1;
        if(StepMM%6==0){
            StepHH=StepHH+1;
        }
    }
    if(StepMM>=60){
        StepMM=1;
    }
}
void ClockWidget::DrawMM(QPainter *painter){
    QPixmap pix_Needle(":/watch/watch/分针备份.png");
    painter->save();
    //设置新的圆心，其实也是旋转中心
    painter->translate(240, 400);
    //旋转一个角度
    painter->rotate(StepMM*6);
    //画指针，注意是在指针中心的反方向开始画
    painter->drawPixmap(-pix_Needle.size().width()/2,-200,pix_Needle.size().width(), pix_Needle.size().height(),pix_Needle);
    //使原点复原
    painter->restore();
}
void ClockWidget::DrawHH(QPainter *painter){
    QPixmap pix_Needle(":/watch/watch/时针.png");
    painter->save();
    //设置新的圆心，其实也是旋转中心
    painter->translate(240, 400);
    //旋转一个角度
    painter->rotate(StepHH*3);
    //画指针，注意是在指针中心的反方向开始画
    painter->drawPixmap(-pix_Needle.size().width()/2,-150,pix_Needle.size().width(), pix_Needle.size().height(),pix_Needle);
    //使原点复原
    painter->restore();
}
void ClockWidget::paintEvent(QPaintEvent *){
    showSS();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    //背景
    QPixmap qPix(":/watch/watch/时间背景.png");
    QSize pixSize=qPix.size();
    QPointF  pointPix(0,0);
    painter.drawPixmap(pointPix,qPix,rect());
    DrawMM(&painter);
    DrawHH(&painter);
    QPixmap qPix1(":/watch/watch/定针.png");
    QSize pixSize1=qPix1.size();
    QPointF  pointPix1(240-pixSize1.width()/2,400-pixSize1.height()/2);
    painter.drawPixmap(pointPix1,qPix1,rect());

    QPixmap pix_Needle(":/watch/watch/秒针备份.png");

    painter.save();
    //设置新的圆心，其实也是旋转中心
    painter.translate(240, 400);
    //旋转一个角度
    painter.rotate(StepNum);
    //画指针，注意是在指针中心的反方向开始画
    painter.drawPixmap(-pix_Needle.size().width()/2,-200,pix_Needle.size().width(), pix_Needle.size().height(),pix_Needle);
    //使原点复原
    painter.restore();

}


