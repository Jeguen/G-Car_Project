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


#ifndef HNC_ALGO_COMPARE_RANGE_HPP
#define HNC_ALGO_COMPARE_RANGE_HPP

#include <algorithm>


namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Compare two sequences
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] first0            Iterator on first element of the first container
		 * @param[in] last0             Iterator on last element of the first container (not included)
		 * @param[in] first1            Iterator on first element of the second container
		 * @param[in] last1_upper_bound Iterator on last element (upper bound) of the second container (not included)
		 * @param[in] comp              Function to compare two elements
		 *
		 * @return true if all comparisons return true, false otherwise
		 *
		 * @note Consider Boost.Range
		 * @note Consider std::equal_range to compare a sequence with one element
		 */
		template <class forward_iterator_t0, class forward_iterator_t1, class compare>
		bool compare_range
		(
			forward_iterator_t0 first0, forward_iterator_t0 const & last0,
			forward_iterator_t1 first1, forward_iterator_t1 const & last1_upper_bound,
			compare comp
		)
		{
			using value_t0 = typename std::iterator_traits<forward_iterator_t0>::value_type;
			using value_t1 = typename std::iterator_traits<forward_iterator_t1>::value_type;
			static_assert(std::is_same<value_t0 , value_t1>::value, "hnc::algo::compare_range invalid call: types of the iterators must be the same");
			// For all elements
			while (first0 != last0)
			{
				// The number of elements between first0 to last0 is greater than the number of elements between first1 and last1_upper_bound
				if (first1 == last1_upper_bound) { return false; }
				// Compare
				if (comp(*first0, *first1) == false) { return false; }
				// Next
				++first0;
				++first1;
			}
			// All comparisons are true
			return true;
		}

		/**
		 * @brief Compare (equality with ==) two sequences
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] first0            Iterator on first element of the first container
		 * @param[in] last0             Iterator on last element of the first container (not included)
		 * @param[in] first1            Iterator on first element of the second container
		 * @param[in] last1_upper_bound Iterator on last element (upper bound) of the second container (not included)
		 *
		 * @return true if all comparisons return true, false otherwise
		 *
		 * @note Consider Boost.Range
		 * @note Consider std::equal_range to compare a sequence with one element
		 */
		template <class forward_iterator_t0, class forward_iterator_t1>
		bool compare_range
		(
			forward_iterator_t0 first0, forward_iterator_t0 const & last0,
			forward_iterator_t1 first1, forward_iterator_t1 const & last1_upper_bound
		)
		{
			using value_t0 = typename std::iterator_traits<forward_iterator_t0>::value_type;
			using value_t1 = typename std::iterator_traits<forward_iterator_t1>::value_type;
			static_assert(std::is_same<value_t0 , value_t1>::value, "hnc::algo::compare_range invalid call: types of the iterators must be the same");
			// Compare function (a == b)
			auto comp = [](value_t0 const & a, value_t0 const & b) -> bool { return a == b; };
			// Compare range
			return hnc::algo::compare_range(first0, last0, first1, last1_upper_bound, comp);
		}
	}
}

#endif
