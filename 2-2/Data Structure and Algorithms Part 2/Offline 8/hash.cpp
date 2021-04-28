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
                return;
            }
            prev = node;
            node = node->next;
        }
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
                //cout<<"Collision not avoided for key "<<key<<endl;
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
                return;
            }
            h_idx = (hash(key)+(i*AuxHash(key)))%size;
            i++;
            if(i == size) break;
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
                //cout<<"Collision not avoided for key :"<<key<<endl;
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
                return;
            }
            h_idx = (hash(key)+(c1*i*AuxHash(key))+(c2*i*i))%size;
            i++;
            if(i == size) break;
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
    int customprobe1 = 0;
    int customprobe2 = 0;
    int chainprobe1 = 0;
    int chainprobe2 = 0;
    int doubleprobe1 = 0;
    int doubleprobe2 = 0;
    for(int i = 1;i<=size;i++){
        string str = random_string(7);
        out<<str<<"\n";
        //cout<<str<<endl;
        //this_thread::sleep_for(chrono::nanoseconds(1));
        bool success = hashc1->Insert(str,i,&Hash1);
        if(success == false){
            i--;
            continue;
        }
        if(i%10 == 0){
            chainprobe1++;
            hashc1->Search(str,&Hash1);
        }

        success = hashc2->Insert(str,i,&Hash2);
        if(i%10 == 0){
            chainprobe2++;
            hashc2->Search(str,&Hash2);
        }

        success = hashd1->Insert(str,i,&Hash1);
        if(i%10 == 0 && success == true){
            doubleprobe1++;
            hashd1->Search(str,&Hash1);
        }

        success = hashd2->Insert(str,i,&Hash2);
        if(i%10 == 0 && success == true){
            doubleprobe2++;
            hashd2->Search(str,&Hash2);
        }

        success = hashp1->Insert(str,i,&Hash1);
        if(i%10 == 0 && success == true){
            customprobe1++;
            hashp1->Search(str,&Hash1);
        }

        success = hashp2->Insert(str,i,&Hash2);
        if(i%10 == 0 && success == true){
            customprobe2++;
            hashp2->Search(str,&Hash2);
        }

    }
    cout<<"Hash1 - Chaining Method Collision: "<<hashc1->getCollision()<<endl;
    cout<<"Hash1 - Chaining Method Avg Probe: "<<hashc1->getProbe()*1.0/chainprobe1<<endl;

    cout<<"Hash2 - Chaining Method Collision: "<<hashc2->getCollision()<<endl;
    cout<<"Hash2 - Chaining Method Avg Probe: "<<hashc2->getProbe()*1.0/chainprobe2<<endl;

    cout<<"Hash1 - DoubleHash Collision: "<<hashd1->getCollision()<<endl;
    cout<<"Hash1 - DoubleHash Avg Probe: "<<hashd1->getProbe()*1.0/doubleprobe1<<endl;

    cout<<"Hash2 - DoubleHash Collision: "<<hashd2->getCollision()<<endl;
    cout<<"Hash2 - DoubleHash Avg Probe: "<<hashd2->getProbe()*1.0/doubleprobe2<<endl;

    cout<<"Hash1 - Custom Probing Collision: "<<hashp1->getCollision()<<endl;
    cout<<"Hash1 - Custom Probing Avg Probe: "<<hashp1->getProbe()*1.0/customprobe1<<endl;

    cout<<"Hash2 - Custom Probing Collision: "<<hashp2->getCollision()<<endl;
    cout<<"Hash2 - Custom Probing Avg Probe: "<<hashp2->getProbe()*1.0/customprobe2<<endl;


    delete hashc1,hashc2,hashd1,hashd2,hashp1,hashp2;

}


