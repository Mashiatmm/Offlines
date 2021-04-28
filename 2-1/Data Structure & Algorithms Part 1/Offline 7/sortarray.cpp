#include <cstdio>
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


int main()
{
    srand(time(0));
    int choice, n;
    int a[]={4,2,15,5,2,5,1233,64,7};
    int *ar=NULL,*ar1=NULL;
    int flag=0,turn;
    double time_taken;
    auto start=chrono::high_resolution_clock::now();
    auto end=chrono::high_resolution_clock::now();
    while(1)
    {
        if(flag==1) break;
        printf("1. Generate average/random case\n");
        printf("2. Generate best/ascending case\n");
        printf("3. Generate worst/descending case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("7. Quit\n");
        printf("> ");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            if(ar) delete ar;
            if(ar1) delete ar1;
            ar=new int[n];
            ar1=new int[n];
            for(int i=0;i<n;i++){
                ar[i]=rand();
                ar1[i]=ar[i];
            }
            break;

        case 2:
            printf("Number of elements: ");
            scanf("%d", &n);
            if(ar) delete ar;
            if(ar1) delete ar1;
            ar=new int[n];
            ar1=new int[n];
            ar[0]=rand();
            ar1[0]=ar[0];
            for(int i=1;i<n;i++){
                ar[i]=ar[i-1]+1;
                ar1[i]=ar[i];
            }
            // do yourself
            break;

        case 3:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            if(ar) delete ar;
            if(ar1) delete ar1;
            ar=new int[n];
            ar1=new int[n];
            ar[0]=rand()+n;
            ar1[0]=ar[0];
            for(int i=1;i<n;i++){
                ar[i]=ar[i-1]-1;
                ar1[i]=ar[i];
            }
            break;

        case 4:
            printf("Applying merge sort\n");
            // do yourself
            time_taken=0;
            if(n<1000){
                turn=1000;
            }
            else turn=100;
            for(int i=0;i<turn;i++){
                if(i>0){
                    for(int j=0;j<n;j++){
                        ar[j]=ar1[j];
                    }
                }
                start=chrono::high_resolution_clock::now();
                MergeSort(ar,0,n-1);
                end=chrono::high_resolution_clock::now();
                time_taken+=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
            time_taken/=turn;
            // this should transform the given array into a sorted array
            cout<<"Time taken to finish: "<<time_taken<<" nanoseconds"<<endl;
            break;

        case 5:
            printf("Applying quicksort\n");
            // do yourself
            time_taken=0;
            if(n<1000){
                turn=1000;
            }
            else turn=100;
            for(int i=0;i<turn;i++){
                if(i>0){
                    for(int j=0;j<n;j++){
                        ar[j]=ar1[j];
                    }
                }
                start=chrono::high_resolution_clock::now();
                QuickSort(ar,0,n-1);
                end=chrono::high_resolution_clock::now();
                time_taken+=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
            time_taken/=turn;

            cout<<"Time taken to finish: "<<time_taken<<" nanoseconds"<<endl;
            break;

        case 6:
            printf("Array\n");
            // do yourself
            for(int i=0;i<n;i++){
                cout<<ar[i]<<" ";
            }
            cout<<endl;
            break;

        case 7:
            flag=1;
            break;
        }
    }
    if(ar) delete ar;
    if(ar1) delete ar1;
}

