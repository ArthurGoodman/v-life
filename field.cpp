#include "field.h"
#include <QtWidgets>
#include "treeuniverse.h"

Field::Field() {
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), SLOT(step()));

    cellSize = 4;
    scale = 1;

    u = new TreeUniverse;

    u->setBit(0, 0);
    u->setBit(0, 1);
    u->setBit(-1, 1);
    u->setBit(0, -1);
    u->setBit(1, 0);
}

Field::~Field() {
    delete timer;
}

void Field::resize(const QSize &size) {
    this->size = size;
}

void Field::start() {
    timer->start(16);
}

void Field::stop() {
    timer->stop();
}

bool Field::alive() {
    return timer->isActive();
}

void Field::shift(QPoint delta) {
    offset += delta;
}

void Field::zoom(double factor) {
    scale *= factor;
}

void Field::step() {
    u->runStep();
}

void Field::render() {
    if (size != image.size())
        image = QImage(size, QImage::Format_RGB32);

    if (image.isNull()) {
        QTimer::singleShot(0, this, SLOT(render()));
        return;
    }

    static QColor bgColor = QColor(64, 64, 64), gridColor = QColor(48, 48, 48), fgColor = QColor(200, 200, 200);

    QPainter p(&image);
    p.fillRect(image.rect(), gridColor);

    int hw = image.width() / 2, hh = image.height() / 2;

    p.translate(hw, hh);

    hw /= cellSize;
    hh /= cellSize;

    for (int y = -hh; y <= hh; ++y)
        for (int x = -hw; x <= hw; ++x) {
            int bit = u->getBit(x + offset.x() / cellSize, y - offset.y() / cellSize);
            if (bit == -1)
                continue;
            p.fillRect(x * (cellSize + 1), -y * (cellSize + 1), cellSize, cellSize, bit ? fgColor : bgColor);
        }

    emit renderedImage(image);

    QTimer::singleShot(0, this, SLOT(render()));
}
