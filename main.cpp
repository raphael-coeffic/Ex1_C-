#include "Graph.hpp"
#include "Algorithms.hpp"

#include <stdexcept>
#include <iostream>



using namespace std;
using namespace raphael;


int main()
{
    raphael::Graph g;
    // undirected matrix that represent a connected graph
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph); // load the graph

    cout << "\n" << endl; 
    g.printGraph();                                    // Should print: "Graph with 3 vertices and 6 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1"
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: 0->2.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->2->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0"
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "No negative cycle found."

    // directed matrix that represents a non-connected graph without cycle.
    vector<vector<int>> graph1 = {
        {0, 1, 0, 1},
        {0, 0, 0, 0},
        {0, 1, 0, 1},
        {0, 0, 0, 0}};

    g.loadGraph(graph1); // load the graph
    cout << "\n" << endl; 
    g.printGraph();                                    // Should print: "Graph with 4 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" 
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: "-1" 
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2}, B={1, 3}"
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "No negative cycle found.".

    // directed weithed matrix
    vector<vector<int>> graph2 = {
        {0, 4, 0, 0},
        {0, 0, -6, 0},
        {0, 0, 0, 3},
        {-2, 0, 0, 0}};
    g.loadGraph(graph2); // load the graph

    cout << "\n" << endl; 

    g.printGraph();                                    
    cout << Algorithms::isConnected(g) << endl;        // Should print: "Graph with 4 vertices and 2 edges."
    cout << Algorithms::shortestPath(g, 0, 1) << endl; // Should print: "Graph contains a negative cycle"
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->2->3->0"
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2}, B={1, 3}."
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "The negative cycle is: 1->2->3->0->1"
    
    
    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 3},
        {1, 0, 3, 0, 4},
        {2, 3, 0, 4, 3},
        {0, 0, 0, 5, 0}};

    cout << "\n" << endl; 

    try
    {
        g.loadGraph(graph3); // try to load the graph
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
    }

    
    return 0;
}