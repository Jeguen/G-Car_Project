// Copyright © 2012, 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_MATH_CARTESIAN_PRODUCT_HPP
#define HNC_MATH_CARTESIAN_PRODUCT_HPP

#include <cmath>


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Return the Cartesian product
		 *
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 *
		 * @param[in] vector_of_values A container of container of values like std::vector of std::vector of T or std::list of std::list of T
		 *
		 * Exemple:
		 * @code
		   // The Cartesian product of
		   {{1, 2, 3}, {a, b}, {I, II, III}}
		   // is
		   {
		   	{1, a, I},
		   	{1, a, II},
		   	{1, a, III},
		   	{1, b, I},
		   	{1, b, II},
		   	{1, b, III},
		   	{2, a, I},
		   	{2, a, II},
		   	{2, a, III},
		   	{2, b, I},
		   	{2, b, II},
		   	{2, b, III},
		   	{3, a, I},
		   	{3, a, II},
		   	{3, a, III},
		   	{3, b, I},
		   	{3, b, II},
		   	{3, b, III}
		   }
		   @endcode
		 *
		 * http://en.wikipedia.org/wiki/Cartesian_product
		 *
		 * @return the Cartesian product
		 */
		template <class container_of_container_of_T>
		container_of_container_of_T cartesian_product(container_of_container_of_T const & vector_of_values)
		{
			using container_of_T = typename container_of_container_of_T::value_type;
			using T = typename container_of_T::value_type;

			// Return
			container_of_container_of_T vector_of_results(1);

			// For each values
			for (container_of_T const & values : vector_of_values)
			{
				// To get new results
				container_of_container_of_T tmp;

				// For each actual results
				for (container_of_T & result : vector_of_results)
				{
					// For each values
					for (T const & e : values)
					{
						// Add new results
						tmp.push_back(result);
						tmp.back().push_back(e);
					}
				}

				// Replace old results
				vector_of_results = tmp;
			}

			// Return
			return vector_of_results;
		}
	}
}

#endif
