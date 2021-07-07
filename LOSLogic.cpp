#include "LOSLogic.h"

Window::Window(QWidget *parent): QWidget(parent){
    LoadWindow();
}

void Window::LoadWindow(){
    
    MainWindowGrid = new QGridLayout;

    // -------------- adding 2D grid 200 buttons---------------//

    QGroupBox *TwoDGridButtonBox = new QGroupBox;
    QGridLayout *TwoDGridButtonGridLayout = new QGridLayout;


    QPushButton* test = new QPushButton;
    TwoDGridButtonGridLayout->addWidget(test);
    TwoDGridButtonBox->setLayout(TwoDGridButtonGridLayout);

    // --------------- adding A-Star and LOS button-------------//

    QGroupBox *SimulateButtonBox = new QGroupBox;
    QGridLayout *SimulateButtonGrid = new QGridLayout;
    LOSButton_ = new QPushButton("Simulate LOS");
    AStarButton_= new QPushButton("Simulate A-Star");
    ResetButton_= new QPushButton("Reset");

    SimulateButtonGrid->addWidget(LOSButton_,0,1);
    SimulateButtonGrid->addWidget(AStarButton_,0,0);

    SimulateButtonBox->setLayout(SimulateButtonGrid);

    //-----------adding both layout to main window--------//

    MainWindowGrid->addWidget(TwoDGridButtonBox,0,0);
    MainWindowGrid->addWidget(SimulateButtonBox,1,0);

    //----------Adding main window grid to QWidget--------//
    //Setting the grid, its title and Size of the window
    setLayout(MainWindowGrid);
    setWindowTitle(tr("LOS Algorithm"));
    resize(1000,600);

}