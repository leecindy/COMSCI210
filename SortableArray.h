// Programmer: Pui Lee
// Programmer's ID: 1147451

#ifndef SortableArray_h
#define SortableArray_h

#include <algorithm>

template <typename V>
class SortableArray
{
public:
    SortableArray(int=2); //constructor with default value 2
    SortableArray(const SortableArray<V>&); //copy constructor
    ~SortableArray() { delete [] values;} //destructor
    SortableArray<V> operator=(const SortableArray<V>&); //assignment operator
    int capacity() const { return cap;} //capacity getter
    void capacity(int); //capacity setter
    V operator[](int) const; //getter
    V& operator[](int); //setter
    void sort(int);
    
private:
    int cap;
    V* values;
    V dummy;
    V* heapSort(V[], int);
};

//constructor
template <typename V>
SortableArray<V>::SortableArray(int cap){
    this->cap = cap;
    dummy = V(); //initial dummy
    values = new V[cap];
    for(int i = 0; i < cap; i++){
        values[i] = V();
    }
}

//copy constructor
template <typename V>
SortableArray<V>::SortableArray(const SortableArray<V>& original){
    cap = original.cap;
    values = new V[cap];
    for(int i = 0; i < cap; i++){
        values[i] = original.values[i];
    }
    dummy = original.dummy;
}

//assignment operator
template <typename V>
SortableArray<V> SortableArray<V>::operator=(const SortableArray<V>& original){
    if(this != &original){
        delete [] values;
        cap = original.cap;
        values = new V[cap];
        for(int i = 0; i < cap; i++){
            values[i] = original.values[i];
        }
        dummy = original.dummy;
    }
    return *this;
}

//capacity setter
template <typename V>
void SortableArray<V>::capacity(int cap) {
    V* temp = new V[cap];
    int limit = min(this->cap, cap);
    for(int i = 0; i < limit; i++){
        temp[i] = values[i];
    }
    for(int i = limit; i < cap; i++){
        temp[i] = V();
    }
    delete [] values;
    values = temp;
    this->cap = cap;
}

//[] getter
template <typename V>
V SortableArray<V>::operator[](int index) const{
    if(index < 0 || index >= cap)
        return dummy;
    return values[index];
}

//[] setter
template <typename V>
V& SortableArray<V>::operator[](int index){
    if(index < 0)
        return dummy;
    else if(index >= cap){
        capacity(2 * index);
    }
    return values[index];
}

//sorting
template <typename V>
V* SortableArray<V>::heapSort(V* a, int size){
    for (int i = 1; i < size; i++)
    {
        for (int index = i;;)
        {
            int parentIndex = (index + 1) / 2 - 1;
            if (parentIndex < 0) break;
            if (a[parentIndex] >= a[index]) break;
            swap(a[parentIndex], a[index]);
            index = parentIndex;
        } }
    
    for (int index = size - 1; index > 0; index--)
    {
        swap(a[0], a[index]);
        int parentIndex = 0;
        while (true)
        {
            int leftChildIndex = 2 * parentIndex + 1;
            int rightChildIndex = 2 * parentIndex + 2;
            if (leftChildIndex >= index) break; // leaf at parentIndex
            if (rightChildIndex >= index) // one-child for parentIndex
            {
                if (a[leftChildIndex] <= a[parentIndex]) break;
                swap(a[leftChildIndex], a[parentIndex]);
                parentIndex = leftChildIndex;
            }
            else if (a[rightChildIndex] < a[leftChildIndex])
            {
                if (a[leftChildIndex] <= a[parentIndex]) break;
                swap(a[leftChildIndex], a[parentIndex]);
                parentIndex = leftChildIndex;
            }
            else
            {
                if (a[rightChildIndex] <= a[parentIndex]) break;
                swap(a[rightChildIndex], a[parentIndex]);
                parentIndex = rightChildIndex;
            } } }
    return a;
}

template <typename V>
void SortableArray<V>::sort(int n){
    if(n == 0) return;
    else{
        V* temp = new V[n];
        for(int i = 0; i < n; i++){
            temp[i] = values[i];
        }
        V* sorted = new V[n];
        sorted = heapSort(temp, n);
        for(int i = n; i < cap; i++){
            sorted[i] = values[i];
        }
        delete [] values;
        values = sorted;
    }
}

#endif /* SortableArray_h */
