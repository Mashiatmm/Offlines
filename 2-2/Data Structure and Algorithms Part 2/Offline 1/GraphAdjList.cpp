#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<chrono>
#include<ctime>
#define WHITE 0
#define GREY 1
#define BLACK 2
#define INFINITY 99999

using namespace std;

class queue{
    int maxsize;
    int size;
    int *ar;
    int front;
    int rear;

public:
    queue(){
        maxsize=2;
        ar=new int[maxsize];
        front=0;
        rear=0;
        size=0;
    }

    void enqueue(int item){
        if(size==maxsize){
            maxsize*=2;
            int *temp=new int[maxsize];
            int j=0;
            for(int i=front;i<size;i++){
                temp[j++]=ar[i];
            }
            for(int i=0;i<front;i++){
                temp[j++]=ar[i];
            }
            delete []ar;
            front=0;
            rear=size;
            ar=temp;
        }
        ar[rear]=item;
        rear=(rear+1)%maxsize;
        size++;
    }

    int dequeue(){
        if(size==0) return -999999;
        int temp=ar[front];
        front=(front+1)%maxsize;
        size--;
        return temp;
    }

    bool empty(){
        if(size==0) return true;
        else return false;
    }

    ~queue(){
        if(ar) delete[] ar;
    }
};

class Arraylist{
    int *list;
    int size;
    int maxsize;

public:
    Arraylist(){
        maxsize=2;
        list=new int[maxsize];
        size=0;
    }

    int searchItem(int item){
        for(int i=0;i<size;i++){
            if(list[i]==item) return i;
        }
        return -1;
    }

    void insertItem(int item){
        if(size==maxsize){
            maxsize*=2;
            list=(int*)realloc(list,maxsize*sizeof(int));
        }
        list[size]=item;
        size++;
    }

    void removeItemAt(int position){
        if(position<0||position>size-1) return;
        list[position]=list[size-1];
        size--;
    }

    void removeItem(int item){
        for(int i=0;i<size;i++){
            if(list[i]==item) {
                    removeItemAt(i);
                    break;
            }
        }
        return;
    }

    int getItem(int position){
        if(position<0||position>size) return -1;
        return list[position];
    }

    int getLength(){
        return size;
    }

    bool empty(){
        if(size==0) return true;
        else return false;
    }

    void printList(){
        for(int i=0;i<size;i++){
            cout<<list[i]<<endl;
        }
    }

    ~Arraylist(){
        delete []list;
    }
};

class Graph{
    int vertices;
    int edge;
    Arraylist *adjlist;
    int *color;
    int *dis;
    int *parent;
    bool directed;

public:
    Graph(bool d){
        directed=d;
        vertices=0;
        edge=0;
        adjlist=0;
        color=0;
        dis=0;
        parent=0;
    }

    void setnVertices(int n){
        vertices=n;
        adjlist=new Arraylist[n];
        parent=new int[n];
        dis=new int[n];
        color=new int[n];
    }

    bool addEdge(int u,int v){
        if(u<0 || u>=vertices || v<0 || v>=vertices) return false;
        if(adjlist[u].searchItem(v)>0) return false;
        else{
            adjlist[u].insertItem(v);
            if(!directed) adjlist[v].insertItem(u);
            edge++;
            return true;
        }
    }

    void printGraph(){
        for(int i=0;i<vertices;i++){
            cout<<i<<": ";
            for(int j=0;j<adjlist[i].getLength();j++){
                cout<<adjlist[i].getItem(j)<<" ";
            }
            cout<<endl;
        }
    }

    void removeEdge(int u,int v){
        if(u<0 || u>=vertices || v<0 || v>=vertices) return;
        adjlist[u].removeItem(v);
        if(!directed) adjlist[v].removeItem(u);
    }

    bool isEdge(int u,int v){
        if(u<0 || u>=vertices || v<0 || v>=vertices) return false;
        if(adjlist[u].searchItem(v)>=0) return true;
        else return false;
    }

    int getoutDegree(int u){
        if(u<0||u>=vertices) return -1;
        return adjlist[u].getLength();
    }

    int getinDegree(int u){
        int degree=0;
        if(u<0||u>=vertices) return -1;
        for(int i=0;i<vertices;i++){
            if(adjlist[i].searchItem(u)>=0) degree++;
        }
        return degree;
    }

    bool hasCommonAdjacent(int u,int v){
        for(int i=0;i<vertices;i++){
            if(adjlist[u].searchItem(i)>=0&&adjlist[v].searchItem(i)>=0) return true;
        }
        return false;
    }

    void bfs(int source){
        for(int i=0;i<vertices;i++){
            parent[i]=-1;
            dis[i]=INFINITY;
            color[i]=WHITE;
        }

        queue q;
        if(color[source]==WHITE) {
                q.enqueue(source);
                dis[source]=0;
                parent[source]=-1;
        }

        while(!q.empty()){
            int temp=q.dequeue();
            cout<<temp<<endl;
            for(int i=0;i<adjlist[temp].getLength();i++){
                int idx=adjlist[temp].getItem(i);
                if(color[idx]==WHITE){
                    q.enqueue(idx);
                    color[idx]=GREY;
                    parent[idx]=temp;
                    dis[idx]=dis[temp]+1;
                }
            }
            color[temp]=BLACK;
        }
    }

    void dfsUtil(int source){
        color[source]=BLACK;
        cout<<source<<endl;

        for(int i=0;i<adjlist[source].getLength();i++){
            int l=adjlist[source].getItem(i);
            if(color[l]==WHITE){
                parent[l]=source;
                dis[l]=dis[source]+1;
                dfsUtil(l);
            }
        }
    }

    void dfs(int source){
        for(int i=0;i<vertices;i++){
            parent[i]=-1;
            dis[i]=INFINITY;
            color[i]=WHITE;
        }
        dis[source]=0;
        dfsUtil(source);
    }

    int getDist(int u,int v){
        bfs(u);
        cout<<"Distance:"<<endl;
        return dis[v];
    }

    ~Graph(){
        delete[] adjlist;
        delete []color;
        delete []parent;
        delete []dis;
    }

};


int main(){
    bool dir;
    int n;
    int choice;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge.        2.Remove edge                3.is Edge \n");
        printf("4. Get Out Degree   5.Get In Degree              6.Has Common Adjacent\n");
        printf("7. BFS              8.DFS                        9.Get distance\n");
        printf("10. Print Graph     11. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            cout<<"Adding Edge between:"<<endl;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            cout<<"Removing Edge between:"<<endl;
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u, v;
            cout<<"Is Edge"<<endl;
            scanf("%d%d", &u, &v);
            cout<<g.isEdge(u,v)<<endl;
        }
        else if(ch==4){
            cout<<" Out Degree of:"<<endl;
            int u,degree;
            scanf("%d",&u);
            degree=g.getoutDegree(u);
            cout<<degree<<endl;
        }
        else if(ch==5){
            cout<<" In Degree of:"<<endl;
            int u,degree;
            scanf("%d",&u);
            degree=g.getinDegree(u);
            cout<<degree<<endl;
        }
        else if(ch==6){
            cout<<"Common Adjacent Existed between"<<endl;
            int u,v;
            scanf("%d%d",&u,&v);
            cout<<g.hasCommonAdjacent(u,v)<<endl;
        }
        else if(ch==7){
            cout<<"BFS Source"<<endl;
            int u;
            scanf("%d",&u);
            g.bfs(u);
        }
        else if(ch==8){
            cout<<"DFS Source"<<endl;
            int u;
            scanf("%d",&u);
            g.dfs(u);
        }
        else if(ch==9){
            cout<<"Distance between :"<<endl;
            int u,v;
            scanf("%d%d",&u,&v);
            cout<<g.getDist(u,v)<<endl;
        }
        else if(ch==10)
        {
            g.printGraph();
        }
        else if(ch==11)
        {
            break;
        }
    }

    srand(time(NULL));
    int nvertices[]={1000,2000,4000,8000,16000};
    int edge,maxlim;
    for(int i=0;i<5;i++){
        edge=nvertices[i];
        maxlim=(edge*edge-edge)/8;
        while(edge<=maxlim){
            Graph g(false);
            g.setnVertices(nvertices[i]);
            int v1,v2;
            for(int j=0;j<edge;j++){
                do{
                    v1=rand()%nvertices[i];
                    v2=rand()%nvertices[i];
                }while(!g.addEdge(v1,v2));
            }

            auto start=chrono::steady_clock::now();
            int source;
            for(int j=0;j<10;j++){
                source=rand()%nvertices[i];
                g.bfs(source);
            }
            auto finish=chrono::steady_clock::now();
            int total_time=chrono::duration_cast<chrono::nanoseconds>(finish- start).count()/10.0;
            cout<<"Vertices : "<<nvertices[i]<<"    Edges: "<<edge<<endl;
            cout<<"BFS Runtime: "<<total_time<<endl;
            edge*=2;
        }
    }
}


