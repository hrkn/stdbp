/*
 * system_error‎.hpp
 *
 *  Created on: 2013/02/15
 *      Author: hrkn
 */

#ifndef STDBP_STD11_SYSTEM_ERROR_HPP_
#define STDBP_STD11_SYSTEM_ERROR_HPP_

#include <cstring>
#include <string>
#include <stdexcept>
#include <functional>

#include "std11/type_traits.hpp"
#include "std11/language_extension/enum_class.hpp"
#include "std11/internal/noncopyable.hpp"

namespace std11
{

class error_condition;
class error_code;
class error_category: noncopyable
{
public:
	error_category(void) {}
	virtual ~error_category(void) throw () {}

	virtual char const* name(void) const throw () =0;
//	virtual error_condition default_error_condition(int ev) const throw ()
//	{
//		return error_condition(ev, *this);
//	}
//
//	virtual bool equivalent(int code, error_condition const& condition) const throw ()
//	{
//		return default_error_condition(code) == condition;
//	}
//	virtual bool equivalent(error_code const& code, int condition) const throw ()
//	{
//		return *this == code.category() && code.value() == condition;
//	}

	virtual std::string message(int ev) const =0;

	bool operator==(error_category const& rhs) const throw ()
	{
		return this == &rhs;
	}
	bool operator!=(error_category const& rhs) const throw ()
	{
		return !(*this == rhs);
	}
	bool operator<(error_category const& rhs) const throw ()
	{
		return std::less<const error_category*>()(this, &rhs);
	}
};

namespace detail
{

class generic_category: public error_category
{
	virtual char const* name(void) const throw ()
	{
		return "generic";
	}
	virtual std::string message(int ev) const
	{
		return std::string(std::strerror(ev));
	}
};

class system_category: public error_category
{
	virtual char const* name(void) const throw ()
	{
		return "system";
	}
	virtual std::string message(int ev) const
	{
		return std::string(std::strerror(ev));
	}
};

}  // namespace detail

const error_category& generic_category(void) throw ()
{
	static detail::generic_category const category;
	return category;
};

const error_category& system_category(void) throw ()
{
	static detail::system_category const category;
	return category;
};


class error_code
{
	// TODO
};

class error_condition
{
	// TODO
};

class system_error : public std::runtime_error
{
	// TODO
};

template <class T>
struct is_error_code_enum : public false_type {};

template <class T>
struct is_error_condition_enum : public false_type {};

struct errc: enum_class<errc>
{
	errc(int v): enum_class<errc>(v) {}

	static errc const
		address_family_not_supported,
		address_in_use,
		address_not_available,
		already_connected,
		argument_list_too_long,
		argument_out_of_domain,
		bad_address,
		bad_file_descriptor,
		bad_message,
		broken_pipe,
		connection_aborted,
		connection_already_in_progress,
		connection_refused,
		connection_reset,
		cross_device_link,
		destination_address_required,
		device_or_resource_busy,
		directory_not_empty,
		executable_format_error,
		file_exists,
		file_too_large,
		filename_too_long,
		function_not_supported,
		host_unreachable,
		identifier_removed,
		illegal_byte_sequence,
		inappropriate_io_control_operation,
		interrupted,
		invalid_argument,
		invalid_seek,
		io_error,
		is_a_directory,
		message_size,
		network_down,
		network_reset,
		network_unreachable,
		no_buffer_space,
		no_child_process,
		no_link,
		no_lock_available,
		no_message_available,
		no_message,
		no_protocol_option,
		no_space_on_device,
		no_stream_resources,
		no_such_device_or_address,
		no_such_device,
		no_such_file_or_directory,
		no_such_process,
		not_a_directory,
		not_a_socket,
		not_a_stream,
		not_connected,
		not_enough_memory,
		not_supported,
		operation_canceled,
		operation_in_progress,
		operation_not_permitted,
		operation_not_supported,
		operation_would_block,
		owner_dead,
		permission_denied,
		protocol_error,
		protocol_not_supported,
		read_only_file_system,
		resource_deadlock_would_occur,
		resource_unavailable_try_again,
		result_out_of_range,
		state_not_recoverable,
		stream_timeout,
		text_file_busy,
		timed_out,
		too_many_files_open_in_system,
		too_many_files_open,
		too_many_links,
		too_many_symbolic_link_levels,
		value_too_large,
		wrong_protocol_type;
};

template <>
struct is_error_condition_enum<errc> : public is_enum<errc> {};

//error_code make_error_code(errc e) throw ()
//{
//	return error_code(static_cast<int>(e), generic_category());
//}

//error_condition make_error_condition(errc e) throw ()
//{
//	return error_condition(static_cast<int>(e), generic_category());
//}


// TODO separate compilation unit
#include <errno.h>

errc const errc::address_family_not_supported(EAFNOSUPPORT);
errc const errc::address_in_use(EADDRINUSE);
errc const errc::address_not_available(EADDRNOTAVAIL);
errc const errc::already_connected(EISCONN);
errc const errc::argument_list_too_long(E2BIG);
errc const errc::argument_out_of_domain(EDOM);
errc const errc::bad_address(EFAULT);
errc const errc::bad_file_descriptor(EBADF);
errc const errc::bad_message(EBADMSG);
errc const errc::broken_pipe(EPIPE);
errc const errc::connection_aborted(ECONNABORTED);
errc const errc::connection_already_in_progress(EALREADY);
errc const errc::connection_refused(ECONNREFUSED);
errc const errc::connection_reset(ECONNRESET);
errc const errc::cross_device_link(EXDEV);
errc const errc::destination_address_required(EDESTADDRREQ);
errc const errc::device_or_resource_busy(EBUSY);
errc const errc::directory_not_empty(ENOTEMPTY);
errc const errc::executable_format_error(ENOEXEC);
errc const errc::file_exists(EEXIST);
errc const errc::file_too_large(EFBIG);
errc const errc::filename_too_long(ENAMETOOLONG);
errc const errc::function_not_supported(ENOSYS);
errc const errc::host_unreachable(EHOSTUNREACH);
errc const errc::identifier_removed(EIDRM);
errc const errc::illegal_byte_sequence(EILSEQ);
errc const errc::inappropriate_io_control_operation(ENOTTY);
errc const errc::interrupted(EINTR);
errc const errc::invalid_argument(EINVAL);
errc const errc::invalid_seek(ESPIPE);
errc const errc::io_error(EIO);
errc const errc::is_a_directory(EISDIR);
errc const errc::message_size(EMSGSIZE);
errc const errc::network_down(ENETDOWN);
errc const errc::network_reset(ENETRESET);
errc const errc::network_unreachable(ENETUNREACH);
errc const errc::no_buffer_space(ENOBUFS);
errc const errc::no_child_process(ECHILD);
errc const errc::no_link(ENOLINK);
errc const errc::no_lock_available(ENOLCK);
errc const errc::no_message_available(ENODATA);
errc const errc::no_message(ENOMSG);
errc const errc::no_protocol_option(ENOPROTOOPT);
errc const errc::no_space_on_device(ENOSPC);
errc const errc::no_stream_resources(ENOSR);
errc const errc::no_such_device_or_address(ENXIO);
errc const errc::no_such_device(ENODEV);
errc const errc::no_such_file_or_directory(ENOENT);
errc const errc::no_such_process(ESRCH);
errc const errc::not_a_directory(ENOTDIR);
errc const errc::not_a_socket(ENOTSOCK);
errc const errc::not_a_stream(ENOSTR);
errc const errc::not_connected(ENOTCONN);
errc const errc::not_enough_memory(ENOMEM);
errc const errc::not_supported(ENOTSUP);
errc const errc::operation_canceled(ECANCELED);
errc const errc::operation_in_progress(EINPROGRESS);
errc const errc::operation_not_permitted(EPERM);
errc const errc::operation_not_supported(EOPNOTSUPP);
errc const errc::operation_would_block(EWOULDBLOCK);
errc const errc::owner_dead(EOWNERDEAD);
errc const errc::permission_denied(EACCES);
errc const errc::protocol_error(EPROTO);
errc const errc::protocol_not_supported(EPROTONOSUPPORT);
errc const errc::read_only_file_system(EROFS);
errc const errc::resource_deadlock_would_occur(EDEADLK);
errc const errc::resource_unavailable_try_again(EAGAIN);
errc const errc::result_out_of_range(ERANGE);
errc const errc::state_not_recoverable(ENOTRECOVERABLE);
errc const errc::stream_timeout(ETIME);
errc const errc::text_file_busy(ETXTBSY);
errc const errc::timed_out(ETIMEDOUT);
errc const errc::too_many_files_open_in_system(ENFILE);
errc const errc::too_many_files_open(EMFILE);
errc const errc::too_many_links(EMLINK);
errc const errc::too_many_symbolic_link_levels(ELOOP);
errc const errc::value_too_large(EOVERFLOW);
errc const errc::wrong_protocol_type(EPROTOTYPE);

}  // namespace std11

#endif /* STDBP_STD11_SYSTEM_ERROR_HPP_ */
