#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_AutoMode_clicked();

    void on_RefreshMode_clicked();

    void on_LightMode_clicked();

    void on_SelectMode_clicked();

    void on_userMode_clicked();



    void on_Btn_cover_clicked();

    void on_WindowSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
