// Programmer: Pui Lee
// Programmer's ID: 1147451

#include <iostream>
#include <string>
using namespace std;

#include <cassert>
#include <cmath>
#include <ctime>
#include "PriorityQueue.h"

int main(){
    // programmer's identification
    cout << "Programmer: Pui Lee\n";
    cout << "Programmer's ID: 1147451\n";
    cout << "File: " << __FILE__ << endl;
    
    
    cout.setf(ios::fixed);
    cout.precision(4);
    double elapsedSecondsNorm = 0;
    
    //define initial records to run
    int n = 1000000;
    
    for(int cycle = 0; cycle < 4; cycle++, n *= 2){
        
        //build a priority queue of size n using a for-loop
        PriorityQueue<int> myQueue;
        for(int i = 0; i < n; i++){
            myQueue.push(i);
        }
        
        //the priority queue to be tested has n values
        assert(n == myQueue.size());
        
        //start the timer
        clock_t startTime = clock();
        
        int reps = 10000;
        for(int rep = 0; rep < reps; rep++){
            myQueue.push(rep);
        }
        
        //stop the timer
        clock_t endTime = clock();
        
        //confirm the priority queue is ordered hi-to-lo
        while(!myQueue.empty()){
            int first = myQueue.top();
            myQueue.pop();
            int second = myQueue.top();
            assert(first >= second);
        }
        
        //compute timing results
        double elapsedSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        double factor = pow(2.0, double(cycle));
        if (cycle == 0) elapsedSecondsNorm = elapsedSeconds;
        double expectedSecondsLog = log(double(n)) / log(n / factor) * elapsedSecondsNorm;
        
        // reporting block
        cout << elapsedSeconds;
        if (cycle == 0) cout << " (expected)";
        else cout << " (expected " << elapsedSecondsNorm << " to " << expectedSecondsLog << ')';
        cout << " for n=" << n << endl;
        
    }
    
    
    
    
    
    
    
}
