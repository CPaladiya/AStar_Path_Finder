#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QTextStream>
#include <QPushButton>
#include <QThread>

//QTextStream out(stdout);
/*This class is buttons in the main window acting as a 2D selectable
pixel grid*/

class GridButton : public QPushButton{
    
    Q_OBJECT

public:
    GridButton(QWidget *parent = nullptr);
    ~GridButton();

    GridButton* parent_{nullptr}; //link to the parent of the button
    GridButton* children_{nullptr}; //link to the children of the button
    bool IsItDestiny_{false}; //if this button is selected as destination  
    bool IsItStart_{false}; //if this button is selected as starting point
    bool IsItBlock_{false}; //if this button is a road block
    float x_GridPos_; //x position of the button within 2D grid
    float y_GridPos_; //y position of the button within 2D grid
    QPushButton* ButtonVar_{nullptr}; //Main button variable for this instance
    static int UseCount_; //The value storing, how many time the button has been pressed
};

int GridButton::UseCount_{0}; //defined the static variable button that will increase with every button press

#endif