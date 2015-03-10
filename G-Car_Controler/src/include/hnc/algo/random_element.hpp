// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_ALGO_RANDOM_ELEMENT_HPP
#define HNC_ALGO_RANDOM_ELEMENT_HPP

#include <iterator>

#include "../random.hpp"


namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Return a random element from a range
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] begin Iterator of first element
		 * @param[in] end   Iterator of last element (not included)
		 *
		 * @return a random element
		 */
		template <class forward_iterator>
		typename std::iterator_traits<forward_iterator>::reference random_element(forward_iterator const & begin, forward_iterator const & end)
		{
			using diff_t = typename std::iterator_traits<forward_iterator>::difference_type;
			
			return *std::next(begin, hnc::random::uniform(diff_t(0), diff_t(std::distance(begin, end) - 1)));
		}
		
		/**
		 * @brief Return a copy of a random element from a range
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] begin Iterator of first element
		 * @param[in] end   Iterator of last element (not included)
		 *
		 * @return a copy of a random element
		 */
		template <class forward_iterator>
		typename std::iterator_traits<forward_iterator>::value_type random_element_copy(forward_iterator const & begin, forward_iterator const & end)
		{
			return hnc::algo::random_element(begin, end);
		}
		
		/**
		 * @brief Return a random element from a container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c A container
		 *
		 * @return a random element
		 */
		template <class container_t>
		typename container_t::value_type & random_element(container_t & c)
		{
			return hnc::algo::random_element(c.begin(), c.end());
		}
		
		/**
		 * @brief Return a const random element from a container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c A container
		 *
		 * @return a const random element
		 */
		template <class container_t>
		typename container_t::value_type const & random_element(container_t const & c)
		{
			return hnc::algo::random_element(c.cbegin(), c.cend());
		}
		
		/**
		 * @brief Return a copy of a random element from a container
		 *
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 *
		 * @param[in] c A container
		 *
		 * @return a copy of a random element
		 */
		template <class container_t>
		typename container_t::value_type random_element_copy(container_t const & c)
		{
			return hnc::algo::random_element_copy(c.cbegin(), c.cend());
		}
	}
}

#endif
