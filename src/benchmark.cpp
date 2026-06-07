#include "benchmark.hpp"
#include "fermat.hpp"
#include "miller_rabin.hpp"

#include <chrono>
#include <iostream>

void benchmark(uint64_t n)
{
    using namespace std::chrono;

    auto start1 =
        high_resolution_clock::now();

    fermatTest(n, 10);

    auto end1 =
        high_resolution_clock::now();

    auto fermatTime =
        duration_cast<microseconds>(
            end1 - start1
        );

    auto start2 =
        high_resolution_clock::now();

    millerRabin(n, 10);

    auto end2 =
        high_resolution_clock::now();

    auto millerTime =
        duration_cast<microseconds>(
            end2 - start2
        );

    std::cout
    << "\nBenchmark Results\n";

    std::cout
    << "Fermat       : "
    << fermatTime.count()
    << " us\n";

    std::cout
    << "MillerRabin  : "
    << millerTime.count()
    << " us\n";
}
