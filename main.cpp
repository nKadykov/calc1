#include <QApplication>
#include "calculator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, atgv);
    Calculator calc;
    calc.show();
    return app.exec();
}
