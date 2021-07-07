#include "LOSLogic.h"

Window::Window(QWidget *parent): QWidget(parent){
    Load2DButtonGrid();
    LoadSimulateButtons();
    DrawMainWindow();
}

Window::~Window(){
    cout<<"Destructor called"<<endl;
    delete(MainWindowGrid_);
    delete(TwoDGridButtonGridLayout_);
    delete(SimulateButtonGrid_);
    delete(TwoDGridButtonBox_);
    delete(SimulateButtonBox_);
    for(int i = 0; i < raw_ ; i++){
        for(int j = 0 ; j<clm_; j++){
            delete(TwoDGridOfButtons_[i][j]);
        }
    }
}

// -------------- adding 2D grid 200 buttons to 2DGrid box---------------//
void Window::Load2DButtonGrid(){
    
    TwoDGridButtonBox_ = new QGroupBox;
    TwoDGridButtonGridLayout_ = new QGridLayout;

    //adding the many button to the layout
    vector<GridButton*> TempRowVec;
    for(int i = 0; i < raw_ ; i++){
        for(int j = 0 ; j<clm_; j++){
            GridButton* TempGridButtonObject = new GridButton(i,j);
            TempRowVec.push_back(TempGridButtonObject);
            TwoDGridButtonGridLayout_->addWidget(TempGridButtonObject->ButtonVar_,i,j);
        } 
        TwoDGridOfButtons_.push_back(TempRowVec);
        TempRowVec.clear();
    }
    TwoDGridButtonGridLayout_->setSpacing(0);
    TwoDGridButtonBox_->setLayout(TwoDGridButtonGridLayout_);
}

// --------------- adding A-Star and LOS button to box below to 2D grid box-------------//
void Window::LoadSimulateButtons(){

    SimulateButtonBox_ = new QGroupBox;
    SimulateButtonGrid_ = new QGridLayout;
    LOSButton_ = new QPushButton("Simulate LOS");
    AStarButton_= new QPushButton("Simulate A-Star");
    ResetButton_= new QPushButton("Reset");

    SimulateButtonGrid_->addWidget(LOSButton_,0,1);
    SimulateButtonGrid_->addWidget(AStarButton_,0,0);

    SimulateButtonBox_->setLayout(SimulateButtonGrid_);
}

//----------------Adding both layout to its grid then adding grid to main layout or window ---------------//
void Window::DrawMainWindow(){
    MainWindowGrid_ = new QGridLayout;

    //-----------adding both layout to main window--------//
    MainWindowGrid_->addWidget(TwoDGridButtonBox_,0,0,10,1);
    MainWindowGrid_->addWidget(SimulateButtonBox_,10,0,1,1);

    setLayout(MainWindowGrid_); //Addimg main grid to the window
    setWindowTitle(tr("LOS Algorithm"));
    //resize(100,200);
}