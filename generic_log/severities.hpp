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
/// generic_log severities header
///
/// This file contains the severity definitions.\n
//=============================

#pragma once

#include "config.h"

namespace logger
{
    namespace severity
    {
        
        //=============================
        /// Error level tags
        //=============================
        struct fatal   {}; ///< Fatal error filter
        struct error   {}; ///< Recoverable error filter
        struct warning {}; ///< Warning filter
        struct info    {}; ///< For passing info based messages through the logging system
        struct debug   {}; ///< For debugging purposes - often used with the developer audience.
        
        //=============================
        /// RTTI function for retrieving name of the severity.
        ///
        /// If the need arises, it is possible to retrieve a string
        /// containing the name of the message's severity.
        /// \verbatim
        /// using logger;
        /// std::cout << severity::get_name(severity::debug());
        /// \endverbatim
        //=============================
        template< typename _Severity >
        string const get_name(_Severity const severity)
        {
            return std::move(string(WIDEN("Unknown severity level")));
        }
        
        //=============================
        /// Specialisation for fatal error tag
        //=============================
        template< >
        string const get_name< severity::fatal >(severity::fatal const severity)
        {
            return std::move(string(WIDEN("Fatal")));
        }
        
        //=============================
        /// Specialisation for error tag
        //=============================
        template< >
        string const get_name< severity::error >(severity::error const severity)
        {
            return std::move(string(WIDEN("Error")));
        }
        
        //=============================
        /// Specialisation for the warning tag
        //=============================
        template< >
        string const get_name< severity::warning >(severity::warning const severity)
        {
            return std::move(string(WIDEN("Warning")));
        }
        
        //=============================
        /// Specialisation for the info tag
        //=============================
        template< >
        string const get_name< severity::info >(severity::info const severity)
        {
            return std::move(string(WIDEN("Info")));
        }
        
        //=============================
        /// Specialisation for the debug tag
        //=============================
        template< >
        string const get_name< severity::debug >(severity::debug const severity)
        {
            return std::move(string(WIDEN("Debug")));
        }
    }
}