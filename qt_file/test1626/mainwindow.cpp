#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wiringPi.h"
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

}

MainWindow::~MainWindow()
{
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
    IsClicked2 = true;
    IsClicked3 = false;
    if(IsClicked2 == true){
        //servoControl();
        ui->horizontalSlider->setEnabled(1);
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

