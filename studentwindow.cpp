#include "studentwindow.h"
#include "ui_studentwindow.h"
#include<QWidget>
studentwindow::studentwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentwindow)
{
    ui->setupUi(this);
}

studentwindow::~studentwindow()
{
    delete ui;
}
