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
    auto Graph::isSymmetric(const std::vector<std::vector<int>>& matrix) -> bool {
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
    auto Graph::isUndirectedGraph() const -> bool {
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
    auto Graph::getAdjMatrix() const -> const std::vector<std::vector<int>>& {
        return adjMatrix; // Return the adjacency matrix
    }
    

    //from here its Ex2

    // Implements of the << operator to print the adjacency matrix
    auto operator<<(std::ostream& os, const Graph& graph) -> std::ostream& {
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
    auto Graph::operator+(const Graph& other) const -> Graph {
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
    auto Graph::operator-(const Graph& other) const -> Graph {
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
    auto Graph::operator+=(int num) -> Graph& {
        for (auto& row : adjMatrix) {
            for (auto& elem : row) {
                elem += num;  // Add the given number to each element
            }
        }
        return *this;  // Return reference to this for chaining
    }

    // Implements of the += operator to add two graphs together (element-wise)
    auto Graph::operator+=(const Graph& other) -> Graph& {
        if (adjMatrix.size() != other.getAdjMatrix().size() ||
            adjMatrix[0].size() != other.getAdjMatrix()[0].size()) {
            throw std::invalid_argument("Graph size mismatch for addition");
        }

        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                adjMatrix[i][j] += other.getAdjMatrix()[i][j];  // Element-wise addition
            }
        }
        return *this;  // Return reference for chaining
    }

    // Implements of the -= operator to sub a number to all indices in the matrix
    auto Graph::operator-=(int num) -> Graph& {
        for (auto& row : adjMatrix) {
            for (auto& elem : row) {
                elem -= num;  // sub the given number to each element
            }
        }
        return *this;  // Return reference to this for chaining
    }

    // Implements of the -= operator to subtract two graphs (element-wise)
    auto Graph::operator-=(const Graph& other) -> Graph& {
        if (adjMatrix.size() != other.getAdjMatrix().size() ||
            adjMatrix[0].size() != other.getAdjMatrix()[0].size()) {
            throw std::invalid_argument("Graph size mismatch for subtraction");
        }

        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                adjMatrix[i][j] -= other.getAdjMatrix()[i][j];  // Element-wise subtraction
            }
        }
        return *this;  // Return reference for chaining
    }

    // Implements of the unary + operator: returns a copy of the graph (identity operation)
    auto Graph::operator+() const -> Graph {
        return *this;  // Return a copy of the current graph
    }

    // Implements of the unary - operator: negates all elements in the adjacency matrix
    auto Graph::operator-() const -> Graph {
        std::vector<std::vector<int>> negatedMatrix(adjMatrix.size(), std::vector<int>(adjMatrix[0].size()));
        
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[0].size(); ++j) {
                negatedMatrix[i][j] = -adjMatrix[i][j];  // Negate the element
            }
        }

        return Graph(negatedMatrix);  // Return a new graph with the negated matrix
    }

    // Helper function to count edges in the adjacency matrix 
    //*Note- both for directed and undirected we count 2 direction
    auto countEdges(const std::vector<std::vector<int>>& matrix) -> int {
        int edgeCount = 0;
        for (const auto& row : matrix) {
            for (int value : row) {
                if (value != 0) {  // If there's an edge
                    edgeCount++;
                }
            }
        }
        return edgeCount;
    }

    // Check if one graph contains another
    auto isContained(const Graph& g1, const Graph& g2) -> bool {
        const auto& adj1 = g1.getAdjMatrix();
        const auto& adj2 = g2.getAdjMatrix();

        for (size_t i = 0; i < adj1.size(); ++i) {
            for (size_t j = 0; j < adj1[0].size(); ++j) {
                if (adj1[i][j] != 0 && (adj2[i][j] == 0 || adj1[i][j] > adj2[i][j])) {
                    return false;  // If `g1` has edges not in `g2`
                }
            }
        }

        return true;  // All edges in `g1` are in `g2`
    }

    // Implement the < operator for Graphs
    bool operator<(const Graph& g1, const Graph& g2) {
        const auto& adj1 = g1.getAdjMatrix();
        const auto& adj2 = g2.getAdjMatrix();

        // Check if g1 is fully contained in g2
        if (isContained(g1, g2)) {
            return true;
        } else if (isContained(g2, g1)) {
            return false;
        } else {
            // If not fully contained in either direction, compare the number of edges
            int edgeCount1 = countEdges(adj1);  
            int edgeCount2 = countEdges(adj2);  
            if (edgeCount1 != edgeCount2) {
                return edgeCount2 < edgeCount1;
            } else {
                // If edge counts are equal, compare the sizes of the graphs
                return adj2.size() < adj1.size();
            }
        }
    }

    // Implement the > operator for Graphs uses the operator '<'
    auto operator>(const Graph& g1, const Graph& g2) -> bool {
        return g2 < g1;  // If `g2 < g1`, then `g1 > g2`
    }
    
    // // Helper function to check if two graphs are exactly equivalent
    bool helpFunctionToOperatorEqual(const Graph& g1, const Graph& g2) {
        const auto& adj1 = g1.getAdjMatrix();
        const auto& adj2 = g2.getAdjMatrix();

        // Check if they have the same number of vertices
        if (adj1.size() != adj2.size()) {
            return false;  // Different sizes mean they're not equivalent
        }

        // Check if they have the same elements in the adjacency matrices
        for (size_t i = 0; i < adj1.size(); ++i) {
            if (adj1[i].size() != adj2[i].size()) {
                return false;  // Different row sizes mean they're not equivalent
            }
            for (size_t j = 0; j < adj1[i].size(); ++j) {
                if (adj1[i][j] != adj2[i][j]) {
                    return false;  // Different edges or weights
                }
            }
        }

        return true;  // Exact equivalence
    }

    // // Helper function to check if two graphs are relatively equivalent
    bool isRelativelyEquivalent(const Graph& g1, const Graph& g2) {
        // Relative equivalence: neither graph is greater than the other
        return (!(g1 > g2)) && (!(g2 > g1));
    }

    bool operator==(const Graph& g1, const Graph& g2) {
        // First check exact equivalence
        if (helpFunctionToOperatorEqual(g1, g2)) {
            return true;  // They are equivalent
        }

        // Then check relative equivalence
        return isRelativelyEquivalent(g1, g2);  // They are equivalent if neither is greater
    }

    // Implement the <= operator for Graphs
    auto operator<=(const Graph& g1, const Graph& g2) -> bool {
        return (g1 < g2) || (g1 == g2);  // True if `g1` is less than or equal to `g2`
    }

    // Implement the >= operator for Graphs
    auto operator>=(const Graph& g1, const Graph& g2) -> bool {
        return (g1 > g2) || (g1 == g2);  // True if `g1` is greater than or equal to `g2`
    }

    // Implement the != operator for Graphs
    auto operator!=(const Graph& g1, const Graph& g2) -> bool {
        return !(g1 == g2);  // If they are not equal, return true
    }

    // Implement the ++ operator Pre-increment 
    auto Graph::operator++() -> Graph& {
        for (auto& row : adjMatrix) {
            for (auto& value : row) {
                value++;  // Add one to each edge
            }
        }
        return *this;  // Return the modified graph
    }

    // Implement the ++ operator Post-increment
     const auto Graph::operator++(int) -> Graph {   // The int parameter indicates post-increment
        Graph temp = *this;  // Save the current state
        ++(*this);  // Apply pre-increment
        return temp;  // Return the original state
    }

    // Implement the -- operator Pre-increment 
     auto Graph::operator--() -> Graph& {
        for (auto& row : adjMatrix) {
            for (auto& value : row) {
                value--;  // Subtract one from each edge
            }
        }
        return *this;  // Return the modified graph
    }

    // Implement the -- operator Post-increment
    const auto Graph::operator--(int) -> Graph {  // The int parameter indicates post-decrement
        Graph temp = *this;  // Save the current state
        --(*this);  // Apply pre-decrement
        return temp;  // Return the original state
    }

    // Implement the *= operator for multiplication with scalar
    auto Graph::operator*=(int multiplier) -> Graph& {
        for (auto& row : adjMatrix) {
            for (auto& value : row) {
                value *= multiplier;  // Multiply each element by the scalar
            }
        }
        return *this;  // Return the modified graph
    }

    // Implement the * operator for multiplying two graphs using matrix multiplication
    auto operator*(const Graph& g1, const Graph& g2) -> Graph {
        const auto& adj1 = g1.getAdjMatrix();
        const auto& adj2 = g2.getAdjMatrix();

        size_t rows1 = adj1.size();
        size_t cols1 = adj1[0].size();
        size_t rows2 = adj2.size();
        size_t cols2 = adj2[0].size();

        // Check if the number of columns in the first matrix matches the number of rows in the second
        if (cols1 != rows2) {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        // Initialize the resulting matrix with zeros
        std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

        // Perform matrix multiplication
        for (size_t i = 0; i < rows1; ++i) {
            for (size_t j = 0; j < cols2; ++j) {
                for (size_t k = 0; k < cols1; ++k) {
                    result[i][j] += adj1[i][k] * adj2[k][j];  // Dot product for matrix multiplication
                }
            }
        }

        // Return a new Graph with the resulting adjacency matrix
        return Graph(result);
    }
}  // namespace ariel // namespace ariel
