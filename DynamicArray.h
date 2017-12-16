// Programmer: Pui Lee
// Programmer's ID: 1147451

#ifndef DynamicArray_h
#define DynamicArray_h

#include <algorithm>

template <typename T>
class DynamicArray
{
public:
    DynamicArray(int=2); //constructor with default value 2
    DynamicArray(const DynamicArray<T>&); //copy constructor
    ~DynamicArray() { delete [] values;} //destructor
    DynamicArray<T> operator=(const DynamicArray<T>&); //assignment operator
    int capacity() const { return cap;} //capacity getter
    void capacity(int); //capacity setter
    T operator[](int) const; //getter
    T& operator[](int); //setter
    
private:
    int cap;
    T* values;
    T dummy;
    
};

//constructor
template <typename T>
DynamicArray<T>::DynamicArray(int cap){
    this->cap = cap;
    dummy = T(); //initial dummy
    values = new T[cap];
    for(int i = 0; i < cap; i++){
        values[i] = T();
    }
}

//copy constructor
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original){
    cap = original.cap;
    values = new T[cap];
    for(int i = 0; i < cap; i++){
        values[i] = original.values[i];
    }
    dummy = original.dummy;
}

//assignment operator
template <typename T>
DynamicArray<T> DynamicArray<T>::operator=(const DynamicArray<T>& original){
    if(this != &original){
        delete [] values;
        cap = original.cap;
        values = new T[cap];
        for(int i = 0; i < cap; i++){
            values[i] = original.values[i];
        }
        dummy = original.dummy;
    }
    return *this;
}

//capacity setter
template <typename T>
void DynamicArray<T>::capacity(int cap) {
    T* temp = new T[cap];
    int limit = min(this->cap, cap);
    for(int i = 0; i < limit; i++){
        temp[i] = values[i];
    }
    for(int i = limit; i < cap; i++){
        temp[i] = T();
    }
    delete [] values;
    values = temp;
    this->cap = cap;
}

//[] getter
template <typename T>
T DynamicArray<T>::operator[](int index) const{
    if(index < 0 || index >= cap)
        return dummy;
    return values[index];
}

//[] setter
template <typename T>
T& DynamicArray<T>::operator[](int index){
    if(index < 0)
        return dummy;
    else if(index >= cap){
        capacity(2 * index);
    }
    return values[index];
}


#endif /* DynamicArray_h */
