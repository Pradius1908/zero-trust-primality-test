#include "carmichael.hpp"
#include "fermat.hpp"
#include "miller_rabin.hpp"

#include <iostream>

void runCarmichaelDemo()
{
    uint64_t nums[] =
    {
        561,
        1105,
        1729,
        2465,
        2821,
        6601
    };

    std::cout
    << "\n=============================\n";
    std::cout
    << " CARMICHAEL DEMONSTRATION\n";
    std::cout
    << "=============================\n";

    for(auto n : nums)
    {
	bool fermat =
    	    fermatDemo(n);

        bool miller =
            millerRabin(n, 10);

        std::cout
        << "\nNumber: " << n
        << "\nFermat       : "
        << (fermat ? "PRIME" : "COMPOSITE")
        << "\nMiller-Rabin : "
        << (miller ? "PRIME" : "COMPOSITE")
        << "\n";
    }
}
