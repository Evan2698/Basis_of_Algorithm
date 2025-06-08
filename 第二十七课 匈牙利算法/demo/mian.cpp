#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

const int INF = std::numeric_limits<int>::max();
using Matrix = std::vector<std::vector<int>>;

// 打印矩阵
void print_matrix(const Matrix &m)
{
    for (const auto &row : m)
    {
        for (int val : row)
            std::cout << val << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// 行规约
void reduce_rows(Matrix &m)
{
    for (auto &row : m)
    {
        int row_min = *std::min_element(row.begin(), row.end());
        for (auto &val : row)
            val -= row_min;
    }
}
// 列规约
void reduce_cols(Matrix &m)
{
    for (size_t j = 0; j < m[0].size(); ++j)
    {
        int col_min = INF;
        for (const auto &row : m)
            col_min = std::min(col_min, row[j]);
        for (auto &row : m)
            row[j] -= col_min;
    }
}

// DFS 尝试从某行找匹配列
bool find_match(int row, const Matrix &matrix, std::vector<int> &match_col, std::vector<bool> &visited)
{
    const int N = matrix.size();
    for (int j = 0; j < N; ++j)
    {
        if (matrix[row][j] == 0 && !visited[j])
        {
            visited[j] = true;
            if (match_col[j] == -1 || find_match(match_col[j], matrix, match_col, visited))
            {
                match_col[j] = row;
                return true;
            }
        }
    }
    return false;
}

// 检查当前 0 矩阵是否可分配成功
bool try_assignment(const Matrix &matrix, std::vector<int> &row_to_col)
{
    int N = matrix.size();
    std::vector<int> match_col(N, -1);
    for (int i = 0; i < N; ++i)
    {
        std::vector<bool> visited(N, false);
        if (!find_match(i, matrix, match_col, visited))
            return false;
    }
    row_to_col = std::vector<int>(N, -1);
    for (int j = 0; j < N; ++j)
        if (match_col[j] != -1)
            row_to_col[match_col[j]] = j;
    return true;
}

// 找未覆盖元素中最小值
int find_min_uncovered(const Matrix &m, const std::vector<bool> &row_cover, const std::vector<bool> &col_cover)
{
    int N = m.size();
    int min_val = INF;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (!row_cover[i] && !col_cover[j])
                min_val = std::min(min_val, m[i][j]);
    return min_val;
}

// 矩阵调整操作
void adjust_matrix(Matrix &m, const std::vector<bool> &row_cover, const std::vector<bool> &col_cover)
{
    int N = m.size();
    int delta = find_min_uncovered(m, row_cover, col_cover);
    // cout << "调整值 delta = " << delta << endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (!row_cover[i] && !col_cover[j])
            {
                m[i][j] -= delta;
            }
            else if (row_cover[i] && col_cover[j])
            {
                m[i][j] += delta;
            }
        }
    std::cout << "调整后矩阵:\n";
    print_matrix(m);
}

// 用最少线覆盖所有零，返回所用线的数量（教学版，加入 Star 和 Prime 标记调试）
int cover_zeros_min_lines(Matrix &m, std::vector<bool> &row_cover, std::vector<bool> &col_cover)
{
    const int N = m.size();
    std::vector<std::vector<bool>> starred(N, std::vector<bool>(N, false));
    std::vector<std::vector<bool>> primed(N, std::vector<bool>(N, false));
    std::vector<int> row_star(N, -1);
    std::vector<int> col_star(N, -1);

    // Step 1: Star独立零
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (m[i][j] == 0 && row_star[i] == -1 && col_star[j] == -1)
            {
                starred[i][j] = true;
                row_star[i] = j;
                col_star[j] = i;
            }
        }
    }

    // Step 2: 覆盖所有包含星号的列
    row_cover.assign(N, false);
    col_cover.assign(N, false);
    for (int j = 0; j < N; ++j)
    {
        if (col_star[j] != -1)
            col_cover[j] = true;
    }

    std::cout << "初始星标矩阵：\n";
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << (starred[i][j] ? "*" : " ") << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "初始覆盖列：";
    for (int j = 0; j < N; ++j)
        std::cout << col_cover[j] << " ";
    std::cout << std::endl;

    // Step 3: 继续进行 Prime 打标直到不能扩展
    bool done = false;
    while (!done)
    {
        done = true;
        for (int i = 0; i < N; ++i)
        {
            if (row_cover[i])
                continue;
            for (int j = 0; j < N; ++j)
            {
                if (m[i][j] == 0 && !col_cover[j])
                {
                    primed[i][j] = true;
                    std::cout << "行" << i << "列" << j << " 被Prime标记\n";
                    if (row_star[i] == -1)
                    {
                        // 找到增广路径，反转标记
                        int r = i, c = j;
                        while (true)
                        {
                            starred[r][c] = true;
                            int prev_c = row_star[r];
                            if (prev_c == -1)
                                break;
                            starred[r][prev_c] = false;
                            r = col_star[prev_c];
                            c = prev_c;
                        }
                        return N; // 成功构造增广路径，即找到最大匹配
                    }
                    else
                    {
                        row_cover[i] = true;
                        col_cover[row_star[i]] = false;
                        done = false;
                        break;
                    }
                }
            }
        }
    }

    int line_count = 0;
    for (bool c : row_cover)
        line_count += c;
    for (bool c : col_cover)
        line_count += c;
    std::cout << "当前覆盖线数量: " << line_count << std::endl;
    return line_count;
}






std::vector<int> hungarian(const Matrix &cost_matrix)
{
    int N = cost_matrix.size();
    int M = cost_matrix[0].size();
    int max_dim = std::max(N, M);

    // 如果矩阵不是方阵，填充为方阵
    Matrix m(max_dim, std::vector<int>(max_dim, 0));
    for(int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            m[i][j] = cost_matrix[i][j];
        }
    }
    for (int i = 0; i < max_dim; ++i)
    {
        for (int j = M; j < max_dim; ++j)
        {
            m[i][j] = INF; // 填充剩余部分为无穷大
        }
    }


    N = M = max_dim;
    std::cout << "初始矩阵:\n";
    print_matrix(m);

    reduce_rows(m);
    std::cout << "行规约后矩阵:\n";
    print_matrix(m);

 
    reduce_cols(m);
    std::cout << "列规约前矩阵:\n";
    print_matrix(m);



    std::vector<int> row_to_col(N, -1);

    while (!try_assignment(m, row_to_col))
    {
        std::vector<bool> row_cover(N, false);
        std::vector<bool> col_cover(N, false);

        cover_zeros_min_lines(m, row_cover, col_cover);
        adjust_matrix(m, row_cover, col_cover);
    }

    return row_to_col;
}

int main()
{

    Matrix cost = {
        {9, 5, 4, 2},
        {4, 3, 5, 8},
        {3, 1, 6, 7},
        {6, 2, 9, 4}};

    int total = 0;
    std::vector<int> assignment = hungarian(cost);
    std::cout << "分配结果:\n";
    for (int i = 0; i < assignment.size(); ++i)
    {
        int j = assignment[i];
        total += cost[i][j];
        std::cout << "员工 " << char('A' + i) << " -> 任务 " << (j + 1) << "（耗时: " << cost[i][j] << "）\n";
    }
    std::cout << "总耗时: " << total << " 小时\n";
}
