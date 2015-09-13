#include "mainwindow.h"
#include <QtWidgets>
#include "widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    resize(qApp->desktop()->size() / 2);
    move(qApp->desktop()->rect().center() - rect().center());
    setMinimumSize(qApp->desktop()->size() / 4);

    w = new Widget;
    setCentralWidget(w);
    w->setFocus();
    w->installEventFilter(this);
}

MainWindow::~MainWindow() {
    delete w;
}

bool MainWindow::eventFilter(QObject *, QEvent *e) {
    if (e->type() == QEvent::KeyPress)
        switch (((QKeyEvent *)e)->key()) {
        case Qt::Key_F11:
            isFullScreen() ? showNormal() : showFullScreen();
            return true;
        case Qt::Key_Escape:
            isFullScreen() ? showNormal() : (void)close();
            return true;
        }

    return false;
}
