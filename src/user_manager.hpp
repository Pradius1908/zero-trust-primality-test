#pragma once

#include <string>

bool registerUser(const std::string& username);

bool authenticateUser(const std::string& username);
