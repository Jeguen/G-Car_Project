// Copyright © 2012, 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_MATH_MEDIAN_HPP
#define HNC_MATH_MEDIAN_HPP

#include <iterator>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "../assert.hpp"


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Median between two iterators
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * If size of the container is odd:
		 * - return a copy of the n/2 element
		 *
		 * Else (size of the container is even):
		 * - return (n/2 + (n+1)/2)/2 value
		 *
		 * @param[in] begin Iterator of first element
		 * @param[in] end Iterator of last element (not included)
		 *
		 * @pre The distance beetween first and last element is >= 1
		 *
		 * @exception std::length_error: hnc::hassert distance between iterators is >= 1 if NDEBUG is not defined
		 *
		 * @return the median
		 */
		template <class input_iterator>
		typename std::iterator_traits<input_iterator>::value_type median(input_iterator const & begin, input_iterator const & end)
		{
			// Get size
			auto const size = std::distance(begin, end);
			
			#ifndef NDEBUG
				hnc::hassert(size > 0, std::length_error("hnc::math::median, Can not compute the median of empty container"));
			#endif
				
			// Do a partial sort copy
			std::vector<typename std::iterator_traits<input_iterator>::value_type> partial_sort(std::size_t(size / 2 + 1));
			std::partial_sort_copy(begin, end, partial_sort.begin(), partial_sort.end());
			
			// Odd
			if (size % 2 == 1)
			{
				return partial_sort.back();
			}
			// Even
			else
			{
				return (partial_sort.back() + *(partial_sort.rbegin() + 1)) / 2;
			}
		}

		/**
		 * @brief Median of a container
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * If size of the container is odd:
		 * - return a copy of the n/2 element
		 *
		 * Else (size of the container is even):
		 * - return (n/2 + (n+1)/2)/2 value
		 *
		 * @param[in] c Container like std::vector, std::list (with a size >= 1)
		 *
		 * @pre The size of the container is >= 1
		 *
		 * @exception std::length_error: hnc::hassert container size is >= 1 if NDEBUG is not defined
		 *
		 * @return the median
		 */
		template <class T, template <class, class Alloc = std::allocator<T>> class Container>
		T median(Container<T> const & c)
		{
			return hnc::math::median(c.begin(), c.end());
		}
	}
}

#endif
