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


#ifndef HNC_MATH_COMBINATION_HPP
#define HNC_MATH_COMBINATION_HPP

#include <cmath>


namespace hnc
{
	namespace math
	{
		namespace
		{
			/**
			 * @brief Return the k-combinations
			 * 
			 * @code
			 * #include <hnc/math.hpp>
			 * @endcode
			 * 
			 * @param[in] first                 Iterator on first value
			 * @param[in] last                  Iterator on last value (not included)
			 * @param[in] k                     Size of combinations
			 * @param[in] combinations          Combinaisons computed
			 * @param[in] combination           Actual combination
			 * @param[in] keep_all_combinations true if keep all combinations, false otherwise
			 * 
			 * @return the k-combinations
			 */
			template <class value_t, template<class, class> class container_t, class alloc_t = std::allocator<value_t>>
			void combinations_generate
			(
				typename container_t<value_t, alloc_t>::const_iterator first,
				typename container_t<value_t, alloc_t>::const_iterator const last,
				std::size_t const k,
				container_t<container_t<value_t, alloc_t>, std::allocator<container_t<value_t, alloc_t>>> & combinations,
				container_t<value_t, alloc_t> combination,
				bool const keep_all_combinations
			)
			{
				while (first != last)
				{
					auto tmp = combination;
					tmp.push_back(*first);
					
					if (keep_all_combinations || tmp.size() == k)
					{
						combinations.push_back(tmp);
					}
					
					++first;
					
					if (tmp.size() < k)
					{
						hnc::math::combinations_generate(first, last, k, combinations, tmp, keep_all_combinations);
					}
				}
			}
		}
		
		/**
		 * @brief Return the k-combinations
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 *
		 * @param[in] values A container with all values
		 * @param[in] k      Size of combinations
		 *
		 * Exemple:
		 * @code
		   // The 2-combinations of
		   { 'a', 'b', 'c', 'd', 'e' }
		   // are
		   {
		   	{ 'a', 'b' },
		   	{ 'a', 'c' },
		   	{ 'a', 'd' },
		   	{ 'a', 'e' },
		   	{ 'b', 'c' },
		   	{ 'b', 'd' },
		   	{ 'b', 'e' },
		   	{ 'c', 'd' },
		   	{ 'c', 'e' }
		   	{ 'd', 'e' }
		   }
		   @endcode
		 *
		 * http://en.wikipedia.org/wiki/Combination
		 *
		 * @return the k-combinations
		 */
		template <class value_t, template<class, class> class container_t, class alloc_t = std::allocator<value_t>>
		container_t<container_t<value_t, alloc_t>, std::allocator<container_t<value_t, alloc_t>>> combinations(container_t<value_t, alloc_t> const & values, std::size_t const k)
		{
			container_t<container_t<value_t, alloc_t>, std::allocator<container_t<value_t, alloc_t>>> combinations;
			
			hnc::math::combinations_generate(values.cbegin(), values.cend(), k, combinations, {}, false);
			
			return combinations;
		}
		
		/**
		 * @brief Return all combinations
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 *
		 * @param[in] values A container with all values
		 *
		 * Exemple:
		 * @code
		   // The all combinations of
		   { 'a', 'b', 'c' }
		   // are
		   {
		   	{ 'a' },
		   	{ 'a', 'b' },
		   	{ 'a', 'b', 'c' },
		   	{ 'a', 'c' },
		   	{ 'b' },
		   	{ 'b', 'c' },
		   	{ 'c' }
		   }
		   @endcode
		 *
		 * http://en.wikipedia.org/wiki/Combination
		 *
		 * @return the all combinations
		 */
		template <class value_t, template<class, class> class container_t, class alloc_t = std::allocator<value_t>>
		container_t<container_t<value_t, alloc_t>, std::allocator<container_t<value_t, alloc_t>>> combinations_all(container_t<value_t, alloc_t> const & values)
		{
			container_t<container_t<value_t, alloc_t>, std::allocator<container_t<value_t, alloc_t>>> combinations;
			
			hnc::math::combinations_generate(values.cbegin(), values.cend(), values.size(), combinations, {}, true);
			
			return combinations;
		}
	}
}

#endif
