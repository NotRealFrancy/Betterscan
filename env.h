#pragma once
#ifndef DOTENV_H
#define DOTENV_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "inputs.h"
#include "getos.h"
#include <cstdlib>
#include <stdlib.h>
inline std::string getEnvironmentVariable(const char* name) {
    char* value;
    size_t len;
    if (_dupenv_s(&value, &len, name) == 0 && value != nullptr) {
        std::string result(value);
        free(value);
        return result;
    }
    return "";
}
inline std::string setEnvironmentVariable(const char* name, const char* value)
{
    string os = getos();
    if (os == "Windows")
    {
        _putenv_s(name, value);
    }
    else
    {
        // setenv(name, value, 1);
    }
    return "";
}
inline std::vector<std::string> getAllEnvironmentVariables()
{
    std::vector<std::string> environmentVariables;
    for (char** env = _environ; *env != nullptr; ++env)
    {
        environmentVariables.push_back(*env);
    }
    return environmentVariables;
}
inline bool containsEnvKey(const char* name)
{
    std::vector<std::string> envvars = getAllEnvironmentVariables();
    for (const string& envvar : envvars)
    {
        vector<string> strings = splitInput(envvar, '=');
        if (strings[0] == name)
        {
            return true;
        }
    }
    return false;
}
#endif