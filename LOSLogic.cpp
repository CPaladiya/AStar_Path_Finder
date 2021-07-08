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
            connect(TempGridButtonObject->ButtonVar_,&QPushButton::clicked,this,&Window::RunLoopToDrawBlocks_);
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

//---------------------------adding delay anywhere we need to avoid data race-----------------------//
void Window::addDelay(){
    QTime dieTime= QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < dieTime)
        {QCoreApplication::processEvents(QEventLoop::AllEvents, 100);};
}

//-------------------------Drawing road blocks between two selected buttons---------------------------//
void Window::RunLoopToDrawBlocks_(){
    //addDelay();
    if(GridButton::drawRoadBlocks_ == true){
        cout<<GridButton::ClickUseCount_<<endl;
        GridButton::drawRoadBlocks_=false;
        int x1 = GridButton::firtsRoadBlock_XPos_;
        int y1 = GridButton::firtsRoadBlock_YPos_;
        int x2 = GridButton::lastRoadBlock_XPos_;
        int y2 = GridButton::lastRoadBlock_YPos_;
        int x_max = x1 > x2 ? x1 : x2 ;
        int y_max = y1 > y2 ? y1 : y2 ;
        int x_min = x1 < x2 ? x1 : x2 ;
        int y_min = y1 < y2 ? y1 : y2 ;

        for(int i = x_min; i<=x_max; i++){
            if(GridButton::totalRoadBlockCount_>99){
                    cout << "You can not select more than 100 road blocks"<<endl;
                    break;
                }
            for(int j = y_min; j<=y_max; j++){
                if(TwoDGridOfButtons_[i][j]->IsItStart_== false && TwoDGridOfButtons_[i][j]->IsItDestiny_==false){
                    TwoDGridOfButtons_[i][j]->ButtonVar_->setStyleSheet("background-color : black");
                    GridButton::totalRoadBlockCount_++;
                }
                
            }
        }
    }
}