//
// Programmer: Pui Lee
// Programmer's ID: 1147451

#ifndef HashTable_h
#define HashTable_h

#include <list>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

template <typename K, typename V, int CAP>
class HashTable
{
public:
    HashTable(int(*)(const K&)=0);
    double loadFactor() const { return 1.0 * siz / CAP;}
    V operator[](const K&) const; //getter
    V& operator[](const K&); //setter
    bool containsKey(const K&) const; //getter
    void deleteKey(const K&); //setter
    queue<K> keys() const;
    int size() const { return siz;}
    void clear();
    
private:
    struct Node{
        K key;
        V value;
    };
    
    list<Node> data[CAP]; //chaining
    int(*hashCode)(const K&); //alias for hashCode function
    int siz;
};

//constructor
template <typename K, typename V, int CAP>
HashTable<K, V, CAP>::HashTable(int(*hashCode)(const K&)){
    this->hashCode = hashCode;
    siz = 0;
}

//getter
template <typename K, typename V, int CAP>
V HashTable<K, V, CAP>::operator[](const K& key) const{
    int index = hashCode(key) % CAP;
    if(index < 0) index += CAP;
    typename list<Node>::const_iterator it;
    for(it = data[index].begin(); it != data[index].end(); it++){
        if(it->key == key)
            return it->value;
    }
}

//setter
template <typename K, typename V, int CAP>
V& HashTable<K, V, CAP>::operator[](const K& key){
    int index = hashCode(key) % CAP;
    if(index < 0) index += CAP;
    typename list<Node>::iterator it;
    if(data[index].empty()) siz++;
    for(it = data[index].begin(); it != data[index].end(); it++){
        if(it->key == key)
            return it->value; //found
    }
    
    //create new node when it's not found
    Node n;
    n.key = key;
    n.value = V();
    data[index].push_back(n);
    return data[index].back().value;
    
}

//containsKey
template <typename K, typename V, int CAP>
bool HashTable<K, V, CAP>::containsKey(const K& key) const{
    int index = hashCode(key) % CAP;
    if(index < 0) index += CAP;
    typename list<Node>::const_iterator it;
    for(it = data[index].begin(); it != data[index].end(); it++){
        if(it->key == key)
            return true;
    }
    return false;
}

//deleteKey
template <typename K, typename V, int CAP>
void HashTable<K, V, CAP>::deleteKey(const K& key){
    int index = hashCode(key) % CAP;
    if(index < 0) index += CAP;
    typename list<Node>::iterator it;
    for(it = data[index].begin(); it != data[index].end(); it++){
        if(it->key == key){
            data[index].erase(it);
        }
        if(data[index].empty()) siz--;
    }
}


//clear
template <typename K, typename V, int CAP>
void HashTable<K, V, CAP>::clear(){
    for(int i = 0; i < CAP; i++){
        data[i].clear();
    }
    siz = 0;
}

//keys function
template <typename K, typename V, int CAP>
queue<K> HashTable<K, V, CAP>::keys() const{
    queue<K> myQueue;
    for(int i = 0; i < CAP; i++){
        typename list<Node>::const_iterator it;
        for(it = data[i].begin(); it != data[i].end(); it++)
            myQueue.push(it->key);
    }
    return myQueue;
}


#endif /* HashTable_h */
