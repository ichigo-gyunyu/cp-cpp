#include "bits/stdc++.h"
#include <cstdint>
#include <numeric>

using namespace std;

// clang-format off
#define LOG1(x) cout << #x << ": " << x << endl
#define LOG2(x, y) cout << #x << ": " << x << ", " << #y << ": " << y << endl
#define FOR(i, l, r) for (ll i = (l); i < (r); i++)
#define ROF(i, l, r) for (ll i = (l); i >= (r); i--)
#define nl "\n"
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define Yes cout << "Yes\n"
#define No cout << "No\n"
#define LINF 1000000000000000007ll
// #define INF 1000000007
#define POW2(x) (1ll << (x))
#define SLEEP(x) this_thread::sleep_for(chrono::seconds(x))

using ll = long long;
using pll = pair<long long, long long>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;
using vpll = vector<pair<long long, long long>>;
using Adj = vector<vector<int>>;
using WAdj = vector<vector<pair<int, long long>>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T> istream& operator >> (istream& i, vector<T> &v) { for(auto &e: v) { i >> e; } return i; }
template<typename T> ostream& operator << (ostream& o, const vector<T> &v) { bool first = true; for(const auto &e : v) {if(!first) cout<<" "; cout<<e; first = false;} return o; }

template <typename T> void LOG(const T &t) { cout << t; }
template <typename T, typename U> void LOG(const pair<T, U> &p) { cout << "(" << p.first << ", " << p.second << ")"; }
template <ranges::range R> void LOG(const R& r) {cout<<"{"; bool first = true; for(const auto &e : r) {if(!first) cout<<", "; LOG(e); first = false;} cout<<"}";}
template <typename T> void LOG(const vector<T> &v) {cout<<"["; bool first = true; for(const auto &e : v) {if(!first) cout<<", "; LOG(e); first = false;} cout<<"]";}
template <typename T, typename... V> void LOG(const T &t, V&&... v) {LOG(t); if (sizeof...(v)) cout<<", "; LOG(v...);}
#ifdef ICHIDBG
#define DBG(x...) cout << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; LOG(x); cout<<"]\e[39m" << endl;
#else
#define DBG(x...)
#endif
// clang-format on

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
void solve() {
    ll n, q;
    cin >> n >> q;
    IntervalSet<ll> is;
    while (q--) {
        ll l, r;
        cin >> l >> r;
        is.Add(l, r);
        ll ans = n - is.TotalLength();
        cout << ans << nl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
