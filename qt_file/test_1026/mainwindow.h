#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mpu_sensor.h"
#include "pir_sensor.h"
#include "rain_sensor.h"
#include "uwave_sensor.h"
#include "logic.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern int gPir;
extern int gUwave;
extern int gRain;
extern double gGyroX;
extern double gGyroY;
extern int gYsig;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void printScreen1(int);
    void printScreen2(int);
    void printScreen3(int);
    void printScreen4(int);
    void printScreen5(int);

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    bool IsClicked1;
    bool IsClicked2;
    bool IsClicked3;

    // thread
    MPU_Sensor *mpu_thread;
    PIR_Sensor *pir_thread;
    Rain_Sensor *rain_thread;
    UWAVE_Sensor *uwave_thread;
    Logic *logic_thread;

};
#endif // MAINWINDOW_H
