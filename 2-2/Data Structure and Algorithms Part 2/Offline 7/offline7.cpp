#include<iostream>
#include<queue>
#include<stack>
#include<fstream>
#include <sstream>

using namespace std;

ofstream out;

class Node
{

public:
    int key;
    Node* child;
    Node *sibling;
    Node* parent;
    int degree;

    Node(int key)
    {
        this->key = key;
        parent = 0;
        sibling = 0;
        child = 0;
        degree = 0;
    }

};



class BinomialHeap
{
    Node* root;


public:
    BinomialHeap()
    {
        root = 0;
    }

    Node* getroot()
    {
        return root;
    }

    void setroot(Node* root)
    {
        this->root = root;
    }

    void MergeUnionHeap(Node* h1,Node *h2)
    {
        if(h1->key > h2->key)
        {
            swap(h2,h1);
        }

        h2->parent = h1;
        h2->sibling = h1->child;
        h1->child = h2;
        h1->degree++;
    }

    void Union(Node *h2)
    {

        if(root == 0)
        {
            root = h2;
            return;
        }
        BinomialHeap* h = new BinomialHeap();
        Node* hhead = h->getroot();
        Node* h2head = h2;
        Node* h1head = root;
        while(h1head != 0 && h2head != 0)
        {

            if(h2head->degree < h1head->degree)
                swap(h1head,h2head);
            if(hhead == 0)
            {
                h->setroot(h1head);
                hhead = h->getroot();
            }
            else
            {

                hhead->sibling = h1head;
                hhead = hhead->sibling;
            }
            h1head = h1head->sibling;

        }

        while(h1head != 0 )
        {
            if(hhead == 0)
            {
                h->setroot(h1head);
                hhead = h->getroot();
            }
            else
            {
                hhead->sibling = h1head;
                hhead = hhead->sibling;
            }
            h1head = h1head -> sibling;
        }
        while(h2head!= 0)
        {
            if(hhead == 0)
            {
                h->setroot(h2head);
                hhead = h->getroot();
            }
            else
            {
                hhead->sibling = h2head;
                hhead = hhead->sibling;
            }
            h2head = h2head -> sibling;
        }


        Adjust(h);

    }

    void Adjust(BinomialHeap* h)
    {

        BinomialHeap* heap = new BinomialHeap();
        Node* heaphead = heap->getroot();

        Node* iter1 = h->getroot();
        Node* iter2 = 0;
        if(iter1->sibling != 0)
        {
            iter2 = iter1->sibling;
        }

        while(iter2 != 0)
        {
            if(iter1->degree == iter2->degree)
            {
                Node* temp = iter2->sibling;
                MergeUnionHeap(iter1,iter2);
                if(iter1->degree < iter2->degree)
                    iter1 = iter2;
                iter2 = temp;
            }
            else
            {
                if(heaphead == 0)
                {
                    if(iter2->degree<iter1->degree){
                        heap->setroot(iter2);
                        iter1->sibling = iter2->sibling;
                        iter2 = iter1;
                    }
                    else
                        heap->setroot(iter1);
                    heaphead = heap->getroot();
                }
                else
                {
                    if(iter2->degree<iter1->degree){
                        heaphead->sibling = iter2;
                        iter1->sibling = iter2->sibling;
                        iter2 = iter1;
                    }
                    else{
                      heaphead->sibling = iter1;
                    }

                    heaphead = heaphead->sibling;
                }

                iter1 = iter2;
                iter2 = iter2->sibling;
            }
        }

        if(iter1!=0)
        {
            //For safety..if there was lastly a Union
            iter1->sibling = 0;
            if(heaphead == 0)
            {
                heap->setroot(iter1);
                heaphead = heap->getroot();
            }
            else
            {
                heaphead->sibling = iter1;
                heaphead = heaphead->sibling;
            }
        }
        delete h;
        this->root = heap->getroot();
    }


    void Insert(int key)
    {
        BinomialHeap* b = new BinomialHeap();
        Node* broot = b->getroot();
        broot = new Node(key);
        Union(broot);
    }

    int FindMin()
    {
        Node* head = root;
        if(head == 0)
            return -99999;
        int min = root->key;
        while(head!=0)
        {
            if(head->key<min)
            {
                min = head->key;
            }
            head = head->sibling;
        }
        return min;
    }

    int ExtractMin()
    {
        Node* head = root;
        Node* minNode = root;
        Node* prevHead = 0;
        Node* beforeMin = 0;
        if(head == 0)
            return -99999;
        int min = root->key;
        while(head!=0)
        {
            if(head->key<min)
            {
                min = head->key;
                minNode = head;
                beforeMin = prevHead;
            }
            prevHead = head;
            head = head->sibling;
        }

        if(minNode == root)
        {
            root = root->sibling;
        }
        else
        {
            beforeMin->sibling = minNode->sibling;
        }
        Node *children = minNode->child;

        stack<Node*> s;
        while(children != 0)
        {
            s.push(children);
            children = children->sibling;
        }
        Node* temp;
        BinomialHeap* bh = new BinomialHeap();
        Node* bhroot = bh->getroot();
        while(!s.empty())
        {
            temp = s.top();
            temp->sibling = 0;
            s.pop();

            if(bhroot == 0)
            {
                bhroot = temp;
                bh->setroot(bhroot);
            }
            else
            {
                bhroot->sibling = temp;
                bhroot = bhroot->sibling;
            }


        }

        delete minNode;
        Union(bh->getroot());

        delete bh;

        return min;
    }

    void Print()
    {
        Node* head = root;

        while(head != 0)
        {
            int h = head->degree;
            //cout<<"Binomial Tree B"<<h<<endl;
            out<<"Binomial Tree B"<<h<<"\n";
            printTree(head);
            head = head->sibling;
        }

    }

    void printTree(Node* temp)
    {
        //cout<<"Level 0: "<<temp->key<<endl;
        out<<"Level 0: "<<temp->key<<"\n";
        queue<Node*> q;
        q.push(temp->child);

        int k = 1;


        while(!q.empty())
        {
            Node* node = q.front();
            int len = q.size();
            if(node!=0)
                out<<"Level "<<k<<": ";
            for(int i = 0; i<len; i++)
            {
                node = q.front();
                q.pop();
                while(node != 0)
                {
                    out<<node->key<<" ";
                    if(node->child!=0){
                        q.push(node->child);
                    }
                    node = node->sibling;
                }
            }

            k++;
            //cout<<endl;
            if(temp->degree != 0){
                out<<"\n";
            }

        }

    }

};


int main()
{
    BinomialHeap* bh = new BinomialHeap();
    ifstream in;
    in.open("in3.txt");

    out.open("output.txt");
    string line;
    char c;
    while(!in.eof())
    {
        in>>c;
        if(in.eof())
            break;
        if(c == 'I')
        {
            int num;
            in>>num;
            bh->Insert(num);
        }
        else if(c == 'P')
        {
            //cout<<"Printing Binomial Heap..."<<endl;
            out<<"Printing Binomial Heap..."<<"\n";
            bh->Print();

        }
        else if(c == 'F')
        {
            //cout<<"Find-Min Returned "<<bh->FindMin()<<endl;
            out<<"Find-Min Returned "<<bh->FindMin()<<"\n";
        }
        else if(c == 'E')
        {
            //cout<<"Extract-Min Returned "<<bh->ExtractMin()<<endl;
            out<<"Extract-Min Returned "<<bh->ExtractMin()<<"\n";
        }
        else if(c == 'U')
        {
            BinomialHeap* U = new BinomialHeap();
            string s,temp;
            getline(in,s);
            stringstream sstream;
            sstream << s;
            while(!sstream.eof())
            {
                sstream>>temp;

                int num = atoi( temp.c_str() );
                U->Insert(num);
                if(sstream.eof())
                    break;
            }
            bh->Union(U->getroot());
        }

    }

    out.close();

}
