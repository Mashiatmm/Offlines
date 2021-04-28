#include<iostream>

using namespace std;


void sort_by_finish(int start[],int finish[],int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(finish[j]<finish[i]){
                swap(finish[i],finish[j]);
                swap(start[i],start[j]);
            }
        }
    }
}

void findmax(int acts[],int start[],int finish[],int k,int n,int idx ){
    acts[idx]=k;
    idx++;
    int m=k;
    k++;
    while(k<n&&finish[m]>start[k]){
        k++;
    }
    if(k<n) findmax(acts,start,finish,k,n,idx);
    else return;
}


int main(){
    int n;
    cin>>n;
    int start[n],finish[n],acts[n];
    for(int i=0;i<n;i++){
        cout<<"Start and Finish:"<<endl;
        cin>>start[i];
        cin>>finish[i];
        acts[i]=-1;
    }

    sort_by_finish(start,finish,n);
    /*cout<<"Sorted :"<<endl;
    for(int i=0;i<n;i++){
        cout<<start[i]<<" "<<finish[i]<<endl;
    }*/

    findmax(acts,start,finish,0,n,0);
    int count=0;
    cout<<"Output:"<<endl;
    for(int i=0;i<n;i++){
        if(acts[i]==-1) break;
        count++;
        cout<<"[ "<<start[acts[i]]<<", "<<finish[acts[i]]<<")  ";
    }
    cout<<endl<<"Max Number of Activities: "<<count<<endl;

}
