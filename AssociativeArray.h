// Programmer: Pui Lee
// Programmer's ID: 1147451

#ifndef AssociativeArray_h
#define AssociativeArray_h

#include <queue>
//#include <queue>

template <typename K, typename V>
class AssociativeArray
{
public:
    AssociativeArray(int=2); //constructor with default value 2
    AssociativeArray(const AssociativeArray<K, V>&); //copy constructor
    ~AssociativeArray() { delete [] data;} //destructor
    AssociativeArray<K, V>& operator=(const AssociativeArray<K, V>&); //assignment operator
    V operator[](const K&) const; //getter
    V& operator[](const K&); //setter
    bool containsKey(const K&) const;
    void deleteKey(const K&);
    queue<K> keys() const;
    int size() const { return siz;}
    void clear();
    
private:
    struct Node{
        K key;
        V value;
        bool inUse;
    };
    
    Node* data;
    int cap;
    V dummy;
    int siz;
    void capacity(int);
    
};

//operator ==
template <typename K, typename V>
bool operator==(const AssociativeArray<K, V>& a, const AssociativeArray<K, V>& b){
    if(a.key == b.key && a.value == b.value && a.inUse == b.inUse)
        return true;
    return false;
}

//constructor
template <typename K, typename V>
AssociativeArray<K, V>::AssociativeArray(int cap){
    this->cap = cap;
    dummy = V(); //initialize dummy
    siz = 0;
    data = new Node[cap];
    for(int i = 0; i < cap; i++){
        data[i].inUse = false;
        data[i].value = V(0);
    }
}

//copy constructor
template <typename K, typename V>
AssociativeArray<K, V>::AssociativeArray(const AssociativeArray<K, V>& original){
    cap = original.cap;
    siz = original.siz;
    data = new Node[cap];
    for(int i = 0; i < cap; i++){
        data[i].key = original.data[i].key;
        data[i].value = original.data[i].value;
        data[i].inUse = original.data[i].inUse;
    }
    dummy = original.dummy;
}

//assignment operator
template <typename K, typename V>
AssociativeArray<K, V>& AssociativeArray<K, V>::operator=(const AssociativeArray<K, V>& original){
    if(this != &original){
        delete[] data;
        cap = original.cap;
        siz = original.siz;
        data = new Node[cap];
        for(int i = 0; i < cap; i++){
            data[i].key = original.data[i].key;
            data[i].value = original.data[i].value;
            data[i].inUse = original.data[i].inUse;
        }
        dummy = original.dummy;
    }
    return *this;
}

//getter
template <typename K, typename V>
V AssociativeArray<K, V>::operator[](const K& key) const{
    for(int i = 0; i < cap; i++){
        if(data[i].inUse){
            if(data[i].key == key)
                return data[i].value;
        }
    }
    return dummy;
}

//setter
template <typename K, typename V>
V& AssociativeArray<K, V>::operator[](const K& key){
    int indexFirstUnusedKey = cap;
    for(int i = 0; i < cap; i++){
        if(data[i].inUse){
            if(data[i].key == key)
                return data[i].value;
        }
        else if(indexFirstUnusedKey == cap)
            indexFirstUnusedKey = i;
    }
    
    if(indexFirstUnusedKey == cap)
        capacity(max(1,cap * 2));
    data[indexFirstUnusedKey].key = key;
    data[indexFirstUnusedKey].value = V(0);
    data[indexFirstUnusedKey].inUse = true;
    siz++;
    
    return data[indexFirstUnusedKey].value;
}

//containsKey
template <typename K, typename V>
bool AssociativeArray<K, V>::containsKey(const K& key) const{
    for(int i = 0; i < cap; i++){
        if(data[i].inUse){
            if(data[i].key == key)
                return true;
        }
    }
    return false;
}

//deleteKey
template <typename K, typename V>
void AssociativeArray<K, V>::deleteKey(const K& key){
    for(int i = 0; i < cap; i++){
        if(data[i].inUse){
            if(data[i].key == key){
                data[i].inUse = false;
                siz--;
            }
        }
    }
}


//clear
template <typename K, typename V>
void AssociativeArray<K, V>::clear(){
    for(int i = 0; i < cap; i++){
        if(data[i].inUse)
            data[i].inUse = false;
    }
    siz = 0;
}

//keys function
template <typename K, typename V>
queue<K> AssociativeArray<K, V>::keys() const{
    queue<K> myQueue;
    for(int i = 0; i < cap; i++){
        if(data[i].inUse)
            myQueue.push(data[i].key);
    }
    return myQueue;
}

//capacity setter function
template <typename K, typename V>
void AssociativeArray<K, V>::capacity(int cap){
    Node* temp = new Node[cap];
    int limit = min(cap, this->cap);
    for(int i = 0; i < limit; i++){
        temp[i].key = data[i].key;
        temp[i].value = data[i].value;
        temp[i].inUse = data[i].inUse;
    }
    for(int i = limit; i < cap; i++){
        temp[i].value = V(0);
        temp[i].inUse = false;
    }
    delete [] data;
    data = temp;
    this->cap = cap;
}


#endif /* AssociativeArray_h */
