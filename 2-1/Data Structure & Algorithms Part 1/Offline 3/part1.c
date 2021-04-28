#include<iostream>
using namespace std;

class stack{
    char *element;
    int top;
    int size;
    stack(){
        size=10;
        element=new element[size];
        top=0;
    }

    ~stack(){
        delete[] element;
    }

    bool empty(){
        if(top==0) return true;
        else return false;
    }

    int size(){
        return top;
    }

    char top(){
        if(top==0){
            cout<<"Stack Empty"<<endl;
        }
        else return element[top-1];
    }

    void push(char x){
        if(top>=size){
            size+=10;
            element=new char[size];
        }

        element[top]=x;
        top++;
    }

    char pop(){
        top--;
        if(size-top>10){
            size-=10;
            element=new char[size];
        }
        return element[top];
    }
};

int main(){
    stack=new char[10];

}
