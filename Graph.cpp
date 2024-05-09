//ID: 208018028, Mail: ronimordechai70@gmail.com
#include "Graph.hpp"
#include <iostream> // For std::cout
#include <stdexcept>  // For std::invalid_argument

namespace ariel {

    // Default constructor for an empty graph with no vertices
    Graph::Graph() : adjMatrix(0, std::vector<int>(0)), isUndirected(true) {}

    // Constructor to initialize a graph with a given adjacency matrix
    Graph::Graph(const std::vector<std::vector<int>>& matrix) {
        validateMatrix(matrix); // Validate that the matrix is square
        adjMatrix = matrix; // Assign the provided matrix to the graph
        isUndirected = isSymmetric(matrix); // Determine if the graph is undirected or directed
    }

    // Validates that the given adjacency matrix is square
    void Graph::validateMatrix(const std::vector<std::vector<int>>& matrix) {
        size_t rowCount = matrix.size(); // Get the number of rows
        for (const auto& row : matrix) {
            if (row.size() != rowCount) { // Ensure each row has the same number of columns
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
    }

    // Checks if the adjacency matrix is symmetric, indicating an undirected graph
    bool Graph::isSymmetric(const std::vector<std::vector<int>>& matrix) {
        size_t size = matrix.size();
        for (size_t i = 0; i < size; i++) { // Iterate through the rows
            for (size_t j = 0; j < size; j++) { // Iterate through the columns
                if (matrix[i][j] != matrix[j][i]) { // If the matrix is not symmetric
                    return false; // It's a directed graph
                }
            }
        }
        return true; // If symmetric, it's an undirected graph
    }

    // Loads a new adjacency matrix into the graph, with validation
    void Graph::loadGraph(const std::vector<std::vector<int>>& newMatrix) {
        validateMatrix(newMatrix); // Validate the matrix is square
        adjMatrix = newMatrix; // Assign the new matrix to the graph
        isUndirected = isSymmetric(newMatrix); // Determine if the graph is undirected or directed
    }

    // Determines if the graph is undirected
    bool Graph::isUndirectedGraph() const {
        return isUndirected; // Return whether the graph is undirected
    }

    // Prints the number of vertices and edges in the graph
    void Graph::printGraph() const {
        size_t vertices = adjMatrix.size(); // Get the number of vertices
        int edges = 0;

        // Check if the graph is undirected or directed
        if (isUndirected) {
            // For undirected graphs, count only unique edges (upper triangle)
            for (size_t i = 0; i < vertices; i++) {
                for (size_t j = i + 1; j < vertices; j++) { // Only count edges in the upper triangle
                    if (adjMatrix[i][j] != 0) { // Count any non-zero edge
                        edges++;
                    }
                }
            }
        } else {
            // For directed graphs, count all non-zero edges
            for (const auto& row : adjMatrix) { // Loop through all rows
                for (int value : row) { // Loop through all columns
                    if (value != 0) { // Count any non-zero edge
                        edges++;
                    }
                }
            }
        }

        // Output the number of vertices and edges in the graph
        std::cout << "Graph with " << vertices << " vertices and " << edges << " edges." << std::endl;
    }

    // Returns the adjacency matrix of the graph
    const std::vector<std::vector<int>>& Graph::getAdjMatrix() const {
        return adjMatrix; // Return the adjacency matrix
    }
    

    //from here its Ex2

    // Implements of the << operator to print the adjacency matrix
    std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        const auto& matrix = graph.getAdjMatrix();
        for (const auto& row : matrix) {
            os << "[";
            for (size_t i = 0; i < row.size(); ++i) {
                os << row[i];
                if (i < row.size() - 1) {
                    os << ", ";
                }
            }
            os << "]\n";  // Newline after each row for readability
        }
        return os;
    }

    // Implements of the + operator to add two graphs
    Graph Graph::operator+(const Graph& other) const {
        const auto& matrix1 = this->getAdjMatrix();
        const auto& matrix2 = other.getAdjMatrix();

        // Ensure both matrices are the same size
        if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
            throw std::invalid_argument("Graphs must be the same size to add them.");
        }

        // Create a new matrix with the same size
        std::vector<std::vector<int>> result(matrix1.size(), std::vector<int>(matrix1[0].size()));

        // Calculate the sum of corresponding indices
        for (size_t i = 0; i < matrix1.size(); ++i) {
            for (size_t j = 0; j < matrix1[0].size(); ++j) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }

        return Graph(result);  // Return a new Graph with the resulting matrix
    }

    // Implements of the - operator to subtract two graphs
    Graph Graph::operator-(const Graph& other) const {
        const auto& matrix1 = this->getAdjMatrix();
        const auto& matrix2 = other.getAdjMatrix();

        if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
            throw std::invalid_argument("Graphs must be the same size to subtract them.");
        }

        std::vector<std::vector<int>> result(matrix1.size(), std::vector<int>(matrix1[0].size()));

        for (size_t i = 0; i < matrix1.size(); ++i) {
            for (size_t j = 0; j < matrix1[0].size(); ++j) {
                result[i][j] = matrix1[i][j] - matrix2[i][j];
            }
        }

        return Graph(result);
    }

    // Implements of the += operator to add a number to all indices in the matrix
    Graph& Graph::operator+=(int num) {
        for (auto& row : adjMatrix) {
            for (auto& elem : row) {
                elem += num;  // Add the given number to each element
            }
        }
        return *this;  // Return reference to this for chaining
    }

    // Implements of the -= operator to sub a number to all indices in the matrix
    Graph& Graph::operator-=(int num) {
        for (auto& row : adjMatrix) {
            for (auto& elem : row) {
                elem -= num;  // sub the given number to each element
            }
        }
        return *this;  // Return reference to this for chaining
    }

    // Implements of the unary + operator: returns a copy of the graph (identity operation)
    Graph Graph::operator+() const {
        return *this;  // Return a copy of the current graph
    }

    // Implements of the unary - operator: negates all elements in the adjacency matrix
    Graph Graph::operator-() const {
        std::vector<std::vector<int>> negatedMatrix(adjMatrix.size(), std::vector<int>(adjMatrix[0].size()));
        
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[0].size(); ++j) {
                negatedMatrix[i][j] = -adjMatrix[i][j];  // Negate the element
            }
        }

        return Graph(negatedMatrix);  // Return a new graph with the negated matrix
    }
}
