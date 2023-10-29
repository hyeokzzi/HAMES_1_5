//#include "button.h"
//#include "mainwindow.h"
//#include "gpio.h"

//extern int gOpenButton; // Cover Button
//extern int gCloseButton; // Cover Button

//Button::Button(QObject *parent) : QThread(parent)
//{
//   pinMode(OPEN_BTN_GPIO, INPUT);
//   pinMode(CLOSE_BTN_GPIO, INPUT);
//}

//void Button::run()
//{
//    while(!m_stopFlag)
//    {
//        // Insert Your Code
//        gOpenButton = digitalRead(OPEN_BTN_GPIO);
//        gCloseButton = digitalRead(CLOSE_BTN_GPIO);

//        //
////       emit ThreadEnd(gOpenButton);
////       emit ThreadEnd(gCloseButton);
//       sleep(1);
//    }
//}

//void Button::stop()
//{
//    m_stopFlag = true;
//}
