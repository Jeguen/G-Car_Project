// Copyright © 2013 Lénaïc Bagnères, hnc@singularity.fr
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


#ifndef HNC_MATH_GCD_HPP
#define HNC_MATH_GCD_HPP

#include "abs.hpp"


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Almost greatest common divisor (result can be negative)
		 * 
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * http://en.wikipedia.org/wiki/Greatest_common_divisor
		 * https://proofwiki.org/wiki/GCD_for_Negative_Integers
		 *
		 * @param[in] a A integer
		 * @param[in] b A integer
		 *
		 * @return almost the greatest common divisor (result can be negative)
		 */
		template <class T>
		T gcd_without_abs(T const & a, T const & b)
		{
			return (b != 0) ? hnc::math::gcd_without_abs(b, a % b) : a;
		}
		
		/**
		 * @brief Greatest common divisor
		 * 
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * http://en.wikipedia.org/wiki/Greatest_common_divisor
		 * https://proofwiki.org/wiki/GCD_for_Negative_Integers
		 *
		 * @param[in] a A integer
		 * @param[in] b A integer
		 *
		 * @return the greatest common divisor of a and b
		 */
		template <class T>
		T gcd(T const & a, T const & b)
		{
			return hnc::math::abs(hnc::math::gcd_without_abs(a, b));
		}
	}
}

#endif
