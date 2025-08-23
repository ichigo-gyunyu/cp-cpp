#include <concepts>
#include <map>
#include <optional>
template <std::totally_ordered T> class IntervalSet {
  private:
    using Interval = std::pair<T, T>;
    std::map<T, T> intervals_;
    T total_length_ = 0;
    auto Length_(const T l, const T r) const -> T { return r - l + 1; }

  public:
    /*
     * Adds interval [l, r] to the interval set. Will merge touching/overlapping intervals.
     */
    void Add(T l, T r) {
        auto it = intervals_.upper_bound(l);

        // if previous interval needs to be merged
        if (it != intervals_.begin()) {
            auto it_prev = std::prev(it);
            if (it_prev->second >= l - 1) {
                it = it_prev;
            }
        }

        T new_l = l, new_r = r;
        while (it != intervals_.end() && it->first <= r + 1) {
            new_l = std::min(new_l, it->first);
            new_r = std::max(new_r, it->second);
            total_length_ -= Length_(it->first, it->second);
            it = intervals_.erase(it);
        }
        total_length_ += Length_(new_l, new_r);
        intervals_[new_l] = new_r;
    }

    /*
     * Returns the (merged) interval that fully covers [l, r], or std::nullopt if none exists
     */
    std::optional<Interval> CoveredBy(T l, T r) const {
        auto it = intervals_.upper_bound(l);
        if (it == intervals_.begin() || std::prev(it)->second < r) {
            return std::nullopt;
        }

        it--;
        return {it->first, it->second};
    }

    /*
     * Check if [l, r] is fully covered by one or more intervals
     */
    bool Covers(T l, T r) const { return CoveredBy(l, r).has_value(); }

    /*
     * Returns the total length covered by all intervals
     */
    T TotalLength() const { return total_length_; }
};
