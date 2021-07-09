#include "Window.h"
#include "AStarLogic.cpp"

Window::Window(QWidget *parent): QWidget(parent){
    Load2DButtonGrid();
    LoadSimulateButtons();
    DrawMainWindow();
    connect(AStarButton_,&QPushButton::clicked,this,&Window::AStarSearch);
    connect(ResetButton_,&QPushButton::clicked,this,&Window::ResetEverything);
}

Window::~Window(){
    cout<<"Destructor called"<<endl;
    delete(MainWindowGrid_);
    delete(TwoDGridButtonGridLayout_);
    delete(SimulateButtonGrid_);
    delete(TwoDGridButtonBox_);
    delete(SimulateButtonBox_);

    //---------------All QGridLayout variables-----------------------//

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
    SimulateButtonGrid_->addWidget(ResetButton_,0,3);

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
void Window::addDelay(int n){
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        {QCoreApplication::processEvents(QEventLoop::AllEvents, 50);};
}

//-------------------------Drawing road blocks between two selected buttons---------------------------//
// This function will draw blocks between two selected points and make sure that it does not increase
//beyond total block number of 100
void Window::RunLoopToDrawBlocks_(){
    addDelay(50);//add delay to make sure that the static variable drawRoadBlocks_ is available
    //first checking the permission to drawing road blocks is given
    if(GridButton::drawRoadBlocks_ == true){
        cout<<GridButton::ClickUseCount_<<endl;
        GridButton::drawRoadBlocks_=false; //setting the permission to false for the next use
        //fetching the starting and diagonal ending point of the road block series we want to draw
        int x1 = GridButton::firtsRoadBlock_XPos_;
        int y1 = GridButton::firtsRoadBlock_YPos_;
        int x2 = GridButton::lastRoadBlock_XPos_;
        int y2 = GridButton::lastRoadBlock_YPos_;
        
        //making sure loop is running from smaller coordinates to bigger
        int x_max = x1 > x2 ? x1 : x2 ;
        int y_max = y1 > y2 ? y1 : y2 ;
        int x_min = x1 < x2 ? x1 : x2 ;
        int y_min = y1 < y2 ? y1 : y2 ;

        //checking if we have not clicked on the same button twice, in that case we wont run the loop
        if(x_max != x_min && y_max != y_min){
            for(int i = x_min; i<=x_max; i++){
                //checking to see if total road block buttons has note gone more than 100 (0 to 99) here
                //if that's the case we will just get out of the loop
                if(GridButton::totalRoadBlockCount_>99){
                    cout << "You can not select more than 100 road blocks"<<endl;
                    break;
                }
                for(int j = y_min; j<=y_max; j++){
                    //making sure that we are not overriding the button which are already asigned as start and finish
                    if(TwoDGridOfButtons_[i][j]->ItsAStart_== false && TwoDGridOfButtons_[i][j]->ItsAFinish_==false){
                        TwoDGridOfButtons_[i][j]->ButtonVar_->setStyleSheet("background-color : black"); //setting the black background
                        TwoDGridOfButtons_[i][j]->ItsABlock_=true; //setting that button has block
                        GridButton::totalRoadBlockCount_++; //increasing the road block count
                    }    
                }
            }
        }
    }
}

//resetting the simulation screen
void Window::ResetEverything(){
    
    //resetting all the GridButton Static variables
    GridButton::ClickUseCount_=0;
    GridButton::firtsRoadBlock_XPos_=0;
    GridButton::firtsRoadBlock_YPos_=0;
    GridButton::lastRoadBlock_XPos_=0;
    GridButton::lastRoadBlock_YPos_=0;
    GridButton::drawRoadBlocks_=false;
    GridButton::totalRoadBlockCount_=0;
    GridButton::Start_={0,0};
    GridButton::Finish_={0,0};

    //resetting all the nodes in 2D grid
    for(int i = 0; i < raw_ ; i++){
        for(int j = 0 ; j<clm_; j++){
            TwoDGridOfButtons_[i][j]->DistFromStart_=0;
            TwoDGridOfButtons_[i][j]->TotalDistance_=0;
            TwoDGridOfButtons_[i][j]->ItsHome_ = false;
            TwoDGridOfButtons_[i][j]->ItsVisited_ = false;
            TwoDGridOfButtons_[i][j]->ItsABlock_ =false;
            TwoDGridOfButtons_[i][j]->ItsAStart_ = false;
            TwoDGridOfButtons_[i][j]->ItsAFinish_=false;
            TwoDGridOfButtons_[i][j]->ButtonVar_->setStyleSheet("background-color : whitesmoke");
        }
    }

    //clear all the Window object variables
    OpenNodes_.clear();
}