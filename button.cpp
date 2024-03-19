#include "button.h"

Button::Button(const QString &text, QWidget *parent) : QToolButton(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // перегруженная функция установки размера виджета по горизонтали и вертикали
    setText(text); // установка текста
}

QSize Button::sizeHint() const {
    QSize size = QToolButton::sizeHint(); // создание size, которое содержит рекомендуемый размер виджета
    size.rheight() += 50; // увеличение высоты
    size.rwidth() = qMax(size.width(), size.height()); // ширина равна максимальному размеру ширины и высоты
    return size; // вернуть размер виджета
}
