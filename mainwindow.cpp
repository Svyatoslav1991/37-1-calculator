#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGlobal>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->settingProgramm();

    this->resize(450, 250);
}

//------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------------------------------------

//настройка приложения
void MainWindow::settingProgramm()
{
    this->setStyleSheet(R"(
                        QMainWindow {
                            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                                        stop:0 #0093E9, stop:0.1 #80D0C7,
                                                        stop:0.5 #FFFFFF, stop:0.9 #80D0C7,
                                                        stop:1 #0093E9);
                            border: 1px solid #005F9E;
                        }
                    )");

    ui->statusbar->hide();
    this->setMinimumSize(400, 250);
    this->setWindowTitle("КАЛЬКУЛЯТОР");
    this->setWindowIcon(QIcon(":/icons/icons/calculator.png"));

    ui->about_action->setIcon(QIcon(":/icons/icons/questionmark.ico"));
    ui->about_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    ui->close_action->setIcon(QIcon(":/icons/icons/cross.png"));
    ui->close_action->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));
\
    ui->multiply_button->setIcon(QIcon(":/icons/icons/cross.png"));
    ui->multiply_button->setIconSize(ui->minus_button->size());

    ui->plus_button->setIcon(QIcon(":/icons/icons/plus.png"));
    ui->plus_button->setIconSize(ui->minus_button->size());

    ui->minus_button->setIcon(QIcon(":/icons/icons/minus.png"));
    ui->minus_button->setIconSize(ui->minus_button->size());

    ui->divide_button->setIcon(QIcon(":/icons/icons/slash.png"));
    ui->divide_button->setIconSize(ui->minus_button->size());

    ui->result_lineEdit->setReadOnly(true);

    m_rx.setPattern("-?\\d+(\\.\\d+)?");
    m_validator = std::make_unique<QRegularExpressionValidator>(m_rx);
    ui->value1_lineEdit->setValidator(m_validator.get());
    ui->value2_lineEdit->setValidator(m_validator.get());

    connect(ui->close_action, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->about_action, SIGNAL(triggered(bool)), this, SLOT(showInfoMessageSlot()));

    m_pButtonSound = std::make_unique<QMediaPlayer>();
    m_pButtonSound->setMedia(QUrl("qrc:/music/music/button.mp3"));
    m_pButtonSound->setVolume(20);
}

//------------------------------------------------------------------------------

void MainWindow::action(Action act)
{
    m_pButtonSound->play();

    if(ui->value1_lineEdit->text().isEmpty())
    {
        ui->result_lineEdit->setText("Введите первое число");
        return;
    }
    else if(ui->value2_lineEdit->text().isEmpty())
    {
        ui->result_lineEdit->setText("Введите второе число");
        return;
    }

    QString value1str = ui->value1_lineEdit->text();
    QString value2str = ui->value2_lineEdit->text();

    if(!isValidValue(value1str))
    {
        ui->result_lineEdit->setText("Неверное первое число");
        return;
    }
    else if(!isValidValue(value2str))
    {
        ui->result_lineEdit->setText("Неверное второе число");
        return;
    }

    double value1 = value1str.toDouble();
    double value2 = value2str.toDouble();
    double result;

    switch (act) {
    case Action::plus:
        result = value1 + value2;
        break;
    case Action::minus:
        result = value1 - value2;
        break;
    case Action::multiply:
        result = value1*value2;
        break;
    case Action::divide:
    {
        if(isZero(value2))
        {
            ui->result_lineEdit->setText("На ноль делить нельзя!");
            return;
        }
        result = value1/value2;
    }
        break;
    default:
        break;
    }

    ui->result_lineEdit->setText(QString::number(result));
}

//------------------------------------------------------------------------------

//проверка числа на правильность
bool MainWindow::isValidValue(QString value) const
{
    return m_rx.match(value).hasMatch();
}

//------------------------------------------------------------------------------

//проверка числа на ноль
bool MainWindow::isZero(double value) const
{
    return qFuzzyCompare(1 + value, 1);
}

//------------------------------------------------------------------------------

//изменение размеров окна
void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->multiply_button->setIconSize(ui->multiply_button->size());
    ui->plus_button->setIconSize(ui->multiply_button->size());
    ui->minus_button->setIconSize(ui->multiply_button->size());
    ui->divide_button->setIconSize(ui->multiply_button->size());

    Q_UNUSED(event)
}

//------------------------------------------------------------------------------

//нажатие на кнопку "плюс"
void MainWindow::on_plus_button_clicked()
{
    this->action(Action::plus);
}

//------------------------------------------------------------------------------

//нажатие на кнопку "минус"
void MainWindow::on_minus_button_clicked()
{
    this->action(Action::minus);
}

//------------------------------------------------------------------------------

//нажатие на кнопку "умножить"
void MainWindow::on_multiply_button_clicked()
{
    this->action(Action::multiply);
}

//------------------------------------------------------------------------------

//нажатие на кнопку "разделить"
void MainWindow::on_divide_button_clicked()
{
    this->action(Action::divide);
}

//------------------------------------------------------------------------------

//нажатие "О программе..."
void MainWindow::showInfoMessageSlot()
{
    QMessageBox::information(this, "О программе \"Калькулятор\"", "Программа является рашением задания 37.1 курса по C++ и представляет собой реализацию простого калькулятора");
}
