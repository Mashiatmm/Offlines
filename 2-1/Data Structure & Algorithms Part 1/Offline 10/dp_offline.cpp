#include<iostream>
#define CORNER 0
#define UP 1
#define LEFT 2
using namespace std;

int n,m;

void memoization(char s1[],char s2[],int n,int m){
    int a[m+1][n+1],b[m+1][n+1];
    for(int i=0;i<=n;i++){
        a[0][i]=0;
        b[i][0]=-1;
    }
    for(int i=0;i<=m;i++){
        a[i][0]=0;
        b[i][0]=-1;
    }

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s2[i-1]==s1[j-1]){
                a[i][j]=1+a[i-1][j-1];
                b[i][j]=CORNER;
            }
            else{
                a[i][j]=max(a[i-1][j],a[i][j-1]);
                if(a[i-1][j]>=a[i][j-1]) b[i][j]=UP;
                else b[i][j]=LEFT;
            }
        }
    }
    int length=a[m][n];

    cout<<"Max Length:"<<length<<endl;
    char longest[length+1];
    int j=m,k=n,l=length-1;
    while(a[j][k]!=0){
        if(b[j][k]==CORNER){
            longest[l]=s2[j-1];
            j--;
            k--;
            l--;
        }
        else{
            if(b[j][k]==UP){
                j--;
            }
            else if(b[j][k]==LEFT){
                k--;
            }
        }
    }
    longest[length]='\0';
    cout<<longest<<endl;

}

int main(){
    cout<<"Enter Size:"<<endl;
    cin>>n;
    char s1[n+1];
    cout<<"Enter 1st String"<<endl;
    cin>>s1;
    cout<<"Enter Size:"<<endl;
    cin>>m;
    char s2[m+1];
    cout<<"Enter 2nd String"<<endl;
    cin>>s2;
    memoization(s1,s2,n,m);
    return 0;
}
