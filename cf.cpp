#include "bits/stdc++.h"
#include <algorithm>

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
// #define LINF 1000000000000000007ll
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

const ll INF = 2e18;
vector<vll> char_counts;

ll solve(int n, ll k, int c_idx, const vll& fib, const string& X, const string& Y) {
    if (k <= 0)
        return 0;
    if (n == 0) {
        ll cnt = 0;
        for (int i = 0; i < min((ll)X.length(), k); ++i) {
            if (X[i] - 'a' == c_idx)
                cnt++;
        }

        return cnt;
    }
    if (n == 1) {
        ll cnt = 0;
        for (int i = 0; i < min((ll)Y.length(), k); ++i) {
            if (Y[i] - 'a' == c_idx)
                cnt++;
        }
        return cnt;
    }

    if (k >= fib[n])
        return char_counts[n][c_idx];

    if (k <= fib[n - 1]) {
        return solve(n - 1, k, c_idx, fib, X, Y);
    } else {
        return char_counts[n - 1][c_idx] + solve(n - 2, k - fib[n - 1], c_idx, fib, X, Y);
    }
}

void solve() {
    string x, y;
    cin >> x >> y;

    vll fib{(ll)x.length(), (ll)y.length()};
    char_counts.assign(92, vll(26, 0));
    for (char c : x)
        char_counts[0][c - 'a']++n;
    for (char c : y)
        char_counts[1][c - 'a']++;

    FOR(i, 0, 89) {
        ll m = fib.size();
        fib.push_back(min(INF, fib[m - 1] + fib[m - 2]));
        FOR(j, 0, 26) { char_counts[m][j] = char_counts[m - 1][j] + char_counts[m - 2][j]; }
    }

    int Q;

    cin >> Q;
    while (Q--) {
        ll L, R;
        char C;
        cin >> L >> R >> C;
        int ci = C - 'a';
        int start_n = fib.size() - 1;
        cout << solve(start_n, R, ci, fib, x, y) - solve(start_n, L - 1, ci, fib, x, y) << "\n";
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
