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
* generic_log audiences header
*
* This file contains the audience definitions.\n
*/

#pragma once

#include <string>

namespace logger
{
    namespace audience
    {
        struct developer {};
        struct support   {};
        struct user      {};

        template< typename _Audience >
        std::string const get_name(_Audience const audience)
        {
            return std::move(std::string("Unknown audience"));
        }

        template< >
        std::string const get_name< audience::developer >(audience::developer const audience)
        {
            return std::move(std::string("Developer"));
        }

        template< >
        std::string const get_name< audience::support >(audience::support const audience)
        {
            return std::move(std::string("Support"));
        }

        template< >
        std::string const get_name< audience::user >(audience::user const audience)
        {
            return std::move(std::string("User"));
        }
    }

}