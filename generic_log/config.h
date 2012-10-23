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
/// generic_log configuration header
///
/// This file contains portability code.
///
/// The generic_log library includes this file itself where required.
/// You shouldn't to include this file.
//=============================

#pragma once

#if defined(UNICODE)
#  define WIDEN(x) L##x
#else
#  define WIDEN(x) x
#endif

#if defined(USE_STL_ALLOC)
#  include <string>
#  include <sstream>

namespace logger
{
#if defined(UNICODE)
    typedef std::wstring       string;
    typedef std::wstringstream stringstream;
#else
    typedef std::string       string;
    typedef std::stringstream stringstream;
#endif
}
#endif

