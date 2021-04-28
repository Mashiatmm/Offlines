#include<iostream>

using namespace std;

class DisjointSet{
    int *parent;
    int *rank;
    int n;
public:
    DisjointSet(int n){
        parent=new int[n];
        rank=new int[n];
        this->n=n;
        for(int i=0;i<n;i++){
           parent[i]=-1;
        }
    }

    void MakeSet(int x){
        parent[x]=x;
        rank[x]=0;
    }

    int FindSet(int x){
        if(parent[x]==-1) return -1;
        if(x!=parent[x]){
            parent[x]=FindSet(parent[x]);
        }
        return parent[x];
    }

    void Union(int u,int v){
        int upar=FindSet(u);
        int vpar=FindSet(v);
        if(upar==vpar||upar==-1||vpar==-1) return;

        int urank=rank[upar];
        int vrank=rank[vpar];

        if(urank>vrank){
            parent[vpar]=upar;
        }
        else if(urank<vrank){
            parent[upar]=vpar;
        }
        else{
            int smaller_index=upar<vpar?upar:vpar;
            int large_idx=upar+vpar-smaller_index;
            parent[large_idx]=smaller_index;
            rank[smaller_index]++;
        }
    }

    void print(int u){
        int upar=FindSet(u);
        if(upar==-1) return;

        for(int i=0;i<n;i++){
            parent[i]=FindSet(i);
            if(parent[i]==upar){
                cout<<i<<" ";
            }
        }
        cout<<endl;
    }
};


int main(){
    cout<<"Size of Set: "<<endl;
    int n,choice;
    cin>>n;
    DisjointSet ds(n);
    while(1){
        cout<<"1:Make Set   2:Find-Set      3:Union"<<endl;
        cout<<"4:Print      5:Quit"<<endl;
        cin>>choice;
        if(choice==1){
            int x;
            cout<<"Make Set of:"<<endl;
            cin>>x;
            if(x>=n){
                cout<<"Max Limit Cross"<<endl;
            }
            else{
                ds.MakeSet(x);
            }
        }
        else if(choice==2){
            int x;
            cin>>x;
            cout<<x<<" is in Set of "<<ds.FindSet(x)<<endl;
        }
        else if(choice==3){
            int u,v;
            cout<<"Enter u and v:"<<endl;
            cin>>u>>v;
            ds.Union(u,v);
        }
        else if(choice==4){
            int u;
            cin>>u;
            cout<<"print :"<<endl;
            ds.print(u);
        }
        else if(choice==5){
            break;
        }
    }
}
