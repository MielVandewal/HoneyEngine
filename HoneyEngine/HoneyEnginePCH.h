#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winerror.h>
#include "../Libs/d3dx12.h"

template<class T>
void SafeDelete(T& toDelete)
{
    if (toDelete)
    {
        delete toDelete;
        toDelete = nullptr;
    }
}

template<class T>
void SafeDeleteArray(T& toDelete)
{
    if (toDelete)
    {
        delete[] toDelete;
        toDelete = nullptr;
    }
}