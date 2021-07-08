#include "GridButton.h"

//-----------static variables and function-----------------//
int GridButton::UseCount_{0}; //defined the static variable button that will increase with every button press
int GridButton::firtsRoadBlock_XPos_{0};
int GridButton::firtsRoadBlock_YPos_{0};
int GridButton::lastRoadBlock_XPos_{0};
int GridButton::lastRoadBlock_YPos_{0};
bool GridButton::drawRoadBlocks_{false};

//-----------class methods---------------------------//

GridButton::GridButton(int X, int Y, QWidget *parent)
            : QPushButton(parent), x_GridPos_(X), y_GridPos_(Y){
    const QSize FixedButtonSize = QSize(20,20); //fixing the button size
    ButtonVar_ = new QPushButton();
    ButtonVar_->setFixedSize(FixedButtonSize);
    connect(ButtonVar_, &QPushButton::clicked, this, &GridButton::setColor);
}

GridButton::~GridButton(){
}

void GridButton::setColor(){
   
    if(UseCount_>1 && UseCount_%2==0){
        ButtonVar_->setStyleSheet("background-color : black");
        firtsRoadBlock_XPos_ = x_GridPos_;
        firtsRoadBlock_YPos_ = y_GridPos_;
        UseCount_++;
    }
    else if(UseCount_>1 && UseCount_%2==1){
        QMutexLocker locker_(&mutex_);
        ButtonVar_->setStyleSheet("background-color : black");
        lastRoadBlock_XPos_ = x_GridPos_;
        lastRoadBlock_YPos_ = y_GridPos_;
        drawRoadBlocks_ = true;
        UseCount_++;
    }
    else if(UseCount_==0){
        ButtonVar_->setStyleSheet("background-color : green");
        IsItStart_ = true;
        UseCount_++;
    }
    else if(UseCount_==1){
        ButtonVar_->setStyleSheet("background-color : red");
        IsItDestiny_=true;
        UseCount_++;
    }
    else {
        std::cout << "You can not add more than 100 Road Blocks!" <<std::endl;
    }
}