//ID: 208018028, Mail: ronimordechai70@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stdexcept> // For std::invalid_argument

namespace ariel {
    class Graph {
    private:
        std::vector<std::vector<int>> adjMatrix;
        bool isUndirected; // New property to store if the graph is undirected

        // Private method to ensure the adjacency matrix is square
        static void validateMatrix(const std::vector<std::vector<int>>& matrix) ;
    
    public:
        //method to check if the adjacency matrix is symmetric
        static bool isSymmetric(const std::vector<std::vector<int>>& matrix) ;

        // Default constructor
        Graph(); 
        
        // Constructor with an initial adjacency matrix
        Graph(const std::vector<std::vector<int>>& matrix);

        // Method to load a new graph with validation
        void loadGraph(const std::vector<std::vector<int>>& newMatrix);

        // Method to determine if the graph is undirected
        bool isUndirectedGraph() const;

        // Print information about the graph
        void printGraph() const;

        // Get the adjacency matrix
        const std::vector<std::vector<int>>& getAdjMatrix() const;

        //from here it Ex2
        // Friend function declaration for the << operator
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

        // Declare the + operator to add two graphs
        Graph operator+(const Graph& other) const;

        // Declare the - operator for subtracting graphs
        Graph operator-(const Graph& other) const;  
        
        // Declare the += operator for adding a number to all indices
        Graph& operator+=(int num);

        // Declare the += operator for adding another graph
        Graph& operator+=(const Graph& other); 

        // Declare the -= operator for subing a number to all indices
        Graph& operator-=(int num);

        // Declare the -= operator for adding another graph
        Graph& operator-=(const Graph& other);   

        // Declare the unary plus operator
        Graph operator+() const; 

        // Declare the unary minus operator 
        Graph operator-() const; 

        // Declaration for the `<` operator (bigger then) 
        friend bool operator<(const Graph& g1, const Graph& g2);  

        // Declaration for the `>` operator (smaller then)
        friend bool operator>(const Graph& g1, const Graph& g2);  

        // Declaration for `==` operator **note- i decided to add this operator
        friend bool operator==(const Graph& g1, const Graph& g2);

        // Declaration for '<=' operator less than or equal to
        friend bool operator<=(const Graph& g1, const Graph& g2);

        // Declaration for '>=' operator greater than or equal 
        friend bool operator>=(const Graph& g1, const Graph& g2);  

        // Declaration for '!=' operator inequality
        friend bool operator!=(const Graph& g1, const Graph& g2);

        // Declaration for '++' operator Pre-increment
        Graph& operator++();

        // Declaration for '++' operator Post-increment
        Graph operator++(int);  

        // Declaration for '--' operator Pre-increment
        Graph& operator--(); 

        // Declaration for '--' operator Post-increment
        Graph operator--(int); 

        // Declaration for '*=' Operator for multiplication with scalar
        Graph& operator*=(int multiplier); 

         // Declaration for '*' operator for graph multiplication
        friend Graph operator*(const Graph& g1, const Graph& g2);  
 
    };
}

#endif // GRAPH_HPP

