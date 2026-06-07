#include "miller_rabin.hpp"

#include <random>

static uint64_t modPow(uint64_t base,
                       uint64_t exp,
                       uint64_t mod)
{
    uint64_t result = 1;
    base %= mod;

    while(exp > 0)
    {
        if(exp & 1)
        {
            __uint128_t temp =
                (__uint128_t)result * base;

            result = temp % mod;
        }

        __uint128_t temp =
            (__uint128_t)base * base;

        base = temp % mod;

        exp >>= 1;
    }

    return result;
}

bool millerRabin(uint64_t n, int rounds)
{
    if(n < 2)
        return false;

    if(n == 2 || n == 3)
        return true;

    if(n % 2 == 0)
        return false;

    uint64_t d = n - 1;
    int r = 0;

    while((d & 1) == 0)
    {
        d >>= 1;
        r++;
    }

    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::uniform_int_distribution<uint64_t>
        dist(2, n - 2);

    for(int i = 0; i < rounds; i++)
    {
        uint64_t a = dist(gen);

        uint64_t x = modPow(a, d, n);

        if(x == 1 || x == n - 1)
            continue;

        bool witnessFound = true;

        for(int j = 0; j < r - 1; j++)
        {
            x = modPow(x, 2, n);

            if(x == n - 1)
            {
                witnessFound = false;
                break;
            }
        }

        if(witnessFound)
            return false;
    }

    return true;
}
