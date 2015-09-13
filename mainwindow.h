#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Widget;

class MainWindow : public QMainWindow {
    Q_OBJECT

    Widget *w;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *, QEvent *);
};

#endif // MAINWINDOW_H
