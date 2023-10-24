#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "wiringSerial.h"
#include "softPwm.h"

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

}

MainWindow::~MainWindow()
{
    //mpu_thread->stop();
    pir_thread->stop();
    rain_thread->stop();
    uwave_thread->stop();
    delete ui;
}


int servoControl(){
    softPwmCreate(1,0,200);
    softPwmWrite(1,5);
    delay(600);
    softPwmWrite(1,25);
    delay(600);
    return 0;
}

void MainWindow::on_pushButton_3_clicked()
{
    if(wiringPiSetup()==-1) return;
    IsClicked1 = false;
    IsClicked2 = false;
    IsClicked3 = true;
    if(IsClicked3 == true){
        //servoControl();
        ui->horizontalSlider->setEnabled(1);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    mpu_thread->start();
    pir_thread->start();
    rain_thread->start();

    IsClicked1 = false;
    IsClicked2 = true;
    IsClicked3 = false;
    if(IsClicked2 == true){
        servoControl();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(wiringPiSetup()==-1) return;
    IsClicked1 = true;
    IsClicked2 = false;
    IsClicked3 = false;
    ui->horizontalSlider->setDisabled(1);
    if(IsClicked1 == true){
        servoControl();
    }
}

void MainWindow::printScreen1(int idx){
    QString string = QString::number(idx);
    string += ": MPU\n";
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
