#pragma once

#ifndef GETOS_H
#define GETOS_H
#include <string>
inline std::string getos()
{
#if defined(_WIN32)
    return "Windows";
#elif defined(__linux__)
    return "Linux";
#elif defined(__APPLE__) && defined(__MACH__)
    return "Mac OS";
#else
    return "Unknown";
#endif
}
#include <iostream>
inline const char* getsystembit()
{
    if (sizeof(void*) == 4)
    {
        return "32 bit";
    }
    else if (sizeof(void*) == 8)
    {
        return "64 bit";
    }
    else
    {
        return "Unknown";
    }
}
#endif