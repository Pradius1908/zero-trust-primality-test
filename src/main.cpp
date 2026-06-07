#include "ensemble.hpp"
#include "rsa.hpp"
#include "user_manager.hpp"
#include "stats.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout
        << "Usage:\n"
        << "./prime_engine test <number>\n"
        << "./prime_engine rsa\n"
        << "./prime_engine register <username>\n"
        << "./prime_engine auth <username>\n"
        << "./prime_engine stats\n";

        return 0;
    }

    std::string command = argv[1];

    /*
    =====================================
    PRIME TEST
    =====================================
    */
    if(command == "test")
    {
        if(argc < 3)
        {
            std::cerr
            << "{\"error\":\"missing_number\"}";
            return 1;
        }

        uint64_t n =
            std::stoull(argv[2]);

        auto result =
            runEnsemble(n);

        std::cout
        << "{"
        << "\"fermat\":"
        << (result.fermat ? "true" : "false")
        << ","
        << "\"miller\":"
        << (result.miller ? "true" : "false")
        << ","
        << "\"confidence\":"
        << result.confidence
        << ","
        << "\"decision\":"
        << (result.decision ? "true" : "false")
        << "}";

        return 0;
    }

    /*
    =====================================
    RSA GENERATION
    =====================================
    */
    if(command == "rsa")
    {
        auto key =
            generateRSA();

        std::cout
        << "{"
        << "\"p\":"
        << key.p
        << ","
        << "\"q\":"
        << key.q
        << ","
        << "\"n\":"
        << key.n
        << ","
        << "\"e\":"
        << key.e
        << ","
        << "\"d\":"
        << key.d
        << "}";

        return 0;
    }

    /*
    =====================================
    REGISTER USER
    =====================================
    */
    if(command == "register")
    {
        if(argc < 3)
        {
            std::cerr
            << "{\"error\":\"missing_username\"}";
            return 1;
        }

        std::string username =
            argv[2];

        bool success =
            registerUser(username);

        if(success)
        {
            std::ofstream log(
                "database/register_logs.csv",
                std::ios::app);

            log
            << username
            << "\n";
        }

        std::cout
        << "{"
        << "\"success\":"
        << (success ? "true" : "false")
        << "}";

        return 0;
    }

    /*
    =====================================
    AUTHENTICATE USER
    =====================================
    */
    if(command == "auth")
    {
        if(argc < 3)
        {
            std::cerr
            << "{\"error\":\"missing_username\"}";
            return 1;
        }

        std::string username =
            argv[2];

        bool success =
            authenticateUser(username);

        std::ofstream log(
            "database/auth_logs.csv",
            std::ios::app);

        log
        << username
        << ","
        << (success ?
            "SUCCESS" :
            "FAILED")
        << "\n";

        std::cout
        << "{"
        << "\"authenticated\":"
        << (success ?
            "true" :
            "false")
        << "}";

        return 0;
    }

    /*
    =====================================
    SYSTEM STATS
    =====================================
    */
    if(command == "stats")
    {
        SystemStats s =
            getStats();

        std::cout
        << "{"
        << "\"users\":"
        << s.users
        << ","
        << "\"attempts\":"
        << s.authAttempts
        << ","
        << "\"success\":"
        << s.successfulAuths
        << "}";

        return 0;
    }

    /*
    =====================================
    UNKNOWN COMMAND
    =====================================
    */
    std::cerr
    << "{\"error\":\"unknown_command\"}";

    return 1;
}
