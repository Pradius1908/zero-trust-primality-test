#pragma once

#include <cstdint>

struct EnsembleResult
{
    bool fermat;
    bool miller;
    bool decision;
    double confidence;
};

EnsembleResult runEnsemble(uint64_t n);
