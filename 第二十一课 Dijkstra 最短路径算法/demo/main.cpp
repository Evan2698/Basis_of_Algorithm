#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>


const int INT_INF = std::numeric_limits<int>::max();

struct Node {
    std::string vertex_name;
    int distance;

    // bool operator <(const Node & other) const {
    //      return vertex_name < other.vertex_name;
    // }
};

typedef std::map<std::string, std::vector<Node>> Graph;

Graph build_graph() {
    Graph graph;
    graph["A"] = {{"B", 65}, {"D", 30}};
    graph["B"] = {{"A", 65}, {"C", 50}, {"D", 30}};
    graph["C"] = {{"B", 50}, {"E", 70}};
    graph["D"] = {{"A", 30}, {"B", 30}, {"E", 40}};
    graph["E"] = {{"C", 70}, {"D", 40}};
    return graph;
}


void dijkstra(const Graph &graph, const std::string &start_vertex) {    

    //1. 建立距离表，并将其初始化为无穷大
    std::map<std::string, int> distances;    
    for (const auto &pair : graph) {
        distances[pair.first] = INT_INF;
    }

    std::map<std::string, std::string> predecessor; // 用于存储前驱节点
    for (const auto &pair : graph) {
        predecessor[pair.first] = ""; // 初始化前驱节点为空
    }


    //2. 建立没有访问的顶点集合
    std::set<std::string> unvisited;
    for (const auto &pair : graph) {
        unvisited.insert(pair.first);
    }  

    //3. 开始顶点的距离为0
    distances[start_vertex] = 0;

    std::string current_vertex = start_vertex;
    
    while (!unvisited.empty()) {
      
        //4. 开始要处理的顶点, 先从未访问的顶点集合中移除
        unvisited.erase(current_vertex);

        //5. 使用广度优先搜索算法，遍历当前顶点的所有邻接点， 并更新距离表
        for (const auto &neighbor : graph.at(current_vertex)) {
            const std::string &neighbor_vertex = neighbor.vertex_name;            
            int edge_distance = neighbor.distance;
            if (unvisited.find(neighbor_vertex) != unvisited.end()) {
                int new_distance = distances[current_vertex] + edge_distance;
                if (new_distance < distances[neighbor_vertex]) {
                    distances[neighbor_vertex] = new_distance;
                    predecessor[neighbor_vertex] = current_vertex; // 更新前驱节点
                }
            }
        }

        //6. 使用最贪心的方式，选择下一个要处理的顶点
        int min_distance = INT_INF;
        for (const auto item : unvisited) {
            const std::string &vertex = item;
            if (distances[vertex] < min_distance) {
                min_distance = distances[vertex];
                current_vertex = vertex;
            }
        }
        
    } 


    //7. 打印结果   
    std::cout << "Shortest distances from vertex " << start_vertex << ":\n";
    for (const auto &pair : distances) {
        const std::string &vertex = pair.first;
        int distance = pair.second;
        if (distance == INT_INF) {
            std::cout << "Distance to " << vertex << ": INF\n";
        } else {
            std::cout << "Distance to " << vertex << ": " << distance << "\n";
        }
    }
    std::cout << std::endl;

    // 打印路径
    std::cout << "Paths:\n";
    for (const auto &pair : distances) {
        const std::string &vertex = pair.first;
        if (vertex != start_vertex && distances[vertex] != INT_INF) {
            std::cout << "Path A to " << vertex << ": ";
            std::string path = vertex;
            std::string pred = predecessor[vertex];
            while (!pred.empty()) {
                path = pred + " -> " + path;
                pred = predecessor[pred];
            }
            std::cout << path << "\n";
        }
    }
    std::cout << std::endl;

 
}

int main() {
    Graph graph = build_graph();
    std::string start_vertex = "A";
    dijkstra(graph, start_vertex);

 
    return 0;
}
