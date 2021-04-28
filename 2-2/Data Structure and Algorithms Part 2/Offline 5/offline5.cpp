#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<cstdlib>
#define INFINITY 10000;

//Ford Fulkerson Method

using namespace std;

typedef pair<int,int> Pair;


class Edge
{
    int u;
    int v;
    int c;
    int f;
public:
    Edge()
    {
    }

    setEdge(int u,int v,int c)
    {
        this->u=u;
        this->v=v;
        this->c=c;
        this->f = 0;
    }


    int getu()
    {
        return u;
    }

    int getv()
    {
        return v;
    }

    void setc(int c){
        this->c = c;
    }

    void add_c(int capacity)
    {
        this->c += capacity;
    }

    int getc() const
    {
        return c;
    }

    void setflow(int f)
    {
        this->f = f;
    }

    void addflow(int a)
    {
        this->f += a;
    }

    int getflow()
    {
        return f;
    }
};



class Graph
{
    int vertices;
    int edge;
    bool directed;
    vector<Pair> *AdjList;
    Edge *e;
    int *pred;

public:
    Graph(bool d)
    {
        directed=d;
        vertices=0;
        edge=0;
        pred = 0;
        AdjList=0;
    }

    void setnVertices(int n)
    {
        vertices=n;
        AdjList=new vector<Pair>[n];
        pred = new int[vertices];
    }

    void setEdges(int m)
    {
        e=new Edge[m];
    }

    bool addEdge(int u,int v,int c)
    {
        if(u<0 || u>=vertices || v<0 || v>=vertices)
            return false;
        if(isEdge(u,v))
            return false;
        e[edge].setEdge(u,v,c);
        AdjList[u].push_back(make_pair(v,c));
        if(!directed)
            AdjList[v].push_back(make_pair(u,c));
        edge++;
        return true;
    }

    bool addFlow(int u,int v,int add_f)
    {
        if(u<0 || u>=vertices || v<0 || v>=vertices)
            return false;

        for(int i = 0; i<edge; i++)
        {
            if(e[i].getu()==u && e[i].getv() ==v)
            {
                e[i].addflow(add_f);
                return true;
            }
        }
        // No edge found.
        return false;
    }

    bool setCapacity(int u,int v,int c)
    {
        if(u<0 || u>=vertices || v<0 || v>=vertices)
            return false;
        for(int i=0; i<AdjList[u].size(); i++)
        {
            if(AdjList[u][i].first==v)
            {
                AdjList[u][i].second = c;
                Edge* e = searchEdge(u,v);
                e->setc(c);
                return true;
            }
        }
        return false;
    }

    bool addCapacity(int u,int v,int c)
    {
        if(u<0 || u>=vertices || v<0 || v>=vertices)
            return false;
        for(int i=0; i<AdjList[u].size(); i++)
        {
            if(AdjList[u][i].first==v)
            {
                AdjList[u][i].second += c;
                Edge *e = searchEdge(u,v);
                e->add_c(c);
                return true;
            }
        }
        return false;
    }

    int getCapacity(int u,int v){
        if(u<0 || u>=vertices || v<0 || v>=vertices)
            return false;
        for(int i=0; i<AdjList[u].size(); i++)
        {
            if(AdjList[u][i].first==v)
            {
                return AdjList[u][i].second;
            }
        }
        return 0;
    }



    bool isEdge(int u,int v)
    {
        if(u<0 || u>=vertices || v<0 || v>=vertices)
            return false;
        for(int i=0; i<AdjList[u].size(); i++)
        {
            if(AdjList[u][i].first==v)
            {
                return true;
            }
        }
        return false;
    }

    Edge* searchEdge(int u, int v)
    {
        for(int i=0; i<edge ; i++)
        {
            if(e[i].getu()==u && e[i].getv()==v)
                return &e[i];
        }

    }



    bool bfs(int s, int t)
    {

        queue<int> q;
        bool visited[vertices];


        for (int i = 0; i < vertices; i++)
        {
            visited[i] = false;
            pred[i] = -1;
        }

        visited[s] = true;
        q.push(s);


        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < AdjList[u].size(); i++)
            {
                if (visited[AdjList[u][i].first] == false && AdjList[u][i].second!=0)
                {
                    visited[AdjList[u][i].first] = true;
                    pred[AdjList[u][i].first] = u;
                    q.push(AdjList[u][i].first);

                    if (AdjList[u][i].first == t)
                    {
                        return true;
                    }


                }
            }
        }


        return false;
    }

    void printGraph()
    {

        for(int i=0; i<edge; i++)
        {
            cout<<e[i].getu()<<" "<<e[i].getv()<<" "<<e[i].getflow()<<"/"<<e[i].getc()<<endl;
        }
    }



    Edge* edges()
    {
        return e;
    }

    int num_of_edge()
    {
        return edge;
    }

    int num_of_vertices()
    {
        return vertices;
    }

    int* predecessor_array()
    {
        return pred;
    }


    ~Graph()
    {

        delete[] AdjList;
        delete []e;
        delete []pred;
    }
};

Graph ResidualNetwork(int n,int m, Edge *e)
{
    Graph g_prime(true);
    g_prime.setnVertices(n);
    g_prime.setEdges(m*2);//Highest Number of Edge

    //two edges for both sides

    for(int i = 0; i<m ; i++)
    {
        int u = e[i].getu();
        int v = e[i].getv();
        int c = e[i].getc();
        int f = e[i].getflow();

        if(g_prime.isEdge(u,v)){
            g_prime.addCapacity(u,v,c-f);
            g_prime.addCapacity(v,u,f);
        }
        else{
            g_prime.addEdge(u,v,c-f);
            g_prime.addEdge(v,u,f);
        }

    }



    return g_prime;
}

int FordFulkersonMethod(Graph g, int s, int t)
{
    int n = g.num_of_vertices();
    int m = g.num_of_edge();
    Edge* e = g.edges();
    int maxflow = 0;
    for(int i = 0 ; i< m ; i++)
    {
        e[i].setflow(0);

    }


    Graph g_prime = ResidualNetwork(n,m,e);
    while(g_prime.bfs(s,t))
    {
        int *p = g_prime.predecessor_array();


        //Find Minimum Capacity
        int minflow = INFINITY;
        int vertex = t;
        while(vertex != s)
        {
            int parent = p[vertex];
            int capacity = g_prime.getCapacity(parent,vertex);


            if(capacity<minflow)
            {
                minflow = capacity;

            }
            vertex = parent;

        }

        // Augment Path
        vertex = t;
        while(vertex != s)
        {
            int parent = p[vertex];

            //reverse edge exists
            if(g.isEdge(vertex,parent)){
                Edge *ed = g.searchEdge(vertex,parent);
                int flow = ed->getflow();
                if(minflow>=flow){
                    ed->setflow(0);
                    g.addFlow(parent,vertex,minflow-flow);
                }
                else{
                    ed->setflow(flow-minflow);
                }
            }
            else{
               g.addFlow(parent,vertex,minflow);
            }


            g_prime.addCapacity(parent,vertex,-minflow);
            g_prime.addCapacity(vertex,parent,minflow);

            vertex = parent;

        }

        maxflow += minflow;



    }

    /*g.printGraph();
    cout<<"Maxflow: "<<maxflow<<endl;*/
    ofstream output_file;
    output_file.open("output.txt");
    output_file<<maxflow<<"\n";
    for(int i=0;i<m;i++){
        output_file<<e[i].getu()<<" "<<e[i].getv()<<" "<<e[i].getflow()<<"/"<<e[i].getc()<<"\n";
    }
    output_file.close();

    return maxflow;

}

int main()
{
    Graph g(true);
    ifstream infile;
    infile.open("input.txt");
    int n,m;
    infile>>n>>m;
    g.setnVertices(n);
    g.setEdges(m);
    int u,v,c;
    for(int i=0; i<m; i++)
    {
        infile>>u>>v>>c;
        g.addEdge(u,v,c);
    }
    int s,t;
    infile>>s>>t;
    infile.close();

    int maxflow = FordFulkersonMethod(g,s,t);

}
