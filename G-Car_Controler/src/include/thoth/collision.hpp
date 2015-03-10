// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

// This file is part of Thōth.

// Thōth is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Thōth is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with Thōth. If not, see <http://www.gnu.org/licenses/>


#ifndef THOTH_COLLISION_HPP
#define THOTH_COLLISION_HPP

#include <hnc/geometry.hpp>

#include "sprite.hpp"


namespace thoth
{
	/**
	 * @brief Collision
	 * 
	 * Detect collision if the total area of a sprite overlaps the other. @n
	 * 
	 * @note If you take care about transparency of the sprite, please use thoth::collision_pixel_perfect function.
	 * 
	 * @code
	   #include <thoth/collision.hpp>
	   @endcode
	 * 
	 * @param[in] sprite_a A thoth::sprite
	 * @param[in] sprite_b A thoth::sprite
	 * 
	 * @return true if sprites are in collision, false otherwise
	 */
	inline bool collision(thoth::sprite const & sprite_a, thoth::sprite const & sprite_b)
	{
		using hnc::geometry::is_in_rectangle;
		
		auto const bounds_a = sprite_a.bounds_global();
		auto const bounds_b = sprite_b.bounds_global();
		
		// In bounds_a
		
		if (is_in_rectangle(bounds_b.left, bounds_b.top, bounds_a)) { return true; }
		
		if (is_in_rectangle(bounds_b.left + bounds_b.width, bounds_b.top, bounds_a)) { return true; }
		
		if (is_in_rectangle(bounds_b.left, bounds_b.top + bounds_b.height, bounds_a)) { return true; }
		
		if (is_in_rectangle(bounds_b.left + bounds_b.width, bounds_b.top + bounds_b.height, bounds_a)) { return true; }
		
		// In bounds_b
		
		if (is_in_rectangle(bounds_a.left, bounds_a.top, bounds_b)) { return true; }
		
		if (is_in_rectangle(bounds_a.left + bounds_a.width, bounds_a.top, bounds_b)) { return true; }
		
		if (is_in_rectangle(bounds_a.left, bounds_a.top + bounds_a.height, bounds_b)) { return true; }
		
		if (is_in_rectangle(bounds_a.left + bounds_a.width, bounds_a.top + bounds_a.height, bounds_b)) { return true; }
		
		return false;
	}
	
	/**
	 * @brief Pixel perfect collision
	 * 
	 * Detect collision only on no-transparent parts of the sprite. @n
	 * 
	 * @note If you do not care about transparency of the sprite, please use thoth::collision function.
	 * @code
	   #include <thoth/collision.hpp>
	   @endcode
	 * 
	 * @param[in] sprite_a A thoth::sprite
	 * @param[in] sprite_b A thoth::sprite
	 *
	 * @return true if sprites are in collision (pixel perfect), false otherwise
	 */
	inline bool collision_pixel_perfect(thoth::sprite const & sprite_a, thoth::sprite const & sprite_b)
	{
		// No collision
		if (thoth::collision(sprite_a, sprite_b) == false)
		{
			return false;
		}
		// Possible collision
		else
		{
			// TODO
			return false;
		}
	}
}

#endif
