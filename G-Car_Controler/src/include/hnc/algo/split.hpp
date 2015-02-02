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


#ifndef HNC_ALGO_SPLIT_HPP
#define HNC_ALGO_SPLIT_HPP

#include <algorithm>
#include <iterator>
#include <vector>

#include "../unused.hpp"


namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Split the container with a delimiter
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c                Container like std::vector, std::string, std::list
		 * @param[in] first            Const iterator of first element
		 * @param[in] last             Const iterator of last element (not included)
		 * @param[in] delimiter        Delimiter
		 * @param[in] return_container Returned container (to stock the chunks) (std::vector by default)
		 *
		 * @return a container with all chunks
		 */
		template <class container, class return_container_t = std::vector<container>>
		return_container_t split
		(
			container const & c,
			typename container::const_iterator first, typename container::const_iterator const & last,
			typename container::value_type const & delimiter,
			return_container_t return_container = return_container_t()
		)
		{
			hnc_unused(c);
			
			using const_iterator_t = typename container::const_iterator;
			const_iterator_t it_0 = first;
			const_iterator_t it_1 = last;
			// Split
			while (it_0 != last)
			{
				// Find
				it_1 = std::find(it_0, last, delimiter);
				// Copy the range
				return_container.push_back(container(it_0, it_1));
				// Delimiter found
				if (it_1 != last)
				{
					// Next
					it_0 = std::next(it_1, 1);
					// Actual position is the last value
					if (it_0 == last)
					{
						// Add empty container
						return_container.push_back(container());
					}
				}
				// End (it_1 == last)
				else
				{
					it_0 = last;
				}
			}

			return return_container;
		}
		/**
		 * @brief Split the container with a delimiter
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c                Container like std::vector, std::string, std::list
		 * @param[in] delimiter        Delimiter
		 * @param[in] return_container Returned container (to stock the chunks) (std::vector by default)
		 *
		 * @return a container with all chunks
		 */
		template <class container, class return_container_t = std::vector<container>>
		return_container_t split
		(
			container const & c,
			typename container::value_type const & delimiter,
			return_container_t return_container = return_container_t()
		)
		{
			return hnc::algo::split(c, c.begin(), c.end(), delimiter, return_container);
		}
	}
}

#endif
