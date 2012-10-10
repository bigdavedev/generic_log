//=============================
///
/// generic_log library
///
/// Copyright Dave Brown \n
/// Distributed under the Boost Software License, Version 1.0.\n
///    (See accompanying file LICENSE_1_0.txt or copy at\n
///     http://www.boost.org/LICENSE_1_0.txt)\n
///
/// see https://github.com/bigdavedev/generic_log for more info\n
///
//=============================

//=============================
/// 
/// \file
/// generic_log audiences header
///
/// This file contains the audience definitions.\n
//=============================

#pragma once

#include <string>
#include <tuple>

namespace logger
{
    namespace audience
    {
        //=============================
        /// Audience tags
        //=============================
        struct developer {}; ///< For messages aimed at developers
        struct support   {}; ///< For messages aimed at support teams
        struct user      {}; ///< For messages aimed at end users

        //=============================
        /// Type list for audiences
        ///
        /// This list will help later when filtering log messages.
        /// For example, if we set the first two parameters to support
        /// and user, then any message passing in to the logging stream
        /// that have developer as their target audience, should
        /// dissappear from the code altogether at compiler time, meaning
        /// that we reduce the need for pre-processor statements.
        //=============================
        template
        < 
            typename _Audience1, 
            typename _Audience2 = std::tr1::_Nil, 
            typename _Audience3 = std::tr1::_Nil 
        >
        struct audience_list : std::tuple< _Audience1, _Audience2, _Audience3 >
        {
        };

        //=============================
        /// RTTI function for retrieving name of audience.
        ///
        /// If the need arises, it is possible to retrieve a string
        /// containing the name of the target audience.
        /// \verbatim
        /// using logger;
        /// std::cout << audience::get_name(audience::developer());
        /// \endverbatim
        //=============================
        template< typename _Audience >
        std::string const get_name(_Audience const audience)
        {
            return std::move(std::string("Unknown audience"));
        }

        //=============================
        /// Specialisation for developer audience tag
        //=============================
        template< >
        std::string const get_name< audience::developer >(audience::developer const audience)
        {
            return std::move(std::string("Developer"));
        }
        
        //=============================
        /// Specialisation for support audience tag
        //=============================
        template< >
        std::string const get_name< audience::support >(audience::support const audience)
        {
            return std::move(std::string("Support"));
        }
        
        //=============================
        /// Specialisation for support audience tag
        //=============================
        template< >
        std::string const get_name< audience::user >(audience::user const audience)
        {
            return std::move(std::string("User"));
        }
    }

}