#include "user_manager.hpp"

#include <fstream>
#include <string>

bool registerUser(const std::string& username)
{
    std::ifstream checkFile(
        "database/users.csv"
    );

    std::string existingUser;

    while(std::getline(
            checkFile,
            existingUser))
    {
        if(existingUser == username)
        {
            return false;
        }
    }

    checkFile.close();

    std::ofstream out(
        "database/users.csv",
        std::ios::app
    );

    out << username << "\n";

    return true;
}

bool authenticateUser(
    const std::string& username)
{
    std::ifstream file(
        "database/users.csv"
    );

    std::string user;

    while(std::getline(file, user))
    {
        if(user == username)
        {
            return true;
        }
    }

    return false;
}
