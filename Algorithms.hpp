#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "Graph.hpp"
#include <string>
#include <limits.h>
#include <algorithm> 



using namespace std;
namespace raphael {
    class Algorithms {
    private:
        static vector<int> path;
        string static negativeCycleDirected(Graph& g);  //Using Bellman-Ford
        string static negativeCycleUndirected(Graph& g); //use bellman ford but for undirected graph
        void static DFSfull(Graph& g, int vertex); // DFS that run on all the graph
        bool static DFSundirected(Graph& g, int vertex, int parent); // DFS for undirected graph
        bool static DFSdirected(Graph& g, int vertex); // DFS for directed graph
        string static printCycle(string flag); // This function can print a cycle with the path and he need to receive flag
                                               // that assume "negative", "cycle" or "shortest" 
 
    public:
        // return 1 if the graph is connected and 0 if not
        int static isConnected(Graph& g); 
        //return a string of the fortest path between start to end and if we don't find a path "-1"
        string static shortestPath(Graph& g, int start, int end); 
        // return a string of the cycle or "0"
        string static isContainsCycle(Graph& g);
        //return a string of the two parts or "0"
        string static isBipartite(Graph& g);
        // return a string of a negative cycle or "No negative cycle found."
        string static negativeCycle(Graph& g);
        
        
    };
}

#endif