#include "bits/stdc++.h"
#include <numeric>
#include <utility>

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

void solve() {
    ll n;
    cin >> n;
    vll a(n);
    cin >> a;
    vll seen(n + 1);
    ll ans = 0;
    for (const auto e : a) {
        if (!seen[e - 1])
            ans++;
        seen[e] = 1;
    }

    cout << ans << nl;
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
