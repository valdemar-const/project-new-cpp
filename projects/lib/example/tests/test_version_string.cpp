#include <example/example.hpp>

#include <cstdlib>
#include <cassert>

int
main(
        int         argc,
        const char *argv[]
)
{
    assert("1.0" == example::version_string());

    return EXIT_SUCCESS;
}
