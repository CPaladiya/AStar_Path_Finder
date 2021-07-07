#ifndef LOSLOGIC_H
#define LOSLOGIC_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <vector>
#include <QTextStream>
#include <QLabel>
#include <iostream>
#include <QTextStream>

using namespace std;

/*class definition of Window object, the main object that will own all the other class objects
and also, will populate the main window grid with required elements*/

class Window : public QWidget{

    Q_OBJECT;

public:

    Window(QWidget *parent = nullptr); //constructor
    ~Window();


};

#endif