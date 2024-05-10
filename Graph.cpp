#include "Graph.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace raphael {
    void Graph::loadGraph(const vector<vector<int>>& matrix) 
    {
        size_t size = matrix.size();
        for (auto& row : matrix) 
        {
            if (row.size() != size) // check that we can receive a non square matrix
            {
                throw invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
        this->mat.resize(size);
        for (size_t i = 0; i < size; ++i) this->mat[i].resize(size); 
        
        this->mat = matrix;
        this->visited.resize(size, false);
        this->recStack.resize(size, false);
    }

    void Graph::printGraph()const 
    {
        cout << "Graph with " << this->mat.size() << " vertices";
        int edgeCount = 0;
        size_t size = this->mat.size();
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (this->mat[i][j] > 0) edgeCount++;
            }
        }
        cout << " and " << edgeCount << " edges." << endl;
        
    }

    int Graph::isDirected()
    {
        size_t size = this->mat.size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                //if we have a difference between the matrix and his transpose the graph is directed
                if(this->mat[i][j] != this->mat[j][i])
                    return 1;
            }
            
        }
        return 0;
        
    }


    void Graph::resetVisited() {
        // init all visited to false
        fill(this->visited.begin(), this->visited.end(), 0);
    }

    void Graph::resetRecStack() {
        // init all recStack to false
        fill(this->recStack.begin(), this->recStack.end(), 0);
    }
    
    void Graph::setVisited(int index, bool val){
        //check if the index is on the graph
        if (this->mat.size() < static_cast<size_t>(index) || index < 0)
        {
            throw out_of_range("Invalid index: The graph doesn't countain this index.");
        }
        this->visited[static_cast<size_t>(index)] = val;
    }

    bool Graph::getVisited(int index){
        //check if the index is on the graph
        if (this->mat.size() <= static_cast<size_t>(index) || index < 0) 
        {
            throw out_of_range("Invalid index: The graph doesn't countain this index.");
        }
        return this->visited[static_cast<size_t>(index)];
    }

    vector<bool> Graph::getVisited(){
        return this->visited;
    }

    vector<vector<int>> Graph::getMatrix(){
        return this->mat;
    }

    void Graph::setRecStack(int index, bool val) {
        //check if the index is on the graph
        if (this->mat.size() <= static_cast<size_t>(index) || index < 0)
        {
            throw out_of_range("Invalid index: The graph doesn't countain this index.");
        }
        this->recStack[static_cast<size_t>(index)] = val;
    }

    bool Graph::getRecStack(int index) {
        //check if the index is on the graph
        if (index >= 0 && index < static_cast<int>(this->recStack.size())) {
            return recStack[static_cast<size_t>(index)];
        } else {
            throw out_of_range("Index out of range in getRecStack.");
        }
    }

    bool Graph::haveNegative(){
        size_t size = this->mat.size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if (this->mat[i][j] < 0)
                {
                    return true;
                }
                
            }
            
        }
        return false;
    }

    
}