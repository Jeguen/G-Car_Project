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


#ifndef THOTH_FONT_HPP
#define THOTH_FONT_HPP

#include <string>

#include <SFML/Graphics/Font.hpp>

#include "media.hpp"
#include "screen.hpp"


namespace thoth
{
	/**
	 * @brief Font
	 * 
	 * @code
	   #include <thoth/font.hpp>
	   @endcode
	 */
	class font
	{
	private:
		
		/// Font
		sf::Font m_font;
		
	public:
		
		/// @brief Constructor
		/// @param[in] font_filename Filename of the font
		font(std::string const & font_filename = thoth::media::default_font_path())
		{
			m_font.loadFromFile(font_filename);
		}
		
		/// @brief Get the SFML font
		/// @return the SFML font
		sf::Font const & sfml_font() const { return m_font; }
		
	public:
		
		/// @brief Get default font size
		/// @return the default font size
		static float default_font_size()
		{
			// TODO
			return 7.5;
		}
		
		/**
		 * @brief Get size of the font in pixels
		 * 
		 * http://en.wikipedia.org/wiki/Dots_per_inch
		 * http://msdn.microsoft.com/en-us/library/windows/desktop/ff684173%28v=vs.85%29.aspx
		 * 
		 * @param[in] font_size Size of the font
		 * @param[in] dpi       Dots per inch of the screen (thoth::font::dpi() by default)
		 * 
		 * @return the size of the font in pixels
		 */
		static unsigned int size_in_pixel(float const font_size, float const dpi = thoth::screen::dpi())
		{
			return static_cast<unsigned int>(std::trunc(font_size * dpi / 72.f));
		}
		
		/// @brief Return the default font
		/// @return the default texture
		static thoth::font const & default_font()
		{
			static thoth::font default_font;
			return default_font;
		}
	};
}

#endif
