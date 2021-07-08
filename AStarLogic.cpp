#include "Window.h"

//----------------less than operator overloaded for comparision-------//
bool Window::Compare(const vector<int> FirstNode, const vector<int> SecondNode){

    int x1 = FirstNode[0];
    int y1 = FirstNode[1];
    int x2 = SecondNode[0];
    int y2 = SecondNode[1]; 
    return (TwoDGridOfButtons_[x1][y1]->TotalDistance_)>(TwoDGridOfButtons_[x2][y2]->TotalDistance_);

}

void Window::SortOpenNodes(){
    sort(OpenNodes_.begin(), OpenNodes_.end(), Compare);
};

//calculating hueristic distance between two points
float Window::Distance(int X1, int Y1, int X2, int Y2){
    return sqrt((float)pow(abs(X1-Y1),2) + (float)pow(abs(X2-Y2),2));
}

void Window::AddNeighbors(vector<vector<int>> &openGrid, const vector<int> &Node, const vector<int> &Finish){
    int x = Node[0];
    int y = Node[1];
    
    //adding all eight neigbors from the NeighborAddress array one by one
    for(int i=0; i<8; i++){
        int Xn = x + NeighborAddress[i][0];
        int Yn = y + NeighborAddress[i][1];
        //now checking if the new Xn and Yn adress is valid and the grid does not have road block over there
        bool XnISValid = Xn >= 0 && Xn < TwoDGridOfButtons_.size();
        bool YnISValid = Yn >= 0 && Yn < TwoDGridOfButtons_.size();
        bool XnYnIsOpenRoad = !(TwoDGridOfButtons_[Xn][Yn]->ItsABlock_);
        bool XnYnNotVisitedAlready = !(TwoDGridOfButtons_[Xn][Yn]->ItsVisited_);
        if(XnISValid && YnISValid && XnYnIsOpenRoad && XnYnNotVisitedAlready){
            vector<int> temp{Xn,Yn};
            openGrid.push_back(temp);
            TwoDGridOfButtons_[Xn][Yn]->parent_ = {x,y};  //setting the new neighbor as children
            TwoDGridOfButtons_[Xn][Yn]->ItsVisited_ = true; //setting this new node as already visited
            //g distance for neighbor Xn Yn is the distance already travelled plus distance between Xn Yn and parent x and y
            TwoDGridOfButtons_[Xn][Yn]->DistFromStart_ = TwoDGridOfButtons_[x][y]->DistFromStart_+ Distance(Xn,x,Yn,y);
            //f-distance for neighbor Xn Yn is distUp unitill now and direct distance between node and goal
            TwoDGridOfButtons_[Xn][Yn]->TotalDistance_ = TwoDGridOfButtons_[Xn][Yn]->DistFromStart_ + Distance(Xn,Finish[0],Yn,Finish[1]);
        }
    }
};

void Window::AStarSearch() {
    
    vector<int> FN = GridButton::Start_; //First node
    vector<int> LN = GridButton::Finish_; //Goal node
    OpenNodes_.push_back(FN); //adding the first node to the open nodes
    TwoDGridOfButtons_[FN[0]][FN[1]]->DistFromStart_ = 0;
    
    //adding eligible neighbors of the first node
    AddNeighbors(OpenNodes_,FN,LN);
    //we will keep this loop running untill we reach either the goal or we run out of node to explore
    while(!OpenNodes_.empty()){
        SortOpenNodes(); //now that we have added the neighbors, we will sort the vector
        vector<int> currentNode_ = OpenNodes_.back(); //getting the cell with minimum TotalDistance
        OpenNodes_.pop_back(); //removing that cell from the open vectors
        if(currentNode_[0]==LN[0] && currentNode_[1]==LN[1]){
            //RegeneratePath();
        }
        AddNeighbors(OpenNodes_,currentNode_,LN);
    }
    cout<<"No Path Found"<<endl;
}

void Window::RegeneratePath(){
    vector<int> Cn {GridButton::Finish_[0],GridButton::Finish_[1]}; //Current Node
    while(!(TwoDGridOfButtons_[Cn[0]][Cn[1]]->ItsHome_)){

        int ParentX = TwoDGridOfButtons_[Cn[0]][Cn[1]]->parent_[0];
        int ParentY = TwoDGridOfButtons_[Cn[0]][Cn[1]]->parent_[1];
        TwoDGridOfButtons_[ParentX][ParentY]->setOrageColor();
        Cn[0] = ParentX;
        Cn[1] = ParentY;
    }

}

