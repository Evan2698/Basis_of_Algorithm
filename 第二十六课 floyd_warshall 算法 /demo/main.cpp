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

std::vector<char> precursor(std::vector<Edge> edges, char current);

int distance(std::vector<Edge> edgs, char u, char v);

void floyd_warshall(std::vector<Edge> & edges, std::vector<char> & vertices) {

    std::map<char, std::map<char, int>> dist;
    for (char v : vertices) {
        for (char u : vertices) {
            if (v == u) {
                dist[v][u] = 0;
            } else {
                dist[v][u] = INF;
            }
        }
    }
    for (const Edge &edge : edges) {
        dist[edge.u][edge.v] = edge.weight;
    }   

    for (char k : vertices) {
        for (char i : vertices) {
            for (char j : vertices) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }


    //--------------------------------------------------------------------------------------------------

    // Output the shortest paths
    for (char i : vertices) {
        for (char j : vertices) {
            if (dist[i][j] == INF) {
                std::cout << "Distance from " << i << " to " << j << " is infinity" << std::endl;
            } else {
                std::cout << "Distance from " << i << " to " << j << " is " << dist[i][j] << std::endl;
            }
        }
    }



    // output A to C  full path 
    char start = 'A';
    char end = 'C';
    std::vector<char> path;
    if (dist[start][end] == INF) {
        std::cout << "No path from " << start << " to " << end << std::endl;
    } else {
        path.push_back(end);
        char current = end;
        while (current != start) {
            std::vector<char> precursors = precursor(edges, current);
            if (precursors.empty()) {
                std::cout << "No path from " << start << " to " << end << std::endl;
                return;
            }
            char next = precursors[0];
            for (char p : precursors) {
                if (dist[start][p] +  distance(edges, p, current) ==  dist[start][current] ) {
                    next = p;
                    break;
                }
            }
                     
            path.push_back(next);
            current = next;
        }

        std::reverse(path.begin(), path.end());
        
        std::cout << "Path from " << start << " to " << end << ": ";
        for (char v : path) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
       
    }
}
int distance(std::vector<Edge> edgs, char u, char v) {
    for (const Edge &edge : edgs) {
        if (edge.u == u && edge.v == v) {
            return edge.weight;
        }
    }
    return INF; // If no edge found, return infinity
}

std::vector<char> precursor(std::vector<Edge> edges, char current){
    std::vector<char> path;
    for (const Edge &edge : edges) {
        if (edge.v == current) {
            path.push_back(edge.u);
        }
    }
    
    return path;
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

    std::vector<char> vertices = {'A', 'B', 'C', 'D', 'E'};
    floyd_warshall(edges, vertices);



    return 0;
}