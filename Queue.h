// Programmer: Pui Lee
// Programmer's ID: 1147451

#ifndef Queue_h
#define Queue_h

template <typename T>
class Queue
{
public:
    Queue();
    Queue(const Queue<T>&);
    ~Queue();
    Queue<T>& operator=(const Queue<T>&);
    void push(const T&);
    T& front();
    T& back();
    void pop();
    int size() const {return siz;}
    bool empty() const;
    void clear();
    
private:
    struct Node{
        T value;
        Node* next;
    };
    Node* firstNode;
    Node* lastNode;
    int siz;
    T dummy;
};

//main constructor
template <typename T>
Queue<T>::Queue(){
    firstNode = nullptr;
    lastNode = nullptr;
    siz = 0;
    dummy = T();
}

//copy constructor
template <typename T>
Queue<T>::Queue(const Queue<T>& original){
    firstNode = nullptr;
    lastNode = nullptr;
    siz = original.siz;
    for(Node* p = original.firstNode; p; p = p->next){
        Node* newNode = new Node;
        newNode->value = p->value;
        newNode->next = nullptr;
        if(lastNode)
            lastNode->next = newNode;
        else
            firstNode = newNode;
        lastNode = newNode;
    }
}

//destructor
template<typename T>
Queue<T>::~Queue<T>(){
    while(firstNode){
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
    }
}

//assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& original){
    if(this != &original){
        //delete existing list
        while(firstNode){
            Node* p = firstNode;
            firstNode = firstNode->next;
            delete p;
        }
        //build new list
        for(Node* p = original.firstNode; p; p = p->next){
            Node* newNode = new Node;
            newNode->value = p->value;
            newNode->next = nullptr;
            if(lastNode)
                lastNode->next = newNode;
            else
                firstNode = newNode;
            lastNode = newNode;
        }
        siz = original.siz;
    }
    return *this;
}

//push
template<typename T>
void Queue<T>::push(const T& x){
    Node* newNode = new Node;
    newNode->value = x;
    newNode->next = nullptr;
    if(lastNode)
        lastNode->next = newNode;
    else
        firstNode = newNode;
    lastNode = newNode;
    siz++;
}

//front
template<typename T>
T& Queue<T>::front(){
    if(!firstNode)
        return dummy;
    return firstNode->value;
}

//back
template<typename T>
T& Queue<T>::back(){
    if(!lastNode)
        return dummy;
    return lastNode->value;
}

//pop
template<typename T>
void Queue<T>::pop(){
    if(firstNode){
        Node*p = firstNode;
        firstNode = firstNode->next;
        delete p;
        siz--;
    }
}

//empty
template<typename T>
bool Queue<T>::empty() const{
    if(firstNode)
        return false;
    else
        return true;
}

//clear
template<typename T>
void Queue<T>::clear(){
    while(firstNode){
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        siz--;
    }
    lastNode = nullptr;
}

#endif /* Queue_h */

