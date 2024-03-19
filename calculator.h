#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QWidget> // виджет - атом пользовательского интерфейса, он получает события мыши, клавиатуры и другие события оконной системы и рисует своё представление на экране, каждый виджет отсортирован в Z-порядке

QT_BEGIN_NAMESPACE // макросы, которые можно переопределить при сборке Qt в определённом пространстве имён
class QLineEdit; // позволяет пользователям вводить и редактировать одну строку обычного текста с помощью функций редактирования
QT_END_NAMESPACE
class Button;

class Calculator : public QWidget // класс Calculator объявляем наследником класса QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
private slots: // слот вызывается, когда излучается сигнал, подключённый к нему, слоты являются обычными функциями и могут быть вызваны обычным образом
    void digitClicked(); // нажатие на цифру
    void unaryOperatorClicked(); // нажатие на унарный оператор
    void additiveOperatorClicked(); // нажатие на аддитивный оператор
    void multiplicativeOperatorClicked(); // нажатие на мультипликативный оператор
    void equalClicked(); // нажатие на оператор равенства
    void pointClicked(); // нажатие на оператор точка
    void changeSignClicked(); // нажатие на оператор изменения знака
    void backspaceClicked(); // нажатие на клавишу удаления
    void clear(); // нажатие на клавишу очистки
    void clearAll(); // нажатие на клавишу очистки всего текста
    void clearMemory(); // функция очистки памяти
    void readMemory(); // функция чтения памяти
    void setMemory(); // функция установки памяти
    void addToMemory(); // функция добавления в память
private:
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member); // шаблонная функция создания кнопки
    void abortOperation(); // функция ошибки
    bool calculate(double rightOperand, const QString &pendingOpeator); // функция вычисления значения
    double sumInMemory; // сумма в памяти
    double sumSoFar; // существующая сумма
    double factorSoFar; // существующий множитель
    QString pendingAdditiveOperator; // рассматриваемый аддитивный оператор
    QString pendingMultiplicativeOperator; // рассматриваемый мультипликативный оператор
    bool waitingForOperand; // булевая переменная ожидания оператора
    QLineEdit *display; // однострочный текст
    enum {NumDigitButtons = 10}; // количество кнопок для цифр
    Button *digitButtons[NumDigitButtons]; // массив кнопок для цифр
};

#endif // CALCULATOR_H
