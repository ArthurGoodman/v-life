#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Field;

class Widget : public QWidget {
    Q_OBJECT

    Field *f;
    QPixmap pixmap;

    QPoint lastPos;

public:
    Widget();
    ~Widget();

protected:
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void updatePixmap(const QImage &);
};

#endif // WIDGET_H
