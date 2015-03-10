// Copyright © 2012, 2014 Lénaïc Bagnères, hnc@singularity.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef HNC_ALGO_SUM_HPP
#define HNC_ALGO_SUM_HPP


namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Sum of elements between two iterators
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] begin Iterator of first element
		 * @param[in] end   Iterator of last element (not included)
		 *
		 * @return the sum
		 *
		 * @note Consider std::accumulate
		 */
		template <class forward_iterator>
		typename std::iterator_traits<forward_iterator>::value_type sum(forward_iterator begin, forward_iterator const & end)
		{
			typedef typename std::iterator_traits<forward_iterator>::value_type sum_type;
			sum_type sum = sum_type();
			for (; begin != end; ++begin) { sum += *begin; }
			return sum;
		}

		/**
		 * @brief Sum of elements of a container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c Container like std::vector, std::list
		 *
		 * @return the sum
		 *
		 * @note Consider std::accumulate
		 */
		template <class T, template <class, class Alloc = std::allocator<T>> class Container>
		T sum(Container<T> const & c)
		{ return hnc::algo::sum(c.begin(), c.end()); }
	}
}

#endif
