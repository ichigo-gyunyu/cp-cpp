#include <numeric>
#include <vector>
class DSU {
  private:
    int num_sets_;
    std::vector<int> parent_;
    std::vector<int> size_;

  public:
    explicit DSU(int n) : num_sets_(n), parent_(n), size_(n, 1) { std::iota(parent_.begin(), parent_.end(), 0); }

    auto FindSet(const int x) -> int {
        if (parent_[x] != x)
            parent_[x] = FindSet(parent_[x]); // path compression
        return parent_[x];
    }

    auto UnionSet(const int x, const int y) -> bool {
        int root_x = FindSet(x);
        int root_y = FindSet(y);

        if (root_x == root_y) {
            return false;
        }

        if (size_[root_x] < size_[root_y]) {
            parent_[root_x] = root_y;
            size_[root_y] += size_[root_x];
        } else {
            parent_[root_y] = root_x;
            size_[root_x] += size_[root_y];
        }
        num_sets_--;
        return true;
    }

    auto GetNumSets() -> int { return num_sets_; }

    auto GetSize(const int x) -> int { return size_[FindSet(x)]; }
};
