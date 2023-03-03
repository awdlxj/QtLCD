#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtWidgets.h"
#include <qtimer.h>
#include <QKeyEvent>


class MyQtWidgets : public QMainWindow
{
    Q_OBJECT

public:
    MyQtWidgets(QWidget *parent = Q_NULLPTR);
    
protected:
    virtual void keyPressEvent(QKeyEvent* ev);

private slots:

     void on_commandLinkButton_clicked();
     void on_commandLinkButton_2_clicked();
     void on_commandLinkButton_3_clicked();
     void on_commandLinkButton_4_clicked();
     void handleTimeout();

     void slidermove();
     void slidermove2();
     void reset1();
     void reset2();
     
private:
    Ui::MyQtWidgetsClass ui;
};
