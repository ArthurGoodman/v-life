#include "widget.h"
#include <QtWidgets>
#include "field.h"

Widget::Widget() {
    setCursor(Qt::OpenHandCursor);

    f = new Field;
    connect(f, SIGNAL(renderedImage(QImage)), SLOT(updatePixmap(QImage)));

    QThread *thread = new QThread;
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), f, SLOT(deleteLater()));
    f->moveToThread(thread);
    thread->start();

    //f->start();
    f->render();
}

Widget::~Widget() {
}

void Widget::resizeEvent(QResizeEvent *) {
    f->resize(size());
}

void Widget::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_Space:
        f->alive() ? f->stop() : f->start();
        break;
    }
}

void Widget::mousePressEvent(QMouseEvent *e) {
    lastPos = e->pos();

    setCursor(Qt::ClosedHandCursor);
}

void Widget::mouseMoveEvent(QMouseEvent *e) {
    f->shift(lastPos - e->pos());
    lastPos = e->pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *) {
    setCursor(Qt::OpenHandCursor);
}

void Widget::wheelEvent(QWheelEvent *e) {
    if (e->delta() > 0)
        f->zoom(1.1);
    else
        f->zoom(1.0 / 1.1);
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawPixmap(0, 0, pixmap);
}

void Widget::updatePixmap(const QImage &image) {
    pixmap = QPixmap::fromImage(image);
    update();
}
