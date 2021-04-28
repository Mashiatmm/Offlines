#include<iostream>

using namespace std;

class Node{
public:
    int value;
    Node *parent;
    Node * left;
    Node *right;

    Node(int val){
        value=val;
        parent=NULL;
        left=NULL;
        right=NULL;
    }
};

class BinarySearchTree{
    Node *root;

public:
    BinarySearchTree(int value){
        root=new Node(value);
    }

    void add_left_child(Node *par,Node *child){
        par->left=child;
        if(child!=NULL){
            child->parent=par;
        }
    }

    void add_right_child(Node *par,Node *child){
        par->right=child;
        if(child!=NULL){
            child->parent=par;
        }
    }

    Node* get_root(){return root;}

    void Insert(int value){
        Node *insert=new Node(value);
        Node *temp=root;
        if(root==NULL){
            insert->parent=NULL;
            root=insert;
            return;
        }
        Node *parentNode;
        while(temp!=NULL){
            parentNode=temp;
            if(temp->value==value) {
                    delete insert;
                    return;
            }
            else if(value>temp->value) temp=temp->right;
            else temp=temp->left;
        }
        temp=parentNode;
        if(value>temp->value){
            add_right_child(temp,insert);
        }else add_left_child(temp,insert);

        insert->value=value;
    }

    bool Search(int find){
        Node *temp=root;
        while(temp!=NULL){
            if(temp->value==find){
                return true;
            }
            else if(find>temp->value){
                temp=temp->right;
            }
            else{
                temp=temp->left;
            }
        }
        return false;
    }

    void transplant(Node *temp,Node *trans){
        if(temp==root){
            root=trans;
        }
        else if(temp==temp->parent->left){
            add_left_child(temp->parent,trans);
        }
        else
            add_right_child(temp->parent,trans);
    }

    void Delete(int value){
        Node *temp=root;
        while(temp!=NULL){
            if(value>temp->value) temp=temp->right;
            else if(value<temp->value) temp=temp->left;
            else{
                //value exists in the binary tree

                //if node has only one child replace it with that child
                if(temp->left==NULL){
                    transplant(temp,temp->right);
                }
                else if(temp->right==NULL){
                    transplant(temp,temp->left);
                }
                else{
                    Node *successor=temp->right;
                    Node *par_successor;
                    while(successor!=NULL){
                        par_successor=successor;
                        successor=successor->left;
                    }
                    successor=par_successor;

                    //stored the successor of temp->right
                    if(successor->parent!=temp){
                        //replace successor by its right subtree
                        transplant(successor,successor->right);
                        //add right subtree of the node to be deleted at successor
                        add_right_child(successor,temp->right);
                    }
                    transplant(temp,successor);
                    add_left_child(successor,temp->left);
                }
                break;
            }
        }
    }

    void in_order(Node *temproot){
        if(temproot==NULL) return;
        in_order(temproot->left);
        cout<<temproot->value<<endl;

        in_order(temproot->right);
    }

    void pre_order(Node *temproot){
        if(temproot==NULL) return;
        cout<<temproot->value<<endl;
        pre_order(temproot->left);
        pre_order(temproot->right);
    }

    int find_k(Node *temproot,int k,int &i){
        if(temproot==NULL) return 0;
        int sum=0;
        sum+=find_k(temproot->left,k,i);
        i++;
        if(i==k) {
                sum+=temproot->value;
        }
        sum+=find_k(temproot->right,k,i);
        return sum;

    }


    int height(Node *root){
        if(root==NULL) return 0;
        int lh=height(root->left);
        int rh=height(root->right);
        return max(lh,rh)+1;
    }
};


int main(){
        cout<<"Insert a root value to create a tree:"<<endl;
        int n,val;
        cin>>n;
        BinarySearchTree *bst=new BinarySearchTree(n);
        while(1){
            cout<<"1:Insert\t 2:Search\t 3:Delete\n4:In Order\t 5:Pre Order\t 6:Exit    7:k"<<endl;
            cin>>val;
            if(val==1){
                cout<<"Insert"<<endl;
                int in;
                cin>>in;
                bst->Insert(in);
            }
            else if(val==2){
                cout<<"Search"<<endl;
                int f;
                cin>>f;
                cout<<bst->Search(f)<<endl;
            }
            else if(val==3){
                cout<<"Delete"<<endl;
                int d;
                cin>>d;
                bst->Delete(d);
            }
            else if(val==4){
                cout<<"In Order Traversal"<<endl;
                bst->in_order(bst->get_root());
            }
            else if(val==5){
                cout<<"Pre Order Traversal"<<endl;
                bst->pre_order(bst->get_root());
            }
            else if(val==7){
                int k,i=0;
                cin>>k;
                cout<<bst->find_k(bst->get_root(),k,i)<<endl;
            }
            else {
                break;
            }
        }

        cout<<bst->height(bst->get_root())<<endl;

}
