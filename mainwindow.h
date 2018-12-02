#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"teacher.h"
#include"student.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeStudent();
    void changeTeacher();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    student *sw;
    teacher *tw;
};

#endif // MAINWINDOW_H
