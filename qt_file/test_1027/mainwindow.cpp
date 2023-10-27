#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "wiringSerial.h"
#include "softPwm.h"

int gPir = 0;
int gUwave = 0;
int gRain = 0;
double gGyroX = 0.0;
double gGyroY = 0.0;
int gJoystick = 0;
int gOpenButton = 0;
int gCloseButton = 0;

int gWindowState = 0;
int gCoverState = 0;
int gOpenDegree = 0;
int gLED = 0;
int gUserMode = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    IsClicked1 = false;
    IsClicked2 = false;
    IsClicked3 = false;
    ui->horizontalSlider->setDisabled(1);
    wiringPiSetup();
    wiringPiSetupGpio();

    // Create Thread Object and Connect Signal/Slot
    mpu_thread = new MPU_Sensor(this);
    connect(mpu_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen1(int)));
    mpu_thread->start();

    pir_thread = new PIR_Sensor(this);
    connect(pir_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen2(int)));
    pir_thread->start();

    rain_thread = new Rain_Sensor(this);
    connect(rain_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen3(int)));
    rain_thread->start();

    uwave_thread = new UWAVE_Sensor(this);
    connect(uwave_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen4(int)));
    uwave_thread->start();

//    button_thread = new Button(this);
//    connect(button_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen6(int)));
//    button_thread->start();

    logic_thread = new Logic(this);
    connect(logic_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen5(int)));
    logic_thread->start();
}

MainWindow::~MainWindow()
{
    mpu_thread->stop();
    pir_thread->stop();
    rain_thread->stop();
    uwave_thread->stop();
    logic_thread->stop();
//    button_thread->stop();
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    mpu_thread->start();
    pir_thread->start();
    rain_thread->start();
    uwave_thread->start();
    logic_thread->start();
//    button_thread->start();
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::printScreen1(int temp){
//    QString string = QString::number(temp.data[0]);
//    string += " - x";

//    string += QString::number(temp.data[1]);

    QString string = QString::number(temp);
    string += "- : MPU x, y\n";
    ui->textBrowser->insertPlainText(string);
}
void MainWindow::printScreen2(int idx){
    QString string = QString::number(idx);
    string += ": PIR\n";
    ui->textBrowser->insertPlainText(string);
}
void MainWindow::printScreen3(int idx){
    QString string = QString::number(idx);
    string += ": rain\n";
    ui->textBrowser->insertPlainText(string);
}
void MainWindow::printScreen4(int idx){
    QString string = QString::number(idx);
    string += ": UWAVE\n";
    ui->textBrowser->insertPlainText(string);
}
void MainWindow::printScreen5(int idx){
//    QString string = QString::number(idx);
//    string += ": LOGIC\n";
//    ui->textBrowser->insertPlainText(string);

    QString string;
    string += QString::number((idx & 0b00100000) >> 5);
    string += QString::number((idx & 0b00010000) >> 4);
    string += QString::number((idx & 0b00001000) >> 3);
    string += QString::number((idx & 0b00000100) >> 2);
    string += QString::number((idx & 0b00000010) >> 1);
    string += QString::number(idx & 0b00000001);
    string += " : LOGIC\n";
    ui->textBrowser->insertPlainText(string);
}
//void MainWindow::printScreen6(int idx){
//    QString string = QString::number(idx);
//    string += ": BUTTON\n";
//    ui->textBrowser->insertPlainText(string);
//}
