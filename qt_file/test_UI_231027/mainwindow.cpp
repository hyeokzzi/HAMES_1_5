#include "mainwindow.h"
#include "ui_mainwindow.h"

extern int gWindowState;
extern int gCoverState;
extern int gOpenDegree;
extern int gLED;
extern int gUserMode;
int UserMode_state = 0;
int Cover_state =0;
int Value =0;
QString string;

//opne 1 close 0
//degree

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Select_groupBox->setHidden(1);
    ui->Cover_groupBox->setHidden(1);
    QPixmap pix("/home/pi/test_UI_231027/image/car_0.png");
    ui -> label_image -> setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_userMode_clicked()
{
    ui->Select_groupBox->setHidden(1);
     ui->Cover_groupBox->setHidden(1);
    UserMode_state = !UserMode_state;
    if(UserMode_state == 0){
        ui->Mode_groupBox->setEnabled(1);
        ui->label_image->setEnabled(1);
        QPixmap pix("/home/pi/test_UI_231027/image/car_0.png");
        ui -> label_image -> setPixmap(pix);
    }
    else if(UserMode_state == 1){

      ui->Mode_groupBox->setDisabled(1);
      ui->label_image->setDisabled(1);

    }

}


void MainWindow::on_AutoMode_clicked()
{
     ui->Select_groupBox->setHidden(1);
     ui->Cover_groupBox->setHidden(1);
     QPixmap pix("/home/pi/test_UI_231027/image/car_100.png");
     ui -> label_image -> setPixmap(pix);
}


void MainWindow::on_RefreshMode_clicked()
{
     ui->Select_groupBox->setHidden(1);
     ui->Cover_groupBox->setHidden(1);
     QPixmap pix("/home/pi/test_UI_231027/image/car_20.png");
     ui -> label_image -> setPixmap(pix);

}


void MainWindow::on_LightMode_clicked()
{
     ui->Select_groupBox->setHidden(1);
     ui->Cover_groupBox->setHidden(1);
     QPixmap pix("/home/pi/test_UI_231027/image/car_light.png");
     ui -> label_image -> setPixmap(pix);

}


void MainWindow::on_SelectMode_clicked()
{
     ui->Cover_groupBox->setVisible(1);
     ui->Select_groupBox->setVisible(1);
     ui ->Select_groupBox->setDisabled(1);
     QPixmap pix("/home/pi/test_UI_231027/image/car_100.png");
     ui -> label_image -> setPixmap(pix);


     /*if(string == "100"){
         QPixmap pix("/home/pi/test_UI_231027/image/car_100.png");
         ui -> label_image -> setPixmap(pix);
     }
     else if(string>"80"){
         QPixmap pix("/home/pi/test_UI_231027/image/car_80.png");
         ui -> label_image -> setPixmap(pix);

     }
     else if(string>"60"){
         QPixmap pix("/home/pi/test_UI_231027/image/car_60.png");
         ui -> label_image -> setPixmap(pix);
     }
     else if(string>"40"){
         QPixmap pix("/home/pi/test_UI_231027/image/car_40.png");
         ui -> label_image -> setPixmap(pix);
     }
     else if(string>"20"){
         QPixmap pix("/home/pi/test_UI_231027/image/car_20.png");
         ui -> label_image -> setPixmap(pix);
     }
     else if(string == "0"){
         QPixmap pix("/home/pi/test_UI_231027/image/car_0.png");
         ui -> label_image -> setPixmap(pix);
     }*/

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
       // Value = ui->WindowSlider->value();
    }
}


void MainWindow::on_WindowSlider_valueChanged(int value)
{
    string = QString::number(value);
    // Value = value;
    //ui->textBrowser->insertPlainText(string);
}

