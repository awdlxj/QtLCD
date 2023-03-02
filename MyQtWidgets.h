#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtWidgets.h"
#include <qtimer.h>

class MyQtWidgets : public QMainWindow
{
    Q_OBJECT

public:
    MyQtWidgets(QWidget *parent = Q_NULLPTR);
    

private slots:

     void on_commandLinkButton_clicked();
     void on_commandLinkButton_2_clicked();
     void on_commandLinkButton_3_clicked();
     
     void handleTimeout();

     void slidermove();

private:
    Ui::MyQtWidgetsClass ui;
};
