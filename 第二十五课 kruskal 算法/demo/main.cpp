
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class UnionFind
{

public:
    UnionFind(std::vector<char> &elements)
    {
        int i = 0;
        for (char element : elements)
        {
            ids[element] = i;
            i++;
        }
    }

    int find(char element)
    {
        if (ids.find(element) == ids.end())
        {
            throw std::invalid_argument("Element not found in Union-Find structure.");
        }
        return ids[element];
    }

    bool union_element(char A, char B) {
        if (ids.find(A) == ids.end() || ids.find(B) == ids.end())
        {
            throw std::invalid_argument("One or both elements not found in Union-Find structure.");
        }
        
        int idA = find(A);
        int idB = find(B);
        
        if (idA == idB)
        {
            return false; // A and B are already in the same set
        }
        
        // Union operation: merge sets by assigning the same id to both elements
        for (auto &pair : ids)
        {
            if (pair.second == idB)
            {
                pair.second = idA;
            }
        }
        
        return true; // A and B were successfully unioned

    }

    bool is_connected(char A, char B) {
        if (ids.find(A) == ids.end() || ids.find(B) == ids.end())
        {
            throw std::invalid_argument("One or both elements not found in Union-Find structure.");
        }
        
        return find(A) == find(B);
    }



private:
    std::map<char, int> ids;
};


struct Edge
{
    char A;
    char B;
    int weight;

    Edge(char a, char b, int w) : A(a), B(b), weight(w) {}
};

void kruskal(std::vector<Edge> &edges, UnionFind &uf, int vertices = 0)
{
    std::sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2) {
        return e1.weight < e2.weight;
    });

    std::vector<Edge> mst;

    int edge_count = 0;

    for (const Edge &edge : edges)
    {
        if (!uf.is_connected(edge.A, edge.B))
        {
            uf.union_element(edge.A, edge.B);
            mst.push_back(edge);
            edge_count++;
        }

        if (edge_count == vertices - 1)
        {
            break; // Minimum spanning tree is complete
        }
    }

    // Output the edges in the minimum spanning tree
    for (const Edge &edge : mst)
    {
        std::cout << edge.A << " - " << edge.B << " : " << edge.weight << std::endl;
    }
}




int main()
{
    std::vector<char> elements = {'A', 'B', 'C', 'D', 'E'};
    UnionFind uf(elements);

    std::vector<Edge> edges = {
        Edge('A', 'B', 65),
        Edge('A', 'D', 30),
        Edge('B', 'D', 30),
        Edge('B', 'C', 50),
        Edge('E', 'D', 40),
        Edge('C', 'E', 70)
    };

    kruskal(edges, uf, 5);
   

    return 0;
}