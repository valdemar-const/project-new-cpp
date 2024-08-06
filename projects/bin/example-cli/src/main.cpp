#include <example/example.hpp>

#include <iostream>

int
main(
        int         argc,
        char const *argv[]
)
{
    std::cout << example::version_string() << std::endl;
    return 0;
}
