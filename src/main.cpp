#include "include/Application.hpp"
#include <iostream>
int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch(std::exception &e)
    {
        std::cout << "\nEXCEPTION CAUGHT: " << e.what() << std::endl;
    }

    return 0;
}
