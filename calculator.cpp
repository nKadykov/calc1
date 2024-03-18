#include "calculator.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>

Calculator::Calculator(QWidget* parent) : QWidget(parent), sumInMemory(0.0), sumSoFar(0.0), factorSoFar(0.0), waitingForOperand(true) {
    display = new QLineEdit("0");
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    for(int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked);
    }
    Button *pointButton = createButton(tr("."), &Calculator::digitClicked);
    Button *changeSignButton = createButton(tr("\302\261"), &Calculator::changeSignClicked);

    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    Button *clearButton = createButton(tr("Clear"), &Calculator::clear);
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);
    Button *clearMemoryButton = createButton(tr("MC"), &Calculator::clearMemory);
    Button *setMemoryButton = createButton(tr("MS"), &Calculator::setMemory);
    Button *addtoMemoryButton = createButton(tr("M+"), &Calculator::addToMemory);
    Button *divisionButton = createButton(tr("\303\267"), &Calculator::multiplicativeOperatorClicked);
    Button *timesButton = createButton(tr("\303\227"), &Calculator::multiplicativeOperatorClicked);
    Button *minusButton = createButton(tr("-"), &Calculator::additiveOperatorClicked);
    Button *plusButton = createButton(tr("+"), &Calculator::additiveOperatorClicked);
}
