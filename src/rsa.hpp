#pragma once

#include <cstdint>

struct RSAKeyPair
{
    uint64_t p;
    uint64_t q;

    uint64_t n;

    uint64_t e;
    uint64_t d;
};

uint64_t generatePrime();

RSAKeyPair generateRSA();
