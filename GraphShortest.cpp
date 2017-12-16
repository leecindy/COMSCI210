// Programmer: Pui Lee
// Programmer's ID: 1147451

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;

#include <cstdlib>

struct Node
{
    string name;
    
    bool isVisited;
    list<pair<int, double> > neighbors;
    int prev;
    double cost;
};

pair<stack<int>, double> getShortestRoute(int iStart, int iEnd, vector<Node>& database)
{
    pair<stack<int>, double> result;
    // TO DO -- write this function
   
    for(int i = 0; i < database.size(); i++){
        database[i].isVisited = false;
        database[i].prev = -1;
        database[i].cost = 0;
    }
 
    queue<int> toDo;
    database[iStart].isVisited = true;
    toDo.push(iStart);
    
    while(!toDo.empty()){
        int i = toDo.front();
        toDo.pop();
        list<pair<int, double> >::iterator it; // to iterate over neighbors
        for(it = database[i].neighbors.begin(); it != database[i].neighbors.end(); it++){
            if(database[it->first].isVisited)
                continue;
            database[it->first].prev = i;
            database[it->first].cost = database[i].cost + 1;
            database[it->first].isVisited = true;
            toDo.push(it->first);
            
            if(it->first == iEnd){
                while(!toDo.empty())
                    toDo.pop();
                break;
            }
        }
    }

    result.second = database[iEnd].cost;

    result.first.push(iEnd);
    while(database[iEnd].prev >= 0){
        result.first.push(database[iEnd].prev);
        iEnd = database[iEnd].prev;
    }
    
    return result;
}

int main()
{
    // programmer's identification
    cout << "Programmer: Pui Lee\n";
    cout << "Programmer's ID: 1147451\n";
    cout << "File: " << __FILE__ << endl;
    
    ifstream fin;
    fin.open("cities.txt");
    if (!fin.good()) throw "I/O error";
    
    // process the input file
    vector<Node> database;
    while (fin.good()) // EOF loop
    {
        string fromCity, toCity, cost;
        
        // read one edge
        getline(fin, fromCity);
        getline(fin, toCity);
        getline(fin, cost);
        fin.ignore(1000, 10); // skip the separator
        
        // add nodes for new cities included in the edge
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
        double edgeCost = atof(cost.c_str());
        database[iFromNode].neighbors.push_back(pair<int, double>(iToNode, edgeCost));
        database[iToNode].neighbors.push_back(pair<int, double>(iFromNode, edgeCost));
    }
    fin.close();
    cout << "Input file processed\n\n";
    
    while (true)
    {
        string fromCity, toCity;
        cout << "\nEnter the source city [blank to exit]: ";
        getline(cin, fromCity);
        if (fromCity.length() == 0) break;
        
        // find the from city
        int iFrom;
        for (iFrom = 0; iFrom < database.size(); iFrom++)
            if (database[iFrom].name == fromCity)
                break;
        
        cout << "Enter the destination city [blank to exit]: ";
        getline(cin, toCity);
        if (toCity.length() == 0) break;
        
        // find the destination city
        int iTo;
        for (iTo = 0; iTo < database.size(); iTo++)
            if (database[iTo].name == toCity)
                break;
        
        cout << "Route";
        pair<stack<int>, double> result = getShortestRoute(iFrom, iTo, database);
        for (; !result.first.empty(); result.first.pop())
            cout << '-' << database[result.first.top()].name;
        cout << "Total edges: " << result.second;  
        cout << endl;
    }
}
