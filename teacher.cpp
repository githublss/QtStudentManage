#include "teacher.h"
#include "ui_teacher.h"
#include"teacher.h"
#include"mainwindow.h"

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

//     QSqlQuery select;
//     select.exec("select * from student;");
//     select.next();
//     qDebug()<< select.value(0).toString()
//             <<select.value(1).toString()
//             <<select.value(2).toString()
//             <<select.value(3).toString();
     model = new QSqlTableModel(this);
     model->setTable("student");
     model->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置model的修改模式

     //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers) //取消提交模式
     ui->tableView->setModel(model);
     model->select();

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
}

void teacher::on_pushButtoncancel_clicked()
{
    model->revertAll();
    model->submitAll();
}

void teacher::on_pushButtonsure_clicked()   //提交修改
{
    model->submitAll();
}

void teacher::on_pushButtondelete_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();  //获取选中的model
    QModelIndexList list = select->selectedIndexes();   //选中的行的索引
    for(int i=0;i<list.size();i++){
        model->removeRow(list.at(i).row());
    }
    QMessageBox::information(this, QStringLiteral("警告！"),QStringLiteral("删除须谨慎，点确定将成真！！"));
}

void teacher::on_pushButtonadd_clicked()
{
    QSqlRecord record = model->record();    //获取空记录
    int row = model->rowCount();            //获取行数
    model->insertRecord(row,record);        //进行添加
}
