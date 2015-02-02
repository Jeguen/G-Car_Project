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


#ifndef THOTH_MOUSE_HPP
#define THOTH_MOUSE_HPP

#include <iostream>

#include <hnc/vector2.hpp>

#include <SFML/Window/Mouse.hpp>

#include "to_hnc.hpp"
#include "window.hpp"


namespace thoth
{
	/**
	 * @brief Test if left mouse button is pressed
	 * 
	 * @code
	   #include <thoth/mouse.hpp>
	   @endcode
	 *
	 * @return true if the left mouse button is pressed, false otherwise
	 */
	inline bool mouse_button_pressed_left()
	{
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}
	
	/**
	 * @brief Test if right mouse button is pressed
	 * 
	 * @code
	   #include <thoth/mouse.hpp>
	   @endcode
	 *
	 * @return true if the right mouse button is pressed, false otherwise
	 */
	inline bool mouse_button_pressed_right()
	{
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	}
	
	/**
	 * @brief Test if middle mouse button is pressed
	 * 
	 * @code
	   #include <thoth/mouse.hpp>
	   @endcode
	 *
	 * @return true if the middle mouse button is pressed, false otherwise
	 */
	inline bool mouse_button_pressed_middle()
	{
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
	}
	
	/**
	 * @brief Test if extra 0 mouse button is pressed
	 * 
	 * @code
	   #include <thoth/mouse.hpp>
	   @endcode
	 *
	 * @return true if the extra 0 mouse button is pressed, false otherwise
	 */
	inline bool mouse_button_pressed_extra_0()
	{
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton1);
	}
	
	/**
	 * @brief Test if extra 1 mouse button is pressed
	 * 
	 * @code
	   #include <thoth/mouse.hpp>
	   @endcode
	 *
	 * @return true if the extra 1 mouse button is pressed, false otherwise
	 */
	inline bool mouse_button_pressed_extra_1()
	{
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2);
	}
	
	/**
	 * @brief Mouse functions
	 * 
	 * @code
	   #include <thoth/mouse.hpp>
	   @endcode
	 */
	namespace mouse
	{
		// position
		
		/**
		 * @brief Return the global position of the mouse
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @return the global position of the mouse
		 */
		inline hnc::vector2<int> position()
		{
			return thoth::to_hnc(sf::Mouse::getPosition());
		}
		
		/**
		 * @brief Return the position of the mouse in the window coordinates
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @param[in] window A sf::RenderWindow
		 *
		 * @return the position of the mouse in the window coordinates
		 */
		inline hnc::vector2<int> position(sf::RenderWindow const & window)
		{
			return thoth::to_hnc(sf::Mouse::getPosition(window));
		}
		
		/**
		 * @brief Return the position of the mouse in the window coordinates
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @param[in] window A thoth::window
		 *
		 * @return the position of the mouse in the window coordinates
		 */
		inline hnc::vector2<int> position(thoth::window const & window)
		{
			return thoth::mouse::position(window.sfml_window());
		}
		
		// set_position
		
		/**
		 * @brief Set the global position of the mouse
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @param[in] x the global position on X axis of the mouse
		 * @param[in] y the global position on Y axis of the mouse
		 */
		inline void set_position(int const x, int const y)
		{
			return sf::Mouse::setPosition(sf::Vector2i(x, y));
		}
		
		/**
		 * @brief Set the global position of the mouse
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @param[in] position the global position of the mouse
		 */
		inline void set_position(hnc::vector2<int> const & position)
		{
			return sf::Mouse::setPosition(thoth::to_sfml(position));
		}
		
		/**
		 * @brief Set the position of the mouse in the window coordinates
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @param[in] x the global position on X axis of the mouse in the window coordinates
		 * @param[in] y the global position on Y axis of the mouse in the window coordinates
		 * @param[in] window A sf::RenderWindow
		 */
		inline void set_position(int const x, int const y, sf::RenderWindow const & window)
		{
			return sf::Mouse::setPosition(sf::Vector2i(x, y), window);
		}
		
		/**
		 * @brief Set the position of the mouse in the window coordinates
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @param[in] position the position of the mouse in the window coordinates
		 * @param[in] window A sf::RenderWindow
		 */
		inline void set_position(hnc::vector2<int> const & position, sf::RenderWindow const & window)
		{
			return sf::Mouse::setPosition(thoth::to_sfml(position), window);
		}
		
		/**
		 * @brief Set the position of the mouse in the window coordinates
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @param[in] x the global position on X axis of the mouse in the window coordinates
		 * @param[in] y the global position on Y axis of the mouse in the window coordinates
		 * @param[in] window A thoth::window
		 */
		inline void set_position(int const x, int const y, thoth::window const & window)
		{
			return thoth::mouse::set_position(x, y, window.sfml_window());
		}
		
		/**
		 * @brief Set the position of the mouse in the window coordinates
		 * 
		 * @code
		   #include <thoth/mouse.hpp>
		   @endcode
		 *
		 * @param[in] position the position of the mouse in the window coordinates
		 * @param[in] window A thoth::window
		 */
		inline void set_position(hnc::vector2<int> const & position, thoth::window const & window)
		{
			return thoth::mouse::set_position(position, window.sfml_window());
		}
	}
}

#endif
