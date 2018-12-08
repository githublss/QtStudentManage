#include "teacher.h"
#include "ui_teacher.h"
#include"teacher.h"
#include"mainwindow.h"
#include"globle.h"

#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QSqlRecord>
#include<QItemSelectionModel>
#include<QModelIndexList>
#include<QMessageBox>
#include<QTextCodec>
#include<QString>

teacher::teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacher)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("设计者：s180201033李赛赛"));
    connect(ui->pushButtonreturn,&QPushButton::clicked,this, &teacher::sendSignal);

     if(QSqlDatabase::contains("qt_sql_default_connection"))
         db = QSqlDatabase::database("qt_sql_default_connection");
     else{
//         db = QSqlDatabase::addDatabase("QMYSQL");
//         db.setHostName("127.0.0.1");
//         db.setDatabaseName("studentmanager");
//         db.setUserName("root");
//         db.setPassword("");
         QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
         db.setDatabaseName("../info.db");
     }

     if(!db.open())  //mysql的动态链接库库要手动下载到Qt的bin目录下，不然无法进行连接
     {
         QMessageBox::warning(this, "error", db.lastError().text());
     }

     model = new QSqlTableModel(this);
     model->setTable("student");
     model->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置model的修改模式
     ui->labelReallyName->setText(username_qj);

     //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers) //取消提交模式
     ui->tableView->setModel(model);
     model->select();
     model->setHeaderData(0, Qt::Horizontal, QStringLiteral("学号"));
     model->setHeaderData(1, Qt::Horizontal, QStringLiteral("姓名"));
     model->setHeaderData(2, Qt::Horizontal, QStringLiteral("性别"));
     model->setHeaderData(3, Qt::Horizontal, QStringLiteral("年龄"));
     model->setHeaderData(4, Qt::Horizontal, QStringLiteral("专业"));
     model->setHeaderData(5, Qt::Horizontal, QStringLiteral("班级"));
     model->setHeaderData(6, Qt::Horizontal, QStringLiteral("地址"));
     model->setHeaderData(7, Qt::Horizontal, QStringLiteral("电话"));
     model->setHeaderData(8, Qt::Horizontal, QStringLiteral("职务"));
     model->setHeaderData(9, Qt::Horizontal, QStringLiteral("密码"));
     model->setHeaderData(10, Qt::Horizontal, QStringLiteral("奖赏"));
     model->setHeaderData(11, Qt::Horizontal, QStringLiteral("惩罚"));

}

teacher::~teacher()
{
    delete ui;
}

void teacher::sendSignal(){
    emit mySignal();
}

void teacher::on_pushButtonreturn_clicked()
{
    MainWindow *dh;
    this->hide();
    dh=new MainWindow  ;

    dh->show();
}

void teacher::on_pushButtonexit_clicked()
{
    this->close();
}

void teacher::on_pushButtonNum_clicked()
{
    QString number = ui->lineEdit->text();
    QString str = QString("id = '%1'").arg(number);

    model->setFilter(str);
    model->select();
}

void teacher::on_pushButtonName_clicked()
{
    QString name = ui->lineEdit->text();
    QString str = QString("name = '%1'").arg(name);

    model->setFilter(str);
    model->select();
}

void teacher::on_pushButtonAll_clicked()
{
    model->setTable("student");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("学号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("姓名"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("性别"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("年龄"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("专业"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("班级"));
    model->setHeaderData(6, Qt::Horizontal, QStringLiteral("地址"));
    model->setHeaderData(7, Qt::Horizontal, QStringLiteral("电话"));
    model->setHeaderData(8, Qt::Horizontal, QStringLiteral("职务"));
    model->setHeaderData(9, Qt::Horizontal, QStringLiteral("密码"));
    model->setHeaderData(10, Qt::Horizontal, QStringLiteral("奖赏"));
    model->setHeaderData(11, Qt::Horizontal, QStringLiteral("惩罚"));
}

void teacher::on_pushButtoncancel_clicked()
{
    model->revertAll();
    model->submitAll();
}

void teacher::on_pushButtonsure_clicked()   //提交修改
{
    model->database().transaction();    //开启事务
    if(model->submitAll())
    {
        model->database().commit();
    }
    else
    {
        model->database().rollback();   //提交过程中一旦出错进行回滚
        QMessageBox::warning(this, tr("tableModel"),QStringLiteral("数据库错误: %1").arg(model->lastError().text()));
    }
}

void teacher::on_pushButtondelete_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();  //获取选中的model
    QModelIndexList list = select->selectedIndexes();   //选中的行的索引
    for(int i=0;i<list.size();i++){
        model->removeRow(list.at(i).row());
    }
    //QMessageBox::information(this, QStringLiteral("警告！"),QStringLiteral("删除须谨慎，点确定将成真！！"));
    int ok = QMessageBox::warning(this,QStringLiteral("删除选中的行!"),QStringLiteral("你确定删除当前选取中的行吗?"),QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        model->submitAll(); //提交，在数据库中删除该行
    } else {
        model->revertAll(); //如果不删除，则撤销
    }
}

void teacher::on_pushButtonadd_clicked()
{
    QSqlRecord record = model->record();    //获取空记录
    int row = model->rowCount();            //获取行数
    model->insertRecord(row,record);        //进行添加
}
