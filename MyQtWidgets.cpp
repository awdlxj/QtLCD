#include "MyQtWidgets.h"
#include <qtime>
#include <qstring.h>
#include <string.h>
#include "timer.h"
#include <QTimer>
#include <qmath.h>

using namespace std;

QString res;
double timenumber, timenumber2;
long timenum,timenum2,timerfreq;
int msec1, sec1, min1, hour1;
char stop1 = 2;//0��ʼ��1Ϊ��ͣ��2Ϊֹͣ
timer timer1, timer2;

QTimer* qtimer1 = new(QTimer);

QString fullnumber(int fullednum, int numofdig);

MyQtWidgets::MyQtWidgets(QWidget* parent)//��ʼ��
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.dial->setValue(499);
    qtimer1->start(qPow(1.01, ui.dial->value()) / 20);

    ui.lcdNumber->setStyleSheet("background-color: black");//������ɫ

    connect(qtimer1, SIGNAL(timeout()), this, SLOT(handleTimeout()));

    connect(ui.dial, SIGNAL(valueChanged(int)), this, SLOT(slidermove()));
    
}
    

void MyQtWidgets::handleTimeout()//ˢ��LCD�ͱ�ǩ
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
        timenum = timenumber * 10000000;//0.1us����
        msec1 = (timenum / 10000) % 1000;
        sec1 = (timenum / 10000000) % 60;
        min1 = (timenum / 600000000) % 60;
        hour1 = timenum / 3600000000;
        res = ":" + fullnumber(hour1, 2) + ":" + fullnumber(min1, 2) + ":" + fullnumber(sec1, 2) + "." + fullnumber(msec1, 3);

        ui.lcdNumber->display(res);
    }
    else;


    ui.label->setText("RealTime: " + QString::number(timenumber, 'f', 7) + " s");
    ui.label_2->setText("TimerFrequency: " + QString::number(timerfreq, 'f', 2) + " Hz");

    if (stop1 == 0)//���ö�Ӧ״̬����ɫ
    {
        QPalette lcdpat = ui.lcdNumber->palette();//��ɫ
        lcdpat.setColor(QPalette::Normal, QPalette::WindowText, Qt::green);//����LCD������ɫ
        ui.lcdNumber->setPalette(lcdpat);
    }
    else if (stop1 == 1)
    {
        QPalette lcdpat = ui.lcdNumber->palette();//��ɫ
        lcdpat.setColor(QPalette::Normal, QPalette::WindowText, Qt::yellow);//����LCD������ɫ
        ui.lcdNumber->setPalette(lcdpat);
    }
    else
    {
        QPalette lcdpat = ui.lcdNumber->palette();//��ɫ
        lcdpat.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);//����LCD������ɫ
        ui.lcdNumber->setPalette(lcdpat);
    }

    fps = 1.0 / timer2.endtimer();
    timer2.starttimer();
    ui.label_3->setText("DisplayFashFrequency: " + QString::number(fps, 'f', 2) + " FPS");
    ui.label_4->setText("DisplayFlashTime: " + QString::number(1000.0 / fps, 'f', 3) + " ms");

}

void MyQtWidgets::on_commandLinkButton_clicked()//��ʼ��ʱ
{
    stop1 = 0;
    timerfreq = timer1.gettimerfreq();
    timer2.gettimerfreq();
    timer1.starttimer();
    qtimer1->start(qPow(1.01,ui.dial->value())/20);
}
void MyQtWidgets::on_commandLinkButton_2_clicked()//��ͣ
{
    stop1 = 1;
    timenumber2 = timenumber;//��¼�м�ʱ��

}
void MyQtWidgets::on_commandLinkButton_3_clicked()//ֹͣ
{
    stop1 = 2;
    timenumber2 = 0;
    timenumber = 0;
    timer1.endtimer();
}
void MyQtWidgets::slidermove()//
{
    qtimer1->start(qPow(1.01, ui.dial->value())/20);
}
QString fullnumber(int fullednum, int numofdig)//���0
{
    QString tmp = QString::number(fullednum);
    while (tmp.length() < numofdig)
    {
        tmp = "0" + tmp;
    }
    return tmp;

}
