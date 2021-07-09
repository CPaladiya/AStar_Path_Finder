#include "Window.h"

//----------------less than operator overloaded for comparision-------//

bool compare(const vector<float> FirstNode, const vector<float> SecondNode){
    return FirstNode[2]>SecondNode[2];
}

void Window::SortOpenNodes(vector<vector<float>> &OpenNodes){
    sort(OpenNodes.begin(), OpenNodes.end(), compare);
};

//calculating hueristic distance between two points
float Window::Distance(int X1, int Y1, int X2, int Y2){
    //cout<< sqrt((float)pow(abs(X1-Y1),2) + (float)pow(abs(X2-Y2),2))<<endl;
    return sqrt((float)pow(abs(X1-Y1),2) + (float)pow(abs(X2-Y2),2));
}

void Window::AddNeighbors(vector<vector<float>> &openGrid, const vector<float> &Node, const vector<float> &Finish){
    int x = (int)Node[0];
    int y = (int)Node[1];
    
    //adding all eight neigbors from the NeighborAddress array one by one
    for(int i=0; i<8; i++){
        int Xn = x + NeighborAddress[i][0];
        int Yn = y + NeighborAddress[i][1];
        //now checking ifthe new Xn and Yn adress is valid and the grid does not have road block over there
        bool XnISValid = (Xn >= 0 && Xn < (int)TwoDGridOfButtons_.size());
        bool YnISValid = (Yn >= 0 && Yn < (int)TwoDGridOfButtons_[0].size());
        if(XnISValid && YnISValid){
            bool XnYnIsBlock = TwoDGridOfButtons_[Xn][Yn]->ItsABlock_;
            bool XnYnVisitedAlready = TwoDGridOfButtons_[Xn][Yn]->ItsVisited_;
            if( !XnYnIsBlock && !XnYnVisitedAlready){
                cout<<"inside neighbor "<< Xn << " "<<Yn <<endl ;
                cout<<"inside neighbor float "<< (float)Xn << " "<< (float)Yn <<endl ;
                vector<float> temp{0,0};
                temp[0] = (float)Xn;
                temp[1] = (float)Yn;
                
                addDelay(SimulationSpeed);
                TwoDGridOfButtons_[Xn][Yn]->setNeighborColor();
                TwoDGridOfButtons_[Xn][Yn]->parent_ = {x,y};  //setting the new neighbor as children
                TwoDGridOfButtons_[Xn][Yn]->ItsVisited_ = true; //setting this new node as already visited
                //g distance for neighbor Xn Yn is the distance already travelled plus distance between Xn Yn and parent x and y
                TwoDGridOfButtons_[Xn][Yn]->DistFromStart_ = TwoDGridOfButtons_[x][y]->DistFromStart_+ Distance(Xn,x,Yn,y);
                //f-distance for neighbor Xn Yn is distUp unitill now and direct distance between node and goal
                TwoDGridOfButtons_[Xn][Yn]->TotalDistance_ = TwoDGridOfButtons_[Xn][Yn]->DistFromStart_ + Distance(Xn,Finish[0],Yn,Finish[1]);
                temp.push_back(TwoDGridOfButtons_[Xn][Yn]->TotalDistance_);
                openGrid.push_back(temp);
            }
        }
    }
};

void Window::AStarSearch() {
    
    vector<float> FN{0,0}; 
    FN[0] = (float)GridButton::Start_[0]; //First node
    FN[1] = (float)GridButton::Start_[1]; 
    cout<<"Start Point "<<FN[0]<<" "<<FN[1]<<endl;
    vector<float> LN{0,0};
    LN[0] = (float)GridButton::Finish_[0]; //Last node
    LN[1] = (float)GridButton::Finish_[1];
    cout<<"End Point "<<LN[0]<<" "<<LN[1]<<endl;
    
    TwoDGridOfButtons_[FN[0]][FN[1]]->DistFromStart_ = 0;
    
    //adding eligible neighbors of the first node
    AddNeighbors(OpenNodes_,FN,LN);
    //we will keep this loop running untill we reach either the goal or we run out of node to explore
    while(!OpenNodes_.empty()){
        SortOpenNodes(OpenNodes_); //now that we have added the neighbors, we will sort the vector
        vector<float> currentNode_ = OpenNodes_.back(); //getting the cell with minimum TotalDistance
        OpenNodes_.pop_back(); //removing that cell from the open vectors
        cout<< "Neighbors "<<currentNode_[0] <<" " <<LN[0]<<" " <<currentNode_[1]<<" " <<LN[1]<<endl;
        if((int)currentNode_[0]== (int)LN[0] && (int)currentNode_[1]==(int)LN[1]){
            cout<<"reached AStar break"<<endl;
            RegeneratePath();
            break;
        }
        addDelay(SimulationSpeed);
        TwoDGridOfButtons_[(int)currentNode_[0]][(int)currentNode_[1]]->setExplorerColor();
        AddNeighbors(OpenNodes_,currentNode_,LN);
    }
    cout<<"reached end of the loop"<<endl;
}

void Window::RegeneratePath(){

    //First we will generate Reverse result vector by first starting with finish and
    //we will keep fetching parent untill we reach home

    vector<int> Cn {GridButton::Finish_[0],GridButton::Finish_[1]}; //Current Node
    ReverseResultVector_.push_back(Cn); //adding finish node to reverse vector
    while(true){
        int ParentX = TwoDGridOfButtons_[Cn[0]][Cn[1]]->parent_[0]; //Fetching parent x index
        int ParentY = TwoDGridOfButtons_[Cn[0]][Cn[1]]->parent_[1]; //Fetching parent y index
        if(TwoDGridOfButtons_[ParentX][ParentY]->ItsHome_==true){ //Checking if the parent is not home/start node
            cout<<"reached regenration break"<<endl;
            break;
        }
        ReverseResultVector_.push_back({ParentX,ParentY}); //adding result to reverse vector
        Cn[0] = ParentX; //assigning parent node as next
        Cn[1] = ParentY;
    }
    ReverseResultVector_.push_back({GridButton::Finish_[0],GridButton::Finish_[1]}); //adding start node to reverse vector

    //now we will use Reverse result vector to produce forward result vector
    ForwardResultVector_ =  ReverseResultVector_;
    reverse(ForwardResultVector_.begin(), ForwardResultVector_.end());

    //next, we will simulate the Forward result vector to show the result on screen
    for(int i=0; i<(int)ForwardResultVector_.size(); i++){
        addDelay(SimulationSpeed);
        TwoDGridOfButtons_[ForwardResultVector_[i][0]][ForwardResultVector_[i][1]]->setFinalPathColor();
    }
}


