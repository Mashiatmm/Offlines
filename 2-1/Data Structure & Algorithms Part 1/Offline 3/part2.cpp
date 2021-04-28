#include<iostream>
using namespace std;

class queue
{
    int *element;
    int FRONT;
    int REAR;
    int ssize;
public:

    queue()
    {
        ssize=10;
        element=new int[ssize];
        FRONT=0;
        REAR=0;
    }

    ~queue()
    {
        delete[] element;
    }

    bool empty()
    {
        if(REAR==FRONT)
            return true;
        else
            return false;
    }

    int size()
    {
        return REAR-FRONT;
    }

    int front()
    {
        if(FRONT==REAR)
        {
            cout<<"Queue empty"<<endl;
            return INT_MAX;
        }
        return element[FRONT];
    }

    int rear()
    {
        if(FRONT==REAR)
        {
            cout<<"Queue empty"<<endl;
            return INT_MAX;
        }
        return element[REAR-1];
    }

    void enqueue(int x)
    {
        if(REAR>=ssize)
        {
            ssize+=10;
            element=(int *)realloc(element,ssize*sizeof(int));
        }
        element[REAR]=x;
        REAR++;
    }

    int dequeue()
    {
        if(FRONT==REAR)
        {
            cout<<"Queue empty"<<endl;
            return INT_MAX;
        }
        int temp=element[FRONT];
        for(int i=FRONT; i<REAR-1; i++)
        {
            element[i]=element[i+1];
        }
        REAR--;
        return temp;
    }

};

class stack
{
    queue q1,q2;

public:

    void push(int x)
    {
        if(q2.empty())
            q1.enqueue(x);
        else if(q1.empty())
            q2.enqueue(x);
    }

    int pop()
    {
        int x;
        if(!q1.empty())
        {
            while(q1.size()!=1){
                x=q1.dequeue();
                q2.enqueue(x);
            }

            x=q1.dequeue();
            return x;
        }
        else if(!q2.empty())
        {
            while(q2.size()!=1){
                x=q2.dequeue();
                q1.enqueue(x);
            }
            x=q2.dequeue();
            return x;
        }
    }

    bool empty()
    {
        if(q1.empty()&&q2.empty())
            return true;
        else
            return false;
    }

    int size()
    {
        return q1.size()+q2.size();
    }

    int top()
    {
        if(!q1.empty())
            return q1.front();
        else
            return q2.front();
    }


};

int main()
{
     queue q;
     int n;
     while(1){
         cout<<"Enter 1:empty 2:size 3:front 4:rear 5:enqueue 6:dequeue 7:exit"<<endl;
         cin>>n;
         if(n==1) cout<<"Empty: "<<q.empty()<<endl;
         else if(n==2) cout<<"Size: "<<q.size()<<endl;
         else if(n==3) cout<<"Front: "<<q.front()<<endl;
         else if(n==4) cout<<"Rear: "<<q.rear()<<endl;
         else if(n==5){
             int l;
             cout<<"Enqueue: ";
             cin>>l;
             q.enqueue(l);
         }
         else if(n==6) cout<<"Dequeue: "<<q.dequeue()<<endl;
         else if(n==7) break;
     }
    stack s;

    //int n;
    while(1)
    {
        cout<<"Enter 1:empty 2:size 3:top 4:push 5:pop 6:exit"<<endl;
        cin>>n;
        if(n==1)
            cout<<"Empty: "<<s.empty()<<endl;
        else if(n==2)
            cout<<"Size: "<<s.size()<<endl;
        else if(n==3)
            cout<<"Top: "<<s.top()<<endl;
        else if(n==4)
        {
            cout<<"Push: ";
            int push_el;
            cin>>push_el;
            s.push(push_el);
        }
        else if(n==5)
        {
            cout<<"Pop: "<<s.pop()<<endl;
        }
        else
            break;
    }
}
