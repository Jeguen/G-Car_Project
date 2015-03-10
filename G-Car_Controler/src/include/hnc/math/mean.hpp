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


#ifndef HNC_MATH_MEAN_HPP
#define HNC_MATH_MEAN_HPP

#include <iterator>
#include <stdexcept>

#include "../algo/sum.hpp"
#include "../assert.hpp"


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Arithmetic mean between two iterators
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * @f$ \text{mean}(X) = \frac{\sum_{i=0}^{n-1}{x_i}}{|X|} @f$ @n
		 * with @f$ X @f$ a vector with the elements between the two iterators @n
		 * with @f$ x_i @f$ an element of the vector @n
		 * with @f$ |X| @f$ the size of the vector
		 *
		 * http://en.wikipedia.org/wiki/Arithmetic_mean
		 *
		 * @param[in] begin Iterator of first element
		 * @param[in] end Iterator of last element (not included)
		 *
		 * @pre The distance beetween first and last element is >= 1
		 *
		 * @exception std::length_error: hnc::hassert distance between iterators is >= 1 if NDEBUG is not defined
		 *
		 * @return the arithmetic mean
		 */
		template <class forward_iterator>
		typename std::iterator_traits<forward_iterator>::value_type mean(forward_iterator const & begin, forward_iterator const & end)
		{
			auto const size = std::distance(begin, end);
			#ifndef NDEBUG
				hnc::hassert(size > 0, std::length_error("hnc::math::mean, Can not compute the mean of empty container"));
			#endif
			auto const sum = hnc::algo::sum(begin, end);
			return (sum / decltype(sum)(size));
		}

		/**
		 * @brief Arithmetic mean of a container
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * @f$ \text{mean}(X) = \frac{\sum_{i=0}^{n-1}{x_i}}{|X|} @f$ @n
		 * with @f$ X @f$ the container @n
		 * with @f$ x_i @f$ an element of the container @n
		 * with @f$ |X| @f$ the size of the container
		 *
		 * http://en.wikipedia.org/wiki/Arithmetic_mean
		 *
		 * @param[in] c Container like std::vector, std::list (with a size >= 1)
		 *
		 * @pre The size of the container is >= 1
		 *
		 * @exception std::length_error: hnc::hassert container size is >= 1 if NDEBUG is not defined
		 *
		 * @return the arithmetic mean (a long double)
		 */
		template <class T, template <class, class Alloc = std::allocator<T>> class Container>
		T mean(Container<T> const & c)
		{
			#ifndef NDEBUG
				hnc::hassert(c.size() > 0, std::length_error("hnc::math::mean, Can not compute the mean of empty container"));
			#endif
			return hnc::math::mean(c.begin(), c.end());
		}
	}
}

#endif
