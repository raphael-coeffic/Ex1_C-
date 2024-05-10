#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;


TEST_CASE("Test isConnected")
{
    raphael::Graph g;       //test connectivity for non oriented
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(raphael::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph1 = {          //test connectivity for oriented
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph1);
    CHECK(raphael::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {      // test not connectivity
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(raphael::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph3 = {  // check for withed graph with negative values and negative cycle
        {0, -1, 0, -2},
        {-1, 0, -2, 0},
        {0, -2, 0, 1},
        {-2, 0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(raphael::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test shortestPath")
{
    raphael::Graph g;
    vector<vector<int>> graph = { //test shortest path for non oriented
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(raphael::Algorithms::shortestPath(g, 0, 2) == "The shortest path is: 0->1->2");

    vector<vector<int>> graph1 = {          //test shortest path for oriented
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(raphael::Algorithms::shortestPath(g, 2, 1) == "-1");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(raphael::Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> graph3 = {  // check for weithed graph with negative values and negative cycle
        {0, -1, 0, -1},
        {-1, 0, -2, 0},
        {0, -2, 0, 1},
        {-1, 0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(raphael::Algorithms::shortestPath(g, 0, 2) == "Graph contains a negative cycle");

    CHECK_THROWS(raphael::Algorithms::shortestPath(g, 0, 5)); // check that we can't receive invalid index

}
TEST_CASE("Test isContainsCycle")
{
    raphael::Graph g;
    vector<vector<int>> graph = {  //test countain cycle for non oriented
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(raphael::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph1 = {          //test shortest path for oriented
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(raphael::Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(raphael::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph3 = {  // check for weithed graph with negative values and negative cycle
        {0, -1, 0, -1},
        {-1, 0, -2, 0},
        {0, -2, 0, 1},
        {-1, 0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(raphael::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->3->0");
}
TEST_CASE("Test isBipartite")
{
    raphael::Graph g;
    vector<vector<int>> graph = {  //test isBipartite for non oriented
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(raphael::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {      //test isBipartite for oriented
        {0, 1, 0, 1},
        {0, 0, 0, 0},
        {0, 1, 0, 1},
        {0, 0, 0, 0}};

    g.loadGraph(graph2);
    CHECK(raphael::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");

    vector<vector<int>> graph3 = {  // check for weithed graph with negative values
        {0, -2, 0, 1},
        {-2, 0, -3, 0},
        {0, -3, 0, 2},
        {1, 0, 2, 0}};
    g.loadGraph(graph3);
    CHECK(raphael::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("Test negativeCycle")
{
    raphael::Graph g;
    vector<vector<int>> graph = {  //test negativeCycle for non oriented
        {0, 3, 0, -1},
        {3, 0, -5, 0},
        {0, -5, 0, 2},
        {-1, 0, 2, 0}};
    g.loadGraph(graph);
    CHECK(raphael::Algorithms::negativeCycle(g) == "The negative cycle is: 3->0->1->2->3");

    vector<vector<int>> graph2 = {      //test negativeCycle for oriented
        {0, 4, 0, 0},
        {0, 0, -6, 0},
        {0, 0, 0, 3},
        {-2, 0, 0, 0}};

    g.loadGraph(graph2);
    CHECK(raphael::Algorithms::negativeCycle(g) == "The negative cycle is: 1->2->3->0->1");
}

TEST_CASE("Test invalid graph")
{
    //test some non square graph
    raphael::Graph g;
    vector<vector<int>> graph = { 
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {1, 0, 3, 0, 4},
        {2, 3, 0, 4, 3},
        {0, 0, 0, 5, 0}};
    CHECK_THROWS(g.loadGraph(graph1));
}