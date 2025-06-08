#include <iostream>
#include <vector>
#include <algorithm>
#include <map>



struct Location {
    int x;
    int y;
    Location():x(0), y(0){}
    Location(int x1, int y1):x(x1), y(y1){}

    bool operator==(const Location& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Location& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Location& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

};


struct Node {
    Location pos;
    int g;
    int h;
    int f;
    Node(int x, int y):pos({x, y}), g(0), h(0), f(g+h){}

    bool operator<(const Node& other) const {
        return f < other.f; // For min-heap
    }

    bool operator ==(const Node& other) const {
        return pos == other.pos;
    }
};

template <typename T>
class astar_queue
{
public:
    astar_queue() {};
    void push(const T &a)
    {

        auto it = std::find(queue.begin(), queue.end(), a);
        if (it != queue.end())
        {
            *it = a;
        }
        else
        {
            queue.push_back(a);
        }
    }
    void pop()
    {
       auto t = top();
       this->queue.erase(std::remove(queue.begin(), queue.end(), t), queue.end());
    }

    T top()
    {
        return  *std::min_element(queue.begin(), queue.end());
    }

    size_t size() const
    {
        return queue.size();
    }

    bool empty() const
    {
        return queue.empty();
    }

private:
    std::vector<T> queue;
};


typedef std::vector<std::vector<int>> Grid;


int heuristic(const Location& a, const Location& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool is_valid(const Location& loc, const Grid& grid) {
    return loc.x >= 0 && loc.x < grid.size() && loc.y >= 0 && loc.y < grid[0].size() && grid[loc.x][loc.y] == 0;
}

std::vector<Location> get_neighbors(const Location& loc, const Grid& grid) {
    std::vector<Location> neighbors;
    std::vector<Location> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (const auto& dir : directions) {
        Location newLoc(loc.x + dir.x, loc.y + dir.y);
        if (is_valid(newLoc, grid)) {
            neighbors.push_back(newLoc);
        }
    }
    return neighbors;
}

std::vector<Location> a_star(const Grid& grid, const Location& start, const Location& goal) {
    astar_queue<Node> open_list;
    std::vector<Location> closed_list;
    std::map<Location, Location> came_from;

    came_from[start] = Location(-1, -1); // Initialize with a flag

    auto start_node = Node(start.x, start.y);
    start_node.g = 0;
    start_node.h = heuristic(start, goal);
    start_node.f = start_node.g + start_node.h;
    open_list.push(start_node);
    
    while (!open_list.empty()) {
        Node current = open_list.top();
        open_list.pop();

        if (current.pos == goal) {
            std::vector<Location> path;

            Location step = current.pos;
            while ( step != Location(-1, -1)) {
                path.push_back(step);
                step = came_from[step];
            }
        
            std::reverse(path.begin(), path.end());
            return path; // Return the path from start to goal            
        }

        closed_list.push_back(current.pos);

        for (const auto& neighbor : get_neighbors(current.pos, grid)) {
            if (std::find(closed_list.begin(), closed_list.end(), neighbor) != closed_list.end()) {
                continue; // Ignore already evaluated nodes
            }

            int g_new = current.g + 1;
            int h_new = heuristic(neighbor, goal);
            int f_new = g_new + h_new;

            Node neighbor_node(neighbor.x, neighbor.y);
            neighbor_node.g = g_new;
            neighbor_node.h = h_new;
            neighbor_node.f = f_new;
            came_from[neighbor] = current.pos;
            open_list.push(neighbor_node);
        }
    }
    return {}; // No path found
    
}



int main(){

    std::vector<std::vector<int>> grid = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0},  
    };

    Location start(0, 0);
    Location goal(2, 2);
    std::vector<Location> path = a_star(grid, start, goal);
    if (path.empty()) {
        std::cout << "No path found!" << std::endl;
    } else {
        std::cout << "Path found: ";
        for (const auto& loc : path) {
            std::cout << "(" << loc.x << ", " << loc.y << ") ";
        }
        std::cout << std::endl;
    }
    return 0;
}