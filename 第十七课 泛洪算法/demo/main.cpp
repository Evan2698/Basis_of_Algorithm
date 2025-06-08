#include <iostream>
#include <vector>
#include <queue>
#include <utility> 
using namespace std;

// 方向数组：四邻域
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

typedef std::pair<int, int> coordinate;

// 泛洪算法（队列实现，BFS方式）
void floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    int oldColor = image[sr][sc];
    if (oldColor == newColor) return; // 颜色相同无需处理
    
    int m = image.size(), n = image[0].size();
    queue<coordinate> q;
    q.push(std::make_pair(sr, sc));
    image[sr][sc] = newColor;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; ++i) { // 遍历四邻域
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && image[nx][ny] == oldColor) {
                image[nx][ny] = newColor;
                q.push(std::make_pair(nx, ny));
            }
        }
    }
}

// 打印图像
void printImage(const vector<vector<int>>& image) {
    for (const auto& row : image) {
        for (int pixel : row) {
            if (pixel == 1) {
                std::cout << "■ ";
            } else if( pixel == 2){
                std::cout << "● "; 
            } else if (pixel == 0) {
                std::cout << "  "; // 未填充区域用空格表示
            } else {              
                std::cout << "  "; // 填充区域用空格表示
            }
          
        }
        cout << endl;
    }
}

int main() {
    // 示例图像 (0表示未填充区域，1表示边界)
    vector<vector<int>> image =  {   
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
    
    cout << "原始图像：" << endl;
    printImage(image);
    
    floodFill(image, 2, 2, 2);
    
    cout << "\n填充后图像：" << endl;
    printImage(image);
    
    return 0;
}
