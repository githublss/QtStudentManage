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

    //添加Sqlite数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库
    db.setDatabaseName("../info.db");

    //打开数据库
    if( !db.open() ) //数据库打开失败
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }
    //对数据库进行初始化
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS `admin`;");
    query.exec("CREATE TABLE `admin` (`id` int(11) NOT NULL DEFAULT '0',`username` text,`password` text,PRIMARY KEY (`id`));");
    query.exec("INSERT INTO `admin` VALUES ('1', 'admin', 'admin');");
    query.exec("INSERT INTO `admin` VALUES ('2', 'admin2', 'admin2');");
    query.exec("DROP TABLE IF EXISTS `student`;");

    query.exec("CREATE TABLE `student` ("
                 "`id` text NOT NULL,"        //学号
                 "`name` text,"                     //姓名
                 "`sex` text,"                      //性别
                 "`age` text,"                      //年龄
                 "`major` text,"                    //专业
                 "`banji` int(11) DEFAULT NULL,"    //班级
                 "`address` text,"                   //地址
                 "`phonenumber` text,"
                 "`beizhu` text,"                       //
                 "`password` text DEFAULT '123456'," //密码
                 "`award` text DEFAULT '无',"    //奖励
                 "`punish` text DEFAULT '无',"   //处罚
                 "PRIMARY KEY (`id`)"
               ");");
    query.exec(QStringLiteral("INSERT INTO `student` VALUES ('1000', '张三', '男', '19', '计科', '162', '上海', '15925637846', '学生', '123456', '无', '记过');"));
    query.exec(QStringLiteral("INSERT INTO `student` VALUES ('1001', '李四', '男', '18', '软件工程', '164', '广东', '14667344366', '学生', '123456', '数学竞赛一等奖', '无');"));
    query.exec(QStringLiteral("INSERT INTO `student` VALUES ('1004', '小李', '女', '19', '信息安全', '161', '广东', '18138494848', '体委', '123456', '运动会跳远第一', '无');"));
    query.exec(QStringLiteral("INSERT INTO `student` VALUES ('1007', '路人乙', '女', '18', '土木工程', '164', '河南', '13545665788', '学委', '123456', '学习积极分子', '无');"));
    query.exec(QStringLiteral("INSERT INTO `student` VALUES ('1008', '路人甲', '男', '18', '网络工程', '163', '上海', '15029389209', '班长', '123456',  '先进班干部', '无');"));
    query.exec(QStringLiteral("INSERT INTO `student` VALUES ('180201033', '李赛', '男', '19', '计算机', '163', '北京', '18170874213', '学生', '123456', '物理竞赛一等奖', '无');"));

    db.close();
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
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("127.0.0.1");
//    db.setDatabaseName("studentmanager");
//    db.setUserName("root");
//    db.setPassword("");

    //为了调试的方便使用了Sqlite数据库来替代MySQL数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库
    db.setDatabaseName("../info.db");

    //打开数据库
    if( !db.open() ) //数据库打开失败
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }

    if(!db.open())  //mysql的动态链接库库要手动下载到Qt的bin目录下，不然无法进行连接
    {
        QMessageBox::warning(this, "error", db.lastError().text());
    }
    bool in=false;
    if(ui->radioButtonTea->isChecked()){    //进入老师模块
        QSqlQuery select;
        QString sql = QString("select * from admin where username = '%1' and password='%2';").arg(username,password);
        in = select.exec(sql);

        if(select.next()){
//            qDebug()<<"go to teacher";

            this->hide();

            username_qj = username;
            password_qj = password;

            tw = new teacher;   //此处有一个数据库连接的大坑
            this->tw->show();

        }
        else{
            QMessageBox::information(this, QStringLiteral("警告！"),QStringLiteral("用户名或密码有误！！！"));
        }


    }
    if(ui->radioButtonstu->isChecked()){    //进入学生模块
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
