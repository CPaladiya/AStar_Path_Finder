#include "GridButton.h"

//-----------static variables and function-----------------//
int GridButton::ClickUseCount_{0}; //defined the static variable button that will increase with every button press
int GridButton::firtsRoadBlock_XPos_{0};
int GridButton::firtsRoadBlock_YPos_{0};
int GridButton::lastRoadBlock_XPos_{0};
int GridButton::lastRoadBlock_YPos_{0};
bool GridButton::drawRoadBlocks_{false};
int GridButton::totalRoadBlockCount_{0};
vector<int> GridButton::Start_{0,0};
vector<int> GridButton::Finish_{0,0};

//-----------class methods---------------------------//

GridButton::GridButton(int X, int Y, QWidget *parent)
            : QPushButton(parent), x_GridPos_(X), y_GridPos_(Y){
    const QSize FixedButtonSize = QSize(20,20); //fixing the button size
    ButtonVar_ = new QPushButton();
    ButtonVar_->setFixedSize(FixedButtonSize);
    connect(ButtonVar_, &QPushButton::clicked, this, &GridButton::setColorAndGetCoOrd);
}

GridButton::~GridButton(){
}

void GridButton::setOrageColor(){
    ButtonVar_->setStyleSheet("background-color : orange");
}

void GridButton::setColorAndGetCoOrd(){
    if(ClickUseCount_>1 && ClickUseCount_%2==0 && totalRoadBlockCount_<99){
        ButtonVar_->setStyleSheet("background-color : black");
        firtsRoadBlock_XPos_ = x_GridPos_;
        firtsRoadBlock_YPos_ = y_GridPos_;
        ClickUseCount_++;
    }
    else if(ClickUseCount_>1 && ClickUseCount_%2==1 && totalRoadBlockCount_<99){
        QMutexLocker locker_(&mutex_);
        drawRoadBlocks_ = true;
        lastRoadBlock_XPos_ = x_GridPos_;
        lastRoadBlock_YPos_ = y_GridPos_;
        ClickUseCount_++;
    }
    else if(ClickUseCount_==0){
        ButtonVar_->setStyleSheet("background-color : green");
        ItsAStart_ = true;
        ItsHome_ = true;
        Start_[0]=x_GridPos_;
        Start_[1]=y_GridPos_;
        ClickUseCount_++;
    }
    else if(ClickUseCount_==1){
        ButtonVar_->setStyleSheet("background-color : red");
        ItsAFinish_=true;
        Finish_[0]=x_GridPos_;
        Finish_[1]=y_GridPos_;
        ClickUseCount_++;
    }
    else {
        std::cout << "You can not add more than 100 Road Blocks!" <<std::endl;
    }
}