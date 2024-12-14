#include "include/dialogs/abstractinterface.h"
#include <QApplication>

QSize AbstractInterface::sizeHint() const {
    QMargins margins = EvaluateMargins();
    return screen->size().shrunkBy(margins);
}

AbstractInterface::AbstractInterface(QWidget *parent) : QDialog(parent) {
    this->setMinimumSize(QSize(300, 300));
    screen = QApplication::screens().constFirst();
    connect(screen, &QScreen::geometryChanged, this, [&](const QRect &rect) {
        Q_UNUSED(rect)
        UpdateWindow();
    });
}

QMargins AbstractInterface::EvaluateMargins() const {
    QMargins margins;
    const int scale = 10;
    const QSize size = screen->geometry().size();

    margins.setTop(size.height() / scale);
    margins.setLeft(size.width() / (scale - 5));
    margins.setRight(size.width() / (scale - 5));
    margins.setBottom(size.height() / scale);

    return margins;
}

void AbstractInterface::UpdateWindow() {
    this->setMaximumSize(screen->size());
    const QRect &rectangle = screen->geometry();
    const QMargins &margins = EvaluateMargins();
    this->setGeometry(rectangle.marginsRemoved(margins));
}
