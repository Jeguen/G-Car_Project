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


#ifndef HNC_ALGO_REPLACE_HPP
#define HNC_ALGO_REPLACE_HPP

#include <algorithm>
#include <iterator>

#include "find_range.hpp"
#include "replace_range.hpp"


namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Replace the first values by others between two iterators
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
		Container & replace
		(
			Container & c, typename Container::iterator first, typename Container::iterator last,
			Container const & old_values, Container const & new_values
		)
		{
			using iterator_t = typename Container::iterator;
			// Find the values
			iterator_t it = hnc::algo::find_range(first, last, old_values);
			// Replace
			if (it != last)
			{
				hnc::algo::replace_range(c, it, std::next(it, std::ptrdiff_t(old_values.size())), new_values.begin(), new_values.end());
			}
			// Return
			return c;
		}

		/**
		 * @brief Replace the first values by others in a container
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
		 * @note Consider std::replace to replace one element by one other element
		 */
		template <class Container>
		Container & replace(Container & c, Container const & old_values, Container const & new_values)
		{
			return hnc::algo::replace(c, c.begin(), c.end(), old_values, new_values);
		}

		/**
		 * @brief Replace the first values by others in a container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c          Container like std::vector, std::list
		 * @param[in] old_values Container with values to be replaced
		 * @param[in] new_values Container with replacement values
		 *
		 * @return a container after replace
		 *
		 * @note Consider Boost.Range
		 * @note Consider std::replace to replace one element by one other element
		 */
		template <class Container>
		Container replace_copy(Container const & c, Container const & old_values, Container const & new_values)
		{
			Container r = c;
			hnc::algo::replace(r, r.begin(), r.end(), old_values, new_values);
			return r;
		}
	}
}

#endif
