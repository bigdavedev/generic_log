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
/// generic_log writing policy header
///
/// This file contains the writing policy definitions.\n
//=============================

#pragma once

#include "config.h"

namespace logger
{
    //=============================
    /// A list of supported writing policies
    ///
    /// -- Visual Studio output window
    /// -- stdout
    /// -- fstream
    /// -- Custom window
    //=============================
    
    //=============================
    /// Writers must implement the following public interface:
    ///
    /// -- static void begin_write()
    /// -- static void end_write()
    /// -- template< typename _Type > static void write(_Type const message)
    //=============================

    //=============================
    /// Default writer outputs to stdout
    //=============================
    struct default_writer
    {
        static void begin_write()
        {
        }

        static void end_write()
        {
            std::cout << std::flush;
        }

        template< typename _Type >
        static void write(_Type const message)
        {
            std::cout << message;
        }
    };

#if defined (WIN32) || defined (_WIN32)
#define NOMINMAX
#include <Windows.h>

    //=============================
    /// Output to the Visual Studio spew
    ///
    /// The cool thing with this is that, when used
    /// with the visualstudio_formatter, we can
    /// double click and navigate to the line where
    /// the logger was invoked.
    //=============================
    struct visualstudio_writer
    {
        static void begin_write()
        {
        }

        static void end_write()
        {
            OutputDebugString(WIDEN("\n"));
        }

        template< typename _Type >
        static void write(_Type const message)
        {
            stringstream buffer;
            buffer << message;
            OutputDebugString(buffer.str().c_str());
        }
    };
#endif
}