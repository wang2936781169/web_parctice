#include <common.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void Perror(const std::string& errorMes)
{
    perror(errorMes.c_str());
    exit(1);
}