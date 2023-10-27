#ifndef JOYSTICK_H
#define JOYSTICK_H


class joystick: public QThread
{
    Q_OBJECT
public:
    explicit joystick(QObject *parent = 0);
    void stop();

    int m_stopFlag = false;

private:
    void run();
    int idx = 2;
    int _detected;

signals:
    void ThreadEnd(int);
};
#endif // JOYSTICK_H

