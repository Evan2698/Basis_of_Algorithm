#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <map>
#include <algorithm>
#include <set>
#include <numeric>

const int INF = std::numeric_limits<int>::max();

struct Edge
{
    char u;
    char v;
    int weight;
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

typedef std::map<char, std::vector<Edge>> Graph;

void prim(Graph &g, char start)
{
    std::set<char> VMST;     // Vertices in the minimum spanning tree
    //std::vector<Edge> queue; // Priority queue for edges
    std::map<Edge, int> queue; // Priority queue for edges for auto sorting

    std::vector<Edge> miniumEdges; // Edges in the minimum spanning tree

    VMST.insert(start);
    for (auto it : g[start])
    {
        if (VMST.find(it.v) == VMST.end())
        {
            //queue.push_back(it);
            queue.insert(std::make_pair(it, 0));
        }
    }

    while (g.size() != VMST.size())
    {
        // std::sort(queue.begin(), queue.end());
        // auto min = queue.front();
        // queue.erase(queue.begin());
        auto min = queue.begin()->first; 
        queue.erase(queue.begin());


        miniumEdges.push_back(min);
        VMST.insert(min.v);
        for (auto it : g[min.v])
        {
            if (VMST.find(it.v) == VMST.end())
            {
                //queue.push_back(it);
                queue.insert(std::make_pair(it, 0));
            }
        }
    }

    std::cout << "Minimum Spanning Tree Edges:\n";
    for (const auto &edge : miniumEdges)
    {
        std::cout << edge.u << " -- " << edge.v << " (Weight: " << edge.weight << ")\n";
    }
    std::cout << "Total Weight: " << std::accumulate(miniumEdges.begin(), miniumEdges.end(), 0,
                                                  [](int sum, const Edge &e) { return sum + e.weight; }) << "\n";
    std::cout << "Vertices in the Minimum Spanning Tree: ";
    for (const auto &v : VMST)
    {
        std::cout << v << " ";
    }
    std::cout << "\n";       

}

void prim_01(Graph &g, char start)
{
    std::map<char, int> key;  //记录各顶点到MST的最小边权
    std::map<char, char> parent; // 记录MST中顶点的父节点
    std::set<char> inMST;       // 标记顶点是否已在MST中

    // 初始化key为INF，parent为0
    for (const auto &p : g)
    {
        key[p.first] = INF;
        parent[p.first] = 0;
    }
    key[start] = 0;

    for (size_t count = 0; count < g.size(); ++count)
    {
        // 选择key最小且未在MST中的顶点u
        char u = 0;
        int minKey = INF;
        for (const auto &kv : key)
        {
            if (inMST.find(kv.first) == inMST.end() && kv.second < minKey)
            {
                minKey = kv.second;
                u = kv.first;
            }
        }
        if (u == 0) break; // 没有可选顶点

        inMST.insert(u);

        // 更新邻接顶点的key和parent
        for (const auto &edge : g[u])
        {
            char v = edge.v;
            int w = edge.weight;
            if (inMST.find(v) == inMST.end() && w < key[v])
            {
                key[v] = w;
                parent[v] = u;
            }
        }
    }

    // 输出结果
    int totalWeight = 0;
    std::cout << "Minimum Spanning Tree Edges:\n";
    for (const auto &kv : parent)
    {
        if (kv.second != 0)
        {
            std::cout << kv.second << " -- " << kv.first << " (Weight: " << key[kv.first] << ")\n";
            totalWeight += key[kv.first];
        }
    }
    std::cout << "Total Weight: " << totalWeight << "\n";
    std::cout << "Vertices in the Minimum Spanning Tree: ";
    for (const auto &v : inMST)
    {
        std::cout << v << " ";
    }
    std::cout << "\n";
}
    
int main()
{
    Graph g;
    g['A'] = {{'A', 'B', 65}, {'A', 'D', 30}};
    g['B'] = {{'B', 'A', 65}, {'B', 'C', 50}, {'B', 'D', 30}};
    g['C'] = {{'C', 'B', 50}, {'C', 'E', 70}};
    g['D'] = {{'D', 'B', 30}, {'D', 'E', 40}, {'D', 'A', 30}};
    g['E'] = {{'E', 'C', 70}, {'E', 'D', 40}};

    char start = 'A';
    std::cout << "Prim's Algorithm starting from vertex " << start << ":\n";
    prim(g, start);
    std::cout << "\n";

    std::cout << "Prim's Algorithm (Optimized) starting from vertex " << start << ":\n";    
    prim_01(g, start);
   

    return 0;
}
