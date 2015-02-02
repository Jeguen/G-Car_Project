// Copyright © 2012, 2014 Lénaïc Bagnères, hnc@singularity.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef HNC_ASSERT_HPP
#define HNC_ASSERT_HPP

#include <string>
#include <stdexcept>


namespace hnc
{
	/**
	 * @brief Throws the exception if the expression is false
	 *
	 * @code
	   #include <hnc/assert.hpp>
	   @endcode
	 * 
	 * If the expression if false, throws the exception @n
	 * Else, do nothing
	 *
	 * You can combine with NDEBUG macro
	 * @code
	   #ifndef NDEBUG
	   hnc::hassert(1 == 1, std::logic_error("1 is not equal 1 !"));
	   #endif
	   @endcode
	 *
	 * @param[in] expression The test (a bool)
	 * @param[in] e          A exception if the test is false
	 *
	 * @exception e if the expression if false
	 */
	template <class Except>
	void hassert(bool const expression, Except const & e)
	{ if (expression == false) { throw e; } }

	/**
	 * @brief Throws the logic_error exception with what message if the expression is false
	 *
	 * @code
	   #include <hnc/assert.hpp>
	   @endcode
	 * 
	 * If the expression if false, throws the logic_error exception with what message @n
	 * Else, do nothing
	 *
	 * You can combine with NDEBUG macro
	 * @code
	   #ifndef NDEBUG
	   hnc::hassert(1 == 1, "1 is not equal 1 !");
	   #endif
	   @endcode
	 *
	 * @param[in] expression Test (a bool)
	 * @param[in] what       Message if the test is false
	 *
	 * @exception std::logic_error(what) if the expression if false
	 */
	inline void hassert(bool const expression, char const * const what)
	{ if (expression == false) { throw std::logic_error(what); } }


	/// @copydoc hnc::hassert(bool const,char const * const)
	inline void hassert(bool const expression, std::string const & what)
	{ if (expression == false) { throw std::logic_error(what); } }
}

#endif
