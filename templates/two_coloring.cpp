#include <optional>
#include <queue>
#include <vector>
class TwoColoring {
  public:
    using Vertex = int;
    using AdjMatrix = std::vector<std::vector<int>>;

    explicit TwoColoring(const AdjMatrix& adj) : adj_(adj), n_(adj.size()) {}

    // Returns a vector<int> colors denoting a possible 2-coloring of the graph, where colors[i] = 0 or 1
    // If no 2-coloring exists, return std::nullopt
    std::optional<std::vector<int>> Run() {
        std::vector<int> colors(n_, -1);
        for (size_t i = 0; i < n_; i++) {
            if (colors[i] != -1)
                continue;

            colors[i] = 0;
            std::queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (const int v : adj_[u]) {
                    if (colors[v] == -1) {
                        colors[v] = colors[u] ^ 1;
                        q.push(v);
                    } else if (colors[u] == colors[v]) {
                        return std::nullopt;
                    }
                }
            }
        }

        return colors;
    }

  private:
    AdjMatrix adj_;
    size_t n_; // number of vertices
};
