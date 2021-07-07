#include "LOSLogic.h"

Window::Window(QWidget *parent): QWidget(parent){
    LoadWindow();
}

void Window::LoadWindow(){
    
    MainWindowGrid = new QGridLayout;

    // -------------- adding 2D grid 200 buttons to 2DGrid box---------------//

    QGroupBox *TwoDGridButtonBox = new QGroupBox;
    QGridLayout *TwoDGridButtonGridLayout = new QGridLayout;

    const QSize FixedButtonSize = QSize(20,20); //fixing the button size
    //adding the many button to the layout
    for(int i = 0; i<20 ; i++){
        for(int j = 0 ; j<30; j++){
            QPushButton *TempButton = new QPushButton();
            TempButton->setFixedSize(FixedButtonSize); //fixing the button size before adding it
            TwoDGridButtonGridLayout->addWidget(TempButton,i,j);
        }
    }
    TwoDGridButtonGridLayout->setSpacing(0);
    TwoDGridButtonBox->setLayout(TwoDGridButtonGridLayout);

    // --------------- adding A-Star and LOS button to box below to 2D grid box-------------//

    QGroupBox *SimulateButtonBox = new QGroupBox;
    QGridLayout *SimulateButtonGrid = new QGridLayout;
    LOSButton_ = new QPushButton("Simulate LOS");
    AStarButton_= new QPushButton("Simulate A-Star");
    ResetButton_= new QPushButton("Reset");

    SimulateButtonGrid->addWidget(LOSButton_,0,1);
    SimulateButtonGrid->addWidget(AStarButton_,0,0);

    SimulateButtonBox->setLayout(SimulateButtonGrid);

    //-----------adding both layout to main window--------//

    MainWindowGrid->addWidget(TwoDGridButtonBox,0,0,10,1);
    MainWindowGrid->addWidget(SimulateButtonBox,10,0,1,1);

    //----------Adding main window grid to QWidget--------//
    //Setting the grid, its title and Size of the window
    setLayout(MainWindowGrid); //Addimg main grid to the window
    setWindowTitle(tr("LOS Algorithm"));
    resize(100,200);

}