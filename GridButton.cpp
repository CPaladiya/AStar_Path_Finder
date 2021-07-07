#include "GridButton.h"

int GridButton::UseCount_{0}; //defined the static variable button that will increase with every button press

GridButton::GridButton(int X, int Y, QWidget *parent)
            : QPushButton(parent), x_GridPos_(X), y_GridPos_(Y){
    const QSize FixedButtonSize = QSize(20,20); //fixing the button size
    ButtonVar_ = new QPushButton();
    ButtonVar_->setFixedSize(FixedButtonSize);
}

GridButton::~GridButton(){
}