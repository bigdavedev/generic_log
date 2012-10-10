/**
*
* generic_log library
*
* Copyright Dave Brown \n
* Distributed under the Boost Software License, Version 1.0.\n
*    (See accompanying file LICENSE_1_0.txt or copy at\n
*     http://www.boost.org/LICENSE_1_0.txt)\n
*
* see https://github.com/bigdavedev/generic_log for more info\n
*
*/

/**
* 
* \file
* generic_log severities header
*
* This file contains the severity definitions.\n
*/

#pragma once

#include <string>

namespace logger
{
    namespace severity
    {
        struct fatal   {};
        struct error   {};
        struct warning {};
        struct message {};
        struct info    {};
        struct debug   {};

        template< typename _Severity >
        std::string const get_name(_Severity const severity)
        {
            return std::move(std::string("Unknown severity level"));
        }

        template< >
        std::string const get_name< severity::fatal >(severity::fatal const severity)
        {
            return std::move(std::string("Fatal"));
        }

        template< >
        std::string const get_name< severity::error >(severity::error const severity)
        {
            return std::move(std::string("Error"));
        }

        template< >
        std::string const get_name< severity::warning >(severity::warning const severity)
        {
            return std::move(std::string("Warning"));
        }

        template< >
        std::string const get_name< severity::message >(severity::message const severity)
        {
            return std::move(std::string("Message"));
        }

        template< >
        std::string const get_name< severity::info >(severity::info const severity)
        {
            return std::move(std::string("Info"));
        }

        template< >
        std::string const get_name< severity::debug >(severity::debug const severity)
        {
            return std::move(std::string("Debug"));
        }
    }
}