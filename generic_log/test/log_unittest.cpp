#include "..\logging.hpp"
#include <iostream>

namespace
{
    bool test_log()
    {
        return true;
    }
}

#include <limits>

namespace 
{
    void pause_console()
    {
        std::cout << "Press ENTER to continue... " << std::flush;
        std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
    }
}

int main()
{
    std::cout << "**********************************************************\n";
    std::cout << "**********************************************************\n";
    std::cout << "*                             _          _               *\n";
    std::cout << "*   __ _  ___ _ __   ___ _ __(_) ___    | | ___   __ _   *\n";
    std::cout << "*  / _` |/ _ \\ '_ \\ / _ \\ '__| |/ __|   | |/ _ \\ / _` |  *\n";
    std::cout << "* | (_| |  __/ | | |  __/ |  | | (__    | | (_) | (_| |  *\n";
    std::cout << "*  \\__, |\\___|_| |_|\\___|_|  |_|\\___|___|_|\\___/ \\__, |  *\n";
    std::cout << "*  |___/                           |_____|       |___/   *\n";
    std::cout << "*                     _ _     _            _             *\n";
    std::cout << "*         _   _ _ __ (_) |_  | |_ ___  ___| |_           *\n";
    std::cout << "*        | | | | '_ \\| | __| | __/ _ \\/ __| __|          *\n";
    std::cout << "*        | |_| | | | | | |_  | ||  __/\\__ \\ |_           *\n";
    std::cout << "*         \\__,_|_| |_|_|\\__|  \\__\\___||___/\\__|          *\n";
    std::cout << "*                                                        *\n";
    std::cout << "**********************************************************\n";
    std::cout << "**********************************************************\n";

    const bool result = test_log();

    pause_console();
}