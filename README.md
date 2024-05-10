Author: Raphael Coeffic, 337614747, racoeffic@gmail.com

In this project, I implemented a graph from an adjacency matrix and the functions that are necessary. 
I have 4 files of implementation, 2 headers and two .cpp, 2 for the implementation of the class of the graph himself and hus basic functions and 2 for some algorithms on graphs.
Finally, I have a file of main, a file of tests and a MAKEFILE.

I am going to explane about each one of them:

Graph.hpp: First  a constructor Graph() that init all the attributes to 0. Function loadGraph() that receive a matrix and buid the graph with the matrix(the function check if this is a quare matrix), printGraph(), a funtion that print the num of vertices and the num of edges of the graph. Function isDirected() that return 1 is the graph is directed and 0 if not. Function haveNegative() that check if the graph contain an negative edge. Finally, we have a lot of function set get ect... that change values of the graph or return values of the graph.

Graph.cpp: This 
