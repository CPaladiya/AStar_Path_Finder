#include "GridButton.h"

int GridButton::UseCount_{0}; //defined the static variable button that will increase with every button press

GridButton::GridButton(QWidget *parent) : QPushButton(parent){
    ButtonVar_ = new QPushButton();
}