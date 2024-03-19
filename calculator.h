#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QWidget> // виджет - атом пользовательского интерфейса, он получает события мыши, клавиатуры и другие события оконной системы и рисует своё представление на экране, каждый виджет отсортирован в Z-порядке

QT_BEGIN_NAMESPACE // макросы, которые можно переопределить при сборке Qt в определённом пространстве имён
class QLineEdit; // позволяет пользователям вводить и редактировать одну строку обычного текст с помощью функций редактирования
QT_END_NAMESPACE
class Button;

class Calculator : public QWidget // класс Calculator объявляем наследником класса QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
private slots: // слот вызывается, когда излучается сигнал, подключённый к нему, слоты являются обычными функциями и могут быть вызваны обычным образом
    void digitClicked(); //
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();
private:
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOpeator);
    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;
    QLineEdit *display;
    enum {NumDigitButtons = 10};
    Button *digitButtons[NumDigitButtons];
};

#endif // CALCULATOR_H
