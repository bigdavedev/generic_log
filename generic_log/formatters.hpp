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

//=============================
/// Include any config that may
/// be required.
//=============================
#include "config.h"

//=============================
/// We need to include the audiences
/// and severities so that we may insert
/// them appropriately
//=============================
#include "audiences.hpp"
#include "severities.hpp"

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

    //=============================
    /// Base formatting policy contains functionality that is shared
    /// between all formatters.
    ///
    /// Formatters act as a buffer between the logger and the writing
    /// policy.  Messages that are sent in to the logging stream come
    /// through the formatters after they have been filtered for content.
    /// During this stage we gather up all the info that the message
    /// requires and convert it to the desired format.
    ///
    /// This base class handles inserting parameters and message details
    /// in to the designated output by passing it on to the writing
    /// policy specified in the derived formatting policy.
    //=============================
    template< typename _DerivedFormatter >
    class base_formatting_policy
    {
    public:
        typedef typename _DerivedFormatter formatter;

        template
        < 
            typename _WritingPolicy, ///< Eventual output location of message
            typename _AudienceList,  ///< The people who should be interested
            typename _Severity,      ///< Log message level
            typename _ParameterList  ///< Tuple of parameters to insert
        >
        static void write_message(char const* filename, unsigned int const linenumber, _ParameterList parameter_list)
        {
            typedef typename _WritingPolicy output;
            output::begin_write();

            formatter::write< output, _AudienceList, _Severity >(filename, linenumber, parameter_list);

            output::end_write();
        }

    protected:
        template
        <
            typename _WritingPolicy,
            typename _Type
        >
        static void write_params(_Type parameter)
        {
            _WritePolicy::write(parameter);
        }

        template
        <
            typename _WritingPolicy,
            typename _Type
        >
        static void write_obj(_Type object)
        {
            _WritePolicy::write(object);
        }

    private:
        template
        <
            typename _WritingPolicy,
            typename _Type
        >
        static void write_param(_Type parameter)
        {
            _WritePolicy::write(parameter);
        }
    };


    class default_formatter
        : public base_formatting_policy< default_formatter >
    {
    public:
        template
        < 
            typename _WritingPolicy, ///< Eventual output location of message
            typename _AudienceList,  ///< The people who should be interested
            typename _Severity,      ///< Log message level
            typename _ParameterList  ///< Tuple of parameters to insert
        >
        static void write(char const* filename, unsigned int const linenumber, _ParameterList parameter_list)
        {
            typedef typename _WritingPolicy output;

            write_obj< output >(audience::get_name(_AudienceList.get<0>()));
            write_obj< output >(':');
            write_obj< output >(severity::get_name(_Severity));
            write_obj< output >("in ");
            write_obj< output >(filename);
            write_obj< output >('@');
            write_obj< output >(linenumber);

            write_params< output >(parameter_list);
        }
    };
}