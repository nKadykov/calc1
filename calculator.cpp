#include "calculator.h"
#include "button.h"

#include <QGridLayout> // берёт пространство, предоставленное ему родительским макетом или родительским виджетом, делит его на строки и столбцы и помещает каждый виджет, которым он управляет, в правильную ячейку
#include <QLineEdit> // позволяет пользователям вводить и редактировать одну строку обычного текста с помощью функций редактирования
#include <QtMath> // библиотека для работы с математическими функциями

Calculator::Calculator(QWidget* parent) : QWidget(parent), sumInMemory(0.0), sumSoFar(0.0), factorSoFar(0.0), waitingForOperand(true) {
    display = new QLineEdit("0"); // выделение памяти под однострочный тектовый редактор, установка начального значения "0"
    display->setReadOnly(true); // дисплей только для чтения
    display->setAlignment(Qt::AlignRight); // выравнивание дисплея по левому краю
    display->setMaxLength(15); // установка максимальной длины дисплея
    QFont font = display->font(); // создание объекта для шрифта дисплея
    font.setPointSize(40); // установка размера
    font.setStyle(QFont::StyleNormal); // установка стиля
    display->setFont(font); // установка шрифта
    for(int i = 0; i < NumDigitButtons; ++i) { // массив создания кнопок для цифр
        digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked);
    }
    Button *pointButton = createButton(tr("."), &Calculator::pointClicked);
    Button *changeSignButton = createButton(tr("\302\261"), &Calculator::changeSignClicked);

    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    Button *clearButton = createButton(tr("Clear"), &Calculator::clear);
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);
    Button *clearMemoryButton = createButton(tr("MC"), &Calculator::clearMemory);
    Button *readMemoryButton = createButton(tr("MR"), &Calculator::readMemory);
    Button *setMemoryButton = createButton(tr("MS"), &Calculator::setMemory);
    Button *addToMemoryButton = createButton(tr("M+"), &Calculator::addToMemory);
    Button *divisionButton = createButton(tr("\303\267"), &Calculator::multiplicativeOperatorClicked);
    Button *timesButton = createButton(tr("\303\227"), &Calculator::multiplicativeOperatorClicked);
    Button *minusButton = createButton(tr("-"), &Calculator::additiveOperatorClicked);
    Button *plusButton = createButton(tr("+"), &Calculator::additiveOperatorClicked);
    Button *squareRootButton = createButton(tr("Sqrt"), &Calculator::unaryOperatorClicked);
    Button *powerButton = createButton(tr("x\302\262"), &Calculator::unaryOperatorClicked);
    Button *reciprocalButton = createButton(tr("1/x"), &Calculator::unaryOperatorClicked);
    Button *equalButton = createButton(tr("="), &Calculator::equalClicked);

    QGridLayout *mainLayout = new QGridLayout; // определение макета

    mainLayout->setSizeConstraint(QLayout::SetMaximumSize); // установка геометрии приложения
    mainLayout->addWidget(display, 0, 0, 1, 6); // добавление дисплея
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2); // добавление кнопки Backspace
    mainLayout->addWidget(clearButton, 1, 2, 1, 2); // добавление кнопки Clear
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2); // добавление кнопки Clear All
    mainLayout->addWidget(clearMemoryButton, 2, 0); // добавление кнопки MC
    mainLayout->addWidget(readMemoryButton, 3, 0); // добавление кнопки MR
    mainLayout->addWidget(setMemoryButton, 4, 0); // добавление кнопки MS
    mainLayout->addWidget(addToMemoryButton, 5, 0); // добавление кнопки M+
    for(int i = 1; i < NumDigitButtons; ++i) { // цикл добавления кнопок цифр
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }
    mainLayout->addWidget(digitButtons[0], 5, 1); // установка кнопки 0
    mainLayout->addWidget(pointButton, 5, 2); // установка кнопки +
    mainLayout->addWidget(changeSignButton, 5, 3); // установка кнопки изменения знака
    mainLayout->addWidget(divisionButton, 2, 4); // добавление кнопки деления
    mainLayout->addWidget(timesButton, 3, 4); // добавление кнопки умножения
    mainLayout->addWidget(minusButton, 4, 4); // добавление кнопки вычитания
    mainLayout->addWidget(plusButton, 5, 4); // добавление кнопки сложения
    mainLayout->addWidget(squareRootButton, 2, 5); // добавление кнопки sqrt
    mainLayout->addWidget(powerButton, 3, 5); // добавление кнопки возведения в степень
    mainLayout->addWidget(reciprocalButton, 4, 5); // добавление кнопки деления 1 на число
    mainLayout->addWidget(equalButton, 5, 5); // добавление кнопки =
    setLayout(mainLayout); // установка макета
    setWindowTitle(tr("Engineering Calculator")); // установка названия окна
}

void Calculator::digitClicked() { // нажатие кнопки цифры
    Button *clickedButton = qobject_cast<Button*>(sender());
    int digitValue = clickedButton->text().toInt();
    if(display->text() == "0" && digitValue == 0.0) {
        return;
    }
    if(waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}

void Calculator::unaryOperatorClicked() { // нажатие клавишы унарного оператора
    Button* clickedButton = qobject_cast<Button*>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;
    if(clickedOperator == tr("Sqrt")) {
        if(operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    }
    else if(clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    }
    else if(clickedOperator == tr("1/x")) {
        if(operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked() { // если нажата клавиша аддитивного оператора
    Button *clickedButton = qobject_cast<Button*>(sender());
    if(!clickedButton) {
        return;
    }
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if(!pendingMultiplicativeOperator.isEmpty()) {
        if(!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if(!pendingAdditiveOperator.isEmpty()) {
        if(!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    }
    else {
        sumSoFar = operand;
    }
    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked() { // если нажата клавиша мультипликативного оператора
    Button *clickedButton = qobject_cast<Button*>(sender());
    if(!clickedButton) {
        return;
    }
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if(!pendingMultiplicativeOperator.isEmpty()) {
        if(!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    }
    else {
        factorSoFar = operand;
    }
    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked() { // если нажата клавиша =
    double operand = display->text().toDouble();
    if(!pendingMultiplicativeOperator.isEmpty()) {
        if(!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if(!pendingAdditiveOperator.isEmpty()) {
        if(!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    }
    else {
        sumSoFar = operand;
    }
    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void Calculator::pointClicked() { // если нажата клавиша .
    if(waitingForOperand) {
        display->setText("0");
    }
    if(!display->text().contains('.')) {
        display->setText(display->text() + tr("."));
    }
    waitingForOperand = false;
}

void Calculator::changeSignClicked() { // если нажата клавиша изменения знака
    QString text = display->text();
    double value = text.toDouble();
    if(value > 0.0) {
        text.prepend(tr("-"));
    }
    else if(value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void Calculator::backspaceClicked() { // если нажата клавиша Backspace
    if(waitingForOperand) {
        return;
    }
    QString text = display->text();
    text.chop(1);
    if(text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void Calculator::clear() { // если нажата клавиша Clear
    if(waitingForOperand) {
        return;
    }
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearAll() { // если нажата клавиша Clear All
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearMemory() { // если нажата клавиша MC
    sumInMemory = 0.0;
}

void Calculator::readMemory() { // если нажата клавиша MR
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory() { // если нажата клавиша MS
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory() { // если нажата клавиша M+
    equalClicked();
    sumInMemory += display->text().toDouble();
}

template<typename PointerToMemberFunction> // описание шаблонной функции создания клавиша
Button *Calculator::createButton(const QString &text, const PointerToMemberFunction &member) {
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}

void Calculator::abortOperation() { // если ошибка
    clearAll();
    display->setText(tr("####"));
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator) { // метод для вычисления результата
    if(pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    }
    else if(pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    }
    else if(pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    }
    else if(pendingOperator == tr("\303\267")) {
        if(rightOperand == 0.0) {
            return false;
        }
        factorSoFar /= rightOperand;
    }
    return true;
}
