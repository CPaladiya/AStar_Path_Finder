#include "GridButton.h"

int GridButton::UseCount_{0}; //defined the static variable button that will increase with every button press

GridButton::GridButton(int X, int Y, QWidget *parent)
            : QPushButton(parent), x_GridPos_(X), y_GridPos_(Y){
    this->setMouseTracking(true); //setting the mouse tracking true to enable hover event
    const QSize FixedButtonSize = QSize(20,20); //fixing the button size
    ButtonVar_ = new QPushButton();
    ButtonVar_->setFixedSize(FixedButtonSize);
    connect(ButtonVar_, &QPushButton::clicked, this, &GridButton::setStartNFinishColor);
}

GridButton::~GridButton(){
}

void GridButton::setStartNFinishColor(){
    
    if(UseCount_>1 && UseCount_<100 && UseCount_%2==0){
        connect(ButtonVar_, SIGNAL(theSignal(GridButton::hovered)), this, SIGNAL(theSignal(GridButton::setRoadBlockColor)));
        UseCount_++; cout<<UseCount_<<endl;
    }
    else if(UseCount_>1 && UseCount_<100 && UseCount_%2==1){
        disconnect(ButtonVar_, SIGNAL(theSignal(GridButton::hovered)));
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

void GridButton::setRoadBlockColor(){
    if(UseCount_>1 && UseCount_ %2==0){
        ButtonVar_->setStyleSheet("background-color : black");
        cout<<"Hover called"<<endl;
        UseCount_++;
    }
}

void GridButton::enterEvent(QEvent *e){
    Q_EMIT hovered();
    QWidget::enterEvent(e); //forwarding the event
}