#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QTextStream>
#include <QPushButton>
#include <QThread>
#include <iostream>
#include <QMutex>
#include <QWaitCondition>
#include <QMutexLocker>

using namespace std;

//QTextStream out(stdout);
/*This class is buttons in the main window acting as a 2D selectable
pixel grid*/

class GridButton : public QPushButton{
    
    Q_OBJECT

public:
    GridButton(int X, int Y, QWidget *parent = nullptr);
    ~GridButton(); 

    void setColor();//setting the color of button based on how many clicks has occured

    GridButton* parent_{nullptr}; //link to the parent of the button
    GridButton* children_{nullptr}; //link to the children of the button
    bool IsItDestiny_{false}; //if this button is selected as destination  
    bool IsItStart_{false}; //if this button is selected as starting point
    bool IsItBlock_{false}; //if this button is a road block
    int x_GridPos_; //x position of the button within 2D grid
    int y_GridPos_; //y position of the button within 2D grid
    QPushButton* ButtonVar_{nullptr}; //Main button variable for this instance
    QMutex mutex_;

    
    //all the static variables
    static int ClickUseCount_; //The value storing, how many time the button has been pressed
    static int firtsRoadBlock_XPos_;
    static int firtsRoadBlock_YPos_;
    static int lastRoadBlock_XPos_;
    static int lastRoadBlock_YPos_;
    static bool drawRoadBlocks_;
    static int totalRoadBlockCount_;
};

#endif