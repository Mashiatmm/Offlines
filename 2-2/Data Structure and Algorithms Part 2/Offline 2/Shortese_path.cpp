#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<vector>
#define WHITE 0
#define GREY 1
#define BLACK 2
#define INFINITY 99999

using namespace std;

typedef pair<int,int> Pair;

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

class Edges{
public:
    int source;
    int destination;
    int weight;

    setEdges(int s,int d,int w){
        source=s;
        destination=d;
        weight=w;
    }
};

class Graph{
    int vertices;
    int edge;
    Arraylist *adjlist;
    Arraylist *weightlist;
    int *color;
    int *dis;
    int *parent;
    Edges *e;
    bool directed;

public:
    Graph(bool d){
        directed=d;
        vertices=0;
        edge=0;
        adjlist=0;
        weightlist=0;
        color=0;
        dis=0;
        parent=0;
    }

    void setnVertices(int n){
        vertices=n;
        adjlist=new Arraylist[n];
        weightlist=new Arraylist[n];
        parent=new int[n];
        dis=new int[n];
        color=new int[n];
    }

    void setnEdges(int m){
        e=new Edges[m];
    }

    bool addEdge(int u,int v,int w){
        if(u<0 || u>=vertices || v<0 || v>=vertices) return false;
        if(adjlist[u].searchItem(v)>0) return false;
        else{
            e[edge].setEdges(u,v,w);
            adjlist[u].insertItem(v);
            weightlist[u].insertItem(w);
            if(!directed) {
                    adjlist[v].insertItem(u);
                    weightlist[v].insertItem(w);
            }
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
            cout<<i<<": ";
            for(int j=0;j<weightlist[i].getLength();j++){
                cout<<weightlist[i].getItem(j)<<" ";
            }
            cout<<endl;
        }
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


    void djikstra_algo(int s,int d){
        for(int i=0;i<vertices;i++){
            parent[i]=-1;
            dis[i]=INFINITY;
        }
        dis[s]=0;
        priority_queue<Pair,vector<Pair>,greater<Pair>> pq;
        pq.push(make_pair(dis[s],s));

        while(!pq.empty()){
            int u=pq.top().second;
            pq.pop();

            for(int i=0;i<adjlist[u].getLength();i++){
                int v=adjlist[u].getItem(i);
                int w=abs(weightlist[u].getItem(i));

                if(dis[u]+w<dis[v]){
                    parent[v]=u;
                    dis[v]=dis[u]+w;
                    pq.push(make_pair(dis[v],v));
                }
            }
        }

        vector<int> path;
        int last=d;
        while(last!=-1){
            path.push_back(last);
            last=parent[last];
        }

        ofstream outputfile;
        string line;
        outputfile.open("output.txt",ios::out|ios::app);
        outputfile<<"Djikstra Algorithm:\n";
        outputfile<<dis[d];
        outputfile<<"\n";
        while(!path.empty()){
            outputfile<<path.back();
            path.pop_back();
            if(!path.empty()) outputfile<<"-> ";
        }
        outputfile<<"\n";
        outputfile.close();

    }


    void bellman_ford(int s,int d){
        for(int i=0;i<vertices;i++){
            parent[i]=-1;
            dis[i]=INFINITY;
        }
        dis[s]=0;

        for(int i=0;i<vertices-1;i++){
            for(int j=0;j<edge;j++){
                int u=e[j].source;
                int v=e[j].destination;
                int w=e[j].weight;

                if(dis[u]!=INFINITY&&((dis[u]+w)<dis[v])){
                    dis[v]=dis[u]+w;
                    parent[v]=u;
                }
            }
        }

        for(int j=0;j<edge;j++){
                int u=e[j].source;
                int v=e[j].destination;
                int w=e[j].weight;

                if(dis[u]!=INFINITY&&((dis[u]+w)<dis[v])){
                    ofstream outputfile;
                    string line;
                    outputfile.open("output.txt",ios::out);
                    outputfile<<"Bellman Ford Algorithm:\n";
                    outputfile<<"Graph contains negative cycle\n";
                    outputfile.close();
                    return;
                }
            }

        vector<int> path;
        int last=d;
        while(last!=-1){
            path.push_back(last);
            last=parent[last];
        }

        ofstream outputfile;
        string line;
        outputfile.open("output.txt",ios::out);
        outputfile<<"Bellman Ford Algorithm:\n";
        outputfile<<dis[d];
        outputfile<<"\n";
        while(!path.empty()){
            outputfile<<path.back();
            path.pop_back();
            if(!path.empty()) outputfile<<"-> ";
        }
        outputfile<<"\n\n";
        outputfile.close();
    }

    ~Graph(){
        delete[] adjlist;
        delete []e;
        delete []weightlist;
        delete []color;
        delete []parent;
        delete []dis;
    }

};

int main(){
    Graph g(true);
    ifstream inputfile;
    inputfile.open("input.txt");
    string line;
    int start=1;
    if(inputfile){
        while(getline(inputfile,line)){
            stringstream s(line);
            Arraylist a;
            int temp;
            while(s>>temp){
                a.insertItem(temp);
            }
            if(a.getLength()==2){
                if(start==1){
                    start=0;
                    g.setnVertices(a.getItem(0));
                    g.setnEdges(a.getItem(1));
                }
                else{
                    g.bellman_ford(a.getItem(0),a.getItem(1));
                    g.djikstra_algo(a.getItem(0),a.getItem(1));

                }
            }
            else{
                g.addEdge(a.getItem(0),a.getItem(1),a.getItem(2));
            }


        }
        inputfile.close();
    }

}




