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

        //From here it Ex2
        /*
        *Note: i used friend functions when the operator needs to access the internal state of both operands or when the left operand is not an instance of the class.
        * and used members functions when the operator modifies the state of the calling object or when only a single object is involved.
        */
        // Friend function declaration for the << operator, this function is friend to allow the function to access the private and protected members of the Graph class.
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

        // Declare the + operator to add two graphs
        Graph operator+(const Graph& other) const;

        // Declare the - operator for subtracting graphs
        Graph operator-(const Graph& other) const;  
        
        // Declare the += operator for adding a number to all indices, it is not comst becouse the graph change.
        Graph& operator+=(int num);

        // Declare the += operator for adding another graph, it is not comst becouse the graph change.
        Graph& operator+=(const Graph& other); 

        // Declare the -= operator for subing a number to all indices, it is not comst becouse the graph change.
        Graph& operator-=(int num);

        // Declare the -= operator for adding another graph, it is not comst becouse the graph change.
        Graph& operator-=(const Graph& other);   

        // Declare the unary plus operator, in this case it is const to ensure that it can be called on const instances of Graph.
        Graph operator+() const; 

        // Declare the unary minus operator, in this case it is const to ensure that it can be called on const instances of Graph.
        Graph operator-() const; 

        // Helper functions(countEdges, isContained) to count edges in the adjacency matrix to operator <
        bool isContained(const Graph& g1, const Graph& g2) const;

        int countEdges(const std::vector<std::vector<int>>& adjMatrix) const;
        
        // Declaration for the `<` operator (bigger then)   
        bool operator<(const Graph& other) const;

        // Declaration for the `>` operator (smaller then)
        bool operator>(const Graph& other) const;  

        // **Helper functions(countEhelpFunctionToOperatorEqualdges, isContained) to operator ==
        // Helper function to check exact equivalence
        bool helpFunctionToOperatorEqual(const Graph& other) const;

        // Helper function to check relative equivalence.
        bool isRelativelyEquivalent(const Graph& other) const;

        // Declaration for `==` operator **note- i decided to add this operator.
        bool operator==(const Graph& other) const;

        // Declaration for '<=' operator less than or equal to.
        bool operator<=(const Graph& other) const;

        // Declaration for '>=' operator greater than or equal.
        bool operator>=(const Graph& other) const;

        // Declaration for '!=' operator inequality.
        bool operator!=(const Graph& other) const;

        // Declaration for '++' operator Pre-increment, this operator return a reference to the modified object itself.
        Graph& operator++();

        // Declaration for '++' operator Post-increment, this is not reference becouse it is return a copy of the object as it was before the modification.
        Graph operator++(int);  

        // Declaration for '--' operator Pre-increment, this operator return a reference to the modified object itself. 
        Graph& operator--(); 

        // Declaration for '--' operator Post-increment, this is not reference becouse it is return a copy of the object as it was before the modification.
        Graph operator--(int); 

        // Declaration for '*=' Operator for multiplication with scalar, this operator return a reference to the modified object itself.
        Graph& operator*=(int multiplier); 

        // Declaration for '*' operator for graph multiplication
        friend Graph operator*(const Graph& g1, const Graph& g2);  
 
    };
}

#endif // GRAPH_HPP

