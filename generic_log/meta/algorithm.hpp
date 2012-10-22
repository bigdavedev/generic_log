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
/// generic_log meta algorithm header
///
/// This file contains meta functions for unpacking
/// parameter packs amongst other utilities.
//=============================

#pragma once

#include <tuple>

namespace logger
{
    namespace meta
    {
        //=============================
        /// Loop over tuple at compile time.
        ///
        /// Using this function we should be able to,
        /// at compile time, retrieve each element in
        /// a given tuple and call a function on it.
        //=============================
        template
        <
            typename _Tuple,                                       ///< The tuple to iterate over
            typename _Function,                                    ///< The function that will operate on each element
            size_t   _Index = std::tuple_size< _Tuple >::value - 1     ///< The length of the tuple
        >
        struct for_each
        {
            static void apply(_Tuple const tuple, _Function function)
            {
                // Retrieve each element from the tuple.
                typedef typename std::tuple_element< _Index, _Tuple >::type element_type;
                element_type element = std::get< _Index >(tuple);

                // Operate on it
                function(element);

                // Continue recursion - "looping"
                for_each< _Tuple, _Function, _Index - 1 >::apply(tuple, function);
            }
        };

        //=============================
        /// Specialisation to end recursion.
        //=============================
        template
        <
            typename _Tuple,
            typename _Function
        >
        struct for_each< _Tuple, _Function, 0 >
        {
            static void apply(_Tuple const tuple, _Function function)
            {
                typedef typename std::tuple_element< 0, _Tuple >::type element_type;
                function(std::get< 0 >(tuple));
            }
        };
    }
}