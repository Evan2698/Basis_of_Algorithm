#include <iostream> 
#include <vector>
#include <limits>
#include <map>
#include <algorithm>


const int INF = std::numeric_limits<int>::max();

struct Edge {
    char u;
    char v;
    int weight;
};

typedef std::map<char, int> dist_map;
typedef std::map<char, char> prev_map;


void bellman_ford(const std::vector<Edge>& edges, char start, int vertex_count, char end ='C') {

    dist_map distances;
    prev_map predecessors;
    // Initialize distances and predecessors
    for (const auto& edge : edges) {
        distances[edge.u] = INF;
        distances[edge.v] = INF;
    }
    distances[start] = 0;

    // Relax edges up to |V| - 1 times
    for (size_t i = 0; i < vertex_count -1; ++i) {
        for (const auto& edge : edges) {
            if (distances[edge.u] != INF && distances[edge.u] + edge.weight < distances[edge.v]) {
                distances[edge.v] = distances[edge.u] + edge.weight;
                predecessors[edge.v] = edge.u;
            }
        }
    }

    // Check for negative-weight cycles
    for (const auto& edge : edges) {
        if (distances[edge.u] != INF && distances[edge.u] + edge.weight < distances[edge.v]) {
            std::cerr << "Graph contains a negative-weight cycle" << std::endl;
            return;
        }
    }

    // Print the results
    std::cout << "Vertex Distance from Source" << std::endl;
    for (const auto& pair : distances) {
        std::cout << " " << pair.first << "\t\t" << pair.second << std::endl;
    }

    std::cout << "Predecessors:" << std::endl;
    auto temp = predecessors[end];
    std::cout << "Path from " << start << " to " << end << ": ";
    std::vector<char> path;
    path.push_back(end);
    while (temp != start) {
        path.push_back(temp);
        temp = predecessors[temp];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    for (const auto& node : path) {       
        if (node == end) {
            std::cout << node;
        } else {
            std::cout << node << " -> ";
        }       
    }
   
    std::cout << std::endl;
}

int main() {
    std::vector<Edge> edges = {
        {'A', 'B', 65},
        {'B', 'A', 65},
        {'B', 'C', 50},
        {'C', 'B', 50},
        {'B', 'D', 30},
        {'D', 'B', 30},
        {'C', 'E', 70},
        {'E', 'C', 70},
        {'D', 'E', 40},
        {'E', 'D', 40},
        {'A', 'D', 30},
        {'D', 'A', 30}
    };

    char start = 'A';
    bellman_ford(edges, start, 5);

    return 0;
}
