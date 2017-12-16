// Programmer: Pui Lee
// Programmer's ID: 1147451

#ifndef Stack_h
#define Stack_h

template <typename T>
class Stack
{
public:
    Stack(); //main constructor
    Stack(const Stack<T>&); //copy constructor
    ~Stack();
    Stack<T>& operator=(const Stack<T>&);
    void push(const T&);
    T& peek();
    void pop();
    void clear();
    int size() const {return siz;}
    bool empty() const;
    
private:
    struct Node{
        T value;
        Node* next;
    };
    Node* firstNode;
    int siz;
    T dummy;
    
};

//main constructor
template <typename T>
Stack<T>::Stack(){
    firstNode = nullptr;
    siz = 0;
    dummy = T(0);
}

//copy constructor
template <typename T>
Stack<T>::Stack(const Stack<T>& original){
    firstNode = nullptr;
    Node* lastNode = nullptr; //temporary tail
    siz = original.size;
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
template <typename T>
Stack<T>::~Stack(){
    while(firstNode){
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
    }
}

//assignment operator
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& original){
    if(this != &original){
        //delete existing list
        while(firstNode){
            Node* p = firstNode;
            firstNode = firstNode->next;
            delete p;
        }
        //build new list
        Node* lastNode = nullptr;
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
template <typename T>
void Stack<T>::push(const T& x){
    Node* newNode = new Node;
    newNode->value = x;
    newNode->next = nullptr;
    if(!firstNode)
        firstNode = newNode;
    else{
        newNode->next = firstNode;
        firstNode = newNode;
    }
    siz++;
}

//peek
template <typename T>
T& Stack<T>::peek(){
    if(!firstNode)
        return dummy;
    return firstNode->value;
}

//pop
template <typename T>
void Stack<T>::pop(){
    if(firstNode){
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        siz--;
    }
}

//clear
template <typename T>
void Stack<T>::clear(){
    while(firstNode){
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        siz--;
    }
}

//empty
template <typename T>
bool Stack<T>::empty() const{
    if(firstNode)
        return false;
    else
        return true;
}


#endif /* Stack_h */
