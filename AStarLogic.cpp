#include "Window.h"

//----------------less than operator overloaded for comparision-------//

bool compare(const vector<float> FirstNode, const vector<float> SecondNode){
    //cout<< FirstNode[2] << " "<<SecondNode[2];
    return FirstNode[2]>SecondNode[2];
}

void Window::SortOpenNodes(vector<vector<float>> &OpenNodes){
    sort(OpenNodes.begin(), OpenNodes.end(), compare);
};

//calculating hueristic distance between two points
float Window::Distance(int X1, int Y1, int X2, int Y2){
    cout<< sqrt((float)pow(abs(X1-Y1),2) + (float)pow(abs(X2-Y2),2))<<endl;
    return sqrt((float)pow(abs(X1-Y1),2) + (float)pow(abs(X2-Y2),2));
}

void Window::AddNeighbors(vector<vector<float>> &openGrid, const vector<float> &Node, const vector<float> &Finish){
    int x = (int)Node[0];
    int y = (int)Node[1];
    
    //adding all eight neigbors from the NeighborAddress array one by one
    for(int i=0; i<8; i++){
        cout<<"loop running"<<endl;
        int Xn = x + NeighborAddress[i][0];
        int Yn = y + NeighborAddress[i][1];
        //now checking if the new Xn and Yn adress is valid and the grid does not have road block over there
        bool XnISValid = Xn >= 0 && Xn < (int)TwoDGridOfButtons_.size();
        bool YnISValid = Yn >= 0 && Yn < (int)TwoDGridOfButtons_.size();
        bool XnYnIsOpenRoad = !(TwoDGridOfButtons_[Xn][Yn]->ItsABlock_);
        bool XnYnNotVisitedAlready = !(TwoDGridOfButtons_[Xn][Yn]->ItsVisited_);
        if(XnISValid && YnISValid && XnYnIsOpenRoad && XnYnNotVisitedAlready){
            vector<float> temp{(float)Xn,(float)Yn};
            TwoDGridOfButtons_[Xn][Yn]->parent_ = {x,y};  //setting the new neighbor as children
            TwoDGridOfButtons_[Xn][Yn]->ItsVisited_ = true; //setting this new node as already visited
            //g distance for neighbor Xn Yn is the distance already travelled plus distance between Xn Yn and parent x and y
            TwoDGridOfButtons_[Xn][Yn]->DistFromStart_ = TwoDGridOfButtons_[x][y]->DistFromStart_+ Distance(Xn,x,Yn,y);
            //f-distance for neighbor Xn Yn is distUp unitill now and direct distance between node and goal
            TwoDGridOfButtons_[Xn][Yn]->TotalDistance_ = TwoDGridOfButtons_[Xn][Yn]->DistFromStart_ + Distance(Xn,Finish[0],Yn,Finish[1]);
            temp.push_back(TwoDGridOfButtons_[Xn][Yn]->TotalDistance_);
            openGrid.push_back(temp);
        } cout<<"loop ended"<<endl;
    }
};

void Window::AStarSearch() {
    
    vector<float> FN{0,0}; 
    FN[0] = (float)GridButton::Start_[0]; //First node
    FN[1] = (float)GridButton::Start_[1]; 
    vector<float> LN{0,0};
    LN[0] = (float)GridButton::Finish_[0]; //Last node
    LN[1] = (float)GridButton::Finish_[1];
    
    TwoDGridOfButtons_[FN[0]][FN[1]]->DistFromStart_ = 0;
    
    //adding eligible neighbors of the first node
    AddNeighbors(OpenNodes_,FN,LN);
    //we will keep this loop running untill we reach either the goal or we run out of node to explore
    while(!OpenNodes_.empty()){
        SortOpenNodes(OpenNodes_); //now that we have added the neighbors, we will sort the vector
        vector<float> currentNode_ = OpenNodes_.back(); //getting the cell with minimum TotalDistance
        OpenNodes_.pop_back(); //removing that cell from the open vectors
        cout<<currentNode_[0] << " " <<LN[0]<<" " <<currentNode_[1]<<" " <<LN[1]<<endl;
        if((int)currentNode_[0]== (int)LN[0] && (int)currentNode_[1]==(int)LN[1]){
            cout<<"we reached here"<<endl;
            RegeneratePath();
            break;
        }
        AddNeighbors(OpenNodes_,currentNode_,LN);
    }
}

void Window::RegeneratePath(){
    vector<int> Cn {GridButton::Finish_[0],GridButton::Finish_[1]}; //Current Node
    while(true){

        int ParentX = TwoDGridOfButtons_[Cn[0]][Cn[1]]->parent_[0];
        int ParentY = TwoDGridOfButtons_[Cn[0]][Cn[1]]->parent_[1];
        if(TwoDGridOfButtons_[ParentX][ParentY]->ItsHome_==true){
            break;
        }
        TwoDGridOfButtons_[ParentX][ParentY]->setOrageColor();
        Cn[0] = ParentX;
        Cn[1] = ParentY;
    }
}


