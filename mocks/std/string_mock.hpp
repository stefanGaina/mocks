/******************************************************************************************************
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
 * software, either in source code form or as a compiled binary, for any purpose,
 * commercial or non-commercial, and by any means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors of this
 * software dedicate any and all copyright interest in the software to the public
 * domain. We make this dedication for the benefit of the public at large and to
 * the detriment of our heirs and successors. We intend this dedication to be an
 * overt act of relinquishment in perpetuity of all present and future rights to
 * this software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * For more information, please refer to <http://unlicense.org>
 *****************************************************************************************************/

#ifndef STD_STRING_MOCK_HPP_
#define STD_STRING_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "string_begin.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace std
{

class string
{
public:
	string(void) noexcept = default;
	string(const string& string_) noexcept(false);
	string(string&& string_) noexcept;
	string(const char* cstring) noexcept(false);
	void operator=(const string& string_) noexcept(false);
	const char* c_str(void) const noexcept;
};

string operator+(const string& string_, const char* cstring) noexcept(false);
string to_string(int __val) noexcept;

} /*< namespace std */

namespace mock
{

class string_interface
{
public:
	virtual ~string_interface(void) noexcept = default;

	virtual void		copy_constructor(const std::string& string_)				   = 0;
	virtual void		move_constructor(std::string&& string_)						   = 0;
	virtual void		constructor(const char*)									   = 0;
	virtual std::string operator_plus(const std::string& string_, const char* cstring) = 0;
	virtual const char* c_str(void)													   = 0;
	virtual void		operator_equal(const std::string& string_)					   = 0;
	virtual std::string to_string(int __val)										   = 0;
};

class string_mock : public string_interface
{
public:
	string_mock(void)
	{
		object = this;
	}

	virtual ~string_mock(void)
	{
		object = nullptr;
	}

	MOCK_METHOD1(copy_constructor, void(const std::string&));
	MOCK_METHOD1(move_constructor, void(std::string&&));
	MOCK_METHOD1(constructor, void(const char*));
	MOCK_METHOD2(operator_plus, std::string(const std::string&, const char*));
	MOCK_METHOD0(c_str, const char*(void));
	MOCK_METHOD1(operator_equal, void(const std::string&));
	MOCK_METHOD1(to_string, std::string(int));

public:
	static string_mock* object;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

string_mock* string_mock::object = nullptr;

} /*< namespace mock */

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace std
{

string::string(const string& string_) noexcept(false)
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "copy_constructor(): nullptr == mock::string_mock::object";
		return;
	}
	mock::string_mock::object->copy_constructor(string_);
}

string::string(string&& string_) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "move_constructor(): nullptr == mock::string_mock::object";
		return;
	}
	mock::string_mock::object->move_constructor(std::move(string_));
}

string::string(const char* const cstring) noexcept(false)
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "constructor(): nullptr == mock::string_mock::object";
		return;
	}
	mock::string_mock::object->constructor(cstring);
}

void string::operator=(const string& string_) noexcept(false)
{
	ASSERT_NE(nullptr, mock::string_mock::object) << "operator_equal(): nullptr == mock::string_mock::object";
	return mock::string_mock::object->operator_equal(string_);
}

const char* string::c_str(void) const noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "c_str(): nullptr == mock::string_mock::object";
		return nullptr;
	}
	return mock::string_mock::object->c_str();
}

string operator+(const string& string_, const char* const cstring) noexcept(false)
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "operator_plus(): nullptr == mock::string_mock::object";
		return string{};
	}
	return mock::string_mock::object->operator_plus(string_, cstring);
}

string to_string(const int __val) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "to_string(): nullptr == mock::string_mock::object";
		return string{};
	}
	return mock::string_mock::object->to_string(__val);
}

} /*< namespace std */

#include "string_end.hpp"

#endif /*< STD_STRING_MOCK_HPP_ */
