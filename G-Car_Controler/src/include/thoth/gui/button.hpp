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

 
#ifndef THOTH_GUI_HPP
#define THOTH_GUI_HPP

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../text.hpp"
#include "../primitives.hpp"
#include "../transformable.hpp"
#include "../mouse_event.hpp"


namespace thoth
{
	namespace gui
	{
		/**
		* @brief Button
		* 
		* @code
		  #include <thoth/gui.hpp>
		  @endcode
		*/
		class button : public thoth::transformable, public thoth::mouse_event_t
		{
		private:
			
			/// Text
			thoth::text m_text;
			
			/// Lines
			thoth::lines_strip m_lines_strip;
			
			/// Background
			thoth::quads m_background;
			
			/// Draw background?
			bool m_background_draw;
			
		public:
			
			/// @brief Constructor from string
			/// @param[in] text A text (empty string by default)
			template <class string_t = std::string>
			button(string_t const & text = "") :
				m_text(),
				m_lines_strip(),
				m_background(),
				m_background_draw(false)
			{
				m_text.set_position(6.f, 6.f);
				set_text(text);
			}
			
			/// @brief Get the text
			/// @return the text
			thoth::text const & text() const { return m_text; }
			
			/// @brief Draw the button on sf::RenderWindow
			/// @param[in,out] window A sf::RenderWindow
			void draw(sf::RenderWindow & window) const
			{
				if (m_background_draw) { window << m_background; }
				window << m_lines_strip;
				window << text();
			}
			
			/// @brief Set the text
			/// @param[in] text A text
			template <class string_t = std::string>
			void set_text(string_t const & text = "")
			{
				m_text.set_text(text);
				
				auto const bounds = m_text.bounds_global();
				m_lines_strip.push_back(1.f, 1.f);
				m_lines_strip.push_back(5.f + bounds.right() + 5.f, 1.f);
				m_lines_strip.push_back(5.f + bounds.right() + 5.f, 5.f + bounds.bottom() + 5.f);
				m_lines_strip.push_back(0.f, 5.f + bounds.bottom() + 5.f);
				m_lines_strip.push_back(1.f, 1.f);
				
				auto const & vertices = m_lines_strip.sfml_vertices();
				m_background.add
				(
					vertices[0].position.x, vertices[0].position.y,
					vertices[1].position.x, vertices[1].position.y,
					vertices[2].position.x, vertices[2].position.y,
					vertices[3].position.x, vertices[3].position.y,
					hnc::color::grey()
				);
			}
			
			// Transformable
			
			/// @copydoc thoth::transformable::position()
			virtual hnc::vector2<float> position() const override
			{
				return thoth::transformable::position_thoth(m_text);
			}
			
			/// @copydoc thoth::transformable::set_position(float const, float const)
			virtual void set_position(float const x, float const y) override
			{
				thoth::transformable::set_position_thoth(m_text, x, y);
			}
			
			using thoth::transformable::set_position;
			
			/// @copydoc thoth::transformable::move(float const, float const)
			virtual void move(float const d_x, float const d_y) override
			{
				thoth::transformable::move(m_text, d_x, d_y);
			}
			
			/// @copydoc thoth::transformable::rotation()
			virtual hnc::degree<float> rotation() const override
			{
				return thoth::transformable::rotation_thoth(m_text);
			}
			
			/// @copydoc thoth::transformable::set_rotation(hnc::degree<float> const &)
			virtual void set_rotation(hnc::degree<float> const & angle) override
			{
				thoth::transformable::set_rotation_thoth(m_text, angle);
			}
			
			using thoth::transformable::set_rotation;
			
			/// @copydoc thoth::transformable::rotate(hnc::degree<float> const &)
			virtual void rotate(hnc::degree<float> const & angle) override
			{
				thoth::transformable::rotate_thoth(m_text, angle);
			}
			
			using thoth::transformable::rotate;
			
			/// @copydoc thoth::transformable::origin()
			virtual hnc::vector2<float> origin() const override
			{
				return thoth::transformable::origin_thoth(m_text);
			}
			
			/// @copydoc thoth::transformable::set_origin(float const, float const)
			virtual void set_origin(float const x, float const y) override
			{
				thoth::transformable::set_origin_thoth(m_text, x, y);
			}
			
			using thoth::transformable::set_origin;
			
			/// @copydoc thoth::transformable::bounds_global()
			virtual hnc::geometry::rectangle<float> bounds_global() const override
			{
				return thoth::transformable::bounds_global_thoth(m_lines_strip);
			}
			
			// Mouse event
		
			/// @brief Call mouse button pressed left
			virtual void call_mouse_button_pressed_left()
			{
				m_background_draw = true;
				thoth::mouse_event_t::call_mouse_button_pressed_left();
			}
			
			/// @brief Call mouse button released left
			virtual void call_mouse_button_released_left()
			{
				m_background_draw = false;
				thoth::mouse_event_t::call_mouse_button_released_left();
			}
		};
	
		/// @brief Operator << between a sf::RenderWindow and a thoth::gui::button
		/// @param[in,out] window A sf::RenderWindow
		/// @param[in]     button A thoth::gui::button
		/// @return the output stream
		inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::gui::button const & button)
		{
			button.draw(window);
			return window;
		}
	}
}

#endif
