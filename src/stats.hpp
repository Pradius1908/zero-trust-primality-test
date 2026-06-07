#pragma once

struct SystemStats
{
    int users;
    int authAttempts;
    int successfulAuths;
};

SystemStats getStats();
