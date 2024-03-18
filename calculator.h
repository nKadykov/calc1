#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QWidget>
#include <QStack>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QRegularExpression>
#include <QFont>

class Calculator
{
    Q_OBJECT
private:
    QLabel* displaystring;
    QStack<QString> stack;
public:
    Calculator(QWidget *pwgt = 0);
    QPushButton* createButton(const QString& str);
    void calculate();
public slots:
    void slotButtonClicked();
};

#endif // CALCULATOR_H
