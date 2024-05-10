# EX1 (GRAPH) IN C++

_Author: Raphael Coeffic, 337614747, racoeffic@gmail.com_

In this project, I implemented a **graph** from an adjacency matrix and the functions that are necessary. 
I have 4 files of implementation, 2 headers and two .cpp, 2 for the implementation of the class of the graph himself and hus basic functions and 2 for some algorithms on graphs.
Finally, I have a file of main, a file of tests and a MAKEFILE.

I am going to explane about each one of them:

## Graph.hpp: 
First  a constructor **Graph()** that init all the attributes to 0. Function `loadGraph()` that receive a matrix and buid the graph with the matrix(the function check if this is a quare matrix, `printGraph()`, a funtion that print the num of vertices and the num of edges of the graph. Function `isDirected()` that return 1 is the graph is directed and 0 if not. Function `haveNegative()` that check if the graph contain an negative edge. Finally, we have a lot of function **set get** ect... that change values of the graph or return values of the graph. 

## Graph.cpp:
Implementation pf `Graph.hpp`. For `loadGraph()`, I receive a matrix, check if this is a quare matrix and load in the attribute a of the matrix of the graph the matrix that I receive. In function `printGraph()` the output is _Graph with **x** vertices and **y** edges._ in Function `isDirected()`, I run on the matrix of the graph and check if vor every edge he is equal to his transpose _(On<sup> 2</sup>)_. `haveNegative()` has the same complexity because he is renu on all the matrix of our graph. Finally, I write a lot of functions of **set get** for touch the attributes because all the attributes are **private**. 

## Algorithms.hpp:
Header for all my algorithms about graph. He counatins five principal functions. First, function **isConnected()** that check if the graph is connected by return of 1/0. **Shortest Path** function that print the shortest path between two vertices or -1. A function that check if the graph countains a **cycle** and print him if we find him or 0. A function that check if the graph is **bipatite** and print the result or 0. And finally, a function that check if the graph countains a **negative cycle** and print him or print that the graph dones'nt countain a negative cycle.

## Algorithms.cpp:
This is the implementation of algorithms.hpp. He countains a lot of help functions. The file countain a vector<> for countain the path of a lot of function like shortestPath or cycle. So for all these functions, we need to translate this path to a string for the output and this is the role of the function `printCycle()` that receive for input a flag that countain a word for describe each string do we want(negative, cycle or shortest). For the implementation of `isConnected()`, I use a function DFSfull that execute a DFS _(O(V+E))_ and we check if with this DFS we visit all the vertices of the graph from vertice 0. is the graph is directed, we need to check the same thing for the transpose graph so the function transpose the matrix and execute the same thing. For the implementation of `shortestPath()`, we first check that the index of the input is on the graph. After that, I execute _Bellman Ford_ _(O(V*E)_ for fint the path. In function `isContainsCycle()` we have two options: If the graph is Directed we use DFS adapted to directed graph anf an undirected graph we use an DFS adapted to him. In function `isBipartite()` I use BFS _(O(V+E))_ for find the two graph and print them (by their vertices) and return 0 if it is not a bipartite graph. Finally, in fuction `negativeCycle()`, it is work a little bit like in `isCountainCycle()` because I adapted Bellan Ford Algorithms to the options of a directed or undirected graph.

## main.cpp:
This file is an **example** of some usages of all my functions.

## tests.cpp:
In this file, I test my functions on a lot of graph, directed, undirected, weithed, with negative values...

## Makefile:
I compile here all my files with `make` or `make all` and clean them with `make clean` in the terminal.
For execute the main please: `./main`
For execute the tests please: `./tests`
