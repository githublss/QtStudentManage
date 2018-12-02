#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"globle.h"

#include<QPixmap>
#include<QString>
#include<QRadioButton>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlError>
#include<QtDebug>
#include"student.h"
#include"teacher.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->labeltitle->show();
//    ui->labelNum->show();
//    ui->lineEditNum->text();
    setWindowTitle(QStringLiteral("设计者：s180201033李赛赛"));
    //设置logo
    QPixmap pixmap = QPixmap("://image/school.png");
    QPixmap fitpixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation); //logo大小自动匹配
//    ui->labelImage->setPixmap(QPixmap("://image/school.png"));
    ui->labelImage->setPixmap(fitpixmap);
    ui->lineEditPass->setEchoMode(QLineEdit::Password);
    ui->radioButtonstu->setChecked(true);   //默认选择学生


    ui->labelImage->setScaledContents(true);
    //connect(sw, &student::mySignal,this,&MainWindow::changeStudent);   //从学生端返回
    //connect(tw, &teacher::mySignal,this,&MainWindow::changeTeacher);   //从老师端返回

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStudent(){
    this->show();
    sw->hide();
}

void MainWindow::changeTeacher(){
    this->show();
    tw->hide();
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEditNum->text();
    QString password = ui->lineEditPass->text();
    if(username==""||password==""){
        QMessageBox::information(this, QStringLiteral("警告！"),QStringLiteral("请按照格式正确填写用户名，密码！！"));
        QString username = ui->lineEditNum->text();

        QString password = ui->lineEditPass->text();

    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("studentmanager");
    db.setUserName("root");
    db.setPassword("");


    if(!db.open())  //mysql的动态链接库库要手动下载到Qt的bin目录下，不然无法进行连接
    {
        QMessageBox::warning(this, "error", db.lastError().text());
    }
    bool in=false;
    if(ui->radioButtonTea->isChecked()){
        QSqlQuery select;
        QString sql = QString("select * from admin where username = '%1' and password='%2';").arg(username,password);
//        qDebug()<<sql;

        in = select.exec(sql);

        if(select.next()){
//            qDebug()<<"go to teacher";
            //db.removeDatabase(db.connectionName());
            tw = new teacher;   //此处有一个数据库连接的大坑
            username_qj = username;
            password_qj = password;
            this->hide();
            this->tw->show();

        }
        else{
            QMessageBox::information(this, QStringLiteral("警告！"),QStringLiteral("用户名或密码有误！！！"));
        }


    }
    if(ui->radioButtonstu->isChecked()){
        QSqlQuery select;
        QString sql = QString("select * from student where name = '%1' and password='%2';").arg(username,password);
//        qDebug()<<sql;

        in =select.exec(sql);

        if(select.next()){
            db.removeDatabase(db.connectionName());
//            qDebug()<<"go to student";
            this->hide();
            username_qj = username;
            password_qj = password;
            sw = new student;   //此处有一个数据库连接的大坑
            this->sw->show();
        }
        else{
            QMessageBox::information(this, QStringLiteral("警告！"),QStringLiteral("用户名或密码有误！！！"));
        }

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}
