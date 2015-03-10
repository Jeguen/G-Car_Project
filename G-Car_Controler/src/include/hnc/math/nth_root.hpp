// Copyright © 2013, 2014 Lénaïc Bagnères, hnc@singularity.fr

// This file is part of hnc.

// hnc is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// hnc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with hnc. If not, see <http://www.gnu.org/licenses/>


#ifndef HNC_MATH_NTH_ROOT_HPP
#define HNC_MATH_NTH_ROOT_HPP

#include <cmath>
#include <stdexcept>

#include "../assert.hpp"
#include "../to_string.hpp"


namespace hnc
{
	namespace math
	{
		// TODO <hnc/tag.hpp> (?)
		
		// Tag dispatch
		namespace
		{
			template <bool>
			struct is_integer { };
		}

		// Floating point
		template <class T>
		T nth_root(T const & a, std::size_t const n, is_integer<false>)
		{
			T r = 1;
			T delta = r;
			T previous_delta = 0;

			while (std::abs(delta + previous_delta) > std::numeric_limits<T>::epsilon())
			{
				previous_delta = delta;
				delta = r;
				// Compute
				r = (T(1) / T(n)) * (T(n - 1) * r + (a / T(std::pow(r, n - 1))));
				// Get delta
				delta -= r;
			}
			
			return r;
		}

		// Integer
		// Actual algorithm works only floating point, use long double for internal computation
		template <class T>
		long double nth_root(T const & a, std::size_t const n, is_integer<true>)
		{
			return nth_root(static_cast<long double>(a), n, is_integer<false>());
		}

		/**
		 * @brief nth root algorithm
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 *
		 * @param[in] a @f$ a @f$ in @f$ \sqrt[n]{a} @f$
		 * @param[in] n @f$ n @f$ in @f$ \sqrt[n]{a} @f$
		 *
		 * Particular cases:
		 * - @f$ a @f$ == @f$ 0 @f$, return @f$ 0 @f$
		 * - @f$ n @f$ == @f$ 0 @f$, return @f$ 1 @f$
		 * - @f$ n @f$ == @f$ 1 @f$, return @f$ a @f$
		 * - @f$ n @f$ == @f$ 2 @f$, return std::sqrt(@f$ a @f$)
		 * - @f$ n @f$ == @f$ 3 @f$, return std::cbrt(@f$ a @f$)
		 *
		 * https://en.wikipedia.org/wiki/Nth_root_algorithm @n
		 * https://fr.wikipedia.org/wiki/Algorithme_de_calcul_de_la_racine_n-i%C3%A8me
		 *
		 * @pre If @f$ n @f$ is odd: @f$ a > 0 @f$
		 *
		 * @exception std::domain_error if @f$ n \% 2 = 0 @f$ and @f$ a < 0 @f$
		 *
		 * @note Use std::pow
		 *
		 * @return the nth root
		 */
		template <class T>
		auto nth_root(T const & a, std::size_t const n) -> decltype(hnc::math::nth_root(a, n, is_integer<std::numeric_limits<T>::is_integer>()))
		{
			static_assert(std::is_arithmetic<T>::value, "hnc::math::nth_root works for arithmetic types only");
			
			// If n is even and a < 0
			if (n % 2 == 0 && a < T(0))
			{
				hnc::hassert(false, std::domain_error("hnc::math::nth_root, Can not compute the " + hnc::to_string(n) + "th root of a negative number (" + hnc::to_string(a) + ")"));
			}

			// a == 0
			if (a == T(0)) { return T(0); }

			// n == 0
			if (n == 0) { return T(1); }

			// n == 1
			if (n == 1) { return a; }

			// sqrt
			if (n == 2) { return std::sqrt(a); }

			// cbrt
			if (n == 3) { return std::cbrt(a); }

			// General
			return nth_root(a, n, is_integer<std::numeric_limits<T>::is_integer>());
		}
	}
}

#endif
