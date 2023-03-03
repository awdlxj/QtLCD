#include "MyQtWidgets.h"
#include <qtime>
#include <qstring.h>
#include <string.h>
#include "timer.h"
#include <QTimer>
#include <qmath.h>
#include <qtime>


using namespace std;

QString res;
double timenumber, timenumber2, beilv = 1;
long long timenum,timenum2,timerfreq;
int msec1, sec1, min1, hour1, day1;
char stop1 = 2;//0开始，1为暂停，2为停止
timer timer1, timer2;

QTimer* qtimer1 = new(QTimer);

QString fullnumber(long fullednum, long numofdig);

MyQtWidgets::MyQtWidgets(QWidget* parent)//初始化
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.dial->setValue(499);
    qtimer1->start(qPow(1.01, ui.dial->value()) / 20);

    beilv = qPow(1.01, ui.dial_2->value() - 500);
    ui.pushButton_2->setText("x" + QString::number(beilv, 'f', 3));

    ui.lcdNumber->setStyleSheet("background-color: grey");//背景颜色

    connect(qtimer1, SIGNAL(timeout()), this, SLOT(handleTimeout()));

    connect(ui.dial, SIGNAL(valueChanged(int)), this, SLOT(slidermove()));
    connect(ui.dial_2, SIGNAL(valueChanged(int)), this, SLOT(slidermove2()));
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(reset1()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(reset2()));
    

    ui.lcdNumber->setSegmentStyle(QLCDNumber::Flat);
}
    
//键盘按下触发事件
void MyQtWidgets::keyPressEvent(QKeyEvent* ev)
{
    if (ev->key() == Qt::Key_Enter)
    {
        if (stop1 != 0)
        {
            MyQtWidgets::on_commandLinkButton_clicked();
        }
        else
        {
            MyQtWidgets::on_commandLinkButton_2_clicked();
        }
        return;
    }

    QWidget::keyPressEvent(ev);
}


void MyQtWidgets::handleTimeout()//刷新LCD和标签
{
    double fps = 0;
    if (stop1 != 1)
    {
        if (stop1 == 2)
        {
            timenumber = 0;
        }
        else
        {
            timenumber = timer1.getthroughtime() + timenumber2;
        }
        timenum = timenumber * 10000000 * beilv;//0.1us步长
        msec1 = (timenum / 10000) % 1000;
        sec1 = (timenum / 10000000) % 60;
        min1 = (timenum / 600000000) % 60;
        hour1 = (timenum / 36000000000) % 24;
        day1 = timenum / 36000000000 / 24;
        

        if (timenumber * beilv >= 9*86400+23 * 3600 + 59 * 60 + 59 + 0.999)//溢出计算
        {
            msec1 = 999;
            sec1 = 59;
            min1 = 59;
            hour1 = 23;
            day1 = 9;
        }
        res = fullnumber(day1, 1) + ":" + fullnumber(hour1, 2) + ":" + fullnumber(min1, 2) + ":" + fullnumber(sec1, 2) + "." + fullnumber(msec1, 3);
        ui.lcdNumber->display(res);
    }
    else;


    ui.label->setText("<html><head/><body><p>RealTime: <span style=\" color:#ff0000; \">" + QString::number(timenumber, 'f', 7) + "</span> s</p></body></html>");
    ui.label_2->setText("<html><head/><body><p>TimerFrequency: <span style=\" color:#ff0000; \">" + QString::number(timerfreq, 'f', 2) + "</span> Hz</p></body></html>");

    if (stop1 == 0)//设置对应状态的颜色
    {
        QPalette lcdpat = ui.lcdNumber->palette();//颜色
        lcdpat.setColor(QPalette::Normal, QPalette::WindowText, Qt::green);//设置LCD文字颜色
        ui.lcdNumber->setPalette(lcdpat);
    }
    else if (stop1 == 1)
    {
        QPalette lcdpat = ui.lcdNumber->palette();//颜色
        lcdpat.setColor(QPalette::Normal, QPalette::WindowText, Qt::yellow);//设置LCD文字颜色
        ui.lcdNumber->setPalette(lcdpat);
    }
    else
    {
        QPalette lcdpat = ui.lcdNumber->palette();//颜色
        lcdpat.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);//设置LCD文字颜色
        ui.lcdNumber->setPalette(lcdpat);
    }

    fps = 1.0 / timer2.endtimer();
    timer2.starttimer();
    ui.label_3->setText("<html><head/><body><p>DisplayFlashFrequency: <span style=\" color:#ff0000; \">" + QString::number(fps, 'f', 2) + "</span> FPS</p></body></html>");
    ui.label_4->setText("<html><head/><body><p>DisplayFlashTime: <span style=\" color:#ff0000; \">" + QString::number(1000.0 / fps, 'f', 3) + "</span> ms</p></body></html>");

}

void MyQtWidgets::on_commandLinkButton_clicked()//开始计时
{
    stop1 = 0;
    timenumber2 = 0;
    timerfreq = timer1.gettimerfreq();
    timer2.gettimerfreq();
    timer1.starttimer();
    qtimer1->start(qPow(1.01,ui.dial->value())/20);
}
void MyQtWidgets::on_commandLinkButton_2_clicked()//暂停
{
    stop1 = 1;
    timenumber2 = timenumber;//记录中间时间

}
void MyQtWidgets::on_commandLinkButton_3_clicked()//停止
{
    stop1 = 2;
    timenumber2 = 0;
    timenumber = 0;
    timer1.endtimer();
}
void MyQtWidgets::on_commandLinkButton_4_clicked()
{
    stop1 = 2;
    timenumber2 = 0;
    timenumber = 0;
    timer1.endtimer();//停止

    QTime current_time = QTime::currentTime();

    stop1 = 0;
    timerfreq = timer1.gettimerfreq();
    timer2.gettimerfreq();
    timer1.starttimer();
    qtimer1->start(qPow(1.01, ui.dial->value()) / 20);

    ui.dial_2->setValue(500);
    ui.dial_2->setSliderPosition(500);

    timenumber2 = current_time.msec() / 1000.0 + current_time.second() + current_time.minute() * 60.0 + current_time.hour() * 3600;

}

void MyQtWidgets::slidermove()//
{
    double tmp = qPow(1.01, ui.dial->value()) / 20;
    qtimer1->start(tmp);
    if (ui.dial->value() == 0)
    {
        ui.pushButton->setText("-- FPS");
    }
    else
    {
        ui.pushButton->setText(QString::number(1000.0 / tmp, 'f', 2) + " FPS");
    }
    
}
void MyQtWidgets::slidermove2()//
{
    beilv = qPow(1.01, ui.dial_2->value() - 500);
    ui.pushButton_2->setText("x" + QString::number(beilv, 'f', 3));

}
void MyQtWidgets::reset1()
{
    ui.dial->setValue(499);
    ui.dial->setSliderPosition(499);
}
void MyQtWidgets::reset2()
{
    ui.dial_2->setValue(500);
    ui.dial_2->setSliderPosition(500);
}
QString fullnumber(long fullednum, long numofdig)//填充0
{
    QString tmp = QString::number(fullednum);
    while (tmp.length() < numofdig)
    {
        tmp = "0" + tmp;
    }
    return tmp;

}
