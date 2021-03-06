#ifndef __GLOBALS_HPP__
#define __GLOBALS_HPP__

#include "primary_app.hpp"

namespace prim
{
    struct Globals
    {
        static inline PrimaryApp* app = nullptr;
        static inline Renderer* mainRenderer = nullptr;
    };
}

#endif // __GLOBALS_HPP__