#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>
#include <set>


using namespace std;

namespace raphael {

    vector<int> Algorithms::path;

    int Algorithms::isConnected(Graph& g) {
        g.resetVisited();  
        Algorithms::DFSfull(g, 0);  // DFS form vertice 0

        // check if all the vertices was visited in DFS
        for (int v : g.getVisited()) {
            if (v == 0) return 0;  // if a vertice was not visited the graph is not connected
        }

        // If the graph is directed, check if he weakly connected by use the transpose of the graph
        if (g.isDirected()) {
            
            // transpose
            size_t rows = g.getMatrix().size();
            size_t cols = g.getMatrix().empty() ? 0 : g.getMatrix()[0].size();
            vector<vector<int>> newMatrix(rows, vector<int>(cols, 0));
            for (size_t i = 0; i < g.getMatrix().size(); ++i) {
                for (size_t j = 0; j < g.getMatrix().size(); ++j) {
                    if (g.getMatrix()[i][j] != 0) {
                        newMatrix[j][i] = g.getMatrix()[i][j]; 
                    }
                }
            }
            Graph tr;
            tr.loadGraph(newMatrix);
            
            
            tr.resetVisited();  
            Algorithms::DFSfull(tr, 0);  

            // check if all the vertices was visited in DFS on the transpose
            for (bool v : tr.getVisited()) {
                if (v == 0) return 0;  // if a vertice was not visited the graph is not weakly connected
            }
        }

        return 1;  // The graph is connected
    }

    
    // shortest path by use Bellman-Ford 
    string Algorithms::shortestPath(Graph& g, int start, int end) {
        Algorithms::path.clear();
        int size = static_cast<int>(g.getMatrix().size());
        if (start < 0 || start >= size || end < 0 || end >= size) //check if the index are valids
        {
            throw invalid_argument("Invalid arguments");
        }
        
        if (negativeCycle(g) != "No negative cycle found.")
        {
            return "Graph contains a negative cycle";
        }
        size_t n = g.getMatrix().size();
        vector<int> dist(n, INT_MAX);
        vector<int> pred(n, -1);  // for build the path
        dist[static_cast<size_t>(start)] = 0;

        for (size_t step = 0; step < n - 1; ++step) {
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.getMatrix()[u][v] && dist[u] != INT_MAX && dist[u] + g.getMatrix()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.getMatrix()[u][v];
                        pred[v] = u;
                    }
                }
            }
        }

        for (int at = end; at != -1; at = pred[static_cast<size_t>(at)]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        // if the path don't beggin at start we don't have path
        if (path[0] != start) {
            return "-1";
        }

        //print the path if we found him
        return Algorithms::printCycle("shortest");
    }

    // use DFS
    string Algorithms::isContainsCycle(Graph& g) {
        g.resetVisited();
        g.resetRecStack();
        Algorithms::path.clear();
        if (g.isDirected()){
            for (size_t i = 0; i < g.getMatrix().size(); i++) {
                if (!g.getVisited(i)) {
                    if (Algorithms::DFSdirected(g, i)) { // dfs for directed graph
                        return Algorithms::printCycle("cycle");
                    }
                }
            }
        }
        else {
            for (size_t i = 0; i < g.getMatrix().size(); i++) {
                if (!g.getVisited(i)) {
                    if (Algorithms::DFSundirected(g, i, -1)) { // dfs for undirected graph
                        return Algorithms::printCycle("cycle");
                    }
                }
            }
        }
        
        return "0";
    }

    // use BFS
    string Algorithms::isBipartite(Graph& g) {
        vector<int> color(g.getMatrix().size(), -1);  // -1 for unclored
        vector<int> setA, setB;

        for (size_t start = 0; start < g.getMatrix().size(); ++start) {
            if (color[start] == -1) {  // this vertice is not colored
                color[start] = 0;
                queue<int> q;
                q.push(start);
                setA.push_back(start);

                while (!q.empty()) {
                    size_t u = static_cast<size_t>(q.front());
                    q.pop();

                    for (size_t v = 0; v < g.getMatrix().size(); v++) { // run on all the vertices
                        if (g.getMatrix()[u][v] != 0) { // check if we have an edge between u and v
                            if (color[v] == -1) {
                                color[v] = 1 - color[u];
                                q.push(v);
                                if (color[v] == 0) {
                                    setA.push_back(static_cast<int>(v));
                                } else {
                                    setB.push_back(static_cast<int>(v));
                                }
                            } else if (color[v] == color[u]) {
                                return "0";  // the graph is not bipartite
                            }
                        }
                    }
                }
            }
        }

        // build the string of the result
        string str;
        str = "The graph is bipartite: A={";
        for (size_t i = 0; i < setA.size(); ++i) {
            if (i > 0) str += ", ";
            str += to_string(setA[i]);
        }
        str += "}, B={";
        for (size_t i = 0; i < setB.size(); ++i) {
            if (i > 0) str += ", ";
            str += to_string(setB[i]);
        }
        str += "}";

        return str;  // string that represent the two graph
    }

    // use bellman Ford
    string Algorithms::negativeCycle(Graph& g) {
        Algorithms::path.clear();

        //if a graph doesn't countain negative values he can't countain a negative cycle
        if (!g.haveNegative()) 
        {
            return "No negative cycle found.";
        }

        if (g.isDirected())
            return negativeCycleDirected(g);
        
        else return negativeCycleUndirected(g);
        
    }
    
    //use bellman ford but for undirected graph
    string Algorithms::negativeCycleUndirected(Graph& g) {
        
        size_t V = g.getMatrix().size();
        vector<int> dist(V, INT_MAX);
        vector<int> pred(V, -1);
        dist[0] = 0;

        // Relax all edges V-1 times.
        for (int i = 0; i < static_cast<int>(V) - 1; i++) {
            for (size_t u = 0; u < V; u++) {
                for (size_t v = 0; v < V; v++) {
                    if (g.getMatrix()[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.getMatrix()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.getMatrix()[u][v];
                        if (pred[u] != static_cast<int>(v)) {  // Avoid length two cycles
                            pred[v] = static_cast<int>(u);
                        }
                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (size_t u = 0; u < V; u++) {
            for (size_t v = 0; v < V; v++) {
                if (g.getMatrix()[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.getMatrix()[u][v] < dist[v]) {
                    // Reconstruct the cycle
                    int current = static_cast<int>(v);
                    vector<bool> visited(V, false);
                    // Find the start of the cycle
                    while (!visited[static_cast<size_t>(current)]) {
                        visited[static_cast<size_t>(current)] = true;
                        current = pred[static_cast<size_t>(current)];
                        if (current == -1) {
                            break;
                        }
                    }
                    if (current != -1) {  // Check if cycle is complete
                        int start = current;
                        do {
                            path.push_back(current);
                            current = pred[static_cast<size_t>(current)];
                        } while (current != start);
                        path.push_back(start);
                        reverse(path.begin(), path.end());

                        return printCycle("negative");
                    }
                }
            }
        }

        return "No negative cycle found.";
    }

    //Using Bellman-Ford
    string Algorithms::negativeCycleDirected(Graph& g) {
        
        size_t V = g.getMatrix().size();
        vector<int> dist(V, INT_MAX);
        vector<int> pred(V, -1);
        path.clear();

        dist[0] = 0; 
        
        // Relax all edges V-1 times.
        for (size_t step = 0; step < V - 1; step++) {
            for (size_t u = 0; u < V; u++) {
                for (size_t v = 0; v < V; v++) {
                    if (g.getMatrix()[u][v] && dist[u] != INT_MAX && dist[u] + g.getMatrix()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.getMatrix()[u][v];
                        pred[v] = static_cast<int>(u);
                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (size_t u = 0; u < V; u++) {
            for (size_t v = 0; v < V; v++) {
                if (g.getMatrix()[u][v] && dist[u] != INT_MAX && dist[u] + g.getMatrix()[u][v] < dist[v]) {
                    // Reconstruct the cycle
                    int x = v;
                    for (size_t i = 0; i < V; i++) {
                        x = pred[static_cast<size_t>(x)];
                    }

                    for (size_t y = static_cast<size_t>(x);; y = static_cast<size_t>(pred[static_cast<size_t>(y)])) {
                        path.push_back(y);
                        if (y == static_cast<size_t>(x) && path.size() > 1) break;
                    }
                    reverse(path.begin(), path.end());
                    return Algorithms::printCycle("negative");// print the cycle
                      
                }
            }
        }

        return "No negative cycle found.";
        
    }

   
    // DFS that run on all the graph
    void Algorithms::DFSfull(Graph& g, int vertex) 
    {
        g.setVisited(vertex, true);
        for (size_t i = 0; i < g.getMatrix()[static_cast<size_t>(vertex)].size(); ++i) 
        {
            if (g.getMatrix()[static_cast<size_t>(vertex)][i] != 0 && g.getVisited(i) == false) 
            {
                Algorithms::DFSfull(g, i);
            }
        }
    }
   
   // This function can print a cycle with the path and he need to receive flag
   // that assume "negative", "cycle" or "shortest"
    string Algorithms::printCycle(string flag) {
        string strPath;
        if (flag == "negative")
            strPath = "The negative cycle is: ";
        if (flag == "cycle") strPath = "The cycle is: ";
        if (flag == "shortest") strPath = "The shortest path is: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) strPath += "->";
            strPath += to_string(path[i]);
        }
        return strPath;
    }

    
    bool Algorithms::DFSdirected(Graph& g, int vertex) {
        g.setVisited(vertex, true); 
        g.setRecStack(vertex, true);  
        path.push_back(vertex);       // add the current vertice to the path

        for (size_t i = 0; i < g.getMatrix()[static_cast<size_t>(vertex)].size(); i++) {
            if (g.getMatrix()[static_cast<size_t>(vertex)][i] != 0) {  // Il y a une arête de vertex à i
                if (!g.getVisited(i)) {
                    if (DFSdirected(g, i)) {
                        return true;  // return true if we find a cycle
                    }
                } else if (g.getRecStack(i)) {
                    path.push_back(i);  // add the last vertice to complete the cycle
                    // printCycle(path);
                    return true;
                }
            }
        }

        path.pop_back();               
        g.setRecStack(vertex, false);  
        return false;
    }

    bool Algorithms::DFSundirected(Graph& g, int vertex, int parent) 
    {
        g.setVisited(vertex, true);
        path.push_back(vertex);
        for (size_t i = 0; i < g.getMatrix().size(); i++)
        {
            // check if we have an edge between vertex and i
            if (g.getMatrix()[static_cast<size_t>(vertex)][i]) {  
                if (!g.getVisited(i)) {
                    if (DFSundirected(g, i, vertex))
                        return true;
                } else if (i != static_cast<size_t>(parent)) {
                    path.push_back(i);  // add the last vertice to complete the cycle
                    return true;
                }
            }
        }
        path.pop_back();
        return false;
    }

}
