#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<cstdlib>
#define INFINITY 100000
#define NIL -1

using namespace std;

typedef pair<double,int> Pair;

class Edge
{
    int u;
    int v;
    double w;

public:
    void setEdge(int u,int v,double w)
    {
        this->u=u;
        this->v=v;
        this->w=w;
    }

    int getu()
    {
        return u;
    }

    int getv()
    {
        return v;
    }

    double getweight()
    {
        return w;
    }

    void reweight(double w)
    {
        this->w=w;
    }

};

class Graph
{
    int vertices;
    bool directed;
    double **Distance_Matrix;
    int **parentMatrix;
    int nEdges;
    vector<Edge> *AdList;
    double *h;

public:
    Graph(bool dir)
    {
        directed=dir;
        nEdges=0;
        Distance_Matrix=0;
        parentMatrix=0;
        AdList=0;
    }

    void setnVertices(int n)
    {
        vertices=n;
        Distance_Matrix=new double*[n];
        parentMatrix=new int*[n];
        for(int i=0; i<n; i++)
        {
            Distance_Matrix[i]=new double[n];
            parentMatrix[i]=new int[n];

            for(int j=0; j<n; j++)
            {
                Distance_Matrix[i][j]=INFINITY;
                parentMatrix[i][j]=NIL;
            }
        }
        AdList= new vector<Edge>[n];
        h=new double[vertices];
    }

    bool isEdge(int u,int v)
    {
        if(!(u<vertices&&u>0))
            return false;
        for(int i=0; i<AdList[u].size(); i++)
        {
            if(AdList[u][i].getv()==v)
            {
                return true;
            }
        }
        return false;

    }

    bool addEdge(int u,int v,double w)
    {
        if(isEdge(u,v))
            return false;
        Edge ed;
        ed.setEdge(u,v,w);
        AdList[u].push_back(ed);
        if(!directed)
        {
            Edge ed1;
            ed1.setEdge(v,u,w);
            AdList[v].push_back(ed1);
        }
    }

    void printGraph()
    {
        cout<<"Graph:"<<endl;
        for(int i=1; i<vertices; i++)
        {
            cout<<i<<" :";
            for(int j=0; j<AdList[i].size(); j++)
            {
                cout<<AdList[i][j].getv()<<"("<<AdList[i][j].getweight()<<")";
                if(j!=AdList[i].size()-1) cout<<"-->";
            }
            cout<<endl;
        }
    }

    void removeEdge(int u,int v)
    {
        for(int i=0; i<AdList[u].size(); i++)
        {
            if(AdList[u][i].getv()==v)
            {
                AdList[u].erase(AdList[u].begin()+i);
                if(!directed)
                {
                    for(int j=0; j<AdList[v].size(); j++)
                    {
                        if(AdList[v][j].getv()==u)
                        {
                             AdList[v].erase(AdList[v].begin()+j);
                             break;
                        }
                    }
                }
                break;
            }
        }
    }

    Edge *searchEdge(int u,int v)
    {
        for(int i=0; i<AdList[u].size(); i++)
        {
            if(AdList[u][i].getv()==v)
            {
                return &AdList[u][i];
            }
        }
        return NULL;
    }

    void reweightEdge(int u,int v,double w)
    {
        Edge* edge_found=searchEdge(u,v);
        if(edge_found==NULL)
            addEdge(u,v,w);
        else
        {
            edge_found->reweight(w);
        }
    }

    double getWeight(int u,int v)
    {
        if(!isEdge(u,v))
            return INFINITY;
        else
        {
            return searchEdge(u,v)->getweight();
        }
    }

    void floydWarshall()
    {
        for(int i=1; i<vertices; i++)
        {
            for(int j=1; j<vertices; j++)
            {
                if(i==j)
                {
                    Distance_Matrix[i][j]=0;
                }
                else
                {
                    if(isEdge(i,j))
                    {
                        Distance_Matrix[i][j]=getWeight(i,j);
                        parentMatrix[i][j]=i;
                    }
                }
            }
        }

        for(int k=1; k<vertices; k++)
        {
            for(int i=1; i<vertices; i++)
            {
                for(int j=1; j<vertices; j++)
                {
                    if(Distance_Matrix[i][j]>Distance_Matrix[i][k]+Distance_Matrix[k][j] && Distance_Matrix[i][k]!=INFINITY && Distance_Matrix[k][j]!= INFINITY )
                    {
                        Distance_Matrix[i][j]=Distance_Matrix[i][k]+Distance_Matrix[k][j];
                        parentMatrix[i][j]=parentMatrix[k][j];
                    }
                }
            }
        }
    }


    bool bellmanFord()
    {
        for(int i=1; i<vertices; i++)
        {
            addEdge(0,i,0);
            h[i]=INFINITY;
        }
        h[0]=0;
        for(int i=0; i<vertices-1; i++)
        {
            for(int j=0; j<vertices; j++)
            {
                for(int k=0; k<AdList[j].size(); k++)
                {
                    Edge e=AdList[j][k];
                    int u=e.getu();
                    int v=e.getv();
                    double w=e.getweight();
                    if(h[v]>h[u]+w&&h[u]!=INFINITY)
                    {
                        h[v]=h[u]+w;
                    }
                }
            }
        }

        //Negative Weight Cycle
        for(int i=0; i<vertices-1; i++)
        {
            for(int j=0; j<vertices; j++)
            {
                for(int k=0; k<AdList[j].size(); k++)
                {
                    Edge e=AdList[j][k];
                    int u=e.getu();
                    int v=e.getv();
                    double w=e.getweight();
                    if(h[v]>h[u]+w&&h[u]!=INFINITY)
                    {
                        return false;
                    }
                }
            }
        }
        return true;

    }

    void djikstra(int n)
    {
        Distance_Matrix[n][n]=0;
        priority_queue<Pair,vector<Pair>,greater<Pair>> pq;
        pq.push(make_pair(Distance_Matrix[n][n],n));

        while(!pq.empty())
        {
            int u=pq.top().second;
            pq.pop();

            for(int i=0; i<AdList[u].size(); i++)
            {
                int v=AdList[u][i].getv();
                double w=AdList[u][i].getweight();

                if(Distance_Matrix[n][u]+w<Distance_Matrix[n][v])
                {
                    parentMatrix[n][v]=u;
                    Distance_Matrix[n][v]=Distance_Matrix[n][u]+w;
                    pq.push(make_pair(Distance_Matrix[n][v],v));
                }
            }
        }

    }

    void johnsonAlgo()
    {
        bool choice=bellmanFord();
        if(!choice)
        {
            cout<<"There is a negative-weight cycle"<<endl;
            return;
        }
        for(int i=1; i<vertices; i++)
        {
            for(int j=0; j<AdList[i].size(); j++)
            {
                int u=AdList[i][j].getu();
                int v=AdList[i][j].getv();
                double w=AdList[i][j].getweight();
                double new_weight=w+h[u]-h[v];
                AdList[i][j].reweight(new_weight);

            }
        }

        for(int i=1; i<vertices; i++)
        {
            djikstra(i);
            for(int j=1;j<vertices;j++){
                Distance_Matrix[i][j]=Distance_Matrix[i][j]+h[j]-h[i];
            }
        }

        for(int i=1; i<vertices; i++)
        {
            for(int j=0; j<AdList[i].size(); j++)
            {
                int u=AdList[i][j].getu();
                int v=AdList[i][j].getv();
                double w=AdList[i][j].getweight();
                double new_weight=w+h[v]-h[u];
                AdList[i][j].reweight(new_weight);

            }
        }
    }

    double getShortestPathWeight(int u,int v)
    {
        return Distance_Matrix[u][v];
    }

    void printShortestPath(int u,int v)
    {
        if(Distance_Matrix[u][v]==INFINITY){
            cout<<"No Path"<<endl;
            return;
        }
        vector<int> s;
        int parent=v;
        while(parent!=u)
        {
            s.push_back(parent);
            parent=parentMatrix[u][parent];
        }
        s.push_back(parent);
        int temp=s.back();
        cout<<temp<<"->";
        s.pop_back();
        while(!s.empty())
        {
            if(s.size()==1){
                cout<<s.back()<<"("<<Distance_Matrix[temp][s.back()]<<")";
            }
            else
                cout<<s.back()<<"("<<Distance_Matrix[temp][s.back()]<<")-->";
            temp=s.back();
            s.pop_back();
        }
    }

    void printDistanceMatrix()
    {
        for(int i=1; i<vertices; i++)
        {
            for(int j=1; j<vertices; j++)
            {
                if(Distance_Matrix[i][j]==INFINITY) cout<<"INF ";
                else cout<<Distance_Matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void printPredecessorMatrix()
    {
        for(int i=1; i<vertices; i++)
        {
            for(int j=1; j<vertices; j++)
            {
                if(parentMatrix[i][j]==NIL) cout<<"NIL ";
                else cout<<parentMatrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }


    void cleanSPInfo()
    {
        for(int i=0; i<vertices; i++)
        {
            for(int j=0; j<vertices; j++)
            {
                Distance_Matrix[i][j]=INFINITY;
                parentMatrix[i][j]=NIL;
            }
        }
    }

    ~Graph()
    {
        for(int i=0; i<vertices; i++)
        {
            delete[] Distance_Matrix[i];
            delete[] parentMatrix[i];
        }

        delete []Distance_Matrix;
        delete[] parentMatrix;
        delete []AdList;
    }
};

int main()
{
    Graph g(true);
    int n,m;
    cin>>n;
    cin>>m;
    g.setnVertices(n+1);
    for(int i=0; i<m; i++)
    {
        int u,v;
        double w;
        cin>>u;
        cin>>v;
        cin>>w;
        g.addEdge(u,v,w);
    }
    cout<<"Graph Created"<<endl;
    while(1)
    {
        cout<<endl;
        cout<<"1 :Clear_SP_Values  2:Floyd-Warshall   3.Johnson     4.Query "<<endl;
        cout<<"5.Print Graph     6:Print Distance Matrix     7.Print Predecessor Matrix "<<endl;
        int c;
        cin>>c;
        cout<<endl;
        if(c==1)
        {
            g.cleanSPInfo();
            cout<<"APSP Matrices Cleared"<<endl;
        }
        else if(c==2)
        {
            g.floydWarshall();
            cout<<"Floyd-Warshall Algorithm Implemented"<<endl;
        }
        else if(c==3)
        {
            g.johnsonAlgo();
            cout<<"Johnson's Algorithm Implemented"<<endl;
        }
        else if(c==4)
        {
            int u,v;
            cin>>u;
            cin>>v;
            cout<<"Shortest Path Weight: "<<g.getShortestPathWeight(u,v)<<endl;
            cout<<"Path: ";
            g.printShortestPath(u,v);
            cout<<endl;
        }
        else if(c==5)
        {
            g.printGraph();
        }
        else if(c==6)
        {
            g.printDistanceMatrix();
        }
        else if(c==7)
        {
            g.printPredecessorMatrix();
        }
        else
            break;
    }
}




