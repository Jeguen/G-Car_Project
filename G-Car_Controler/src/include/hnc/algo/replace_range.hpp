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


#ifndef HNC_ALGO_REPLACE_RANGE_HPP
#define HNC_ALGO_REPLACE_RANGE_HPP

#include <algorithm>
#include <iterator>


namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Replace a sequence of a container by an other sequence
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in,out] c            Container
		 * @param[in]     first        Iterator on first element
		 * @param[in]     last         Iterator on last element (not included)
		 * @param[in]     values_first Iterator on first element of the values
		 * @param[in]     values_last  Iterator on last element (of the values (not included)
		 *
		 * @warning Iterators of the container can became invalid (if insert or remove values)
		 *
		 * @note Consider std::replace to replace one value by one other value
		 */
		template <class Container, class forward_iterator_t>
		void replace_range
		(
			Container & c,
			typename Container::iterator first, typename Container::iterator last,
			forward_iterator_t const & values_first, forward_iterator_t const & values_last
		)
		{
			using iterator_t0 = typename Container::iterator;
			using difference_t0 = typename std::iterator_traits<iterator_t0>::difference_type;
			// Get size
			difference_t0 range_size = std::distance(first, last);
			difference_t0 values_size = std::distance(values_first, values_last);
			if ((range_size == difference_t0(0) && values_size == difference_t0(0)) == false)
			{
				// range_size == values_size
				if (range_size == values_size)
				{
					std::copy(values_first, values_last, first);
				}
				// range_size < values_size
				else if (range_size < values_size)
				{
					// Copy
					forward_iterator_t const copy_end = std::next(values_first, range_size);
					std::copy(values_first, copy_end, first);
					// Update first
					std::advance(first, range_size);
					// Insert
					c.insert(first, copy_end, values_last); // first is invalid now
				}
				// range_size > values_size
				else
				{
					// Copy
					std::copy(values_first, values_last, first);
					// Update first
					std::advance(first, values_size);
					// Remove
					c.erase(first, std::next(first, range_size - values_size)); // first is invalid now
				}
			}
		}
		
		/**
		 * @brief Replace a sequence of a container by an other container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in,out] c          Container
		 * @param[in]     first      Iterator on first element
		 * @param[in]     last       Iterator on last element (not included)
		 * @param[in]     new_values New values
		 *
		 * @warning Iterators of the container can became invalid (if insert or remove values)
		 *
		 * @note Consider std::replace to replace one value by one other value
		 */
		template <class Container_T0, class Container_T1>
		void replace_range
		(
			Container_T0 & c,
			typename Container_T0::iterator first, typename Container_T0::iterator last,
			Container_T1 const & new_values
		)
		{
			hnc::algo::replace_range(c, first, last, new_values.begin(), new_values.end());
		}
	}
}

#endif
