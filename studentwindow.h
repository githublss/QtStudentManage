#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDockWidget>

namespace Ui {
class studentwindow;
}

class studentwindow : public QWidget
{
    Q_OBJECT

public:
    explicit studentwindow(QWidget *parent = nullptr);
    ~studentwindow();

private:
    Ui::studentwindow *ui;
};

#endif // STUDENTWINDOW_H
