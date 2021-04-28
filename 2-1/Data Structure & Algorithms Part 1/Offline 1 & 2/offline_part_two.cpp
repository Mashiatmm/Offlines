#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<chrono>
#include<cstring>

using namespace std;

void possible_members(char *s)
{
    int i;
    for(i=0; i<10; i++)
    {
        s[i]=i+'0';
    }
    int count=0;
    while(count<26)
    {
        s[i]=count+65;
        count++;
        i++;
    }
    count=0;
    while(count<26)
    {
        s[i]=count+97;
        count++;
        i++;
    }
}

void sort(char *set,int n){
    char min,temp;
    int idx;
    for(int i=0;i<n-1;i++){
            min=set[i];
            idx=i;
            for(int j=i+1;j<n;j++){
                if(min>set[j]){
                    min=set[j];
                    idx=j;
                }
            }
            temp=set[i];
            set[i]=set[idx];
            set[idx]=temp;
    }
}

void power_set_generator(char *set,string subset,int i)
{
    if(i<0){
        cout<<"{"<<subset<<"}"<<endl;
        return;
    }

    subset+=set[i];
    subset+=' ';
    power_set_generator(set,subset,i-1);
    int length=subset.length();

    subset.erase(length-2,2);
    while(set[i]==set[i-1]){
        i--;
    }

    power_set_generator(set,subset,i-1);
}

int main()
{
    int n,i;
    char s[62];
    possible_members(s);
    srand(time(0));
    for(int i=3; i<=3; i++)
    {
        n=i;
        char set[n];

        for(int i=0; i<n; i++)
        {
            set[i]=s[rand()%62];
            cout<<set[i]<<" ";
        }
        cout<<endl<<"Power Set:"<<endl;
        sort(set,n);

        auto start=chrono::high_resolution_clock::now();

        string subset="";
        power_set_generator(set,subset,n-1);

        auto end=chrono::high_resolution_clock::now();
        double time_taken=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        cout<<"For "<<n<<" set of elements,time taken is : "<<time_taken<<" nanoseconds"<<endl;
        cout<<endl;
    }
    return 0;
}
