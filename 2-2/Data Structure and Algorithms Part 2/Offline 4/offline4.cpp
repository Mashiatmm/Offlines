#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstdlib>

using namespace std;

typedef pair<int,int> Pair;


class DisjointSet{
    int n;
    int *parent;
    int *rank;

public:
    DisjointSet(int n){
        this->n=n;
        parent=new int[n];
        rank=new int[n];
        for(int i=0;i<n;i++) parent[i]=-1;
    }

    void MakeSet(int x){
        parent[x]=x;
        rank[x]=0;
    }

    int FindSet(int x){
        if(parent[x]==-1) return -1;
        if(parent[x]!=x){
            parent[x]=FindSet(parent[x]);
        }
        return parent[x];
    }

    void Union(int u,int v){
        if(parent[u]==-1||parent[v]==-1) return;
        int urank=rank[u];
        int vrank=rank[v];

        if(urank>vrank){
            parent[v]=u;
        }
        else if(urank<vrank){
            parent[u]=v;
        }
        else{
            parent[u]=v;
            rank[u]++;
        }
    }
};

class Edge{
    int u;
    int v;
    int w;
public:
    void setEdge(int u,int v,int w){
        this->u=u;
        this->v=v;
        this->w=w;
    }

    int getu(){
        return u;
    }

    int getv(){
        return v;
    }

    int getw() const{
        return w;
    }
};


bool compare(const Edge & l, const Edge & r)
{
    return l.getw() < r.getw();
}

class Graph{
    int vertices;
    int edge;
    bool directed;
    vector<Pair> *AdjList;
    Edge *e;

public:
    Graph(bool d){
        directed=d;
        vertices=0;
        edge=0;
        AdjList=0;
    }

    void setnVertices(int n){
        vertices=n;
        AdjList=new vector<Pair>[n];
    }

    void setEdges(int m){
        e=new Edge[m];
    }

    bool addEdge(int u,int v,int w){
        if(u<0 || u>=vertices || v<0 || v>=vertices) return false;
        if(isEdge(u,v)) return false;
        e[edge].setEdge(u,v,w);
        AdjList[u].push_back(make_pair(v,w));
        if(!directed) AdjList[v].push_back(make_pair(u,w));
        edge++;
    }

    void printGraph(){
        for(int i=0;i<vertices;i++){
            cout<<i<<": ";
            for(int j=0;j<AdjList[i].size();j++){
                cout<<AdjList[i][j].first<<"("<<AdjList[i][j].second<<") ";
            }
            cout<<endl;
        }
    }


    bool isEdge(int u,int v){
        if(u<0 || u>=vertices || v<0 || v>=vertices) return false;
        for(int i=0; i<AdjList[u].size(); i++)
        {
            if(AdjList[u][i].first==v)
            {
                return true;
            }
        }
        return false;
    }

    void KruskalAlgo(){
        int cost=0;
        sort(e,&e[edge],compare);

        DisjointSet Set(vertices);
        for(int i=0;i<vertices;i++){
            Set.MakeSet(i);
        }
        int count=0,idx=0;
        Edge result[vertices-1];
        while(count<vertices-1){
            int x=Set.FindSet(e[idx].getu());
            int y=Set.FindSet(e[idx].getv());

            if(x!=y){
                Set.Union(x,y);
                cost+=e[idx].getw();
                result[count]=e[idx];
                count++;
            }

            idx++;
        }
        /*cout<<cost<<endl;
        cout<<"Kruskal's Algorithm:"<<endl;
        for(int i=0;i<vertices-1;i++){
            cout<<result[i].getu()<<" "<<result[i].getv()<<endl;
        }*/
        ofstream output_file;
        output_file.open("output.txt");
        output_file<<cost<<"\n";
        output_file<<"Kruskal's Algorithm:\n";
        for(int i=0;i<vertices-1;i++){
            output_file<<result[i].getu()<<" "<<result[i].getv()<<"\n";
        }
        output_file.close();
    }

    void Prim(){
        int key[vertices];
        int visit[vertices];
        int parent[vertices];
        priority_queue<Pair,vector<Pair>,greater<Pair>> pq;
        for(int i=0;i<vertices;i++){
            key[i]=INFINITY;
            visit[i]=0;
            parent[i]=-1;
        }
        cout<<"Prim's Algorithm:"<<endl;

        Edge result[vertices-1];
        int count=0;
        int root=rand()%vertices;
        key[root]=0;
        pq.push(make_pair(key[root],root));

        while(!pq.empty()){
            int u=pq.top().second;
            pq.pop();
            if(visit[u]==1) continue;
            visit[u]=1;
            Edge ed;
            ed.setEdge(parent[u],u,pq.top().first);
            if(parent[u]!=-1){
                result[count]=ed;
                count++;
            }
            for(int i=0;i<AdjList[u].size();i++){
                int v=AdjList[u][i].first;
                int w=AdjList[u][i].second;
                if(visit[v]==0&&key[v]>key[u]+w){
                    key[v]=key[u]+w;
                    parent[v]=u;
                    pq.push(make_pair(key[v],v));
                }
            }
        }

        cout<<"Root Node= "<<root<<endl;
        for(int i=0;i<vertices-1;i++){
            cout<<result[i].getu()<<" "<<result[i].getv()<<endl;
        }

        ofstream output_file;
        output_file.open("output.txt",ios::out|ios::app);
        output_file<<"Prim's Algorithm:\n";
        output_file<<"Root Node= "<<root<<"\n";
        for(int i=0;i<vertices-1;i++){
            output_file<<result[i].getu()<<" "<<result[i].getv()<<"\n";
        }
        output_file.close();
    }

    ~Graph(){

        delete[] AdjList;
        delete []e;
    }
};


int main(){
    Graph g(false);
    ifstream infile;
    infile.open("input.txt");
    int n,m;
    infile>>n>>m;
    g.setnVertices(n);
    g.setEdges(m);
    int u,v;
    int w;
    for(int i=0;i<m;i++){
        infile>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    infile.close();
    g.printGraph();
    g.KruskalAlgo();
    g.Prim();
}
