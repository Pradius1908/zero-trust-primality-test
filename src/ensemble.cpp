#include "ensemble.hpp"
#include "fermat.hpp"
#include "miller_rabin.hpp"

EnsembleResult runEnsemble(uint64_t n)
{
    EnsembleResult result;

    result.fermat =
        fermatTest(n, 10);

    result.miller =
        millerRabin(n, 10);

    int score = 0;

    if(result.fermat)
        score += 1;

    if(result.miller)
        score += 3;

    result.confidence =
        (score / 4.0) * 100.0;

    result.decision =
        score >= 3;

    return result;
}
