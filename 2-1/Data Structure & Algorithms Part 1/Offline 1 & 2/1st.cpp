#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>

using namespace std;

void SelectionSort(int array[],int n)
{
    int min,idx,temp;
    for(int i=0; i<n-1; i++)
    {
        min=array[i];
        idx=i;
        for(int j=i+1; j<n; j++)
        {
            if(min>array[j])
            {
                min=array[j];
                idx=j;
            }
        }
        temp=array[i];
        array[i]=array[idx];
        array[idx]=temp;
    }

}

void InsertionSort(int array[],int n)
{
    int temp;
    for(int i=1; i<n; i++)
    {
        temp=array[i];
        for(int j=i-1; j>=0; j--)
        {
            if(array[j]>temp)
            {
                array[j+1]=array[j];
                if(j==0)
                {
                    array[j]=temp;
                }
            }
            else
            {
                array[j+1]=temp;
                break;
            }
        }
    }
}



int main()
{
    int size[]= {10,100,200,500,1000,2000,5000,10000};
    int n,turn;
    srand(time(0));
    for(int s=0; s<8; s++)
    {
        n=size[s];
        if(n>2000){
            turn=1000;
        }
        else{ turn=10000;}
        double time_taken=0,time_taken_2=0,time_taken_best=0,time_taken_best_2=0,time_taken_worst=0,time_taken_worst_2=0;
        int array[n],array2[n],array3[n],array4[n];
        for(int i=0; i<turn; i++)
        {
            for(int i=0; i<n; i++)
            {
                array[i]=rand()%100000;
                array2[i]=array[i];
            }
            //Average Case
            auto start=chrono::high_resolution_clock::now();
            SelectionSort(array,n);
            auto end=chrono::high_resolution_clock::now();
            time_taken+=chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            start=chrono::high_resolution_clock::now();
            InsertionSort(array2,n);
            end=chrono::high_resolution_clock::now();
            time_taken_2+=chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            //Best Case
            start=chrono::high_resolution_clock::now();
            SelectionSort(array,n);
            end=chrono::high_resolution_clock::now();
            time_taken_best+=chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            start=chrono::high_resolution_clock::now();
            InsertionSort(array2,n);
            end=chrono::high_resolution_clock::now();
            time_taken_best_2+=chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            //Worst Case
            for(int i=0; i<n; i++)
            {
                array3[i]=array[n-1-i];
                array4[i]=array3[i];
            }

            start=chrono::high_resolution_clock::now();
            SelectionSort(array3,n);
            end=chrono::high_resolution_clock::now();
            time_taken_worst+=chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            start=chrono::high_resolution_clock::now();
            InsertionSort(array4,n);
            end=chrono::high_resolution_clock::now();
            time_taken_worst_2+=chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        }


        time_taken/=turn;
        time_taken_2/=turn;
        time_taken_best/=turn;
        time_taken_best_2/=turn;
        time_taken_worst/=turn;
        time_taken_worst_2/=turn;
        cout<<"n: "<<n<<endl;
        cout<<"Selection Sort: "<<endl<<time_taken<<" microseconds(Average Case)"<<endl<<time_taken_best<<"  microseconds(Best Case)"<<endl;
        cout<<time_taken_worst<<" microseconds(Worst Case)"<<endl<<endl;
        cout<<"Insertion Sort: "<<endl<<time_taken_2<<" microseconds(Average Case)"<<endl<<time_taken_best_2<<"  microseconds(Best Case)"<<endl;
        cout<<time_taken_worst_2<<" microseconds(Worst Case)"<<endl<<endl;

        cout<<endl;
    }

    return 0;
}
