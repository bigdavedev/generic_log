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
#include "meta\meta.hpp"

#include <functional>

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
        typedef typename _DerivedFormatter formatter; ///< Convenience typedef
        typedef base_formatting_policy< formatter > this_type;

        //=============================
        /// Function for sending messages to the desired
        /// output.
        ///
        /// We need to explicitly supply the writing policy
        /// as a template parameter since the formatter
        /// doesn't, and rightfully shouldn't have a clue
        /// about where the message is headed. Here we prepare
        /// the write policy before passing the work of
        /// formatting on to the derived class.  We also need
        /// to inform the write policy that we are done formatting.
        //=============================
        template
        < 
            typename _WritingPolicy, ///< Eventual output location of message
            typename _AudienceList,  ///< The people who should be interested
            typename _Severity,      ///< Log message level
            typename _ParameterList  ///< Tuple of parameters to insert
        >
        static void write_message(char const* filename, unsigned int const linenumber, _AudienceList audience_list, _Severity severity_list, _ParameterList parameter_list)
        {
            typename _WritingPolicy::begin_write();

            formatter::write< typename _WritingPolicy >(filename, linenumber, audience_list, severity_list, parameter_list);

            typename _WritingPolicy::end_write();
        }

    protected:
        template
        <
            typename _WritingPolicy, ///< Where to send the parameters
            typename _ParameterPack,  ///< A tuple containing all the parameters
            std::size_t _Index
        >
        struct write_params
        {
            static void apply(_ParameterPack parameters)
            {
                write_params< typename _WritingPolicy, _ParameterPack, _Index - 1 >::apply(parameters);
                write_obj< typename _WritingPolicy >(std::get< _Index >(parameters));
                write_obj< typename _WritingPolicy >(" ");
            }
        };
        
        template
        <
            typename _WritingPolicy, ///< Where to send the parameters
            typename _ParameterPack  ///< A tuple containing all the parameters
        >
        struct write_params< _WritingPolicy, _ParameterPack, 0 >
        {
            static void apply(_ParameterPack parameters)
            {
                write_obj< typename _WritingPolicy >(std::get< 0 >(parameters));
                write_obj< typename _WritingPolicy >(" ");
            }
        };

        template
        <
            typename _WritingPolicy,
            typename _Type
        >
        static void write_obj(_Type object)
        {
            typename _WritingPolicy::write(object);
        }

    private:
        template
        <
            typename _WritingPolicy,
            typename _Type
        >
        static void write_param(_Type parameter)
        {
            typename _WritingPolicy::write(parameter);
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
        static void write(char const* filename, unsigned int const linenumber, _AudienceList audience_list, _Severity severity_list, _ParameterList parameter_list)
        {
            write_obj< typename _WritingPolicy >(audience::get_name(std::get<0>(audience_list)));
            write_obj< typename _WritingPolicy >(':');
            write_obj< typename _WritingPolicy >(severity::get_name(std::get<0>(severity_list)));
            write_obj< typename _WritingPolicy >(" in ");
            write_obj< typename _WritingPolicy >(filename);
            write_obj< typename _WritingPolicy >('@');
            write_obj< typename _WritingPolicy >(linenumber);
            write_obj< typename _WritingPolicy >(" - ");

            write_params< typename _WritingPolicy, _ParameterList, std::tuple_size< _ParameterList >::value - 1 >::apply(parameter_list);
        }
    };

    class visualstudio_formatter
        : public base_formatting_policy< visualstudio_formatter >
    {
    public:
        template
        < 
            typename _WritingPolicy, ///< Eventual output location of message
            typename _AudienceList,  ///< The people who should be interested
            typename _Severity,      ///< Log message level
            typename _ParameterList  ///< Tuple of parameters to insert
        >
        static void write(char const* filename, unsigned int const linenumber, _AudienceList audience_list, _Severity severity_list, _ParameterList parameter_list)
        {
            write_obj< typename _WritingPolicy >(filename);
            write_obj< typename _WritingPolicy >("(");
            write_obj< typename _WritingPolicy >(linenumber);
            write_obj< typename _WritingPolicy >("): ");
            write_obj< typename _WritingPolicy >(severity::get_name(std::get<0>(severity_list)));
            write_obj< typename _WritingPolicy >(": ");

            write_params< typename _WritingPolicy, _ParameterList, std::tuple_size< _ParameterList >::value - 1 >::apply(parameter_list);
        }
    };
}