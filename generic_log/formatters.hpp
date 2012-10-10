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
/// generic_log formatting policy header
///
/// This file contains the formatting policy definitions.\n
/// Note that a formatting policy is not necessarily a writing
/// policy.  In generic_log, the formatting policy simply
/// performs text decoration such that the message will be displayed
/// as is deemed appropriate for the environment the code is being
/// run in.  For example, people using Visual Studio may want to
/// have the messages formatted the same way that Visual Studio
/// does to have a more uniform/familiar spew.  Whether or not
/// they choose to display the log output in the Visual Studio
/// output window or not has nothing to do with their preference
/// of formatting.
//=============================

#pragma once

namespace logger
{
    //=============================
    /// A list of supported formatting policies
    ///
    /// -- Visual Studio format
    /// -- GCC format
    /// -- Code::Blocks format
    /// -- Custom format
    //=============================
}