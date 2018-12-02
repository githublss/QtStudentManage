#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include<QSqlTableModel>
namespace Ui {
class student;
}

class student : public QWidget
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = nullptr);
    ~student();
    void sendSignal();
    QSqlDatabase db;

signals:
    void mySignal();

private slots:
    void on_pushButtonreturn_clicked();

    void on_pushButtonquit_clicked();

    void on_pushButtonupdate_clicked();

    void on_pushButtonsure_clicked();

    void on_pushButtoncancel_clicked();


private:
    Ui::student *ui;
    QSqlTableModel *model;

};

#endif // STUDENT_H
