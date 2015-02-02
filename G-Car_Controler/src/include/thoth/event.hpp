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


#ifndef THOTH_EVENT_HPP
#define THOTH_EVENT_HPP

#include <string>

#include <hnc/optional.hpp>
#include <hnc/vector2.hpp>

#include <SFML/Window/Event.hpp>

#include "keyboard.hpp"


namespace thoth
{
	/**
	 * @brief Event
	 * 
	 * @code
	   #include <thoth/event.hpp>
	   @endcode
	 */
	class event
	{
	private:
		
		/// Event is valid
		bool m_is_valid;
		
		/// Event
		sf::Event m_event;
		
	public:
		
		/// @brief Default constructor
		event() :
			m_is_valid(false),
			m_event()
		{ }
		
		/// @brief Constructor
		/// @param[in] is_valid True if evetn is valid
		/// @param[in] event    A sf::Event
		event(bool const is_valid, sf::Event const & event) :
			m_is_valid(is_valid),
			m_event(event)
		{ }
		
		/// @brief The event is valid?
		/// @return true if the event is valid, false otherwise
		bool is_valid() const { return m_is_valid; }
		
		/// @brief The event is valid?
		/// @return true if the event is valid, false otherwise
		operator bool() const { return is_valid(); }
		
		/// @brief Get the SFML event
		/// @return true if the event is valid, false otherwise
		sf::Event const & sfml_event() const { return m_event; }
		
		// Window
		
		/// @brief Event is window closed?
		/// @return true if the event is window closed, false otherwise
		bool window_closed() const { return m_event.type == sf::Event::Closed; }
		
		/// @brief Event is window resized?
		/// @return the size of the window in a hnc::optional<hnc::vector2<unsigned int>>
		hnc::optional<hnc::vector2<unsigned int>> window_resized() const
		{
			using return_type = hnc::optional<hnc::vector2<unsigned int>>;
			
			if (m_event.type == sf::Event::Resized)
			{
				return return_type({m_event.size.width, m_event.size.height});
			}
			else
			{
				return return_type();
			}
		}
		
		/// @brief Event is lost focus?
		/// @return true if the event is lost focus, false otherwise
		bool focus_lost() const { return m_event.type == sf::Event::LostFocus; }
		
		/// @brief Event is gained focus?
		/// @return true if the event is gained focus, false otherwise
		bool focus_gained() const { return m_event.type == sf::Event::GainedFocus; }
		
		// Text
		
		/// @brief Event is text entered?
		/// @return the character in a hnc::optional<char32_t>
		hnc::optional<char32_t> text() const
		{
			using return_type = hnc::optional<char32_t>;
			
			if (m_event.type == sf::Event::TextEntered)
			{
				return return_type(m_event.text.unicode);
			}
			else
			{
				return return_type();
			}
		}
		
		// Key
		
		/// @brief Event is key pressed?
		/// @return the key in a hnc::optional<thoth::keyboard>
		hnc::optional<thoth::keyboard> key_pressed() const
		{
			using return_type = hnc::optional<thoth::keyboard>;
			
			if (m_event.type == sf::Event::KeyPressed)
			{
				return return_type(thoth::keyboard(m_event.key.code));
			}
			else
			{
				return return_type();
			}
		}
		
		/// @brief Event is key released?
		/// @return the key in a hnc::optional<thoth::keyboard>
		hnc::optional<thoth::keyboard> key_released() const
		{
			using return_type = hnc::optional<thoth::keyboard>;
			
			if (m_event.type == sf::Event::KeyReleased)
			{
				return return_type(thoth::keyboard(m_event.key.code));
			}
			else
			{
				return return_type();
			}
		}
		
		// Mouse
		
		/// @brief Event is mouse left button pressed?
		/// @return true if the event is mouse left button pressed, false otherwise
		bool mouse_button_pressed_left() const
		{
			return m_event.type == sf::Event::MouseButtonPressed && m_event.mouseButton.button == sf::Mouse::Left;
		}
		
		/// @brief Event is mouse left button released?
		/// @return true if the event is mouse left button released, false otherwise
		bool mouse_button_released_left() const
		{
			return m_event.type == sf::Event::MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Left;
		}
		
		/// @brief Event is mouse right button pressed?
		/// @return true if the event is mouse right button pressed, false otherwise
		bool mouse_button_pressed_right() const
		{
			return m_event.type == sf::Event::MouseButtonPressed && m_event.mouseButton.button == sf::Mouse::Right;
		}
		
		/// @brief Event is mouse right button released?
		/// @return true if the event is mouse right button released, false otherwise
		bool mouse_button_released_right() const
		{
			return m_event.type == sf::Event::MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Right;
		}
		
		/// @brief Event is mouse middle button pressed?
		/// @return true if the event is mouse middle button pressed, false otherwise
		bool mouse_button_pressed_middle() const
		{
			return m_event.type == sf::Event::MouseButtonPressed && m_event.mouseButton.button == sf::Mouse::Middle;
		}
		
		/// @brief Event is mouse middle button released?
		/// @return true if the event is mouse middle button released, false otherwise
		bool mouse_button_released_middle() const
		{
			return m_event.type == sf::Event::MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Middle;
		}
		
		/// @brief Event is mouse extra_0 button pressed?
		/// @return true if the event is mouse extra_0 button pressed, false otherwise
		bool mouse_button_pressed_extra_0() const
		{
			return m_event.type == sf::Event::MouseButtonPressed && m_event.mouseButton.button == sf::Mouse::XButton1;
		}
		
		/// @brief Event is mouse extra_0 button released?
		/// @return true if the event is mouse extra_0 button released, false otherwise
		bool mouse_button_released_extra_0() const
		{
			return m_event.type == sf::Event::MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::XButton1;
		}
		
		/// @brief Event is mouse extra_1 button pressed?
		/// @return true if the event is mouse extra_1 button pressed, false otherwise
		bool mouse_button_pressed_extra_1() const
		{
			return m_event.type == sf::Event::MouseButtonPressed && m_event.mouseButton.button == sf::Mouse::XButton2;
		}
		
		/// @brief Event is mouse extra_1 button released?
		/// @return true if the event is mouse extra_1 button released, false otherwise
		bool mouse_button_released_extra_1() const
		{
			return m_event.type == sf::Event::MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::XButton2;
		}
		
		/// @brief Event is mouse wheel moved?
		/// @return the delta in a hnc::optional<int>
		hnc::optional<int> mouse_wheel_moved() const
		{
			using return_type = hnc::optional<int>;
			
			if (m_event.type == sf::Event::MouseWheelMoved)
			{
				return return_type(m_event.mouseWheel.delta);
			}
			else
			{
				return return_type();
			}
		}
		
		/// @brief Event is mouse moved?
		/// @return true if the event is mouse moved, false otherwise
		bool mouse_moved() const { return m_event.type == sf::Event::MouseMoved; }
		
		/// @brief Event is mouse entered?
		/// @return true if the event is mouse entered, false otherwise
		bool mouse_entered() const { return m_event.type == sf::Event::MouseEntered; }
		
		/// @brief Event is mouse left?
		/// @return true if the event is mouse left, false otherwise
		bool mouse_left() const { return m_event.type == sf::Event::MouseLeft; }
	};
}

#endif
