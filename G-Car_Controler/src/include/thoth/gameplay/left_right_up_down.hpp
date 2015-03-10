// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr
// Copyright © 2014 Rodolphe Cargnello, rodolphe.cargnello@gmail.com

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

 
#ifndef THOTH_GAMEPLAY_LEFT_RIGHT_UP_DOWN_HPP
#define THOTH_GAMEPLAY_LEFT_RIGHT_UP_DOWN_HPP

#include <SFML/Graphics.hpp>

#include "../sprite_animated.hpp"


namespace thoth
{
	namespace gameplay
	{
		/**
		 * @brief Animate and move the sprite
		 * 
		 * @code
		   #include <thoth/gameplay.hpp>
		   @endcode
		 * 
		 * @param[in] moving Moving distance
		 * @param[in] sprite A thoth::sprite_animated with "left", "right", "up" and "down" animations
		 */
		void left_right_up_down(float const moving, thoth::sprite_animated & sprite)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				sprite.animate("left");
				sprite.move(-moving, 0.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				sprite.animate("right");
				sprite.move(moving, 0.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				sprite.animate("up");
				sprite.move(0.f, -moving);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				sprite.animate("down");
				sprite.move(0.f, moving);
			}
			else
			{
				sprite.reset();
			}
		}
	}
}

#endif
