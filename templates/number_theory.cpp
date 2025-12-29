#include "bits/stdc++.h"
#include <cstdint>
class NT {
  public:
    static constexpr std::size_t MAXN = 300003;
    // static constexpr std::uint64_t MOD = 998244353;
    static constexpr std::uint64_t MOD = 1000000007;

    template <std::size_t N, std::size_t MOD> static auto ComputeFactorialsMod() -> std::array<uint64_t, N> {
        std::array<uint64_t, N> facts = {};
        facts[0] = 1;
        for (std::size_t i = 1; i < N; i++) {
            facts[i] = (facts[i - 1] * i) % MOD;
        }

        return facts;
    }

    static auto ComputeFactorialsMod() -> std::array<uint64_t, MAXN> { return ComputeFactorialsMod<MAXN, MOD>(); }

    // Pre-compute nCk using nCk = n-1Ck-1 + n-1Ck
    // Use for 2 <= N <= 5000
    template <std::size_t N, std::uint64_t MOD>
    static auto ComputeNChooseKMod() -> std::array<std::array<uint64_t, N>, N> {
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
    template <std::uint64_t MOD> static auto BinPow(std::uint64_t a, std::uint64_t b) -> uint64_t {
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
    static auto BinPow(std::uint64_t a, std::uint64_t b) -> uint64_t { return BinPow<MOD>(a, b); }

    // a^(phi(MOD)-1) = a^-1 (mod MOD), for prime MOD, phi(MOD) = MOD - 1
    static auto InverseModePrime(std::uint64_t a) -> uint64_t { return BinPow(a, MOD - 2); }

    /*
     * Compute is_prime array using Sieve of Eratosthenes
     */
    template <std::size_t N> static auto ComputeIsPrimes() -> std::array<bool, N> {
        std::array<bool, N> is_prime;
        is_prime.fill(true);
        is_prime[0] = is_prime[1] = false;

        for (std::size_t i = 2; i < N; i++) {
            if (is_prime[i] && i * i < N) {
                for (std::size_t j = i * i; j < N; j += i) {
                    is_prime[j] = false;
                }
            }
        }

        return is_prime;
    }

    static auto ComputeIsPrimes() -> std::array<bool, MAXN> { return ComputeIsPrimes<MAXN>(); }

    template <std::size_t N> static auto ComputePrimes(const std::array<bool, N>& is_prime) -> std::vector<uint64_t> {
        std::vector<uint64_t> primes;
        for (std::size_t i = 0; i < is_prime.size(); i++) {
            if (is_prime[i]) {
                primes.push_back(i);
            }
        }

        return primes;
    }

    template <std::size_t N> static auto ComputePrimes() -> std::vector<uint64_t> {
        return ComputePrimes<N>(ComputeIsPrimes<N>());
    }

    static auto ComputePrimes(const std::array<bool, MAXN>& is_prime) -> std::vector<uint64_t> {
        return ComputePrimes<MAXN>(is_prime);
    }

    static auto ComputePrimes() -> std::vector<uint64_t> { return ComputePrimes<MAXN>(); }

    template <std::size_t N> static auto ComputeSmallestPrimeFactor() -> std::array<uint64_t, N> {
        std::array<uint64_t, N> spf;
        spf.fill(1);
        spf[0] = 0;

        for (std::size_t i = 2; i < N; i++) {
            if (spf[i] != 1)
                continue;
            for (std::size_t j = i; j < N; j += i) {
                spf[j] = i;
            }
        }

        return spf;
    }

    static auto ComputeSmallestPrimeFactor() -> std::array<uint64_t, MAXN> {
        return ComputeSmallestPrimeFactor<MAXN>();
    }

    template <std::size_t N>
    static auto UniquePrimeFactors(uint64_t x, const std::array<uint64_t, N>& spf) -> std::unordered_set<uint64_t> {
        std::unordered_set<uint64_t> upfs;
        while (x != 1) {
            upfs.insert(spf[x]);
            x /= spf[x];
        }

        return upfs;
    }

    static auto UniquePrimeFactors(uint64_t x, const std::array<uint64_t, MAXN>& spf) -> std::unordered_set<uint64_t> {
        return UniquePrimeFactors<MAXN>(x, spf);
    }

    template <std::size_t N>
    static auto ComputeUniquePrimeFactors(const std::array<uint64_t, N>& spf) -> std::array<std::unordered_set<uint64_t>, N> {
        std::array<std::unordered_set<uint64_t>, N> upf_map = {};
        for (std::size_t i = 1; i < N; i++) {
            upf_map[i] = UniquePrimeFactors<N>(i, spf);
        }

        return upf_map;
    }

    static auto ComputeUniquePrimeFactors(const std::array<uint64_t, MAXN>& spf)
        -> std::array<std::unordered_set<uint64_t>, MAXN> {
        return ComputeUniquePrimeFactors<MAXN>(spf);
    }
};
