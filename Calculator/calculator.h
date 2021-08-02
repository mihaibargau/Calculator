#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui; 
private slots:
    void MemoryClear();
    void NumPressed();
    void MathButtonPressed();
    void MemoryStore();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void MemoryGet();
    void Clear();
};
#endif // CALCULATOR_H
