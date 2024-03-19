#include <QApplication> // класс управления потоком управления и основные настройки приложения с графическим интерфейсом
#include "calculator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // создание объекта класса QApplications
    Calculator calc; // создание объекта класса калькулятор
    calc.show(); // показывает виджет и его наследников
    return app.exec(); // входит в цикл событий и ожидает, пока exec() не вызвана
}
