#include "bits/stdc++.h"

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

    Adj adj(n);
    FOR(i, 0, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vll par(n, -1);
    function<void(ll, ll)> dfs_par = [&](ll u, ll p) {
        par[u] = p;

        for (const auto v : adj[u]) {
            if (v == p)
                continue;
            dfs_par(v, u);
        }
    };
    dfs_par(0, -1);

    vvll dp(n, vll(3, -1));
    function<void(ll, ll)> dfs = [&](ll u, ll p) {
        DBG(u, p);
        for (const auto v : adj[u]) {
            if (v == p)
                continue;
            dfs(v, u);
        }

        if (adj[u].size() <= 2)
            return;

        ll mx1 = -1;
        for (const auto v : adj[u]) {
            if (v == p)
                continue;
            mx1 = max(mx1, dp[v][1]);
        }
        if (mx1 != -1) {
            dp[u][0] = 1 + mx1;
            DBG(u, mx1, dp[u][0]);
            if (adj[u].size() > 3) {
                dp[u][1] = 1 + mx1;
            }
        }

        if (adj[u].size() > 3) {
            vll mxs;
            for (const auto v : adj[u]) {
                if (v == p)
                    continue;
                if (dp[v][1] == -1)
                    continue;
                mxs.push_back(dp[v][1]);
            }

            if (mxs.size() > 1) {
                ranges::sort(mxs);
                ll m1 = mxs.back();
                mxs.pop_back();
                ll m2 = mxs.back();
                mxs.pop_back();
                dp[u][2] = 1 + m1 + m2;
            }
        }

        DBG(u, adj[u].size());
        if (adj[u].size() >= 2) {
            dp[u][0] = max(dp[u][0], 1ll);
        }
        if (adj[u].size() >= 3) {
            dp[u][1] = max(dp[u][1], 1ll);
        }
        DBG(u, dp[u][0], dp[u][1], dp[u][2]);
    };
    dfs(0, -1);

    ll ans = 1;
    FOR(i, 0, n) {
        DBG(dp[i]);
        ll mx = ranges::max(dp[i]);
        ans = max(ans, mx);
    }

    cout << ans << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
