#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <utility>




// 定义图类
class Graph {
private:
    int V; // 顶点数
    std::vector<std::list<int>> adjList; // 邻接表

public:
    Graph(int V); // 构造函数
    void addEdge(int v, int w); // 添加边
    void printGraph(); // 打印图
    void BFS(int start, int target); // 广度优先搜索
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

void Graph::BFS(int start, int target) {
    std::vector<bool> visited(V, false); // 访问标记
    std::vector<int> parent(V, -1); // 记录路径
    std::queue<int> queue; // 队列

    visited[start] = true; // 标记起始顶点为已访问
    queue.push(start); // 将起始顶点加入队列

    while (!queue.empty()) {
        int current = queue.front(); // 获取队首元素
        queue.pop(); // 出队

        if (current == target) { // 找到目标顶点
            std::cout << "Path from " << start << " to " << target << ": ";
            int temp = target;
            while (temp != -1) {
                std::cout << temp << " ";
                temp = parent[temp];
            }
            std::cout << std::endl;
            return;
        }

        for (auto i : adjList[current]) { // 遍历邻接顶点
            if (!visited[i]) { // 如果未访问
                visited[i] = true; // 标记为已访问
                parent[i] = current; // 记录路径
                queue.push(i); // 加入队列
            }
        }
    }

    std::cout << "No path found from " << start << " to " << target << std::endl;
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

    g.BFS(0, 6); // 从顶点0开始搜索目标顶点7





    return 0;
}
