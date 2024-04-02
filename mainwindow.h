#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <memory>
#include <QMediaPlayer>
#include "constants.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QRegularExpression m_rx;
    std::unique_ptr<QRegularExpressionValidator> m_validator;
    std::unique_ptr<QMediaPlayer> m_pButtonSound;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void settingProgramm();//настройка приложения
    void action(Action act);
    bool isValidValue(QString value) const;//проверка числа на правильность
    bool isZero(double value) const;//проверка числа на ноль

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event);//изменение размеров окна

private slots:
    void on_plus_button_clicked();//нажатие на кнопку "плюс"
    void on_minus_button_clicked();//нажатие на кнопку "минус"
    void on_multiply_button_clicked();//нажатие на кнопку "умножить"
    void on_divide_button_clicked();//нажатие на кнопку "разделить"
    void showInfoMessageSlot();//нажатие "О программе..."
};
#endif // MAINWINDOW_H
