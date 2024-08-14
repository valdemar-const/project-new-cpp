#include "config.h"
#include <example/example.hpp>

std::string
example::version_string()
{
    return CFG_LIBRARY_VERSION;
}
