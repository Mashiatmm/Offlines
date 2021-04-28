#include<cstdio>
#include<iostream>
#include<ctime>
#include<chrono>

using namespace std;

void Merge(int a[],int l,int mid,int h){
    int n1=mid-l+1;
    int n2=h-mid;
    int L[n1],H[n2];
    for(int i=0;i<n1;i++){
        L[i]=a[l+i];
    }
    for(int i=0;i<n2;i++){
        H[i]=a[l+n1+i];
    }
    int i=0,j=0,k=l;
    while(i<n1&&j<n2){
        if(L[i]<H[j]){
            a[k]=L[i];
            i++;
        }
        else{
            a[k]=H[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        a[k]=L[i];
        i++;
        k++;
    }
    while(j<n2){
        a[k]=H[j];
        j++;
        k++;
    }
}

void MergeSort(int a[],int l,int h){
    if(l>=h) return;
    int mid=(l+h)/2;
    MergeSort(a,l,mid);
    MergeSort(a,mid+1,h);
    Merge(a,l,mid,h);
}

int partition(int a[],int l,int h){
    int pivot=a[h],start=l;
    for(int i=l;i<h;i++){
        if(a[i]<=pivot){
            int temp=a[start];
            a[start]=a[i];
            a[i]=temp;
            start++;
        }
    }
    int temp=a[start];
    a[start]=pivot;
    a[h]=temp;
    return start;
}

void QuickSort(int a[],int l,int h){
    if(l>=h) return;
    int mid=partition(a,l,h);
    QuickSort(a,l,mid-1);
    QuickSort(a,mid+1,h);
}


int main(){
    int s[]={10,100,500,1000,2000,5000};
    srand(time(0));
    int turn,n;
    for(int i=0;i<6;i++){
        if(s[i]<=1000) turn=1000;
        else turn=100;
        n=s[i];
        double time_taken=0,time_taken_2=0,time_taken_best=0,time_taken_best_2=0,time_taken_worst=0,time_taken_worst_2=0;
        int array[n],array2[n],array3[n],array4[n];
        for(int i=0; i<turn; i++)
        {
            for(int i=0; i<n; i++)
            {
                array[i]=rand()%100000;
                array2[i]=array[i];
            }

            //Random Case
            auto start=chrono::high_resolution_clock::now();
            MergeSort(array,0,n-1);
            auto end=chrono::high_resolution_clock::now();
            time_taken+=chrono::duration_cast<chrono::microseconds>(end - start).count();

            start=chrono::high_resolution_clock::now();
            QuickSort(array2,0,n-1);
            end=chrono::high_resolution_clock::now();
            time_taken_2+=chrono::duration_cast<chrono::microseconds>(end - start).count();

            //Ascending Case
            start=chrono::high_resolution_clock::now();
            MergeSort(array,0,n-1);
            end=chrono::high_resolution_clock::now();
            time_taken_best+=chrono::duration_cast<chrono::microseconds>(end - start).count();

            start=chrono::high_resolution_clock::now();
            QuickSort(array2,0,n-1);
            end=chrono::high_resolution_clock::now();
            time_taken_best_2+=chrono::duration_cast<chrono::microseconds>(end - start).count();

            //Descending Case
            for(int i=0; i<n; i++)
            {
                array3[i]=array[n-1-i];
                array4[i]=array3[i];
            }

            start=chrono::high_resolution_clock::now();
            MergeSort(array3,0,n-1);
            end=chrono::high_resolution_clock::now();
            time_taken_worst+=chrono::duration_cast<chrono::microseconds>(end - start).count();

            start=chrono::high_resolution_clock::now();
            QuickSort(array4,0,n-1);
            end=chrono::high_resolution_clock::now();
            time_taken_worst_2+=chrono::duration_cast<chrono::microseconds>(end - start).count();
        }

        time_taken/=turn;
        time_taken_2/=turn;
        time_taken_best/=turn;
        time_taken_best_2/=turn;
        time_taken_worst/=turn;
        time_taken_worst_2/=turn;
        cout<<"n: "<<n<<endl;
        cout<<"Merge Sort: "<<endl<<time_taken<<" microseconds(Average Case)"<<endl<<time_taken_best<<"  microseconds(Ascending Case)"<<endl;
        cout<<time_taken_worst<<" microseconds(Descending Case)"<<endl<<endl;
        cout<<"Quick Sort: "<<endl<<time_taken_2<<" microseconds(Average Case)"<<endl<<time_taken_best_2<<" microseconds(Ascending Case)"<<endl;
        cout<<time_taken_worst_2<<" microseconds(Descending Case)"<<endl<<endl;

        cout<<endl;
    }
}
