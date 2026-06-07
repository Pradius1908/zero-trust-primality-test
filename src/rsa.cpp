#include "rsa.hpp"
#include "miller_rabin.hpp"

#include <random>
#include <iostream>

static uint64_t gcd(uint64_t a,
                    uint64_t b)
{
    while(b)
    {
        uint64_t t = b;
        b = a % b;
        a = t;
    }

    return a;
}

static long long extendedGCD(
    long long a,
    long long b,
    long long &x,
    long long &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;

        return a;
    }

    long long x1, y1;

    long long g =
        extendedGCD(
            b,
            a % b,
            x1,
            y1
        );

    x = y1;

    y =
        x1 -
        y1 * (a / b);

    return g;
}

static uint64_t modInverse(
    uint64_t a,
    uint64_t m)
{
    long long x, y;

    extendedGCD(
        a,
        m,
        x,
        y
    );

    return (x % m + m) % m;
}

uint64_t generatePrime()
{
    std::random_device rd;

    std::mt19937_64 gen(rd());

    std::uniform_int_distribution<uint64_t>
        dist(10000, 50000);

    while(true)
    {
        uint64_t candidate =
            dist(gen);

        if(candidate % 2 == 0)
            candidate++;

        if(millerRabin(
                candidate,
                10))
        {
            return candidate;
        }
    }
}

RSAKeyPair generateRSA()
{
    RSAKeyPair key;

    key.p =
        generatePrime();

    do
    {
        key.q =
            generatePrime();
    }
    while(key.q == key.p);

    key.n =
        key.p * key.q;

    uint64_t phi =
        (key.p - 1) *
        (key.q - 1);

    key.e = 65537;

    while(
        gcd(
            key.e,
            phi
        ) != 1)
    {
        key.e += 2;
    }

    key.d =
        modInverse(
            key.e,
            phi
        );

    return key;
}
