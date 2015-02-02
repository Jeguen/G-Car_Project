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


#ifndef HNC_TO_TYPE_HPP
#define HNC_TO_TYPE_HPP

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "to_string.hpp"


namespace hnc
{
	namespace
	{
		// Convert a T into a return_t (with hnc::convert<return_t, T>::call(in);)
		// General class
		template <class return_t, class T>
		class convert
		{
		public:
			static return_t call(T const & in)
			{
				// Declare a stream with in
				std::stringstream ss;
				ss.precision(std::numeric_limits<T>::digits10+1);
				ss << in;
				// Get return_t from stream
				return_t r;
				ss >> r;
				// Return
				return r;
			}
		};

		// Convert a T into a return_t (with hnc::convert<return_t, T>::call(in);)
		// Partial specialization with std::string as return_t
		template <class T>
		class convert<std::string, T>
		{
		public:
			static std::string call(T const & in) { return hnc::to_string(in); }
		};
	}
	
	/**
	 * @brief Convert the input into a another type
	 *
	 * @code
	   #include <hnc/to_type.hpp>
	   @endcode
	 * 
	 * The input is converted into the return_t type. @n
	 * We use a std::stringstream to do the conversion.
	 *
	 * Exemple:
	 * @code
	   // return_type output = hnc::to_<return_type>(input);
	      int         output = hnc::to_<int>        ("420");
	   @endcode
	 *
	 * @warning Prefer the hnc::to_type(e) function !
	 * @code
	   int i = hnc::to_<int>("42"); // You can use hnc::to_int
	   double d = hnc::to_<double>("42.1"); // You can use hnc::to_double
	   @endcode
	 *
	 * @warning Avoid unsigned int
	 *
	 * @warning Keep logic and do not use something like to_<int>(a_double), because:
	 * - Just use constructor: int(a_double)
	 * - or create a new variable: int i = a_double
	 * - or use C++ static_cast: static_cast<int>(a_double)
	 * - or use C cast: (int)(a_double)
	 *
	 * @note Consider Boost.Coerce or Boost.Lexical_Cast for safe conversion
	 *
	 * @param[in] in The input
	 *
	 * Specialization when:
	 * - return_t is std::string
	 *
	 * @return the converted input into a return_t
	 */
	template <class return_t, class T>
	return_t to_(T const & in)
	{
		return hnc::convert<return_t, T>::call(in);
	}
}

#endif
