#include <algorithm>
#include <concepts>
#include <limits>
#include <optional>
#include <queue>
#include <utility>
#include <vector>
template <std::totally_ordered T> class Dijkstra {
  public:
    using Vertex = int;
    using Weight = T;
    using Edge = std::pair<Vertex, Weight>; // (neighbour, weight)
    using AdjMatrix = std::vector<std::vector<Edge>>;

    // n - number of vertices in the graph
    explicit Dijkstra(size_t n) : adj_(n), prev_(n), dist_(n) {}

    explicit Dijkstra(const AdjMatrix& adj) : adj_(adj), prev_(adj_.size()), dist_(adj_.size()) {}

    explicit Dijkstra(const AdjMatrix&& adj) : adj_(std::move(adj)), prev_(adj_.size()), dist_(adj_.size()) {}

    void AddEdge(Vertex u, Vertex v, Weight w, bool isDirected = false) {
        adj_[u].emplace_back(v, w);
        if (!isDirected)
            adj_[v].emplace_back(u, w);
    }

    void Run(Vertex source) {
        std::ranges::fill(dist_, INF);
        std::ranges::fill(prev_, std::nullopt);
        dist_[source] = static_cast<Weight>(0);

        using DistanceNode = std::pair<Weight, Vertex>;
        std::priority_queue<DistanceNode, std::vector<DistanceNode>, std::greater<DistanceNode>> pq;
        pq.emplace(static_cast<Weight>(0), source);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (dist_[u] < d)
                continue;

            for (const auto& [v, w] : adj_[u]) {
                if (dist_[v] > d + w) {
                    dist_[v] = d + w;
                    prev_[v] = u;
                    pq.emplace(d + w, v);
                }
            }
        }
    }

    [[nodiscard]] std::optional<Weight> DistanceTo(Vertex target) {
        if (dist_[target] == INF)
            return std::nullopt;
        return dist_[target];
    }

    [[nodiscard]] std::optional<std::vector<Vertex>> PathTo(Vertex target) {
        if (!DistanceTo(target))
            return std::nullopt;

        std::vector<Vertex> path;
        for (std::optional<Vertex> u{target}; u.has_value(); u = prev_[u.value()]) {
            path.push_back(u.value());
        }

        std::ranges::reverse(path);
        return path;
    }

  private:
    constexpr static Weight INF = std::numeric_limits<Weight>::max();
    AdjMatrix adj_;
    std::vector<std::optional<Vertex>> prev_;
    std::vector<Weight> dist_;
};
