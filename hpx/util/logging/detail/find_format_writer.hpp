// logger_to_writer.hpp

// Boost Logging library
//
// Author: John Torjo, www.torjo.com
//
// Copyright (C) 2007 John Torjo (see www.torjo.com for email)
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.
// See http://www.torjo.com/log2/ for more details


#ifndef JT28092007_logger_to_writer_HPP_DEFINED
#define JT28092007_logger_to_writer_HPP_DEFINED

#include <hpx/util/logging/detail/fwd.hpp>
#include <hpx/util/logging/format_fwd.hpp>
#include <memory>
#include <string>

namespace hpx { namespace util { namespace logging {

// ... the hard part - for logger_format_write

namespace formatter {
    template< class arg_type, class ptr_type_> struct base ;
}

namespace destination {
    template< class arg_type, class ptr_type_> struct base ;
}

namespace msg_route {
    template<class formatter_base, class destination_base > struct simple ;
    template<class formatter_base, class destination_base,
    class formatter_array, class destination_array> class with_route;
}

namespace format_and_write {
    template<class msg_type> struct simple ;

    template<class formatter_base, class destination_base,
    class msg_type> struct use_cache ;
}
namespace array {
    template <class base_type > class shared_ptr_holder ;
}

namespace writer {
    template<
            class formatter_base,
            class destination_base,
            class apply_format_and_write ,
            class router_type ,
            class formatter_array ,
            class destination_array >
    struct format_write ;
}


namespace detail {

    //////////// find_format_write_params
    template<class string, class formatter_base, class destination_base>
        struct find_format_write_params {
        typedef typename ::hpx::util::logging::format_and_write::simple<string>
            apply_format_and_write ;
        typedef typename ::hpx::util::logging::msg_route::simple<formatter_base,
            destination_base> router_type;
    };
}


namespace detail {
    template< class format_base_type , class destination_base_type >
        struct format_find_writer {

        typedef ::hpx::util::logging::optimize::cache_string_one_str format_msg_type;
        typedef std::string destination_msg_type;

        typedef ::hpx::util::logging::formatter::base< default_, default_ >
            default_format_base;
        typedef ::hpx::util::logging::destination::base< default_, default_ >
            default_destination_base;

        typedef typename use_default<format_base_type, default_format_base >
            ::type format_base;
        typedef typename use_default<destination_base_type, default_destination_base >
            ::type destination_base;

        typedef typename detail::find_format_write_params<format_msg_type,
            format_base, destination_base >
            ::apply_format_and_write apply_format_and_write;
        typedef typename detail::find_format_write_params<format_msg_type,
            format_base, destination_base >::router_type router_type;

        typedef ::hpx::util::logging::array::shared_ptr_holder<format_base >
            formatter_array ;
        typedef ::hpx::util::logging::array::shared_ptr_holder<destination_base >
            destination_array ;

        typedef writer::format_write<
            format_base,
            destination_base,
            apply_format_and_write,
            router_type,
            formatter_array,
            destination_array > type;
    };
}

}}}

#endif
