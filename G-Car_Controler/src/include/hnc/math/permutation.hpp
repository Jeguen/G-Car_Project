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


#ifndef HNC_MATH_COMBINAISON_HPP
#define HNC_MATH_COMBINAISON_HPP

#include <cmath>


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Return the k-combinaisons
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 *
		 * @param[in] values A container with all values
		 * @param[in] k      Size of combinaisons
		 *
		 * Exemple:
		 * @code
		   // The 2-combinaisons of
		   { 'a', 'b', 'c' }
		   // is
		   {
		   	{ 'a', 'b' },
		   	{ 'a', 'c' },
		   	{ 'b', 'c' }
		   }
		   @endcode
		 *
		 * http://en.wikipedia.org/wiki/Combination
		 *
		 * @return the k-combinaisons
		 */
		template <class value_t, template<class, class> class container_t, class alloc_t = std::allocator<value_t>>
		container_t<container_t<value_t, alloc_t>, std::allocator<container_t<value_t, alloc_t>>> combinaisons(container_t<value_t, alloc_t> const & values, std::size_t const k)
		{
// 			using container_of_T = typename container_of_container_of_T::value_type;
// 			using T = typename container_of_T::value_type;
			
			container_t<container_t<value_t, alloc_t>, std::allocator<container_t<value_t, alloc_t>>> combinaisons;
			
			for (std::size_t i = 0; i < values.size(); ++i)
			{
				combinaisons.emplace_back(1, values[i]);
			}
			
			for (std::size_t i = 0; i < values.size(); ++i)
			{
				//for (std::size_t j = i; j < values.size(); ++j)
				{
					// Add values
					for (std::size_t k = 0; k < combinaisons.size(); ++k)
					{
						if (k != i)
						{
							combinaisons[k].push_back(values[i]);
						}
					}
				}
			}
// 
// 			// Return
// 			container_of_container_of_T vector_of_results(1);
// 
// 			// For each values
// 			for (container_of_T const & values : vector_of_values)
// 			{
// 				// To get new results
// 				container_of_container_of_T tmp;
// 
// 				// For each actual results
// 				for (container_of_T & result : vector_of_results)
// 				{
// 					// For each values
// 					for (T const & e : values)
// 					{
// 						// Add new results
// 						tmp.push_back(result);
// 						tmp.back().push_back(e);
// 					}
// 				}
// 
// 				// Replace old results
// 				vector_of_results = tmp;
// 			}

			// Return
			return combinaisons;
		}
	}
}

#endif
