#include <iostream>
#include <time.h>
#include <string>

#define Debug 0
#define Error 1

const std::string com[] = {
    "Debug",
    "Error"};

std::ostream &Log(int command)
{
    std::cout << "[" << (unsigned)time(nullptr) << "]:"
              << "[" << com[command] << "]" <
        " ";
    return std::cout;
}