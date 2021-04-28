#include<iostream>
#include<fstream>
#include<sstream>
#include<queue>
#include<chrono>
#include<ctime>
#define INF 99999

using namespace std;
int startvertex;
int n;

int exact(int** tsp,int path[],int s,int f){
    if(s==f){
        int dis = tsp[startvertex][path[0]];
        for(int i=0;i<n-1;i++){
            //cout<<path[i]<<" ";
            if(i == n-2){
                dis += tsp[path[i]][startvertex];
                continue;
            }
            dis+=tsp[path[i]][path[i+1]];
        }
        //cout<<endl;
        return dis;
    }
    int min = INF;
    for(int i = s;i <= f; i++){
        int temp = path[i-1];
        path[i-1] = path[s-1];
        path[s-1] = temp;


        int dis = exact(tsp,path,s+1,f);
        if(dis<min) min = dis;
        temp = path[i-1];
        path[i-1] = path[s-1];
        path[s-1] = temp;

    }
    return min;
}

class Node{
public:
    int** ReducedMatrix;
    int cost;
    int vertex;
    int level;

};

Node* NewNode(int** ParentMatrix,int level,int i,int j){

    Node* node = new Node;
    node->level = level;
    node->vertex = j;

    node->ReducedMatrix = new int*[n];

    for(int r = 0; r<n; r++){
        node->ReducedMatrix[r] = new int[n];
        for(int col = 0; col<n; col++){
            node->ReducedMatrix[r][col] = ParentMatrix[r][col];

        }
    }


    if(level != 0){
        for(int k = 0;k<n;k++){
            node->ReducedMatrix[i][k] = INF;
            node->ReducedMatrix[k][j] = INF;
        }
        node->ReducedMatrix[j][startvertex] = INF;
    }
    return node;
}

int RowReduction(int** ReducedMatrix){
    int row[n];
    int sum = 0;
    for(int r = 0; r<n; r++){
        row[r] = INF;
        for(int col = 0; col<n; col++){
            if(row[r]>ReducedMatrix[r][col]){
                    row[r] = ReducedMatrix[r][col];
            }
        }
    }

    for(int r = 0; r<n; r++){
        for(int col = 0; col<n; col++){
            if(ReducedMatrix[r][col]!= INF && row[r]!=INF){
                ReducedMatrix[r][col]-=row[r];
            }
        }
        if(row[r] != INF){
            sum += row[r];
        }
    }

    return sum;
}

int ColumnReduction(int** ReducedMatrix){
    int column[n];
    int sum = 0;
    for(int col = 0; col<n; col++){
        column[col] = INF;
        for(int r = 0; r<n; r++){
            if(column[col]>ReducedMatrix[r][col]){
                    column[col] = ReducedMatrix[r][col];
            }
        }
    }

    for(int col = 0; col<n; col++){
        for(int r = 0; r<n; r++){
            if(ReducedMatrix[r][col]!= INF && column[col]!=INF){
                    ReducedMatrix[r][col]-=column[col];
            }

        }
        if(column[col] != INF){
            sum += column[col];
        }
    }

    return sum;
}

int calculateCost(int** ReducedMatrix){
    return RowReduction(ReducedMatrix) + ColumnReduction(ReducedMatrix) ;
}

struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};


int BranchAndBound(int** tsp){
    priority_queue<Node*, std::vector<Node*>, comp> pq;
    Node* root = NewNode(tsp,0,-1,0);
    root->cost = calculateCost(root->ReducedMatrix);
    pq.push(root);

    while(!pq.empty()){
        Node* parent = pq.top();
        pq.pop();

        int i = parent->vertex;

        if(parent->level == n-1){
            return parent->cost;
        }

        for(int k = 0;k<n;k++){
            if(parent->ReducedMatrix[i][k] != INF){
                Node *child = NewNode(parent->ReducedMatrix,parent->level+1,i,k);
                child->cost = parent->cost + parent->ReducedMatrix[i][k] + calculateCost(child->ReducedMatrix);
                pq.push(child);
            }
        }

        delete parent;
    }
}

int main(){

    startvertex = 0;

    int **tsp = new int*[n];
    int **costMatrix = new int*[n];
    ifstream in;
    in.open("input.txt");
    in>>n;
    for(int k = 0 ;k<n;k++){
        tsp[k] = new int[n];
        costMatrix[k] = new int[n];
        for(int l = 0 ;l<n;l++){
            in>>tsp[k][l];
            costMatrix[k][l] = tsp[k][l];

            if(k == l){
                costMatrix[k][l] = INF;
                tsp[k][l] = 0;
            }
            //cout<<tsp[k][l]<<" ";
        }
    }


    int j = 0;

    int path[n-1];
    for(int i = 0; i<n;i++){
        if(i == startvertex){
            continue;
        }
        path[j] = i;
        j++;
    }

    auto start=chrono::steady_clock::now();
    int exactdis = exact(tsp,path,1,n-1);
    auto finish=chrono::steady_clock::now();
    int exact_time=chrono::duration_cast<chrono::microseconds>(finish- start).count()/10.0;

    cout<<exactdis<<": "<<exact_time<<endl;


    start=chrono::steady_clock::now();
    int bbdis = BranchAndBound(costMatrix);
    finish=chrono::steady_clock::now();
    int bb_time=chrono::duration_cast<chrono::microseconds>(finish- start).count()/10.0;


    cout<<bbdis<<": "<<bb_time<<endl;
    in.close();
}
