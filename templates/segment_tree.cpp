#include <vector>
template <typename T, typename F> class SegmentTree {
  private:
    int n_;
    std::vector<T> tree_;
    T identity_;
    F fn_; // any associative function

  public:
    // build empty segment tree
    SegmentTree(int n, T identity, F merge) : n_(n), identity_(identity), fn_(merge) {
        tree_.assign(2 * n_, identity_);
    }

    // build segment tree from array
    SegmentTree(const std::vector<T>& a, T identity, F merge) : n_(static_cast<int>(a.size())), fn_(merge) {
        tree_.assign(2 * n_, identity_);
        for (int i = 0; i < n_; i++) {
            tree_[n_ + i] = a[i];
        }
        for (int i = n_ - 1; i > 0; i--) {
            tree_[i] = fn_(tree_[i << 1], tree_[i << 1 | 1]);
        }
    }

    // point update a[pos] = val
    void Update(int pos, T val) {
        pos += n_;
        tree_[pos] = val;
        for (pos >>= 1; pos > 0; pos >>= 1) {
            tree_[pos] = fn_(tree_[pos << 1], tree_[pos << 1 | 1]);
        }
    }

    // query [l, r)
    T Query(int l, int r) const {
        T resL = identity_, resR = identity_;
        for (l += n_, r += n_; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resL = fn_(resL, tree_[l++]);
            if (r & 1)
                resR = fn_(resR, tree_[--r]);
        }

        return fn_(resL, resR);
    }
};
