#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

typedef pair<double, int> pii; // (距离, 节点)

const double INF = numeric_limits<double>::infinity();

class Graph {
public:
    int V; // 节点数量
    vector<vector<pii>> adj; // 邻接表

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, double w) {
        adj[u].emplace_back(w, v);
    }

    // Dijkstra算法
    vector<double> dijkstra(int source) {
        vector<double> dist(V, INF);
        dist[source] = 0.0;
        priority_queue<pii, vector<pii>, std::greater<pii>> pq;
        pq.emplace(0.0, source);

        while (!pq.empty()) {
            double current_dist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (current_dist > dist[u])
                continue;

            for (auto &[weight, v] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        return dist;
    }
};

int main() {
    // 节点编号示例：
    // 0: 阅读数学基础, 1: 学习代数, 2: 学习几何, 3: 学习概率, 
    // 4: 完成代数作业, 5: 完成几何作业, 6: 完成概率作业

    int V = 7;
    Graph g(V);

    // 添加边和权重
    g.addEdge(0, 1, 2.0);   // 阅读数学基础 -> 学习代数
    g.addEdge(0, 2, 2.5);   // 阅读数学基础 -> 学习几何
    g.addEdge(1, 3, 3.0);   // 学习代数 -> 学习概率
    g.addEdge(2, 3, 1.5);   // 学习几何 -> 学习概率
    g.addEdge(1, 4, 1.0);   // 学习代数 -> 完成代数作业
    g.addEdge(2, 5, 1.0);   // 学习几何 -> 完成几何作业
    g.addEdge(3, 6, 2.0);   // 学习概率 -> 完成概率作业

    int source = 0; // 起始节点 阅读数学基础
    vector<double> distances = g.dijkstra(source);

    // 输出最短路径距离
    vector<string> node_names = {
        "阅读数学基础", "学习代数", "学习几何", 
        "学习概率", "完成代数作业", "完成几何作业", "完成概率作业"
    };
    cout << "从任务 \"" << node_names[source] << "\" 到各任务的最短时间：" << endl;
    for(int i = 0; i < V; ++i){
        if(distances[i] < INF)
            cout << node_names[source] << " -> " << node_names[i] 
                 << " : " << distances[i] << " 小时" << endl;
        else
            cout << node_names[source] << " -> " << node_names[i] 
                 << " : 无法到达" << endl;
    }

    return 0;
}
