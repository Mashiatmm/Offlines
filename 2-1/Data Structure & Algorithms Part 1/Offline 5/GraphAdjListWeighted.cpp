#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	ArrayList *weightedList;
	int *color;
	int* parent;
	int *dist;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u,bool out=true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;
	color=NULL;
	parent=NULL;
	dist=NULL;
	weightedList=NULL;
	 //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
	weightedList=new ArrayList[nVertices];
	color=new int[nVertices];
	parent=new int[nVertices];
	dist=new int[nVertices];
}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    if(adjList[u].searchItem(v)<0){
        adjList[u].insertItem(v) ;
        weightedList[u].insertItem(w);
        if(!directed) {
                adjList[v].insertItem(u) ;
                weightedList[v].insertItem(w);
        }
    }
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    int idx=adjList[u].searchItem(v);
    if(idx>=0) weightedList[u].removeItemAt(idx);
    adjList[u].removeItem(v);
    if(!directed) {
            int idx=adjList[v].searchItem(u);
            if(idx>=0) weightedList[u].removeItemAt(idx);
            adjList[v].removeItem(u) ;
    }
    this->nEdges--;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    if(adjList[u].searchItem(v)>=0) return true;
    if(directed){
        if(adjList[v].searchItem(u)>=0) return true;
    }
    return false;

}

int Graph::getDegree(int u,bool out)
{
    //returns the degree of vertex u
     if(u<0 || u>=nVertices) return 0;
    int degree=0;
    if(out){
        degree=adjList[u].getLength();
    }
    else{
        for(int i=0;i<nVertices;i++){
            if(adjList[i].searchItem(u)>=0){
                degree++;
            }
        }
    }
    return degree;

}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 || u>=nVertices) return ;
    adjList[u].printList();
    if(directed){
        cout<<"Inward Direction: ";
        for(int i=0;i<nVertices;i++){
            if(adjList[i].searchItem(u)>=0) cout<<i<<" ";
        }

    }
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    for(int i=0;i<adjList[u].getLength();i++){
        int temp=adjList[u].getItem(i);
        if(adjList[temp].searchItem(v)>=0) {return true;}
        if(adjList[v].searchItem(temp)>=0) {return true;}
    }
    if(directed){
        for(int i=0;i<nVertices;i++){
            if(adjList[i].searchItem(u)>=0){
                if(adjList[i].searchItem(v)>=0) return true;
                if(adjList[v].searchItem(i)>=0) return true;
            }
        }
    }
    return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    cout<<"BFS"<<endl;
    Queue q;
    for(int i=0;i<nVertices;i++){
        color[i]=WHITE;
        parent[i]=-1;
        dist[i]=INFINITY;
    }
    q.enqueue(source);
    color[source]=GREY;
    dist[source]=0;
    while(!q.empty()){
        int temp=q.dequeue();
        cout<<temp<<endl;
        for(int i=0;i<adjList[temp].getLength();i++){
            int l=adjList[temp].getItem(i);
            int weight=weightedList[temp].getItem(i);
            if(color[l]==WHITE){
                q.enqueue(l);
                color[l]=GREY;
                parent[l]=temp;
                dist[l]=dist[parent[l]]+weight;
                cout<<l<<" "<<dist[l]<<endl;
            }
        }
        color[temp]=BLACK;
    }

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    int dis=dist[v];
    if(directed){
        bfs(v);
        if(dis>dist[u]) dis=dist[u];
    }
    cout<<"Distance:"<<endl;
    return dis;
    //return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
        printf("%d:", i);
        for(int j=0; j<weightedList[i].getLength();j++)
        {
            printf(" %d", weightedList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    delete[] adjList;
    delete []weightedList;
    delete[] color;
    delete[] parent;
    delete[] dist;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
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
        printf("1. Add edge.    2.Remove edge                3.is Edge \n");
        printf("4. Get Degree   5.Print Adjacent Vertices    6.Common Adjacent\n");
        printf("7. BFS          8.Get distance               9. Print Graph  10. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v, w;
            cout<<"Adding Edge between:"<<endl;
            scanf("%d%d%d", &u, &v,&w);
            g.addEdge(u, v, w);
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
            cout<<"Degree of:"<<endl;
            int u,degree;
            scanf("%d",&u);
            if(!dir) degree=g.getDegree(u);
            else{
                int direction;
                cout<<"Enter 1 if out degree, 0 if in degree"<<endl;
                cin>>direction;
                if(direction==1) degree=g.getDegree(u,true);
                else degree=g.getDegree(u,false);
            }
            cout<<degree<<endl;
        }
        else if(ch==5){
            cout<<"Adjacent Vertices"<<endl;
            int u;
            scanf("%d",&u);
            g.printAdjVertices(u);
        }
        else if(ch==6){
            cout<<"Common Adjacent Existd between"<<endl;
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
            cout<<"Distance between :"<<endl;
            int u,v;
            scanf("%d%d",&u,&v);
            cout<<g.getDist(u,v)<<endl;
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            break;
        }
    }

}

