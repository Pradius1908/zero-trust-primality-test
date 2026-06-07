#include "fermat.hpp"

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

bool fermatTest(uint64_t n,
                int iterations)
{
    if(n <= 1)
        return false;

    if(n <= 3)
        return true;

    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::uniform_int_distribution<uint64_t>
        dist(2, n - 2);

    for(int i = 0; i < iterations; i++)
    {
        uint64_t a = dist(gen);

        if(modPow(a, n - 1, n) != 1)
            return false;
    }

    return true;
}

bool fermatDemo(uint64_t n)
{
    if(n <= 1)
        return false;

    if(n <= 3)
        return true;

    uint64_t a = 2;

    return modPow(a, n - 1, n) == 1;
}
