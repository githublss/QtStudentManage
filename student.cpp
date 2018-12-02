#include "student.h"
#include "ui_student.h"
#include"student.h"
#include"mainwindow.h"
#include"globle.h"
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlError>
#include<QtDebug>

#include<QString>
#include<QSqlTableModel>
#include<QSqlRecord>
#include<QItemSelectionModel>
#include<QModelIndexList>
#include<QMessageBox>
#include<QTextCodec>
#include<QString>

student::student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::student)
{
    ui->setupUi(this);
    connect(ui->pushButtonreturn,&QPushButton::clicked,this, &student::sendSignal);//返回主页
    setWindowTitle(QStringLiteral("设计者：s180201033李赛赛"));
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else{
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("studentmanager");
        db.setUserName("root");
        db.setPassword("");
    }

    if(!db.open())  //mysql的动态链接库库要手动下载到Qt的bin目录下，不然无法进行连接
    {
        QMessageBox::warning(this, "error", db.lastError().text());
    }

//    QSqlQuery select;
//    select.exec("select * from student;");
//    select.next();
//    qDebug()<< select.value(0).toString()
//            <<select.value(1).toString()
//            <<select.value(2).toString()
//            <<select.value(3).toString();
    model = new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置model的修改模式
    ui->labelReallyName->setText(username_qj);
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers) //取消提交模式
    ui->tableView->setModel(model);

    QString str = QString("name = '%1'").arg(username_qj);

    model->setFilter(str);  //只显示本学生的信息
    model->select();
}

student::~student()
{
    delete ui;
}

void student::sendSignal(){
    emit mySignal();
}

void student::on_pushButtonreturn_clicked()
{
    MainWindow *dh;
    this->hide();
    dh=new MainWindow  ;

    dh->show();
}

void student::on_pushButtonquit_clicked()
{
    this->close();
}

void student::on_pushButtonupdate_clicked()
{
    QMessageBox::information(this, QStringLiteral("警告！"),QStringLiteral("直接在表上操作即可！！"));
}

void student::on_pushButtonsure_clicked()
{
    model->submitAll();
}

void student::on_pushButtoncancel_clicked()
{
    model->revertAll();
    model->submitAll();
}
