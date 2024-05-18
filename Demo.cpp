//ID: 208018028, Mail: ronimordechai70@gmail.com
/*
 * Demo program for Exercise 2.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

auto main() -> int
{
    cout << "Demo operators checking:" << endl;
    ariel::Graph g1;
    cout << "Test to graph1 (operator <<):" << endl;
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
    cout << "Test to graph3 (operator +):" << endl;
    cout << g3 << "\n";  // Should print the matrix: [0, 2, 1], [2, 0, 3], [1, 3, 0]

    ariel::Graph g4 = g1 - g2;  // Subtract the two graphs
    cout << "Test to graph4 (operator -):" << endl;
    cout << g4 << "\n";  // Should print the matrix: [0, 0, -1], [0, 0, -1], [-1, -1, 0]

    g4 += 5;  // Add 5 to all elements in the adjacency matrix
    cout << "Test to graph4 (operator +=):" << endl;
    cout << g4 << "\n";  // Should print the matrix: [5, 5, 4], [5, 5, 4], [4, 4, 5]

    g4 -= 5;  // Subtract 5 from all elements in the adjacency matrix
    cout << "Test to graph1 (operator -=):" << endl;
    cout << g4 << "\n";  // Should print the matrix: [0, 0, -1], [0, 0, -1], [-1, -1, 0] (go back to the original g4)
    
    ariel::Graph negatedG1 = -g1;  // Unary minus to negate all elements
    cout << "Test to graph1 (operator unary-):" << endl;
    cout << negatedG1 << "\n";  // Should print the matrix: [0, -1, 0], [-1, 0, -1], [0, -1, 0]

    ariel::Graph identityG1 = +g1;  // Unary plus, should keep identity
    cout << "Test to graph1 (operator unary+):" << endl;
    cout << identityG1 << "\n";  // Should print the matrix: [0, 1, 0], [1, 0, 1], [0, 1, 0]

    // Test the < operator
    cout << "Test to graphs 1,2 (operator <):" << endl;
    cout << "g1 < g2: " << (g1 < g2) << endl;  // Should be true becouse g2 has more edges
    cout << "g2 < g1: " << (g2 < g1) << endl;  // Should be false

    ariel::Graph g5;
    // 3x3 matrix with fewer edges
    vector<vector<int>> graph5 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g5.loadGraph(graph5);
    cout << "Test to graphs 1,5 (operator <):" << endl;
    cout << "g1 < g5: " << (g1 < g5) << endl;  // Should be false
    cout << "g5 < g1: " << (g5 < g1) << endl;  // Should be true

    ariel::Graph g6;
    // A 4x4 matrix with more vertices but fewer edges
    vector<vector<int>> graph6 = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} };
    g6.loadGraph(graph6);
    cout << "Test to graphs 1,6 (operator <):" << endl;
    cout << "g1 < g6: " << (g1 < g6) << endl;  // Should be false (g1 has more edges)
    cout << "g6 < g1: " << (g6 < g1) << endl;  // Should be true (g1 has more edges)

    ariel::Graph g7;
    // A 2x2 matrix 
    vector<vector<int>> graph7 = {
        {0, 1},
        {1, 0}};
    g7.loadGraph(graph7);
    cout << "Test to graphs 1,2,7 (operator <):" << endl;
    cout << "g7 < g1: " << (g7 < g1) << endl;  // Should be true (g7 contain in g1)
    cout << "g7 < g2: " << (g7 < g2) << endl;  // Should be true (g7 contain in g2)
    cout << "g1 < g7: " << (g1 < g7) << endl;  // Should be false 
    cout << "\n";
    cout << "Test to graphs 2,7 (operator >):" << endl;
    cout << "g2 > g7: " << (g2 > g7) << endl;  // Should be true
    cout << "g7 > g2: " << (g7 > g2) << endl;  // Should be false 
    cout << "\n";

    ariel::Graph g8;
    // A 2x2 matrix 
    vector<vector<int>> graph8 = {
        {1, 0},
        {0, 1}};
    g8.loadGraph(graph8);
    cout << "Test to graphs 1,2 (operator ==):" << endl;
    cout << "g1 == g2: " << (g1 == g2) <<endl;  // Should be false (different edges)
    cout << "g1 == g1: " << (g1 == g1) <<endl;  // Should be true 
    cout << "\n";
    cout << "Test to graphs 7,8 (operator <,>):" << endl;
    cout << "g7 < g8: " << (g7 > g8) << endl;   // Should be false
    cout << "g7 > g8: " << (g7 > g8) << endl;   // Should be false
    cout << "\n";
    cout << "Test to graphs 7,8 (operator ==):" << endl;
    cout << "g7 == g8: " << (g7 == g8) <<endl;  // Should be true (!(g7 > g8) && !(g8 > g7))
    cout << "\n";
    
    cout << "Test to graphs 1,2 (operator <=):" << endl;
    cout << "g1 <= g2: " << (g1 <= g2) << endl;  // Should be true (g2 has more edges)
    cout << "g2 <= g1: " << (g2 <= g1) << endl;  // Should be false (g2 is greater)
    cout << "\n";
    
    cout << "Test to graphs 1,2 (operator >=):" << endl;
    cout << "g1 >= g2: " << (g1 >= g2) << endl;  // Should be false (g2 has more edges)
    cout << "g2 >= g1: " << (g2 >= g1) << endl;  // Should be true
    cout << "\n";
    cout << "Test to graphs 7,8 (operator !=):" << endl;
    cout << "g7 != g8: " << (g7 != g8) << endl;  // Should be false (relative equivalence)
    cout << "g1 != g2: " << (g1 != g2) << endl;  // Should be true
    cout << "\n";

    cout << "Test to graph1 (operator ++g1, --g1):" << endl;
    ++g1;//Pre-increment: add one to all elements
    cout << "After pre-increment (g1):\n" << g1 << endl; // Should print the matrix: [1, 2, 1], [2, 1, 2], [1, 2, 1]
    --g1;//Pre-increment: sub one to all elements  
    cout << "After pre-decrement (g1):\n" << g1 << endl; // Should print the matrix: [0, 1, 0], [1, 0, 1], [0, 1, 0]

    cout << "Test to graphs 1,9 (operator g1++):" << endl;
    // Post-increment (should add one but return the previous state)
    ariel::Graph g9 = g1++;  // g9 should have the previous state
    cout << "After post-increment (g1):\n" << g1 << endl;  // New state -should print the matrix: [1, 2, 1], [2, 1, 2], [1, 2, 1]
    cout << "Previous state (g9):\n" << g9<< endl;  // Previous state - should print the matrix: [0, 1, 0], [1, 0, 1], [0, 1, 0]
    
    cout << "Test to graphs 1,10 (operator g1--):" << endl;
    // Post-decrement (should subtract one but return the previous state)
    ariel::Graph g10 = g1--;  // g10 should have the previous state
    cout << "After post-decrement (g1):\n" << g1 << endl;  // New state - should print the matrix: [0, 1, 0], [1, 0, 1], [0, 1, 0]
    cout << "Previous state (g10):\n" << g10 << endl;  // Previous state - should print the matrix: [1, 2, 1], [2, 1, 2], [1, 2, 1] - becouse the operator g1++

    cout << "Test to graph1 (operator *=):" << endl;
    g1 *= -2;        // Multiply the graph by -2.
    cout<< "After multiplication by -2 (g1):\n" <<g1 << endl;; // Should print the matrix of the graph: [0, -2, 0], [-2, 0, -2], [0, -2, 0]
    g1 *= -10;
    cout<< "After multiplication by -10 (g1):\n" <<g1 << endl;; // Should print the matrix of the graph: [0, 20, 0], [20, 0, 20], [0, 20, 0]
    g1 *= 0;
    cout<< "After multiplication by 0 (g1):\n" <<g1 << endl;; // Should print the matrix of the graph: [0, 0, 0], [0, 0, 0], [0, 0, 0]
    
    ariel::Graph g11;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph11 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g11.loadGraph(graph11); // Load the graph to the object.
    g1 += g11; // to go back to the original g1
    ariel::Graph g12 = g1 * g2; // Multiply the two graphs together.
    cout << "Test to graphs 12 (operator *):" << endl;
    cout<< "Resulting graph after multiplication g1 and g2:\n" <<g12 << endl;; // Should print the multiplication of the matrices of g1 and g2: [1, 0, 2], [1, 3, 1], [1, 0, 2]

    // 5x5 matrix that represents a connected graph.
    cout << "Test to graph 14 (invalid use operator *):" << endl;
    vector<vector<int>> graph13 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    ariel::Graph g13;
    g13.loadGraph(graph13); // Load the graph to the object.
    try
    {
        ariel::Graph g14 = g13 * g1; // Multiply the two graphs together.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print "The number of columns in the first matrix must be equal to the number of rows in the second matrix."
    }
    cout << "\n";

    // Checks how the functions from Ex1 will work with the operators from Ex2
    cout << "Checks functions from Ex1 with operators:" << endl;
    vector<vector<int>> graph15 = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}};

    vector<vector<int>> graph16 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    ariel::Graph g15, g16;
    g15.loadGraph(graph15);
    g16.loadGraph(graph16);

    // Using operators
    ariel::Graph g17 = g16 - g15;
    cout << "Graph 17 after the change is: \n" <<g17 << endl;
    g15 += g16; // Add g16 to g15 using the += operator
    g16 -= g15; // Subtract g15 from g16 using the -= operator
    cout << "Graph 15 after the change is: \n" <<g15 << endl;
    cout << "Graph 16 after the change is: \n" <<g16 << endl;
    
    cout << "Test to graph 15,16,17 isConnected function:" << endl;
    // Check if g15 is connected
    cout << "Is g15 connected: " << ariel::Algorithms::isConnected(g15) << endl; // Should print: "1" (true).
    // Check if g16 is connected
    cout << "Is g16 connected: " << ariel::Algorithms::isConnected(g16) << endl; // Should print: "1" (true).
    // Check if g17 is connected
    cout << "Is g17 connected: " << ariel::Algorithms::isConnected(g17) << endl; // Should print: "0" (false).

    cout << "\n";
    cout << "Test to graph 15,16,17 shortestPath function:" << endl;
    // Find shortest path in g15
    string shortestPathG1 = ariel::Algorithms::shortestPath(g15, 0, 2); // Should print: 0->3->2.
    // Check the shortest path result for g15
    cout << "Shortest path in g15: " << shortestPathG1 << endl;
    // Find shortest path in g16
    string shortestPathG16 = ariel::Algorithms::shortestPath(g16, 0, 2); // "Should print: Graph contains a negative cycle so there is no shortest path".
    // Check the shortest path result for g16
    cout << "Shortest path in g16: " << shortestPathG16 << endl;
    // Find shortest path in g17
    string shortestPathG17 = ariel::Algorithms::shortestPath(g17, 0, 3); // Should print: 0->3.
    // Check the shortest path result for g17
    cout << "Shortest path in g17: " << shortestPathG17 << endl;
    cout << "\n";

    cout << "Test to graph 15,16,17 isContainsCycle function:" << endl;
    // Check if g15 contains a cycle
    cout << "Does g15 contain a cycle: " << ariel::Algorithms::isContainsCycle(g15) << endl; // Should print: "The cycle is: 0->1->2->3->0".
    // Check if g16 contains a cycle
    cout << "Does g16 contain a cycle: " << ariel::Algorithms::isContainsCycle(g16) << endl; // Should print: "Graph contains a negative cycle: 3->2->3".
    // Check if g17 contains a cycle
    cout << "Does g17 contain a cycle: " << ariel::Algorithms::isContainsCycle(g17) << endl; // Should print: "0" there is no cycle.
    cout << "\n";

    cout << "Test to graph 15,16,17 isBipartite function:" << endl;
    // Check if g15 is bipartite
    cout << "Is g15 bipartite: " << ariel::Algorithms::isBipartite(g15) << endl; // Should print: "0"
    // Check if g16 is bipartite
    cout << "Is g16 bipartite: " << ariel::Algorithms::isBipartite(g16) << endl; // Should print: "0"
    // Check if g17 is bipartite
    cout << "Is g17 bipartite: " << ariel::Algorithms::isBipartite(g17) << endl; // Should print: "The graph is bipartite: A={0,1,2}, B={3}"
    cout << "\n";

    cout << "Test to graph 15,16,17 negativeCycle function:" << endl;
    // Check if g15 contains a negative cycle
    cout << "Does g15 contain a negative cycle: " << ariel::Algorithms::negativeCycle(g15) << endl; // Should print: "Graph does not contain a negative cycle"
    // Check if g16 contains a negative cycle
    cout << "Does g16 contain a negative cycle: " << ariel::Algorithms::negativeCycle(g16) << endl; // Should print: "Graph contains a negative cycle: 3->2->3"
    // Check if g17 contains a negative cycle
    cout << "Does g17 contain a negative cycle: " << ariel::Algorithms::negativeCycle(g17) << endl; // Should print: "Graph does not contain a negative cycle"
}
