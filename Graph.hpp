#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <stdexcept>
#include <vector>

#define TRUE 1
#define FALSE 0

using namespace std;
namespace raphael{
    
    class Graph {
    private:
        vector<vector<int>> mat;
        vector<bool> visited; 
        vector<bool> recStack;         // recursion for the directed graph

    public:
        Graph() : mat(0), visited(false), recStack(false) {} //constructor
        void loadGraph(const vector<vector<int>>& mat); //load
        void printGraph() const; // print num of vertices and num of edges
        int isDirected();  // return 1 if the graph is directed and 0 if not
      
        void setVisited(int index, bool val); 
        void resetVisited(); 
        void resetRecStack(); 
        vector<bool> getVisited(); // receive all
        bool getVisited(int index); // overload the precedent function and return if a specific index was visited
        vector<vector<int>> getMatrix(); // return the matrix of the graph
        void setRecStack(int index, bool val); 
        bool getRecStack(int index);
        bool haveNegative(); // if we have a negative edge in the graph return 1 if not 0

    };
}



#endif