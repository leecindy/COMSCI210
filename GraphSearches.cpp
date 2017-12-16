// Programmer: Pui Lee
// Programmer's ID: 1147451

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct Node
{
    string name;
    
    bool isVisited;
    list<int> neighbors;
};

queue<int> doBreadthFirstSearch(int iOriginNode, vector<Node>& database)
{
    queue<int> searchOrder; // return this queue of indices
    queue<int> toDo;
    
    for(int i = 0; i < database.size(); i++){
        database[i].isVisited = false;
    }
    
    database[iOriginNode].isVisited = true;
    searchOrder.push(iOriginNode);
    toDo.push(iOriginNode);
    
    while(!toDo.empty()){
        int iTarget = toDo.front();
        list<int>::const_iterator it;
        for(it = database[iTarget].neighbors.begin(); it != database[iTarget].neighbors.end(); it++){
            if(database[*it].isVisited == false){
                database[*it].isVisited = true;
                searchOrder.push(*it);
                toDo.push(*it);
            }
        }
        toDo.pop();
    }
    return searchOrder;
}

queue<int> doDepthFirstSearch(int iOriginNode, vector<Node>& database)
{
    queue<int> searchOrder; // return this queue of indices
    stack<int> toDo;
    
    for(int i = 0; i < database.size(); i++){
        database[i].isVisited = false;
    }
    
    toDo.push(iOriginNode);
    
    while(!toDo.empty()){
        int iTarget = toDo.top();
        toDo.pop();
        
        if(database[iTarget].isVisited == false){
            database[iTarget].isVisited = true;
            searchOrder.push(iTarget);
        
            list<int>::reverse_iterator rit;
            for(rit = database[iTarget].neighbors.rbegin(); rit != database[iTarget].neighbors.rend(); rit++){
                if(database[*rit].isVisited == false){
                    toDo.push(*rit);
                }
            }
        }
   
    }
    return searchOrder;
}


int main()
{
    ifstream fin;
    fin.open("cities.txt");
    if (!fin.good()) throw "I/O error";
    
    // process the input file
    vector<Node> database;
    while (fin.good()) // EOF loop
    {
        string fromCity, toCity;
        
        // read one edge
        getline(fin, fromCity);
        getline(fin, toCity);
        fin.ignore(1000, 10); // skip the line with distance
        fin.ignore(1000, 10); // skip the separator
        
        // add vertices for new cities included in the edge
        int iToNode = -1, iFromNode = -1, i;
        for (i = 0; i < database.size(); i++) // seek "to" city
            if (database[i].name == fromCity)
                break;
        if (i == database.size()) // not in database yet
        {
            // store the node if it is new
            Node fromNode = {fromCity};
            database.push_back(fromNode);
        }
        iFromNode = i;
        
        for (i = 0; i < database.size(); i++) // seek "from" city
            if (database[i].name == toCity)
                break;
        if (i == database.size()) // not in vector yet
        {
            // store the node if it is new
            Node toNode = {toCity};
            database.push_back(toNode);
        }
        iToNode = i;
        
        // store bi-directional edges
        database[iFromNode].neighbors.push_back(iToNode);
        database[iToNode].neighbors.push_back(iFromNode);
    }
    fin.close();
    cout << "Input file processed\n\n";
    
    while (true)
    {
        // get the start city for the search
        string startCity;
        cout << "\nEnter the start city [blank to exit]: ";
        getline(cin, startCity);
        if (startCity.length() == 0) break;
        
        // find the start city
        int i;
        for (i = 0; i < database.size(); i++)
            if (database[i].name == startCity)
                break;
        
        // BFS result by copy-pop
        cout << "BFS";
        for (queue<int> q = doBreadthFirstSearch(i, database); !q.empty(); q.pop())
            cout  << '-'<< database[q.front()].name;
        cout << endl;
        
        // DFS result by copy-pop
        cout << "DFS";
        for (queue<int> q = doDepthFirstSearch(i, database); !q.empty(); q.pop())
            cout  << '-'<< database[q.front()].name;
        cout << endl;
    }
}
