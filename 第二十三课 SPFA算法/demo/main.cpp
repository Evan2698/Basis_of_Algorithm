#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <map>
#include <queue>
#include <algorithm>

typedef std::pair<char, int> Edge;

typedef std::map<char, std::vector<Edge>> Graph;

const int INF = std::numeric_limits<int>::max();

void spfa(Graph &g, char start, char target)
{
    std::map<char, int> dist;
    std::map<char, bool> in_queue;

    int v = g.size();

    for (const auto &pair : g)
    {
        dist[pair.first] = INF;
    }

    dist[start] = 0;
    std::queue<char> q;
    q.push(start);
    in_queue[start] = true;
    while (!q.empty())
    {
        char u = q.front();
        q.pop();
        in_queue[u] = false;

        for (const auto &edge : g[u])
        {
            char v = edge.first;
            int weight = edge.second;

            if (dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;

                if (!in_queue[v])
                {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    std::cout << "Vertex Distance from Source" << std::endl;
    for (const auto &pair : dist)
    {
        std::cout << " " << pair.first << "\t\t" << pair.second << std::endl;
    }
    std::cout << "Predecessors:" << std::endl;
    auto temp = target;
    std::cout << "Path from " << start << " to " << target << ": ";
    std::vector<char> path;     
    //path.push_back(target);
    while (temp != start)
    {
        path.push_back(temp);
        for (const auto &edge : g[temp])
        {
            if (dist[temp] == dist[edge.first] + edge.second)
            {
                temp = edge.first;
                break;
            }
        }
    }
    path.push_back(start);  
    std::reverse(path.begin(), path.end());

    for (const auto &node : path)
    {
        if (node == target)
        {
            std::cout << node;
        }
        else
        {
            std::cout << node << " -> ";
        }
    }   

    std::cout << std::endl; 
}

int main()
{
    Graph g;
    g['A'] = {{'B', 65}, {'D', 30}};
    g['B'] = {{'A', 65}, {'C', 50}, {'D', 30}};
    g['C'] = {{'B', 50}, {'E', 70}};
    g['D'] = {{'B', 30}, {'E', 40}, {'A', 30}};
    g['E'] = {{'C', 70}, {'D', 40}};

    char start = 'A';
    char target = 'C';

    spfa(g, start, target);

    return 0;
}