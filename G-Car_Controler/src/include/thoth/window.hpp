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


#ifndef THOTH_WINDOW_HPP
#define THOTH_WINDOW_HPP

#include <string>

#include <hnc/vector2.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include "to_hnc.hpp"
#include "to_sfml.hpp"
#include "event.hpp"


namespace thoth
{
	/**
	 * @brief Window
	 * 
	 * @code
	   #include <thoth/window.hpp>
	   @endcode
	 */
	class window
	{
	private:
		
		/// SFML window
		sf::RenderWindow m_window;
		
	public:
		
		/// @brief Constructor
		/// @param[in] width  Width of the window
		/// @param[in] height Height of the window
		/// @param[in] title  Title of the window
		window
		(
			unsigned int const width, unsigned int const height,
			std::string const & title
		) :
			m_window(sf::VideoMode(width, height), title)
		{ }
		
		/// @brief Default constructor
		window() : window(1024, 768, "thoth::window") { }
		
		/// @brief Get the SFML window
		/// @return the SFML window
		sf::RenderWindow const & sfml_window() const { return m_window; }
		
		/// @brief Get next event
		/// @return next event
		thoth::event event()
		{
			sf::Event event;
			return thoth::event(m_window.pollEvent(event), event);
		}
		
		/// @brief Clear the window with a color
		/// @param[in] color A hnc::color (white by default)
		void clear(hnc::color const & color = hnc::color::white()) { m_window.clear(thoth::to_sfml(color)); }
		
		/// @brief Draw an object
		/// @param[in] t Object to be drawn
		/// @pre Operator << between a sf::RenderWindow and a T exists
		/// @return the window
		template <class T>
		thoth::window & draw(T const & t) { m_window << t; return *this; }
		
		/// @brief Update the window
		void update() { m_window.display(); }
		
		/// @brief The window is open?
		/// @return true is the window is open, false otherwise
		bool is_open() const { return m_window.isOpen(); }
		
		/// @brief The window is open?
		/// @return true is the window is open, false otherwise
		operator bool() const { return is_open(); }
		
		/// @brief Close the window
		void close() { m_window.close(); }
		
		/// @brief Get the size of the window
		/// @return the size of the window
		hnc::vector2<unsigned int> size() const { return thoth::to_hnc(m_window.getSize()); }
		
		/// @brief Set the size of the window
		/// @param[in] width  Width of the window
		/// @param[in] height Height of the window
		void set_size(unsigned int const width, unsigned int const height)
		{
			m_window.setSize(sf::Vector2u(width, height));
			// TODO
		}
		
		/// @brief Set the size of the window
		/// @param[in] size Size of the window
		void set_size(hnc::vector2<unsigned int> const & size) { set_size(size.x, size.y); }
		
// 		/// @brief Get the title of the window
// 		/// @return the title of the window
// 		std::string title() const { return m_window.getTitle(); } // TODO
		
		/// @brief Set the title of the window
		/// @param[in] title Title
		void set_title(std::string const & title) { m_window.setTitle(title); }
	};
	
	/// @brief Operator << between a thoth::window and a T
	/// @param[in,out] window A thoth::window
	/// @param[in]     t      Object to be drawn
	/// @return the window
	template <class T>
	thoth::window & operator <<(thoth::window & window, T const & t)
	{
		return window.draw(t);
	}
}

#endif
