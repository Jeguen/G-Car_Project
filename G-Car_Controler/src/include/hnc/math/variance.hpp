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


#ifndef HNC_MATH_VARIANCE_HPP
#define HNC_MATH_VARIANCE_HPP

#include <iterator>

#include "mean.hpp"


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Compute variance between two iterators
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * @f$ \text{variance}(X) = \mathbb{E}[(X - \mathbb{E}(X))^2] @f$ @n
		 * with @f$ \mathbb{E} @f$ the expected value, the mean is this case @n
		 * with @f$ X @f$ a vector with the elements between the two iterators @n
		 * so, we have @f$ \mathbb{E}(X) \Leftrightarrow \bar{X} @f$ and @f$ \text{variance}(X) = \overline{(X - \overline{X})^2} @f$
		 *
		 * http://en.wikipedia.org/wiki/Variance#Definition
		 *
		 * @param[in] begin Iterator of first element
		 * @param[in] end Iterator of last element (not included)
		 *
		 * @pre The distance beetween first and last element is >= 1
		 *
		 * @return the variance
		 */
		template <class forward_iterator>
		typename std::iterator_traits<forward_iterator>::value_type variance(forward_iterator begin, forward_iterator const & end)
		{
			using return_t = typename std::iterator_traits<forward_iterator>::value_type;
			
			return_t mean = hnc::math::mean(begin, end);
			return_t variance = 0.;
			for (forward_iterator it = begin; it != end; ++it)
			{
				return_t tmp = return_t(*it) - mean; // tmp = X - E(X)
				variance += tmp * tmp;
			}
			variance /= return_t(std::distance(begin, end));
			return variance;
		}

		/**
		 * @brief Compute variance of a container
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * Variance of a container like std::vector, std::list @n
		 * @f$ \text{variance}(X) = \mathbb{E}[(X - \mathbb{E}(X))^2] @f$ @n
		 * with @f$ \mathbb{E} @f$ the expected value, the mean is this case @n
		 * with @f$ X @f$ the container @n
		 * so, we have @f$ \mathbb{E}(X) \Leftrightarrow \bar{X} @f$ and @f$ \text{variance}(X) = \overline{(X - \overline{X})^2} @f$
		 *
		 * http://en.wikipedia.org/wiki/Variance#Definition
		 *
		 * @param[in] c Container like std::vector, std::list (with a size >= 1)
		 *
		 * @pre The size of the container is >= 1
		 *
		 * @return the variance
		 */
		template <class T, template <class, class Alloc = std::allocator<T>> class Container>
		T variance(Container<T> const & c)
		{ return hnc::math::variance(c.begin(), c.end()); }
	}
}

#endif
