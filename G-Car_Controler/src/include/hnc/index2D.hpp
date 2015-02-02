// Copyright © 2012-2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef INDEX2D_HPP
#define INDEX2D_HPP

#include "assert.hpp"


namespace hnc
{
	/// @brief To manipulate 2D index
	namespace index2D
	{
		/**
		 * @brief Transform a 2D index (i, j) into a index 1D (i * row_size + j)
		 *
		 * @code
		   #include <hnc/index2D.hpp>
		   @endcode
		 * 
		 * @param[in] i        row number
		 * @param[in] j        col number
		 * @param[in] row_size size of a row (>= 1)
		 *
		 * @pre The size of the row must be >= 1
		 *
		 * @exception std::invalid_argument: hnc::hassert row_size >= 1 if NDEBUG is not defined
		 *
		 * @return index 1D (i * row_size + j)
		 */
		template <class index_t>
		index_t index1D(index_t const i, index_t const j, index_t const row_size)
		{
			#ifndef NDEBUG
				hnc::hassert(row_size >= index_t(1), std::invalid_argument("hnc::index2D::index1D, row_size must be >= 1"));
			#endif
			return (i * row_size + j);
		}
	}
}

#endif
