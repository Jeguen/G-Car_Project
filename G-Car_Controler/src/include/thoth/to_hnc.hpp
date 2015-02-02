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


#ifndef THOTH_TO_HNC_HPP
#define THOTH_TO_HNC_HPP

#include <hnc/vector2.hpp>
#include <hnc/vector2D.hpp>
#include <hnc/color.hpp>
#include <hnc/geometry/rectangle.hpp>
#include <hnc/int.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace thoth
{
	/**
	 * @brief Convert a sf::Vector2<T> into a hnc::vector2<T>
	 * 
	 * @code
	   #include <thoth/to_hnc.hpp>
	   @endcode
	 * 
	 * @param[in] vector2 A sf::Vector2<T>
	 * 
	 * @return the hnc::vector2<T>
	 */
	template <class T>
	hnc::vector2<T> to_hnc(sf::Vector2<T> const & vector2)
	{
		return { vector2.x, vector2.y };
	}
	
	/**
	 * @brief Convert a sf::Color into a hnc::color
	 * 
	 * @code
	   #include <thoth/to_hnc.hpp>
	   @endcode
	 * 
	 * @param[in] color A sf::Color
	 * 
	 * @return the hnc::color
	 */
	inline hnc::color to_hnc(sf::Color const & color)
	{
		return { color.r, color.g, color.b, color.a };
	}
	
	/**
	 * @brief Convert a sf::Rect<T> into a hnc::geometry::rectangle<T>
	 * 
	 * @code
	   #include <thoth/to_hnc.hpp>
	   @endcode
	 * 
	 * @param[in] rectangle A sf::Rect<T>
	 * 
	 * @return the hnc::geometry::rectangle<T>
	 */
	template <class T>
	hnc::geometry::rectangle<T> to_hnc(sf::Rect<T> const & rectangle)
	{
		return { rectangle.left, rectangle.top, rectangle.width, rectangle.height };
	}
	
	/**
	 * @brief Convert a sf::Image into a hnc::vector2D<hnc::color>
	 * 
	 * @code
	   #include <thoth/to_hnc.hpp>
	   @endcode
	 * 
	 * @param[in] image A sf::Image
	 * 
	 * @return the hnc::vector2D<hnc::color>
	 */
	inline hnc::vector2D<hnc::color> to_hnc(sf::Image const & image)
	{
		hnc::vector2D<hnc::color> image_hnc(image.getSize().x, image.getSize().y);
		
		for (std::size_t i = 0; i < image_hnc.nb_row(); ++i)
		{
			for (std::size_t j = 0; j < image_hnc.nb_col(); ++j)
			{
				auto const color_sfml = image.getPixel(hnc::uint_t(i), hnc::uint_t(j));
				image_hnc(i, j) = thoth::to_hnc(color_sfml);
			}
		}
		
		return image_hnc;
	}
}

#endif
