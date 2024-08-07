#include <example/example.hpp>

#include <iostream>

int
main(
        int         argc,
        const char *argv[]
)
{
    std::cout << example::version_string() << std::endl;
    return 0;
}
