#include "ensemble.hpp"
#include "carmichael.hpp"
#include "benchmark.hpp"
#include "rsa.hpp"

#include <iostream>

int main()
{
    while(true)
    {
        std::cout
        << "\n============================\n";

        std::cout
        << " ZERO TRUST ADMIN CONSOLE\n";

        std::cout
        << "============================\n";

        std::cout
        << "1. Test Number\n";
        std::cout
        << "2. Carmichael Demo\n";
        std::cout
        << "3. Benchmark\n";
        std::cout
        << "4. Generate RSA\n";
        std::cout
        << "5. Exit\n";

        int choice;

        std::cin >> choice;

        if(choice == 1)
        {
            uint64_t n;

            std::cout
            << "Number: ";

            std::cin >> n;

            auto result =
                runEnsemble(n);

            std::cout
            << "\nFermat      : "
            << result.fermat;

            std::cout
            << "\nMiller      : "
            << result.miller;

            std::cout
            << "\nConfidence  : "
            << result.confidence
            << "%\n";
        }

        else if(choice == 2)
        {
            runCarmichaelDemo();
        }

        else if(choice == 3)
        {
            uint64_t n;

            std::cout
            << "Number: ";

            std::cin >> n;

            benchmark(n);
        }

        else if(choice == 4)
        {
            auto key =
                generateRSA();

            std::cout
            << "\np = "
            << key.p;

            std::cout
            << "\nq = "
            << key.q;

            std::cout
            << "\nn = "
            << key.n;

            std::cout
            << "\ne = "
            << key.e;

            std::cout
            << "\nd = "
            << key.d
            << "\n";
        }

        else if(choice == 5)
        {
            break;
        }
    }

    return 0;
}
