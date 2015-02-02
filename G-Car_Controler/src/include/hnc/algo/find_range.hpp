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


#ifndef HNC_ALGO_FIND_RANGE_HPP
#define HNC_ALGO_FIND_RANGE_HPP

#include <algorithm>

#include <hnc/algo/compare_range.hpp>


namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Find a sequence in an other sequence
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] first        Iterator on first element
		 * @param[in] last         Iterator on last element (not included)
		 * @param[in] values_first Iterator on first element of the values that we are looking for
		 * @param[in] values_last  Iterator on last element (upper bound) of the values that we are looking for (not included)
		 *
		 * @return a iterator on the first element of the finded sequence, last if not found
		 *
		 * @note Consider Boost.Range
		 * @note Consider std::find to find one element in a sequence
		 */
		template <class forward_iterator_t0, class forward_iterator_t1>
		forward_iterator_t0 find_range
		(
			forward_iterator_t0 first, forward_iterator_t0 const & last,
			forward_iterator_t1 const & values_first, forward_iterator_t1 const & values_last
		)
		{
			typename std::iterator_traits<forward_iterator_t1>::difference_type values_size = std::distance(values_first, values_last);
			// Check if values is not empty
			if (values_size != 0)
			{
				// Find the first element of values
				forward_iterator_t0 it = std::find(first, last, *values_first);
				// it to last can not contains the values
				while (it != last && std::distance(it, last) >= values_size)
				{
					// Compare this position with values
					bool ranges_are_equal = hnc::algo::compare_range(it, std::next(it, values_size), values_first, values_last);
					// Range found
					if (ranges_are_equal)
					{
						return it;
					}
					// Next
					++it;
					it = std::find(it, last, *values_first);
				}
			}
			// Range not found
			return last;
		}

		/**
		 * @brief Find a sequence (a container) in an other sequence
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] first Iterator on first element
		 * @param[in] last  Iterator on last element (not included)
		 * @param[in] values Values that we are looking for
		 *
		 * @return a iterator on the first element of the finded sequence, last if not found
		 *
		 * @note Consider Boost.Range
		 * @note Consider std::find to find one element in a sequence
		 */
		template <class forward_iterator_t, class Container>
		forward_iterator_t find_range
		(
			forward_iterator_t first, forward_iterator_t const & last,
			Container const & values
		)
		{
			return hnc::algo::find_range(first, last, values.begin(), values.end());
		}

		/**
		 * @brief Find a container in an other const container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c Container
		 * @param[in] values Values that we are looking for
		 *
		 * @return a const iterator on the first element of the finded sequence, last if not found
		 *
		 * @note Consider std::find to find one element in a sequence
		 */
		template <class Container>
		typename Container::const_iterator find_range
		(
			Container const & c,
			Container const & values
		)
		{
			return hnc::algo::find_range(c.begin(), c.end(), values.begin(), values.end());
		}

		/**
		 * @brief Find a container in an other container
		 *
		 * @code
		 * #include <hnc/algo.hpp>
		 * @endcode
		 *
		 * @param[in] c Container
		 * @param[in] values Values that we are looking for
		 *
		 * @return a iterator on the first element of the finded sequence, last if not found
		 *
		 * @note Consider std::find to find one element in a sequence
		 */
		template <class Container>
		typename Container::iterator find_range
		(
			Container & c,
			Container const & values
		)
		{
			return hnc::algo::find_range(c.begin(), c.end(), values.begin(), values.end());
		}
	}
}

#endif
