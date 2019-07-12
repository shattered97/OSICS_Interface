#ifndef N7714AWINDOW_H
#define N7714AWINDOW_H
#include "Worker.h"
#include <QWidget>

namespace Ui {
class n7714awindow;
}

class n7714awindow : public QWidget
{
    Q_OBJECT

public:
    explicit n7714awindow(Worker *worker, QWidget *parent = nullptr);
    ~n7714awindow();

private:
    Ui::n7714awindow *ui;
    Worker *worker;
};

#endif // N7714AWINDOW_H
