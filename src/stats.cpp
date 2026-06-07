#include "stats.hpp"

#include <fstream>
#include <string>

SystemStats getStats()
{
    SystemStats stats;

    stats.users = 0;
    stats.authAttempts = 0;
    stats.successfulAuths = 0;

    std::ifstream usersFile(
        "database/users.csv"
    );

    std::string line;

    while(std::getline(
            usersFile,
            line))
    {
        stats.users++;
    }

    std::ifstream authFile(
        "database/auth_logs.csv"
    );

    while(std::getline(
            authFile,
            line))
    {
        stats.authAttempts++;

        if(line.find("SUCCESS")
           != std::string::npos)
        {
            stats.successfulAuths++;
        }
    }

    return stats;
}
