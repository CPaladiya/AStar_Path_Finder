#include "GridButton.h"

int GridButton::UseCount_{0}; //defined the static variable button that will increase with every button press

GridButton::GridButton(int X, int Y, QWidget *parent)
            : QPushButton(parent), x_GridPos_(X), y_GridPos_(Y){
    const QSize FixedButtonSize = QSize(20,20); //fixing the button size
    ButtonVar_ = new QPushButton();
    ButtonVar_->setFixedSize(FixedButtonSize);
    connect(ButtonVar_, &GridButton::clicked, this, &GridButton::setColor);
}

GridButton::~GridButton(){
}

void GridButton::setColor(){
    
    if(UseCount_>1 && UseCount_ < 102){
        ButtonVar_->setStyleSheet("background-color : black");
        UseCount_++;
    }
    else if(UseCount_==0){
        ButtonVar_->setStyleSheet("background-color : green");
        UseCount_++;
    }
    else if(UseCount_==1){
        ButtonVar_->setStyleSheet("background-color : red");
        UseCount_++;
    }
    else {
        std::cout << "You can not add more than 100 Road Blocks!" <<std::endl;
    }
}