#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include<QSqlTableModel>
namespace Ui {
class teacher;
}

class teacher : public QWidget
{
    Q_OBJECT

public:
    explicit teacher(QWidget *parent = nullptr);
    ~teacher();
    void sendSignal();
    QSqlDatabase db;
signals:
    void mySignal();

private slots:
    void on_pushButtonreturn_clicked();

    void on_pushButtonexit_clicked();

    void on_pushButtonNum_clicked();

    void on_pushButtonName_clicked();

    void on_pushButtonAll_clicked();

    void on_pushButtoncancel_clicked();

    void on_pushButtonsure_clicked();

    void on_pushButtondelete_clicked();

    void on_pushButtonadd_clicked();

private:
    Ui::teacher *ui;
    QSqlTableModel *model;

};

#endif // TEACHER_H
