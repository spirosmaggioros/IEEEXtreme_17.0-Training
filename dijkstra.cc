#include <bits/stdc++.h>
#include <limits>
#include <queue>

constexpr int64_t INF = std::numeric_limits<int64_t>::max();

namespace graph {
void addEdge(std::vector<std::vector<std::pair<int, int>>> *adj, int u, int v,
             int w) {
    (*adj)[u].push_back(std::make_pair(v, w));
    // (*adj)[v - 1].push_back(std::make_pair(u - 1, w));
}

int dijkstra(std::vector<std::vector<std::pair<int, int>>> *adj, int s, int t) {
    int n = adj->size();
    std::vector<int64_t> dist(n, INF);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, s));
    dist[s] = 0;

    while (!pq.empty()) {
        int currentNode = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();
        for (std::pair<int, int> edge : (*adj)[currentNode]) {
            if (currentDist + edge.second < dist[edge.first]) {
                dist[edge.first] = currentDist + edge.second;
                pq.push(std::make_pair(dist[edge.first], edge.first));
            }
        }
    }
    if (dist[t] != INF) {
        return dist[t];
    }
    return -1;
}
}  
int main() {
    int vertices = int(), edges = int();
    std::cout << "Enter the number of vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges : ";
    std::cin >> edges;

    std::vector<std::vector<std::pair<int, int>>> adj(
        vertices, std::vector<std::pair<int, int>>());

    int u = int(), v = int(), w = int();
    while (edges--) {
        std::cin >> u >> v >> w;
        graph::addEdge(&adj, u, v, w);
    }

    int s = int(), t = int();
    std::cin >> s >> t;
    int dist = graph::dijkstra(&adj, s, t);
    if (dist == -1) {
        std::cout << "Target not reachable from source" << std::endl;
    } else {
        std::cout << "Shortest Path Distance : " << dist << std::endl;
    }
    return 0;
}
