// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_MATH_STANDARD_DEVIATION_HPP
#define HNC_MATH_STANDARD_DEVIATION_HPP

#include <cmath>

#include "variance.hpp"


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Compute the standard deviation of elements between two iterators
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * @f$ \text{standard_deviation}(X) = \sqrt{\mathbb{E}[(X - \mathbb{E}(X))^2]} @f$ @n
		 * with @f$ \mathbb{E} @f$ the expected value, the mean is this case @n
		 * with @f$ X @f$ a vector with the elements between the two iterators @n
		 * so, we have @f$ \mathbb{E}(X) \Leftrightarrow \bar{X} @f$ and @f$ \text{variance}(X) = \overline{(X - \overline{X})^2} @f$ @n
		 * and @f$ \text{standard_deviation}(X) = \sqrt{\text{variance}(X)} @f$
		 *
		 * http://en.wikipedia.org/wiki/Standard_deviation#Definition_of_population_values
		 *
		 * @param[in] begin Iterator of first element
		 * @param[in] end Iterator of last element (not included)
		 *
		 * @pre The distance beetween first and last element is >= 1
		 *
		 * @return the standard deviation
		 */
		template <class forward_iterator>
		auto standard_deviation(forward_iterator begin, forward_iterator const & end) -> decltype(std::sqrt(*begin))
		{
			return std::sqrt(hnc::math::variance(begin, end));
		}

		/**
		 * @brief Compute standard deviation of a container
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * @f$ \text{standard_deviation}(X) = \sqrt{\mathbb{E}[(X - \mathbb{E}(X))^2]} @f$ @n
		 * with @f$ \mathbb{E} @f$ the expected value, the mean is this case @n
		 * with @f$ X @f$ a vector with the elements between the two iterators @n
		 * so, we have @f$ \mathbb{E}(X) \Leftrightarrow \bar{X} @f$ and @f$ \text{variance}(X) = \overline{(X - \overline{X})^2} @f$ @n
		 * and @f$ \text{standard_deviation}(X) = \sqrt{\text{variance}(X)} @f$
		 *
		 * http://en.wikipedia.org/wiki/Standard_deviation#Definition_of_population_values
		 *
		 * @param[in] c Container like std::vector, std::list (with a size >= 1)
		 *
		 * @pre The size of the container is >= 1
		 *
		 * @return the standard deviation
		 */
		template <class T, template <class, class Alloc = std::allocator<T>> class Container>
		auto standard_deviation(Container<T> const & c) -> decltype(std::sqrt(c.front()))
		{ return hnc::math::standard_deviation(c.begin(), c.end()); }
	}
}

#endif
