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


#ifndef HNC_ALGO_REPLACE_ALL_HPP
#define HNC_ALGO_REPLACE_ALL_HPP

#include <algorithm>
#include <iterator>

#include "find_range.hpp"
#include "replace_range.hpp"


namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Replace all values by others between two iterators
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in,out] c          Container like std::vector, std::list
		 * @param[in]     first      Iterator of first element
		 * @param[in]     last       Iterator of last element (not included)
		 * @param[in]     old_values Container with values to be replaced
		 * @param[in]     new_values Container with replacement values
		 *
		 * @return the container
		 *
		 * @note Consider Boost.Range
		 * @note Consider std::replace to replace one element by one other element
		 */
		template <class Container>
		Container & replace_all
		(
			Container & c, typename Container::iterator first, typename Container::iterator last,
			Container const & old_values, Container const & new_values
		)
		{
			using iterator_t = typename Container::iterator;
			using difference_type = typename std::iterator_traits<iterator_t>::difference_type;
			// Find the values
			iterator_t it = hnc::algo::find_range(first, last, old_values);
			// Replace
			while (it != last)
			{
				// Replace can invalidate the iterator
				difference_type distance_begin_it = std::distance(c.begin(), it);
				difference_type distance_it_last = std::distance(it, last);
				// Replace
				hnc::algo::replace_range(c, it, std::next(it, std::ptrdiff_t(old_values.size())), new_values.begin(), new_values.end());
				// Resume and advance iterators
				if (old_values.size() < new_values.size())
				{
					it = std::next(c.begin(), distance_begin_it + std::ptrdiff_t(new_values.size()) - std::ptrdiff_t(old_values.size()) + 1);
					last = std::next(it, distance_it_last - 1);
				}
				else if (old_values.size() > new_values.size())
				{
					it = std::next(c.begin(), distance_begin_it);
					last = std::next(it, distance_it_last - std::ptrdiff_t(old_values.size() - new_values.size()));
				}
				else // Same size
				{
					std::advance(it, old_values.size());
				}
				// Next replace
				it = hnc::algo::find_range(it, last, old_values);
			}
			// Return
			return c;
		}

		/**
		 * @brief Replace all values by others in a container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in,out] c          Container like std::vector, std::list
		 * @param[in]     old_values Container with values to be replaced
		 * @param[in]     new_values Container with replacement values
		 *
		 * @return the container
		 *
		 * @note Consider Boost.Range
		 * @note Consider std::replace to replace one element by one other element
		 */
		template <class Container>
		Container & replace_all(Container & c, Container const & old_values, Container const & new_values)
		{
			return hnc::algo::replace_all(c, c.begin(), c.end(), old_values, new_values);
		}

		/**
		 * @brief Replace all values by others in a container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c          Container like std::vector, std::list
		 * @param[in] old_values Container with values to be replaced
		 * @param[in] new_values Container with replacement values
		 *
		 * @return a container after replaces
		 *
		 * @note Consider Boost.Range
		 * @note Consider std::replace to replace one element by one other element
		 */
		template <class Container>
		Container replace_all_copy(Container const & c, Container const & old_values, Container const & new_values)
		{
			Container r = c;
			hnc::algo::replace_all(r, r.begin(), r.end(), old_values, new_values);
			return r;
		}
	}
}

#endif
