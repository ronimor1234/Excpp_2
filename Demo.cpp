/*
 * Demo program for Exercise 3.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
    ariel::Graph g1;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph); // Load the graph to the object.

    cout<<g1; // Should print the matrix of the graph: [0, 1, 0], [1, 0, 1], [0, 1, 0] (but one under the other)
    cout << "\n";

    // 3x3 matrix that represents a weighted connected graph.
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    ariel::Graph g2;
    g2.loadGraph(weightedGraph); // Load the graph to the object.

    ariel::Graph g3 = g1 + g2;  // Add the two graphs together
    cout << g3 << "\n";  // Should print the matrix: [0, 2, 1], [2, 0, 3], [1, 3, 0]

    ariel::Graph g4 = g1 - g2;  // Subtract the two graphs
    cout << g4 << "\n";  // Should print the matrix: [0, 0, -1], [0, 0, -1], [-1, -1, 0]

    g4 += 5;  // Add 5 to all elements in the adjacency matrix
    cout << g4 << "\n";  // Should print the matrix: [5, 5, 4], [5, 5, 4], [4, 4, 5]

    g4 -= 5;  // Subtract 5 from all elements in the adjacency matrix
    cout << g4 << "\n";  // Should print the matrix: [0, 0, -1], [0, 0, -1], [-1, -1, 0] (go back to the original g4)
    
    ariel::Graph negatedG1 = -g1;  // Unary minus to negate all elements
    std::cout << negatedG1 << "\n";  // Should print the matrix: [0, -1, 0], [-1, 0, -1], [0, -1, 0]

    ariel::Graph identityG1 = +g1;  // Unary plus, should keep identity
    std::cout << identityG1 << "\n";  // Should print the matrix: [0, 1, 0], [1, 0, 1], [0, 1, 0]

    // g1 *= -2;        // Multiply the graph by -2.
    // cout<<g1; // Should print the matrix of the graph: [0, -2, 0], [-2, 0, -2], [0, -2, 0]

    // g1 /= -2;
    // ariel::Graph g4 = g1 * g2; // Multiply the two graphs together.
    // cout<<g4;           // Should print the multiplication of the matrices of g1 and g2: [0, 0, 2], [1, 0, 1], [1, 0, 0]

    // // 5x5 matrix that represents a connected graph.
    // vector<vector<int>> graph2 = {
    //     {0, 1, 0, 0, 1},
    //     {1, 0, 1, 0, 0},
    //     {0, 1, 0, 1, 0},
    //     {0, 0, 1, 0, 1},
    //     {1, 0, 0, 1, 0}};
    // ariel::Graph g5;
    // g5.loadGraph(graph2); // Load the graph to the object.
    // try
    // {
    //     ariel::Graph g6 = g5 * g1; // Multiply the two graphs together.
    // }
    // catch (const std::invalid_argument &e)
    // {
    //     cout << e.what() << endl; // Should print "The number of columns in the first matrix must be equal to the number of rows in the second matrix."
    // }
}
