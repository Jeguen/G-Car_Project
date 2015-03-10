// Copyright © 2012-2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_TO_STRING_HPP
#define HNC_TO_STRING_HPP

#include <string>
#include <sstream>
#include <limits>
#include <type_traits>
#include <iomanip>


namespace hnc
{
	/**
	 * @brief Convert a std::ostringstream into a std::string
	 *
	 * @code
	   #include <hnc/to_string.hpp>
	   @endcode
	 *
	 * @param[in] o A std::ostringstream
	 *
	 * @return the std::string that corresponds to the std::ostringstream
	 */
	inline std::string to_string_with_ostringstream(std::ostringstream & o)
	{
		return (o.str());
	}
	
	// Floating point
	template <class T>
	void save_in_ostringstream(std::ostringstream & o, T const & t, std::true_type const)
	{
		o << std::setprecision(std::numeric_limits<T>::digits10 + 1);
		o << t;
	}
	
	// Not floating point
	template <class T>
	void save_in_ostringstream(std::ostringstream & o, T const & t, std::false_type const)
	{
		o << t;
	}
	
	/**
	 * @brief Save the input in a std::ostringstream
	 *
	 * @code
	   #include <hnc/to_string.hpp>
	   @endcode
	 *
	 * @param[in] o A std::ostringstream
	 * @param[in] t Object to be saved
	 */
	template <class T>
	void save_in_ostringstream(std::ostringstream & o, T const & t)
	{
		save_in_ostringstream(o, t, std::is_floating_point<T>());
	}
	
	/**
	 * @brief Convert the input into a std::string with a std::ostringstream
	 *
	 * @code
	   #include <hnc/to_string.hpp>
	   @endcode
	 *
	 * @param[in] o    A std::ostringstream
	 * @param[in] t    Object to be converted
	 * @param[in] args Other objects to be converted
	 *
	 * @return the std::string that corresponds to the input
	 */
	template <class T, class... args_t>
	std::string to_string_with_ostringstream(std::ostringstream & o, T const & t, args_t const & ... args)
	{
		hnc::save_in_ostringstream(o, t);
		return hnc::to_string_with_ostringstream(o, args...);
	}
	
	/**
	 * @brief Convert the input into a std::string with a std::ostringstream
	 *
	 * @code
	   #include <hnc/to_string.hpp>
	   @endcode
	 *
	 * @param[in] args Objects to be converted
	 *
	 * @return the std::string that corresponds to the input
	 */
	template <class... args_t>
	std::string to_string(args_t const & ... args)
	{
		std::ostringstream o;
		
		return hnc::to_string_with_ostringstream(o, args...);
	}

	// Specialization for std::string
	std::string to_string(std::string const & in)
	{
		return in;
	}

	// Specialization for char const * const
	std::string to_string(char const * const in)
	{
		return std::string(in);
	}
}

#endif
