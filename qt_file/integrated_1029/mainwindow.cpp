#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "wiringSerial.h"
#include "softPwm.h"

int UserMode_state = 0;
int Cover_state =0;
int Value =0;


int gPir = 0;
int gUwave = 0;
int gUwave2 = 0;
int gRain = 0;
double gGyroX = 0.0;
double gGyroY = 0.0;
int gJoystick = 0;
int gOpenButton = 0;
int gCloseButton = 0;

int g_stop_moving_cover = 1;
int g_stop_moving_window = 1;

int gWindowState = 0;
int gCoverState = 0;
int gOpenDegree = 0;
int gLED = 0;
int gUserMode = 0;

int cnt = 0;
int prev_value = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    IsClicked1 = false;
    IsClicked2 = false;
    IsClicked3 = false;
    wiringPiSetup();
    wiringPiSetupGpio();

    ui->Select_groupBox->setHidden(1);
    ui->Cover_groupBox->setHidden(1);
    QPixmap pix("/home/pi/HAMES_1_5/qt_file/temp/image/car_0.png");
    ui -> label_image -> setPixmap(pix);


    // Create Thread Object and Connect Signal/Slot
    mpu_thread = new MPU_Sensor(this);
    //connect(mpu_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen1(int)));
    mpu_thread->start();

    pir_thread = new PIR_Sensor(this);
    //connect(pir_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen2(int)));
    pir_thread->start();

    rain_thread = new Rain_Sensor(this);
    //connect(rain_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen3(int)));
    rain_thread->start();

    uwave_thread = new UWAVE_Sensor(this);
    //connect(uwave_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen4(int)));
    uwave_thread->start();

    logic_thread = new Logic(this);
    //connect(logic_thread, SIGNAL(ThreadEnd(int)), this, SLOT(printScreen5(int)));
    logic_thread->start();
}

MainWindow::~MainWindow()
{
    mpu_thread->stop();
    pir_thread->stop();
    rain_thread->stop();
    uwave_thread->stop();
    logic_thread->stop();
    delete ui;
}

void MainWindow::on_userMode_clicked()
{

    // set ui
    ui->Select_groupBox->setHidden(1);
    ui->Cover_groupBox->setHidden(1);
    UserMode_state = !UserMode_state;

    gUserMode = UserMode_state; // set

    if(UserMode_state == 0){
        ui->Mode_groupBox->setEnabled(1);
        ui->label_image->setEnabled(1);
        QPixmap pix("/home/pi/HAMES_1_5/qt_file/temp/image/car_0.png");
        ui -> label_image -> setPixmap(pix);
    }
    else if(UserMode_state == 1){

      ui->Mode_groupBox->setDisabled(1);
      ui->label_image->setDisabled(1);

    }

}


void MainWindow::on_AutoMode_clicked()
{
    // set variable
    gCoverState = OPEN;
    gWindowState = OPEN;
    g_stop_moving_cover = 0;
    g_stop_moving_window = 0;
    gOpenDegree = 100;


    // set ui
     ui->Select_groupBox->setHidden(1);
     ui->Cover_groupBox->setHidden(1);
     QPixmap pix("/home/pi/HAMES_1_5/qt_file/temp/image/car_100.png");
     ui -> label_image -> setPixmap(pix);
}


void MainWindow::on_RefreshMode_clicked()
{
    // set variable
    gCoverState = OPEN;
    gWindowState = OPEN;
    g_stop_moving_cover = 0;
    g_stop_moving_window = 0;
    gOpenDegree = 20;

     ui->Select_groupBox->setHidden(1);
     ui->Cover_groupBox->setHidden(1);
     QPixmap pix("/home/pi/HAMES_1_5/qt_file/temp/image/car_20.png");
     ui -> label_image -> setPixmap(pix);

}


void MainWindow::on_LightMode_clicked()
{
    // set variable
    gCoverState = OPEN;
    gWindowState = CLOSE;
    g_stop_moving_cover = 0;
    g_stop_moving_window = 0;
    gOpenDegree = 100;

     ui->Select_groupBox->setHidden(1);
     ui->Cover_groupBox->setHidden(1);
     QPixmap pix("/home/pi/HAMES_1_5/qt_file/temp/image/car_light.png");
     ui -> label_image -> setPixmap(pix);

}


void MainWindow::on_SelectMode_clicked()
{
    // set variable

     ui->Cover_groupBox->setVisible(1);
     ui->Select_groupBox->setVisible(1);
     ui ->Select_groupBox->setDisabled(1);
     QPixmap pix("/home/pi/HAMES_1_5/qt_file/temp/image/car_100.png");
     ui -> label_image -> setPixmap(pix);
}


void MainWindow::on_Btn_cover_clicked()
{
    Cover_state = !Cover_state;
    if(Cover_state == 1){
        ui->Select_groupBox->setEnabled(1);
    }
    else if(Cover_state == 0){
        ui ->Select_groupBox->setDisabled(1);
        ui->WindowSlider->setValue(0);

    }
}


void MainWindow::on_WindowSlider_valueChanged(int value)
{
    QString string = QString::number(value);
}

void MainWindow::on_WindowSlider_sliderReleased()
{
    // set variable
    gCoverState = OPEN;
    gWindowState = OPEN;
    g_stop_moving_cover = 0;
    g_stop_moving_window = 0;
    gOpenDegree =ui->WindowSlider->value();

}

