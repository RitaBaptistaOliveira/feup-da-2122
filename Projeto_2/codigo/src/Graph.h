#ifndef FEUP_DA_PROJ2_GRAPH_H
#define FEUP_DA_PROJ2_GRAPH_H


#include <vector>
#include <list>
#include <iostream>
#include <float.h>
#include <set>
#include <map>

using namespace std;

class Graph {
    /**
     * Represents a trip from a node to another
     */
    struct Edge {
        int dest;   /**< Destination node */
        int capacity; /**< Capacity of the vehicle */
        int duration; /**< Duration of the trip */
        int flow; /** Current number of people in the vehicle */
    };

    /**
     * Represents a bus stop
     */
    struct Node {
        list<Edge> adj; /**< The list of outgoing edges (to adjacent nodes) */
        int parent; /**< Number of the node that precedes this node */
        bool visited; /**< True if the node was already visited or false otherwise */
    };

    int n;              /**< Graph size (number of stops) */
    vector<Node> nodes; /**< The list of nodes being represented */
    int minDuration;    /**< Minimum duration of travel */

public:

/**
 * Constructor of the Graph class.
 * Initializes a new instance of the Graph class using default values
 */
    Graph();

/**
 * Sets the size of the graph
 * @param nodes Size of the graph
 */
    void setSize(int nodes);

/**
 * Adds an edge to the list of edge of the src node
 * The edge represents the trip of a certain duration the bus with a certain capacity makes from src to dest
 * @param src The source node where the edge is going to be added
 * @param dest The destination of the edge
 * @param capacity The capacity of the edge
 * @param duration The duration of the edge
 */
    void addEdge(int src, int dest, int capacity = 1, int duration = 0);

//Scenario 1.1 and 1.2

/**
 * Scenario 1.1
 * Uses the Widest Path algorithm to return the maximum capacity of the network
 * Time complexity: Same as the Widest Path algorithm: O(log(V) * E), where V is the number of nodes and E is the number of edges
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @return -1 if the path from src to target is not possible or 0 otherwise
 */
    int scenario1_1(int src, int target);

/**
 * Scenario 1.2
 * Maximizes the group size (the capacity) and/or minimizes the amount of bus transfers
 * Chooses if one option is better than the other and displays it, or displays both options if the situation is pareto optimal
 * Uses the BFS to minimize the amount of bus transfers and the Widest Path algorithm to maximize the group size
 * Time Complexity: Same as the Widest Path algorithm: O(log(V) * E), where V is the number of nodes and E is the number of edges
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @return -1 if the path from src to target is not possible or 0 otherwise
 */
    int scenario1_2(int src, int target);
/**
 * Widest Path algorithm.
 * Variant of the Dijkstra algorithm
 * Maximizes the weight (i.e. the capacity) of the minimun-weight edge in the path.
 * Time complexity: O(log(V) * E), where V is the number of nodes and E is the number of edges
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 */
    int widestPath(int src, int target);

/**
 * Breadth First Search.
 * Computes the path with the least amount of nodes from the given source node
 * Time Complexity: O(V + E), where V is the number of nodes and E is the number of edges
 * @param src Number of the origin/source node
 */
    void bfs(int src);

/**
 * Calls the BFS algorithm and composes the path
 * Time Complexity: Same as the BFS: O(V + E), where V is the number of nodes and E is the number of edges
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @return an empty list if a path from src to target doesn't exist or the path from src to target otherwise
 */
    list<int> bfs_path(int src, int target);

/**
 * Composes the path for scenarios 1.1 and 2.2
 * Time Complexity: O(n)
 * @param target Number of the destination/target node
 * @param path List with nodes forming a path
 */
    void computePath(int target, list<int> &path);

/**
 * Displays the path and its capacity
 * Time Complexity: O(n)
 * @param path List with the numbers of the nodes that form the path
 * @param cap Capacity of the path
 */
    static void displayPath(list<int> &path, int cap) ;


//Scenario 2.1, 2.2 and 2.3

/**
 * Scenario 2.1 and 2.2
 * Determines the paths a group of a given size that can separate itself can take from a origin to a destination
 * Allows the user to increment the group size by a given number of people, if they desire
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @param size Initial size of the group (specified by the user)
 */
    void scenario2_1_2(int src, int target, int size);

/**
 * Scenario 2.3
 * Determines the maximum group dimension (i.e. the maximum flow) using the Edmonds-Karp algorithm and their multiple paths
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 */
    void scenario2_3(int src, int target);

/**
 * Breadth First Search (for the Ford Fulkerson Method)
 * Uses the BFS to compute the path with the least amount of nodes from the given source node
 * Unlike a standard BFS, it has into account the flow and the capacity of each edge
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @return true if there are no paths to the target node, or false otherwise
 */
    bool bfsFF(int src, int target);

/**
 * Ford-Fulkerson Method using the Edmonds-Karp algorithm
 * Uses the Edmonds-Karp algorithm to calculate maximum flow between the source and the target node.
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @param paths Vector with multiple list of the different path taken by the group
 * @return The maximum flow of the graph
 */
    int edmondsKarp(int src, int target, vector<list<int>> &paths);

/**
 * Ford-Fulkerson Method using the Edmonds-Karp algorithm
 * Uses the Edmonds-Karp Algorithm in a way that allows the network to be filled up tp a certain group size(i.e. flow)
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @param groupSize Group size chosen by the user
 * @param paths Vector with multiple list of the different path taken by the group
 * @param maxReached Boolean used to check if the maximum flow has or hasn't been reached
 * @param maxFlow Maximum Flow in the network at a given moment
 * @return The flow of the graph. In this case, either the group size or the maximum flow
 */
    int edmondsKarpAlt(int src, int target, int groupSize, vector<list<int>> &paths, bool &maxReached, int &maxFlow);

/**
 * Auxiliary function for the Edmonds-Karp algorithm
 * Composes the path and calculates the path flow
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @param paths Vector with multiple list of the different path taken by the group
 * @param maxFlow Maximum Flow in the network at a given moment
 * @param pathFlow Flow of a specific path
 */
    void EK(int src, int target, vector<list<int>> &paths, int &maxFlow, int &pathFlow);

/**
 * Prints all the edges of the graph along with their capacity and flow
 */
    void printGraph();

/**
 * Displays the multiple paths taken by a group that can be separated in a network
 * @param paths Vector with multiple list of the different path taken by the group
 * @param flow Flow of the network
 */
    static void displayPaths(vector<list<int>> &paths, int flow);

/**
 * Updates the flow of each edge of the graph along a path
 * @param src Number of the origin/source node
 * @param target Number of the destination/target node
 * @param flow Flow to be added to each edge of the path
 */
    void updateFlow(int src, int target, int flow);

//Scenario 2.4 and 2.5

/**
 * Calculates the earliest start of each node of the graph
 * @return a vector with all the earliest finish values
 */
    vector<int> earliestStart(bool print);

/**
 * Calculates the earliest start of each node of the graph
 * @return a vector with all the latest finish values
 */
    vector<int> latestFinish();

/**
 * Calculates the total slack of each node of the graph
 */
    void maxWaitingTime();

/**
 * Transposes a graph and returns an instance of the new graph
 * @return graph transposed
 */
    Graph transposeGraph();
};

#endif //FEUP_DA_PROJ2_GRAPH_H
