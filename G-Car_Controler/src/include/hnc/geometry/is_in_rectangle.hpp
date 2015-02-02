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


#ifndef HNC_GEOMETRY_IS_IN_RECTANGLE_HPP
#define HNC_GEOMETRY_IS_IN_RECTANGLE_HPP

#include "rectangle.hpp"
#include "../vector2.hpp"


namespace hnc
{
	namespace geometry
	{
		/**
		 * @brief Test if a point is in the rectangle
		 * 
		 * @code
		   	#include <hnc/geometry.hpp>
		   @endcode
		 * 
		 * @param[in] x         Coordinate x
		 * @param[in] y         Coordinate y
		 * @param[in] rectangle A hnc::geometry::rectangle
		 *
		 * @return true if the point { x, y } is in the rectangle, false otherwise
		 */
		template <class T>
		bool is_in_rectangle(T const & x, T const & y, hnc::geometry::rectangle<T> const & rectangle)
		{
			return
			(
				x >= rectangle.left &&
				x <= rectangle.left + rectangle.width &&
				y >= rectangle.top &&
				y <= rectangle.top + rectangle.height
			);
		}
		
		/**
		 * @brief Test if a point is in the rectangle
		 * 
		 * @code
		   	#include <hnc/geometry.hpp>
		   @endcode
		 * 
		 * @param[in] point     A hnc::vector2<T>
		 * @param[in] rectangle A hnc::geometry::rectangle
		 *
		 * @return true if the point { x, y } is in the rectangle, false otherwise
		 */
		template <class T>
		bool is_in_rectangle(hnc::vector2<T> const & point, hnc::geometry::rectangle<T> const & rectangle)
		{
			return hnc::geometry::is_in_rectangle(point.x, point.y, rectangle);
		}
	}
}

#endif
