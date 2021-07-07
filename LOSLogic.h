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

class GridButton;
class Window : public QWidget{

    Q_OBJECT;

public:

    Window(QWidget *parent = nullptr); //constructor
    ~Window();

    vector<vector<GridButton*>> 2DButGrid; //adding GridButton instances here


    //---------------All the required buttons-----------------------//
    QPushButton* AStarButton_; //Button to simulate A-Star Algorithm
    QPushButton* LOSButton_; //Button to simulate LOS Algorithm
    QPushButton* ResetButton_; //Button to reset the system

    //---------------Func to setup the window-----------------------//
    void LoadWindow();
    void HideResetButton_();
    void ShowResetButton_();
};

#endif