#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// 定义节点结构
struct Node
{
    int x, y;
    double f, g, h;
    Node *parent;

    Node(int _x, int _y) : x(_x), y(_y), f(0), g(0), h(0), parent(nullptr) {}
};

// A*算法实现
std::vector<Node *> astar(Node *start, Node *goal, const std::vector<std::vector<int>> &map)
{
    std::vector<Node *> openSet;
    std::vector<Node *> closedSet;

    openSet.push_back(start);

    while (!openSet.empty())
    {
        // 寻找当前开放集中f值最小的节点
        auto currentIt = std::min_element(openSet.begin(), openSet.end(),
                                          [](const Node *a, const Node *b)
                                          {
                                              return a->f < b->f;
                                          });

        Node *current = *currentIt;
        openSet.erase(currentIt);
        closedSet.push_back(current);

        if (current->x == goal->x && current->y == goal->y)
        {
            // 找到路径，回溯生成路径
            std::vector<Node *> path;
            while (current != nullptr)
            {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // 生成相邻节点
        std::vector<Node *> neighbors;
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue; // 忽略当前节点
                int nx = current->x + dx;
                int ny = current->y + dy;

                if (nx >= 0 && nx < map[0].size() && ny >= 0 && ny < map.size() && map[ny][nx] == 0)
                {
                    Node *neighbor = new Node(nx, ny);
                    neighbors.push_back(neighbor);
                }
            }
        }

        // 处理相邻节点
        for (Node *neighbor : neighbors)
        {
            if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end())
            {
                // 跳过已关闭的节点
                continue;
            }

            double tentative_g = current->g + 1; // 假设距离为1

            auto neighborIt = std::find(openSet.begin(), openSet.end(), neighbor);
            if (neighborIt == openSet.end() || tentative_g < neighbor->g)
            {
                // 更新或添加新节点
                neighbor->g = tentative_g;
                neighbor->h = std::abs(neighbor->x - goal->x) + std::abs(neighbor->y - goal->y);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;

                if (neighborIt == openSet.end())
                {
                    openSet.push_back(neighbor);
                }
            }
        }
    }

    // 未找到路径
    return std::vector<Node *>();
}

void run_AStar()
{
    // 定义地图数组，0表示可通行，1表示障碍物
    std::vector<std::vector<int>> map = {
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    // 设置起点和终点
    Node start(0, 0);
    Node goal(19, 19);

    // 计时开始
    auto start_time = chrono::high_resolution_clock::now();

    // 执行A*算法
    for (int i = 0; i < 1000; i++)
    {
        std::vector<Node *> path = astar(&start, &goal, map);
    }

    // 计时结束
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start_time);
    cout << "A-Star Path Finding Time: " << duration.count() << "ms" << endl;
}

int main()
{
    run_AStar();
    return 0;
}
