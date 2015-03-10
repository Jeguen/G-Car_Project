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


#ifndef HNC_MATH_GEOMETRIC_MEAN_HPP
#define HNC_MATH_GEOMETRIC_MEAN_HPP

#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <numeric>

#include "../assert.hpp"
#include "nth_root.hpp"


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Geometric mean between two iterators
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * Compute @f$ \text{geometric_mean} = \sqrt[n]{x_1 \times x_2 \times x_3 \times ... \times x_n} @f$
		 *
		 * http://en.wikipedia.org/wiki/Geometric_mean
		 *
		 * @param[in] begin Iterator of first element
		 * @param[in] end Iterator of last element (not included)
		 *
		 * @pre The distance beetween first and last element is >= 1
		 *
		 * @exception std::length_error hnc::hassert distance between iterators is >= 1 if NDEBUG is not defined
		 * @exception std::domain_error if @f$ x_1 \times x_2 \times x_3 \times ... \times x_n < 0 @f$ and @f$ n \% 2 == 0 @f$
		 *
		 * @return the geometric mean
		 */
		template <class input_iterator>
		typename std::iterator_traits<input_iterator>::value_type geometric_mean(input_iterator const & begin, input_iterator const & end)
		{
			// Get size
			auto const size = std::distance(begin, end);
			
			#ifndef NDEBUG
				hnc::hassert(size > 0, std::length_error("hnc::math::geometric_mean, Can not compute the geometric mean of empty container"));
			#endif

			// Get type of element
			using element_t = typename std::iterator_traits<input_iterator>::value_type;
			
			// Compute x x1 * x2 * x3 * ... * xn
			element_t x = std::accumulate(begin, end, element_t(1), std::multiplies<element_t>());

			// Return the geometric mean = nth_root of x
			return element_t(hnc::math::nth_root(x, std::size_t(size)));
		}

		/**
		 * @brief Geometric mean of a container
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 *
		 * Compute @f$ \text{geometric_mean} = \sqrt[n]{x_1 \times x_2 \times x_3 \times ... \times x_n} @f$
		 *
		 * @param[in] c Container like std::vector, std::list (with a size >= 1)
		 */
		template <class T, template <class, class Alloc = std::allocator<T>> class Container>
		T geometric_mean(Container<T> const & c)
		{
			return hnc::math::geometric_mean(c.begin(), c.end());
		}
	}
}

#endif
