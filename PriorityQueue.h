// Programmer: Pui Lee
// Programmer's ID: 1147451

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <algorithm>
using namespace std;

template<typename V>
class PriorityQueue
{
public:
    PriorityQueue(int=2);
    PriorityQueue(const PriorityQueue<V>&);
    ~PriorityQueue() { delete [] values;}
    PriorityQueue<V>& operator=(const PriorityQueue<V>&);
    
    void push(const V&);
    void pop();
    V top() const { return values[0];}
    int size() { return siz;}
    bool empty() { return siz == 0 ? true : false;}
    void clear() { siz = 0;}
    
private:
    V* values;
    int cap;
    int siz;
    void capacity(int);
};

//constructor
template<typename V>
PriorityQueue<V>::PriorityQueue(int cap){
    this->cap = cap;
    siz = 0;
    values = new V[cap];
}

//copy constructor
template<typename V>
PriorityQueue<V>::PriorityQueue(const PriorityQueue<V>& original){
    cap = original.cap;
    siz = original.siz;
    values = new V[cap];
    for(int i = 0; i < cap; i++){
        values[i] = original.values[i];
    }
}

//assignment operator
template<typename V>
PriorityQueue<V>& PriorityQueue<V>::operator=(const PriorityQueue<V>& original){
    if(this != original){
        delete[] values;
        cap = original.cap;
        siz = original.siz;
        values = new V[cap];
        for(int i = 0; i < cap; i++){
            values[i] = original.values[i];
        }
    }
    return *this;
}

//push
template<typename V>
void PriorityQueue<V>::push(const V& value){
    if(siz == cap)
        capacity(cap * 2);
    values[siz] = value;
    int index = siz;
    while(index > 0){
        int p_index = (index + 1) / 2 - 1;
        if(values[index] < values[p_index])
            break;
        else{
            swap(values[index], values[p_index]);
            index = p_index;
        }
    }
    siz++;
}

//pop
template<typename V>
void PriorityQueue<V>::pop(){
    int index = 0;
    while(index <= siz){
        int l_index = index * 2 + 1;
        int r_index = index * 2 + 2;
        if(l_index >= siz)
            break;
        else if(r_index >= siz){
            values[index] = values[l_index];
            index = l_index;
            break;
        }
        else if(values[r_index] < values[l_index]){
            values[index] = values[l_index];
            index = l_index;
        }
        else{
            values[index] = values[r_index];
            index = r_index;
        }
    }
    siz--;
    if(index == siz)
        return;
    else{
        values[index] = values[siz];
        while(siz > 1 && index > 0){
            int p_index = (index + 1) / 2 - 1;
            if(values[index] < values[p_index])
                break;
            else{
                swap(values[index], values[p_index]);
                index = p_index;
            }
        }
    }
    
}

//capacity
template<typename V>
void PriorityQueue<V>::capacity(int cap){
    V* temp = new V[cap];
    int limit = min(this->cap, cap);
    for(int i = 0; i < limit; i++){
        temp[i] = values[i];
    }
    for(int i = limit; i < cap; i++){
        temp[i] = V();
    }
    delete[] values;
    values = temp;
    this->cap = cap;
    
}


#endif /* PriorityQueue_h */
