#include<iostream>

using namespace std;

class PriorityQueue
{
    int *H;
    int size;
    int MaxSize;
public:
    PriorityQueue()
    {
        size=0;
        MaxSize=100;
        H=new int[MaxSize+1];
        H[0]=0;
    }

    PriorityQueue(int s)
    {
        size=0;
        MaxSize=s;
        H=new int[s+1];
        H[0]=0;
    }

    int parent(int i){
        return i/2;
    }

    int left(int i){
    return 2*i;
    }

    int right(int i){
        return 2*i+1;
    }

    void MaxHeapify(int i){
        int left_index=left(i);
        int right_index=right(i);
        int maximum=H[i];
        int index=i;
        if(maximum<H[left_index]&&left_index<=H[0]){
            maximum=H[left_index];
            index=left_index;
        }
        if(maximum<H[right_index]&&right_index<=H[0]){
            maximum=H[right_index];
            index=right_index;
        }

        if(maximum!=H[i]){
            int temp=H[i];
            H[i]=H[index];
            H[index]=temp;
            MaxHeapify(index);
        }
    }

    void UpperHeapify(int i){
        int p=parent(i);
        if(H[p]<H[i]&&i>1)
        {
            int temp=H[p];
            H[p]=H[i];
            H[i]=temp;
            UpperHeapify(p);
        }
    }

    void Insert(int x)
    {
        size++;
        if(size>=MaxSize){
            MaxSize*=2;
            H=(int *)realloc(H,MaxSize*sizeof(int));
        }
        H[0]=size;
        H[size]=x;
        UpperHeapify(size);
    }

    int FindMax(){
        if(size==0){
            cout<<"Empty"<<endl;
            return INT_MIN;
        }
        return H[1];
    }

    int ExtractMax(){
        if(size==0){
            cout<<"Empty"<<endl;
            return INT_MIN;
        }
        int maximum=H[1];
        H[1]=H[size];
        size--;
        H[0]=size;
        MaxHeapify(1);
        return maximum;
    }


    void IncreaseKey(int i,int key){
        if(i>size||i<0){
            cout<<"Invalid"<<endl;
            return;
        }
        if(H[i]>key){
            cout<<"Lesser value"<<endl;
            return;
        }
        H[i]=key;
        UpperHeapify(i);
    }

    void DecreaseKey(int i,int key){
        if(i>size||i<0){
            cout<<"Invalid"<<endl;
            return;
        }
        if(H[i]<key){
            cout<<"Greater value"<<endl;
            return;
        }
        H[i]=key;
        MaxHeapify(i);
    }

    void print(){
        cout<<"Size of Heap: "<<H[0]<<endl;
        cout<<"Heap:"<<endl;
        for(int i=1;i<=H[0];i++){
            cout<<H[i]<<endl;
        }
    }

};

int main(){
    cout<<"Insert maxsize:"<<endl;
    int s;
    cin>>s;
    if(s<=0) return 0;
    PriorityQueue pq(s);
    int choice;
    while(1){
        cout<<"1:Insert         2:FindMax           3:ExtractMax"<<endl;
        cout<<"4.IncreaseKey    5:Decrease Key      6:Print     7:Quit"<<endl;
        cin>>choice;
        if(choice==1){
            int n;
            cout<<"Insert:"<<endl;
            cin>>n;
            pq.Insert(n);
        }
        else if(choice==2){
            cout<<"Maximum :"<<pq.FindMax()<<endl;
        }
        else if(choice==3){
            cout<<"Extracting Max :"<<pq.ExtractMax()<<endl;
        }
        else if(choice==4){
            cout<<"Insert index No.: ";
            int i,key;
            cin>>i;
            cout<<"Insert New key: ";
            cin>>key;
            pq.IncreaseKey(i,key);
        }
        else if(choice==5){
            cout<<"Insert index No.: ";
            int i,key;
            cin>>i;
            cout<<"Insert New key: ";
            cin>>key;
            pq.DecreaseKey(i,key);
        }
        else if(choice==6){
            cout<<"Priority Queue:"<<endl;
            pq.print();
        }
        else if(choice==7){
            break;
        }
    }

}
