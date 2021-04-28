#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int n;
    cin>>n;
    int mice[n],holes[n];
    for(int i=0;i<n;i++){
        cin>>mice[i];
        cin>>holes[i];
    }
    sort(mice,mice+n);
    sort(holes,holes+n);

    int max=0;
    for(int i=0;i<n;i++){
        if(abs(mice[i]-holes[i])>max) max=abs(mice[i]-holes[i]);
    }
    cout<<max<<endl;
    return main();
}
