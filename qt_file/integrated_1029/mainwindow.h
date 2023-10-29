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
extern int gJoystick;
extern int gOpenButton;
extern int gCloseButton;

extern int gWindowState;
extern int gCoverState;
extern int gOpenDegree;
extern int gLED;
extern int gUserMode;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


private slots:
    void on_AutoMode_clicked();
    void on_RefreshMode_clicked();
    void on_LightMode_clicked();
    void on_SelectMode_clicked();
    void on_userMode_clicked();
    void on_Btn_cover_clicked();
    void on_WindowSlider_valueChanged(int value);

    void on_WindowSlider_sliderReleased();

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
