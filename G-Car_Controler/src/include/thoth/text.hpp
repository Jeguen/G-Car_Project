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


#ifndef THOTH_TEXT_HPP
#define THOTH_TEXT_HPP

#include <string>

#include <hnc/color.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "font.hpp"
#include "transformable.hpp"
#include "to_sfml.hpp"


namespace thoth
{
	/**
	 * @brief Text
	 * 
	 * @code
	   #include <thoth/text.hpp>
	   @endcode
	 */
	class text : public thoth::transformable
	{
	private:
		
		/// Text
		sf::Text m_text;
		
	public:
		
		/// @brief Constructor from string
		/// @param[in] text  A text (empty string by default)
		/// @param[in] color A hnc::color (black by default)
		template <class string_t = std::string>
		text(string_t const & text = "", hnc::color const & color = hnc::color::black()) :
			m_text
			(
				text,
				thoth::font::default_font().sfml_font(),
				thoth::font::size_in_pixel(thoth::font::default_font_size())
			)
		{
			set_color(color);
		}
		
		/// @brief Get the SFML text
		/// @return the SFML text
		sf::Text const & sfml_text() const { return m_text; }
		
		/// @brief Set the text
		/// @param[in] text A text
		template <class string_t = std::string>
		void set_text(string_t const & text = "")
		{
			m_text.setString(text);
		}
		
		/// @brief Set the color
		/// @param[in] color A hnc::color
		void set_color(hnc::color const & color)
		{
			m_text.setColor(thoth::to_sfml(color));
		}
		
		// Transformable
		
		/// @copydoc thoth::transformable::position()
		virtual hnc::vector2<float> position() const override { return thoth::transformable::position_sfml(m_text); }
		
		/// @copydoc thoth::transformable::set_position(float const, float const)
		virtual void set_position(float const x, float const y) override { thoth::transformable::set_position_sfml(m_text, x, y); }
		
		using thoth::transformable::set_position;
		
		/// @copydoc thoth::transformable::move(float const, float const)
		virtual void move(float const d_x, float const d_y) override { thoth::transformable::move(m_text, d_x, d_y); }
		
		/// @copydoc thoth::transformable::rotation()
		virtual hnc::degree<float> rotation() const override { return thoth::transformable::rotation_sfml(m_text); }
		
		/// @copydoc thoth::transformable::set_rotation(hnc::degree<float> const &)
		virtual void set_rotation(hnc::degree<float> const & angle) override { thoth::transformable::set_rotation_sfml(m_text, angle); }
		
		using thoth::transformable::set_rotation;
		
		/// @copydoc thoth::transformable::rotate(hnc::degree<float> const &)
		virtual void rotate(hnc::degree<float> const & angle) override { thoth::transformable::rotate_sfml(m_text, angle); }
		
		using thoth::transformable::rotate;
		
		/// @copydoc thoth::transformable::origin()
		virtual hnc::vector2<float> origin() const override { return thoth::transformable::origin_sfml(m_text); }
		
		/// @copydoc thoth::transformable::set_origin(float const, float const)
		virtual void set_origin(float const x, float const y) override { thoth::transformable::set_origin_sfml(m_text, x, y); }
		
		using thoth::transformable::set_origin;
		
		/// @copydoc thoth::transformable::bounds_global()
		virtual hnc::geometry::rectangle<float> bounds_global() const override { return thoth::transformable::bounds_global_sfml(m_text); }
	};
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::text
	/// @param[in,out] window A sf::RenderWindow
	/// @param[in]     text   A thoth::text
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::text const & text)
	{
		window.draw(text.sfml_text());
		return window;
	}
}

#endif
