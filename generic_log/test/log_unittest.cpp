#include "..\logging.hpp"
#include <iostream>
#include <sstream>
#define NOMINMAX
#include <Windows.h>

namespace test
{
    struct test_writer
    {
    public:
        static void begin_write()
        {
            ::OutputDebugString(WIDEN("Starting to test the default formatting policy\n"));
            ::OutputDebugString(WIDEN("//=====================\n"));
        }

        static void end_write()
        {
            ::OutputDebugString(WIDEN("\n"));
            ::OutputDebugString(WIDEN("//=====================\n"));
            ::OutputDebugString(WIDEN("Test over.\n"));
        }

        template< typename _Type >
        static void write(_Type const parameter)
        {
            logger::stringstream buffer;
            buffer << parameter;
            ::OutputDebugString(buffer.str().c_str());
        }
        
        template< >
        static void write(wchar_t const* parameter)
        {
            logger::stringstream buffer;
            buffer << parameter;
            ::OutputDebugString(buffer.str().c_str());
        }
    };

    bool test_log()
    {
        using namespace logger;

        auto audience_members = std::make_tuple(audience::developer(), audience::support());
        auto severity = std::make_tuple(severity::debug());
        visualstudio_formatter::write_message< test_writer >(__FILE__, __LINE__, audience_members, severity, std::make_tuple("Hello", "World", 256, 512.5f));
        return true;
    }
}

#include <limits>

namespace 
{
    void pause_console()
    {
        std::cout << "Press ENTER to continue... " << std::flush;
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
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

    const bool result = test::test_log();

    std::cout << "The log tests were " << (result ? "successful" : "unsuccessful") << std::endl;

    pause_console();
}