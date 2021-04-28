#include<iostream>
#include<fstream>
#include<cstdlib>
#define RED 1
#define BLACK 0
#define INF 99999


using namespace std;

class Node
{

public:
    int key;
    Node *parent;
    Node* left;
    Node* right;
    int color;

    Node() {
        color = BLACK;
        left = 0;
        right = 0;
        key = INF;
    }

    Node(int key)
    {
        this->key = key;
        left = new Node();
        right = new Node();
        left->parent = this;
        right->parent = this;
        parent = 0;
        color = RED;
    }

};

class RedBlackTree
{

    Node *root;

public:
    RedBlackTree()
    {
        root = new Node();
    }

    void LeftRotate(Node *x)
    {
        Node* y = x->right;

        x->right = y->left;
        /*
        if(y->left!=0){
            y->left->parent = x;
        }
        */
        y->left->parent = x;

        y->parent = x->parent;

        if(x->parent == 0)
        {
            root = y;
        }
        else if(x->parent->left == x)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void RightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        /*
        if(y->right!= 0){
            y->right->parent = x;
        }
        */
        y->right->parent = x;
        y->parent = x->parent;
        if(x->parent == 0)
        {
            root = y;
        }
        else if(x->parent->left == x)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;

    }

    Node* TreeSuccessor(Node* z){
        Node* y = z;
        if(y->right->key != INF){
            y = y->right;
        }
        while(y->left->key != INF){
            y = y->left;
        }

        return y;
    }

    void Insert(int key)
    {
        Node* z = new Node(key);
        Node* y = 0;
        Node* x = root;


        while(x->key != INF)
        {
            y = x;
            if(z->key < x->key)
            {
                x = x->left;
            }
            else{
                x = x->right;
            }
        }


        z->parent = y;
        if(y == 0||y->key == INF)
        {
            root = z;
        }
        else if(z->key < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
        InsertFixUp(z);
    }

    void InsertFixUp(Node* z)
    {
        if(z->parent != 0)
        {
            while(z->parent->color == RED)
            {

                //Case 1 to 3 where parent of z is a left child
                if(z->parent->parent->left == z->parent)
                {

                    Node* y = z->parent->parent->right;
                    /*
                    int uncleColor = BLACK;
                    if(y!=0){
                        uncleColor = y->color;
                    }
                    */
                    if(y->color == RED)
                    {
                        //case I

                        y->color = BLACK;
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    }
                    else
                    {
                        //y color BLACK
                        if(z->parent->right == z)
                        {
                            //case II
                            z = z->parent;
                            LeftRotate(z);
                        }
                        //Case III
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        RightRotate(z->parent->parent);
                    }
                }
                else if(z->parent->parent->right == z->parent)
                {
                    //int uncleColor = BLACK;
                    Node* y = z->parent->parent->left;
                    /*
                    if(y!=0){
                        uncleColor = y->color;
                    }
                    */
                    if(y->color == RED)
                    {
                        y->color = BLACK;
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    }
                    else
                    {
                        //y color BLACK
                        if(z->parent->left == z)
                        {
                            //Case II Mirror
                            z = z->parent;
                            RightRotate(z);
                        }
                        //Case III Mirror
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        LeftRotate(z->parent->parent);
                    }
                }

                if(z->parent == 0) break;
            }
        }

        root->color = BLACK;
    }

    Node* Find(int key){
        Node* x = root;
        while(x->key != INF ){
            if(x->key == key) return x;
            else if(key > x->key){
                x = x->right;
            }
            else{
                x = x->left;
            }
        }

        return 0;
    }


    void Delete(int key){
        Node* z = Find(key);
        Node* y;
        Node* x;
        if(z->left->key == INF || z->right->key == INF){
            y=z;
        }
        else{
            y = TreeSuccessor(z);
        }
        if(y->left->key != INF){
            x = y->left;
        }
        else{
            x = y->right;
        }

        x->parent = y->parent;

        if(y->parent == 0){
                root = x;
                if(x->key == INF) {
                        root = new Node();
                        return;
                }

        }
        else if(y->parent->left == y){
            y->parent->left = x;
        }
        else{
            y->parent->right = x;
        }

        if(y != z){
            z->key = y->key;
        }

        if(y->color == BLACK){
            DeleteFixUp(x);
        }
    }


    void DeleteFixUp(Node* x){
       Node* w;
       while(x->color == BLACK && x != root){
            if(x->parent->left == x){
                w = x->parent->right;

                //sibling red--- Case 1
                if(w->color == RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }

                //Sibling Black and its children Black----- Case 2
                if(w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    x = x->parent;
                }
                else{
                    //Case 3
                    if(w->right->color == BLACK){
                        w->left->color = BLACK;
                        w->color = RED;
                        RightRotate(w);
                        w = x->parent->right;
                    }

                    //Case 4
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(x->parent);
                    x =  root;
                }
            }
            else{
                // x being the Right Child
                w = x->parent->left;

                //sibling red--- Case 1
                if(w->color == RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }

                 //Sibling Black and its children Black----- Case 2
                if(w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    x = x->parent;
                }
                else{
                    //Case 3
                    if(w->left->color == BLACK){
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = x->parent->left;
                    }

                    //Case 4
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(x->parent);
                    x =  root;
                }

            }
        }
        x->color = BLACK;

    }

    void preOrder(Node *t)
    {
        if(t->key == INF) return; //In case of empty tree
        cout<<t->key<<":";
        if(t->color == RED) cout<<"r";
        else cout<<"b";
        if(t->left->key != INF||t->right->key!=INF){
            cout<<"(";
            preOrder(t->left);
            cout<<")(";
            preOrder(t->right);
            cout<<") ";
        }

    }

    void printGraph()
    {
        preOrder(root);
        cout<<endl;
    }

    ~RedBlackTree()
    {
        delete root;
    }

};

int main()
{

    RedBlackTree rbt;
    char c;
    int num;
    ifstream infile;
    infile.open("input1.txt");


    while(!infile.eof())
    {
        infile>>c>>num;
        if(c == 'F'){
            Node* x = rbt.Find(num);
            if(x == 0){
                cout<<"False"<<endl;
            }
            else{
                cout<<"True"<<endl;
            }
        }
        else if(c == 'I'){
            rbt.Insert(num);
            rbt.printGraph();
        }
        else if(c == 'D'){
            rbt.Delete(num);
            rbt.printGraph();
        }


    }
    infile.close();



}


