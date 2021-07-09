#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <vector>
#include <QTextStream>
#include <iostream>
#include <QTextStream>
#include <QTime>
#include <cmath>
#include "GridButton.h"

using namespace std;

/*class definition of Window object, the main object that will own all the other class objects
and also, will populate the main window grid with required elements*/

 //adding GridButton instances here

class Window : public QWidget{

    Q_OBJECT;

    int raw_{20};
    int clm_{30};

public:

    Window(QWidget *parent = nullptr); //constructor
    ~Window();

    //we will use this array to calculate cost to neighbors and to add neighbors
    const float NeighborAddress[8][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
    vector<vector<float>> OpenNodes_; //vector to store open nodes 
    vector<vector<GridButton*>> OpenGridButtons_; //vector to store open buttons
    vector<vector<GridButton*>> TwoDGridOfButtons_;

    //---------------All QGridLayout variables-----------------------//
    QGridLayout* MainWindowGrid_{nullptr}; //main grid that will hold all the boxes and will be added to main window
    QGridLayout* TwoDGridButtonGridLayout_{nullptr}; //Grid that will hold 2D grid buttons
    QGridLayout* SimulateButtonGrid_{nullptr}; //Grid that will hold A-Star and LOS button

    //---------------All QGroupBox variables-----------------------//
    QGroupBox* TwoDGridButtonBox_{nullptr}; //will hold TwoDGridButtonGridLayout
    QGroupBox* SimulateButtonBox_{nullptr}; //will hold SimulateButtonBox

    //---------------All the required buttons-----------------------//
    QPushButton* AStarButton_{nullptr}; //Button to simulate A-Star Algorithm
    QPushButton* LOSButton_{nullptr}; //Button to simulate LOS Algorithm
    QPushButton* ResetButton_{nullptr}; //Button to reset the system
    
    //---------------Func to setup the window and buttons-----------------------//
    void Load2DButtonGrid();
    void LoadSimulateButtons();
    void DrawMainWindow();
    void HideResetButton_();
    void ShowResetButton_();
    void addDelay(int n);
    void RunLoopToDrawBlocks_();


    //---------------A-Star search Func------------------//
    float Distance(int X1, int Y1, int X2, int Y2); //calculating distance between two points
    void AStarSearch();//A-star search simulation
    void AddNeighbors(vector<vector<float>> &OpenNodes, const vector<float> &Node, const vector<float> &Finish); //Adding neighbours of node to opennodes
    void SortOpenNodes(vector<vector<float>> &OpenNodes); //Sorting the nodes from highest to lowest
    void RegeneratePath(); //Display path 
};

#endif