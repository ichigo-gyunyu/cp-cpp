#include "bits/stdc++.h"
namespace NT {
constexpr std::size_t MAXN = 300003;
// constexpr std::uint64_t MOD = 998244353;
constexpr std::uint64_t MOD = 1000000007;

template <std::size_t N, std::size_t MOD> inline auto ComputeFactorialsMod() -> std::array<uint64_t, N> {
    std::array<uint64_t, N> facts = {};
    facts[0] = 1;
    for (std::size_t i = 1; i < N; i++) {
        facts[i] = (facts[i - 1] * i) % MOD;
    }
    return facts;
}

std::array<uint64_t, MAXN> factorials = ComputeFactorialsMod<MAXN, MOD>();

// Pre-compute nCk using nCk = n-1Ck-1 + n-1Ck
// Use for 2 <= N <= 5000
template <std::size_t N, std::uint64_t MOD> inline auto ComputeNChooseKMod() -> std::array<std::array<uint64_t, N>, N> {
    std::array<std::array<uint64_t, N>, N> nCk;
    nCk[1][0] = 1, nCk[1][1] = 1;

    for (std::size_t i = 2; i < N; i++) {
        nCk[i][0] = 1;
        for (std::size_t j = 1; j < i; j++) {
            nCk[i][j] = (nCk[i - 1][j - 1] + nCk[i - 1][j]) % MOD;
        }
        nCk[i][i] = 1;
    }

    return nCk;
}

// Compute a^b (mod MOD) using binary exponentiation
template <std::uint64_t MOD> inline auto BinPow(std::uint64_t a, std::uint64_t b) -> uint64_t {
    uint64_t res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Compute a^b (mod MOD) using binary exponentiation
inline auto BinPow(std::uint64_t a, std::uint64_t b) -> uint64_t {
    uint64_t res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// a^(phi(MOD)-1) = a^-1 (mod MOD), for prime MOD, phi(MOD) = MOD - 1
inline auto InverseModePrime(std::uint64_t a) -> uint64_t { return BinPow(a, MOD - 2); }

} // namespace NT
using namespace NT;
