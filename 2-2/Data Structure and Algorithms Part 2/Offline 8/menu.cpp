#include<iostream>
#include<cmath>
#include<random>
#include <ctime>
#include <unistd.h>
#include<fstream>
using namespace std;

int size;

int Hash1(string key){
    //djb2 modified
    unsigned long hash = 0;
    for(int i = 0;i<key.length();i++){
        hash += (hash*33)+int(key[i]);
    }
    hash = hash%size;
    return hash;
}

int Hash2(string key){
    //FNV1 modified
    unsigned long hash = 14695981039346656037;
    unsigned long fnv_prime = 1099511628211;
    for(int i = 0;i<key.length();i++){
        hash = hash*fnv_prime;
        hash = hash^int(key[i]);
    }
    hash = hash%size;
    return hash;
}

string random_string(size_t length )
{
    static const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
    static default_random_engine rng( time(nullptr) ) ;
    static uniform_int_distribution<size_t> distribution( 0, alphabet.size() - 1 ) ;

    string str ;
    while( str.size() < length ) str += alphabet[ distribution(rng) ] ;
    return str ;
}

class HashNode{
public:

    string key;
    int val;
    HashNode* next;

    HashNode(string key,int val){
        this->key = key;
        this->val = val;
        next = 0;
    }

};

class HashMapChain{
    HashNode** h;
    int collision;
    int probe;

public:
    HashMapChain(){
        h = new HashNode*[size];
        for(int i = 0;i<size;i++){
            h[i] = 0;
        }
        collision = 0;
        probe = 0;
    }

    bool Insert(string key,int value,int hash(string)){
        //int k = StringtoKey(key);
        int h_idx = hash(key);

        HashNode* prev = 0;
        HashNode* node = h[h_idx];
        if(node!=0){
            collision++;
        }
        while(node != 0){
            if(node->key == key){
                cout<<"key already exists"<<endl;
                collision--;
                return false;
            }
            prev = node;
            node = node->next;
        }

        if(prev == 0){
            h[h_idx] = new HashNode(key,value);
        }
        else{
            prev->next = new HashNode(key,value);
        }

        return true;

    }

    int Search(string key,int hash(string)){
        //int k = StringtoKey(key);
        int h_idx = hash(key);
        HashNode* node = h[h_idx];
        while(node != 0){
            probe++;
            if(node->key == key){
                return node->val;
            }
            node = node->next;
        }
        return -99999;

    }

    void del(string key,int hash(string)){
        //int k = StringtoKey(key);;
        int h_idx = hash(key);
        HashNode* node = h[h_idx];
        HashNode* prev = 0;
        while(node != 0){
            if(node->key == key){
                if(prev != 0){
                    prev->next = node->next;
                    delete node;
                }
                else{
                    h[h_idx] = h[h_idx]->next;
                }
                cout<<"Key deleted"<<endl;
                return;
            }
            prev = node;
            node = node->next;
        }
        cout<<"Key not found"<<endl;
    }

    int getProbe(){return probe;}
    int getCollision(){return collision;}

    ~HashMapChain(){
       for(int i = 0;i<size;i++){
            delete h[i];
        }
        delete h;
    }

};

class DoubleHash{
    HashNode** h;
    int collision;
    int probe;

public:
    DoubleHash(){
        h = new HashNode*[size];
        for(int i = 0;i<size;i++){
            h[i] = 0;
        }
        collision = 0;
        probe = 0;
    }

    int AuxHash(string key){
        unsigned long hash = 0;
        for(int i = 0;i<key.length();i++){
            hash += key[i];
            hash += (hash<<10);
            hash ^= (hash>>6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash%size;
    }

    bool Insert(string key,int value,int hash(string)){
        //int k = StringtoKey(key);
        //int c = 0;
        int h_idx = hash(key);
        int i = 1;
        while(h[h_idx]!=0){
            if(h[h_idx]->key == key){
                cout<<key<<" key already exists"<<endl;
                return false;
            }
            h_idx = (hash(key)+(i*AuxHash(key)))%size;
            i++;
            collision++;
            if(i == size){
                cout<<"Double Hash Collision not avoided for key "<<key<<endl;
                return false;
            }
        }

        h[h_idx] = new HashNode(key,value);
        //collision += c;
        return true;

    }

    int Search(string key,int hash(string)){
        //int k = StringtoKey(key);
        int h_idx = hash(key);
        int i = 0;
        while(h[h_idx]!= 0){
            probe++;
            if(h[h_idx]->key == key){
                return h[h_idx]->val;
            }

            h_idx = (hash(key)+(i*AuxHash(key)))%size;
            i++;
            if(i == size) break;
        }
        return -99999;

    }

    void del(string key,int hash(string)){
        //int k = StringtoKey(key);
        int h_idx = hash(key);
        int i = 0;
        while(h[h_idx]!= 0){
            if(h[h_idx]->key == key){
                h[h_idx] = 0;
                cout<<"Key deleted"<<endl;
                return;
            }
            h_idx = (hash(key)+(i*AuxHash(key)))%size;
            i++;
            if(i == size){
                    cout<<"Key not found"<<endl;
                    break;
            }
        }

    }

    int getProbe(){return probe;}
    int getCollision(){return collision;}

    ~DoubleHash(){
       for(int i = 0;i<size;i++){
            delete h[i];
        }
        delete h;
    }

};


class CustomProbe{
    HashNode** h;
    int c1,c2;
    int collision ;
    int probe;

public:
    CustomProbe(){
        h = new HashNode*[size];
        for(int i = 0;i<size;i++){
            h[i] = 0;
        }
        this->c1 = 7;
        this->c2 = 61;
        collision = 0;
        probe = 0;
    }

    int AuxHash(string key){
        unsigned long hash = 0;
        for(int i = 0;i<key.length();i++){
            hash += key[i];
            hash += (hash<<10);
            hash ^= (hash>>6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash%size;
    }

    bool Insert(string key,int value,int hash(string)){
        //int k = StringtoKey(key);
        //int c = 0;
        int h_idx = hash(key);
        int i = 1;
        while(h[h_idx]!=0){
            if(h[h_idx]->key == key){
                cout<<key<<" key already exists"<<endl;
                return false;
            }
            h_idx = (hash(key)+(c1*i*AuxHash(key))+(c2*i*i))%size;
            i++;
            collision++;
            if(i == size){
                cout<<"Custom Hash Collision not avoided for key :"<<key<<endl;
                return false;
            }
        }

        h[h_idx] = new HashNode(key,value);
        //collision += c;
        return true;

    }

    int Search(string key,int hash(string)){
        //int k = StringtoKey(key);
        int h_idx = hash(key);
        int i = 0;
        while(h[h_idx]!= 0){
            probe++;
            if(h[h_idx]->key == key){
                return h[h_idx]->val;
            }

            h_idx = (hash(key)+(c1*i*AuxHash(key))+(c2*i*i))%size;
            i++;
            if(i == size) break;
        }
        return -99999;

    }

    void del(string key,int hash(string)){
        int h_idx = hash(key);
        int i = 0;
        while(h[h_idx]!= 0){
            if(h[h_idx]->key == key){
                h[h_idx] = 0;
                cout<<"Key Deleted"<<endl;
                return;
            }
            h_idx = (hash(key)+(c1*i*AuxHash(key))+(c2*i*i))%size;
            i++;
            if(i == size){
                    cout<<"Key not found"<<endl;
                    break;
            }
        }

    }

    int getProbe(){return probe;}
    int getCollision(){return collision;}

    ~CustomProbe(){
       for(int i = 0;i<size;i++){
            delete h[i];
        }
        delete h;
    }

};


int main(){

    cout<<"Size: ";
    cin>>size;
    ofstream out;
    out.open("output.txt");
    HashMapChain* hashc1 = new HashMapChain();
    CustomProbe* hashp1 = new CustomProbe();
    DoubleHash* hashd1 = new DoubleHash();
    HashMapChain* hashc2 = new HashMapChain();
    CustomProbe* hashp2 = new CustomProbe();
    DoubleHash* hashd2 = new DoubleHash();

    for(int i = 1;i<=size/2;i++){
        string str = random_string(7);
        out<<str<<"\n";
        cout<<str<<endl;
        bool success = hashc1->Insert(str,i,&Hash1);
        if(success == false){
            i--;
            continue;
        }

        success = hashc2->Insert(str,i,&Hash2);


        success = hashd1->Insert(str,i,&Hash1);
        success = hashd2->Insert(str,i,&Hash2);

        success = hashp1->Insert(str,i,&Hash1);
        success = hashp2->Insert(str,i,&Hash2);

    }
    int option,i = size/2+1;
    while(1){
        cout<<"1.Insert  2.Delete 3.Search"<<endl;
        cin>>option;
        if(option == 1){
            string str;
            cout<<"Input: ";
            cin>>str;
            cout<<endl;
            i++;
            hashc1->Insert(str,i,&Hash1);
            hashc2->Insert(str,i,&Hash2);


            hashd1->Insert(str,i,&Hash1);
            hashd2->Insert(str,i,&Hash2);

            hashp1->Insert(str,i,&Hash1);
            hashp2->Insert(str,i,&Hash2);

        }
        else if(option == 2){
            string str;
            cout<<"Delete: ";
            cin>>str;
            cout<<endl;
            hashc1->del(str,&Hash1);
            hashc2->del(str,&Hash2);


            hashd1->del(str,&Hash1);
            hashd2->del(str,&Hash2);

            hashp1->del(str,&Hash1);
            hashp2->del(str,&Hash2);
        }
        else if(option == 3){
            string str;
            cout<<"Search: ";
            cin>>str;
            cout<<endl;

            cout<<"Hash1 Chaining: "<<hashc1->Search(str,&Hash1)<<endl;
            cout<<"Hash2 Chaining: "<<hashc2->Search(str,&Hash2)<<endl;


            cout<<"Hash1 Double Hash: "<<hashd1->Search(str,&Hash1)<<endl;
            cout<<"Hash2 Double Hash: "<<hashd2->Search(str,&Hash2)<<endl;

            cout<<"Hash1 Custom Hash: "<<hashp1->Search(str,&Hash1)<<endl;
            cout<<"Hash2 Custom Hash: "<<hashp2->Search(str,&Hash2)<<endl;
        }
    }


}



