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

    void setColorAndGetCoOrd();//setting the color of button based on how many clicks has occured
    void setOrageColor();//setting orange color for final result

    vector<int> parent_; //link to the parent of the button
    //float HueDistToFinish_{0}; //h-score direct distance to finish point
    float DistFromStart_{0}; //g-score so far distance from start
    float TotalDistance_{0}; //f-score = (g+h) total score
    bool ItsHome_{false}; //Variable used to identify home while regenerating path
    bool ItsAFinish_{false}; //if this button is selected as destination  
    bool ItsAStart_{false}; //if this button is selected as starting point
    bool ItsABlock_{false}; //if this button is a road block
    bool ItsVisited_{false}; //status if the cell is already visited
    int x_GridPos_; //x position of the button within 2D grid
    int y_GridPos_; //y position of the button within 2D grid
    QPushButton* ButtonVar_{nullptr}; //Main button variable for this instance
    QMutex mutex_;

    
    //all the static variables
    static int ClickUseCount_; //The value storing, how many time the button has been pressed
    static int firtsRoadBlock_XPos_; //while putting road block first element of the block and its X pos
    static int firtsRoadBlock_YPos_; //while putting road block first element of the block and its Y pos
    static int lastRoadBlock_XPos_; //while putting road block last element of the block and its X pos
    static int lastRoadBlock_YPos_; //while putting road block last element of the block and its Y pos
    static bool drawRoadBlocks_; //indiation to start drawing road blocks once we have start and finish xy points
    static int totalRoadBlockCount_; //NUmber of total road blocks within grid
    static vector<int>Start_; //storing xy of starting point
    static vector<int>Finish_; //storing xy of finish point
};

#endif