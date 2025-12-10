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

void solve() {
    ll n;
    cin >> n;
    vll a(n), b(n);
    cin >> a >> b;

    ll ne = 0;
    for (const auto e : a) {
        if (e % 2 == 0) {
            ne++;
            if (ne >= 2)
                break;
        }
    }

    if (ne >= 2) {
        cout << 0 << nl;
        return;
    }

    vll oddbs;
    unordered_set<ll> pfseen;
    unordered_set<ll> evenpfs;
    ll evena = 0, evenb = 0;
    FOR(i, 0, n) {
        if (a[i] % 2) {
            oddbs.push_back(b[i]);
            const auto& upfs = upf_map[a[i]];
            for (const auto p : upfs) {
                if (pfseen.contains(p)) {
                    cout << 0 << nl;
                    return;
                }
                pfseen.insert(p);
            }
        } else {
            const auto& upfs = upf_map[a[i]];
            for (const auto p : upfs) {
                evenpfs.insert(p);
            }
            evena = a[i];
            evenb = b[i];
        }
    }
    vpll ab(n);
    FOR(i, 0, n) { ab[i] = {b[i], a[i]}; }
    ranges::sort(ab);
    FOR(i, 0, n) {
        b[i] = ab[i].first;
        a[i] = ab[i].second;
    }

    auto times_poss = [&](ll x) {
        // assert(x > 0);
        unordered_set<ll> pfwo = pfseen;
        const auto& upfx = upf_map[x];
        for (const auto p : upfx) {
            pfwo.erase(p);
        }

        ll ans = LINF;
        for (const auto p : pfwo) {
            ll thistimes = (x / p) * p + p - x;
            if (thistimes < 0)
                continue;
            ans = min(ans, thistimes);
        }
        return ans;
    };

    ll ans = 0;
    if (ne == 1) {
        ranges::sort(oddbs);
        for (const auto epf : evenpfs) {
            if (pfseen.contains(epf)) {
                cout << 0 << nl;
                return;
            }
        }
        ans = oddbs[0];
        ll times = times_poss(evena);
        if (times != LINF)
            ans = min(ans, evenb * times);
        cout << ans << nl;
        return;
    }

    // no evens;
    ans = b[0] + b[1];

    FOR(i, 0, n) {
        const auto& upfs0 = upf_map[a[i]];
        const auto& upfs1 = upf_map[a[i] + 1];
        for (const auto pf : upfs1) {
            if (pfseen.contains(pf) && !upfs0.contains(pf)) {
                ans = min(ans, b[i]);
                break;
            }
        }
    }

    if (b[0] < b[1]) {
        ll times = times_poss(a[0]);
        if (times != LINF)
            ans = min(ans, b[0] * times);
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
