#include "button.h"

Button::Button(const QString &text, QWidget *parent) : QToolButton(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); //
    setText(text);
}

QSize Button::sizeHint() const {
    QSize size = QToolButton::sizeHint(); // создание size, которое содержит рекомендуемый размер виджета
    size.rheight() += 20; // увеличение высоты
    size.rwidth() = qMax(size.width(), size.height()); // ширина равна максимальному размеру ширины и высоты
    return size; // вернуть размер виджета
}
