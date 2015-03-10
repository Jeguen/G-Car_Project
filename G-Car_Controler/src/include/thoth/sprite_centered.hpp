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


#ifndef THOTH_SPRITE_CENTERED_HPP
#define THOTH_SPRITE_CENTERED_HPP

#include "sprite.hpp"


namespace thoth
{
	/**
	 * @brief Centered sprite
	 * 
	 * @code
	   #include <thoth/sprite_centered.hpp>
	   @endcode
	 */
	class sprite_centered : public thoth::sprite
	{
	public:
		
		/// @brief Constructor
		/// @param[in] texture Texture (thoth::default_texture() by default)
		/// @param[in] x       Position x of the left top (0 by default)
		/// @param[in] y       Position x of the left top (0 by default)
		sprite_centered
		(
			thoth::texture const & texture = thoth::default_texture(),
			float const x = 0,
			float const y = 0
		) :
			thoth::sprite(texture)
		{
			set_origin(float(this->texture().size().x) / 2.f, float(this->texture().size().y) / 2.f);
			set_position(x, y);
		}
		
		/// @brief Set texture
		/// @param[in] texture Texture
		void set_texture(thoth::texture const & texture)
		{
			thoth::sprite::set_texture(texture);
			set_origin(float(this->texture().size().x) / 2.f, float(this->texture().size().y) / 2.f);
			set_position(position());
		}
	};
}

#endif
