#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QImage>

class TreeUniverse;

class Field : public QObject {
    Q_OBJECT

    QImage image;
    QTimer *timer;
    QSize size;

    TreeUniverse *u;

    int cellSize;

    QPoint offset;
    double scale;

public:
    Field();
    ~Field();

    void resize(const QSize &size);

    void start();
    void stop();

    bool alive();

    void shift(QPoint delta);
    void zoom(double factor);

public slots:
    void render();

private slots:
    void step();

signals:
    void renderedImage(const QImage &);
};

#endif // FIELD_H
