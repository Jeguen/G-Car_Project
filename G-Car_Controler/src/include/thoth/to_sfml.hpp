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


#ifndef THOTH_TO_SFML_HPP
#define THOTH_TO_SFML_HPP

#include <hnc/vector2.hpp>
#include <hnc/color.hpp>
#include <hnc/geometry/rectangle.hpp>
#include <hnc/vector2D.hpp>
#include <hnc/int.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace thoth
{
	/**
	 * @brief Convert a hnc::vector2<T> into a sf::Vector2<T>
	 * 
	 * @code
	   #include <thoth/to_sfml.hpp>
	   @endcode
	 * 
	 * @param[in] vector2 A hnc::vector2<T>
	 * 
	 * @return the sf::Vector2<T>
	 */
	template <class T>
	sf::Vector2<T> to_sfml(hnc::vector2<T> const & vector2)
	{
		return sf::Vector2<T>(vector2.x, vector2.y);
	}
	
	/**
	 * @brief Convert a hnc::color into a sf::Color
	 * 
	 * @code
	   #include <thoth/to_sfml.hpp>
	   @endcode
	 * 
	 * @param[in] color A hnc::color
	 * 
	 * @return the sf::Color
	 */
	inline sf::Color to_sfml(hnc::color const & color)
	{
		return sf::Color(color.r.i, color.g.i, color.b.i, color.a.i);
	}
	
	/**
	 * @brief Convert a hnc::geometry::rectangle<T> into a sf::Rect<T>
	 * 
	 * @code
	   #include <thoth/to_sfml.hpp>
	   @endcode
	 * 
	 * @param[in] rectangle A hnc::geometry::rectangle<T>
	 * 
	 * @return the sf::Rect<T>
	 */
	template <class T>
	sf::Rect<T> to_sfml(hnc::geometry::rectangle<T> const & rectangle)
	{
		return sf::Rect<T>(rectangle.left, rectangle.top, rectangle.width, rectangle.height);
	}
	
	/**
	 * @brief Convert a hnc::vector2D<hnc::color> into a sf::Image
	 * 
	 * @code
	   #include <thoth/to_hnc.hpp>
	   @endcode
	 * 
	 * @param[in] image A hnc::vector2D<hnc::color>
	 * 
	 * @return the sf::Image
	 */
	inline sf::Image to_sfml(hnc::vector2D<hnc::color> const & image)
	{
		sf::Image image_sfml;
		image_sfml.create(hnc::uint_t(image.nb_row()), hnc::uint_t(image.nb_col()));
		
		for (std::size_t i = 0; i < std::size_t(image_sfml.getSize().x); ++i)
		{
			for (std::size_t j = 0; j < std::size_t(image_sfml.getSize().y); ++j)
			{
				image_sfml.setPixel(hnc::uint_t(i), hnc::uint_t(j), thoth::to_sfml(image(i, j)));
			}
		}
		
		return image_sfml;
	}
}

#endif
