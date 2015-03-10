// Copyright © 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef HNC_MATH_ABS_HPP
#define HNC_MATH_ABS_HPP


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Return the absolute value
		 * 
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 *
		 * @param[in] n Value
		 *
		 * @return the absolute value
		 */
		template <class T>
		T abs(T const & n)
		{
			return (n >= 0) ? n : -n;
		}
	}
}

#endif
