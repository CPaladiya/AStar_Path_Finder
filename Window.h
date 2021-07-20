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
and also, will populate the main window grid with required elements such as simulation and reset button*/

class Window : public QWidget{

    Q_OBJECT;

    int raw_{20}; //number of raws in cell grid
    int clm_{30}; //number of column in cell grid
    int SimulationSpeed{10}; //in ms

public:

    Window(QWidget *parent = nullptr); //constructor
    ~Window();

    //we will use this array to calculate cost to neighbors and to add neighbors
    const float NeighborAddress[8][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
    vector<vector<float>> OpenNodes_; //vector to store open nodes's indices
    vector<vector<GridButton*>> TwoDGridOfButtons_; //vector to store pointer GridButton instances for 2D grid
    vector<vector<int>> ForwardResultVector_; //vector to store result in forward direction
    vector<vector<int>> ReverseResultVector_; //vector to store result in reverse direction

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
    void Load2DButtonGrid(); //loadint the GridButton pointer vector
    void LoadSimulateButtons(); //loading simulation and reset buttons
    void DrawMainWindow(); //adding all drawn entities to the main window
    void addDelay(int n); //adding delay wherever required
    void RunLoopToDrawBlocks_(); //Running loops to make block selection using only two input


    //---------------A-Star search Func------------------//
    float Distance(int X1, int Y1, int X2, int Y2); //calculating direct distance between two points
    void AStarSearch();//A-star search simulation
    void AddNeighbors(vector<vector<float>> &OpenNodes, const vector<float> &Node, const vector<float> &Finish); //Adding neighbours of node to opennodes
    void SortOpenNodes(vector<vector<float>> &OpenNodes); //Sorting the nodes from highest to lowest total distance = cost up untill now + hueristic distance
    void RegeneratePath(); //Regenerate path by going to parent of each node untill we reach start point
    void ResetEverything(); //clearing the screen for new simulation
};

#endif