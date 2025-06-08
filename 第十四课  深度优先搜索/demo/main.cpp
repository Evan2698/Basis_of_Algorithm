#include <iostream>
#include <vector>
#include <stack>
#include <list>




// 定义图类
class Graph {
private:
    int V; // 顶点数
    std::vector<std::list<int>> adjList; // 邻接表

public:
    Graph(int V); // 构造函数
    void addEdge(int v, int w); // 添加边
    void printGraph(); // 打印图
    void DFS(int start, int target); // 深度优先搜索
};

// 构造函数
Graph::Graph(int V) {
    this->V = V;
    adjList.resize(V);
}

// 添加边
void Graph::addEdge(int v, int w) {
    adjList[v].push_back(w);
    // 因为是无向图，所以添加双向边
    adjList[w].push_back(v);
}

// 打印图
void Graph::printGraph() {
    for (int v = 0; v < V; ++v) {
        std::cout << "adjacency of vertex " << v << ": ";
        for (auto i : adjList[v])
            std::cout << i << " ";
        std::cout << std::endl;
    }
}

void Graph::DFS(int start, int target) {
    std::vector<bool> visited(V, false);
    std::stack<int> stack;

    stack.push(start);
    visited[start] = true;

    while (!stack.empty()) {
        int v = stack.top();
        if (v == target) {
            std::cout << "Found target: " << target << std::endl;
            break;
        }

        bool found_in_adjacency_list = false;
        for (auto i : adjList[v]) {
            if (!visited[i]) {
                stack.push(i);
                visited[i] = true;
                found_in_adjacency_list = true;
                break;
            }
        }

        if (!found_in_adjacency_list) {
            stack.pop();
        }
    } 
    
    if (stack.empty()) {
        std::cout << "Target " << target << " not found." << std::endl;
    } else {
        std::cout << "Path to target: ";
        while (!stack.empty()) {
            std::cout << stack.top() << " ";
            stack.pop();
        }
        std::cout << std::endl;
    }
}

int main() {
    // 创建有8个顶点的图（数字0至7）
    Graph g(8);

    // 根据图片中的连接添加边
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(3, 4);  
    g.addEdge(4, 6);
    g.addEdge(2, 5);
    g.addEdge(4, 5);
    g.addEdge(5, 7); 
    g.addEdge(6, 7);

    // 打印图
    g.printGraph();

    g.DFS(0, 6); // 从顶点0开始搜索目标顶点7

    return 0;
}
