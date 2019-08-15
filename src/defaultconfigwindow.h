#ifndef DEFAULTCONFIGWINDOW_H
#define DEFAULTCONFIGWINDOW_H

#include <QMainWindow>

namespace Ui {
class DefaultConfigWindow;
}

class DefaultConfigWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DefaultConfigWindow(QWidget *parent = nullptr);
    ~DefaultConfigWindow();

private:
    Ui::DefaultConfigWindow *ui;
};

#endif // DEFAULTCONFIGWINDOW_H
