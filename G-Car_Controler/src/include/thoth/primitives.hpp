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


#ifndef THOTH_PRIMITIVES_HPP
#define THOTH_PRIMITIVES_HPP

#include <vector>

#include <hnc/vector2.hpp>
#include <hnc/except.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "to_sfml.hpp"
#include "transformable.hpp"


namespace thoth
{
	/**
	 * @brief Primitives
	 * 
	 * @code
	   #include <thoth/primitives.hpp>
	   @endcode
	 */
	class primitives : public thoth::transformable
	{
	private:
		
		/// Texture
		std::vector<sf::Vertex> m_pixels;
		
	public:
		
		/// @brief Default constructor
		primitives() = default;
		
		/// @brief Destructor
		virtual ~primitives() { }
		
		/// @brief Add a pixel
		/// @param[in] x     Position on X axis
		/// @param[in] y     Position on Y axis
		/// @param[in] color A hnc::color (black by default)
		void push_back(float const x, float const y, hnc::color const & color = hnc::color::black())
		{
			m_pixels.emplace_back(sf::Vector2f(x, y), thoth::to_sfml(color));
		}
		
		/// @brief Add a pixel
		/// @param[in] position Position
		/// @param[in] color A hnc::color (black by default)
		void push_back(hnc::vector2<float> const & position, hnc::color const & color = hnc::color::black())
		{
			push_back(position.x, position.y, color);
		}
		
		/// @brief Get the SFML vertices
		/// @return the SFML vertices
		std::vector<sf::Vertex> const & sfml_vertices() const { return m_pixels; }
		
		// Transformable
		
		/// @copydoc thoth::transformable::position()
		virtual hnc::vector2<float> position() const override
		{
			// TODO
			throw hnc::except::incomplete_implementation("thoth::primitives::position is not implemented yet");
		}
		
		/// @copydoc thoth::transformable::set_position(float const, float const)
		virtual void set_position(float const x, float const y) override
		{
			// TODO
			throw hnc::except::incomplete_implementation("thoth::primitives::set_position is not implemented yet");
		}
		
		using thoth::transformable::set_position;
		
		/// @copydoc thoth::transformable::move(float const, float const)
		virtual void move(float const d_x, float const d_y) override
		{
			for (auto & e : m_pixels)
			{
				e.position.x += d_x;
				e.position.y += d_y;
			}
		}
		
		/// @copydoc thoth::transformable::rotation()
		virtual hnc::degree<float> rotation() const override
		{
			// TODO
			throw hnc::except::incomplete_implementation("thoth::primitives::rotation is not implemented yet");
		}
		
		/// @copydoc thoth::transformable::set_rotation(hnc::degree<float> const &)
		virtual void set_rotation(hnc::degree<float> const & angle) override
		{
			// TODO
			throw hnc::except::incomplete_implementation("thoth::primitives::set_rotation is not implemented yet");
		}
		
		using thoth::transformable::set_rotation;
		
		/// @copydoc thoth::transformable::rotate(hnc::degree<float> const &)
		virtual void rotate(hnc::degree<float> const & angle) override
		{
			// TODO
			throw hnc::except::incomplete_implementation("thoth::primitives::set_rotation is not implemented yet");
		}
		
		using thoth::transformable::rotate;
		
		/// @copydoc thoth::transformable::origin()
		virtual hnc::vector2<float> origin() const override
		{
			// TODO
			throw hnc::except::incomplete_implementation("thoth::primitives::origin is not implemented yet");
		}
		
		/// @copydoc thoth::transformable::set_origin(float const, float const)
		virtual void set_origin(float const x, float const y) override
		{
			// TODO
			throw hnc::except::incomplete_implementation("thoth::primitives::set_origin is not implemented yet");
		}
		
		using thoth::transformable::set_origin;
		
		/// @copydoc thoth::transformable::bounds_global()
		virtual hnc::geometry::rectangle<float> bounds_global() const override
		{
			hnc::geometry::rectangle<float> bounds;
			
			if (m_pixels.empty() == false)
			{
				bounds.left = m_pixels[0].position.x;
				bounds.top = m_pixels[0].position.y;
				bounds.width = m_pixels[0].position.x;
				bounds.height = m_pixels[0].position.y;
				
				for (std::size_t i = 1; i < m_pixels.size(); ++i)
				{
					bounds.left = std::min(bounds.left, m_pixels[i].position.x);
					bounds.top = std::min(bounds.top, m_pixels[i].position.y);
					bounds.width = std::max(bounds.width, m_pixels[i].position.x);
					bounds.height = std::max(bounds.height, m_pixels[i].position.y);
				}
			}
			
			return bounds;
		}
	};
	
	
	/**
	 * @brief Pixels
	 * 
	 * @code
	   #include <thoth/primitives.hpp>
	   @endcode
	 */
	class pixels : public thoth::primitives
	{ };
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::pixels
	/// @param[in,out] window A sf::RenderWindow
	/// @param[in]     pixels A thoth::pixels
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::pixels const & pixels)
	{
		window.draw(pixels.sfml_vertices().data(), static_cast<unsigned int>(pixels.sfml_vertices().size()), sf::Points);
		return window;
	}
	
	
	/**
	 * @brief Lines
	 * 
	 * @code
	   #include <thoth/primitives.hpp>
	   @endcode
	 */
	class lines : public thoth::primitives
	{
	public:
		
		/// @brief Add a line
		/// @param[in] x_start     Position on X axis of the start
		/// @param[in] y_start     Position on Y axis of the start
		/// @param[in] color_start A hnc::color of the start
		/// @param[in] x_end       Position on X axis of the end
		/// @param[in] y_end       Position on Y axis of the end
		/// @param[in] color_end   A hnc::color of the end
		void push_back
		(
			float const x_start, float const y_start, hnc::color const & color_start,
			float const x_end, float const y_end, hnc::color const & color_end
		)
		{
			thoth::primitives::push_back(x_start, y_start, color_start);
			thoth::primitives::push_back(x_end, y_end, color_end);
		}
		
		/// @brief Add a black line
		/// @param[in] x_start     Position on X axis of the start
		/// @param[in] y_start     Position on Y axis of the start
		/// @param[in] x_end       Position on X axis of the end
		/// @param[in] y_end       Position on Y axis of the end
		/// @param[in] color       A hnc::color (black by default)
		void push_back
		(
			float const x_start, float const y_start,
			float const x_end, float const y_end,
			hnc::color const & color = hnc::color::black()
		)
		{
			push_back(x_start, y_start, color, x_end, y_end, color);
		}
		
		/// @brief Add a line
		/// @param[in] position_start Position of the start
		/// @param[in] color_start    A hnc::color of the start
		/// @param[in] position_end   Position of the start
		/// @param[in] color_end      A hnc::color of the end
		void push_back
		(
			hnc::vector2<float> const & position_start, hnc::color const & color_start,
			hnc::vector2<float> const & position_end, hnc::color const & color_end
		)
		{
			push_back(position_start.x, position_start.y, color_start, position_end.x, position_end.y, color_end);
		}
		
		/// @brief Add a line
		/// @param[in] position_start Position of the start
		/// @param[in] position_end   Position of the start
		/// @param[in] color          A hnc::color (black by default)
		void push_back
		(
			hnc::vector2<float> const & position_start,
			hnc::vector2<float> const & position_end,
			hnc::color const & color = hnc::color::black()
		)
		{
			push_back(position_start, color, position_end, color);
		}
	};
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::lines
	/// @param[in,out] window A sf::RenderWindow
	/// @param[in]     lines  A thoth::lines
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::lines const & lines)
	{
		window.draw(lines.sfml_vertices().data(), static_cast<unsigned int>(lines.sfml_vertices().size()), sf::Lines);
		return window;
	}
	
	
	/**
	 * @brief Lines strip
	 * 
	 * @code
	   #include <thoth/primitives.hpp>
	   @endcode
	 */
	class lines_strip : public thoth::primitives
	{ };
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::lines_strip
	/// @param[in,out] window      A sf::RenderWindow
	/// @param[in]     lines_strip A thoth::lines_strip
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::lines_strip const & lines_strip)
	{
		window.draw(lines_strip.sfml_vertices().data(), static_cast<unsigned int>(lines_strip.sfml_vertices().size()), sf::LinesStrip);
		return window;
	}
	
	
	/**
	 * @brief Triangles
	 * 
	 * @code
	   #include <thoth/primitives.hpp>
	   @endcode
	 */
	class triangles : public thoth::primitives
	{
	public:
		
		/// @brief Add a triangle
		/// @param[in] x_0     Position on X axis of first point
		/// @param[in] y_0     Position on Y axis of first point
		/// @param[in] color_0 A hnc::color of first point
		/// @param[in] x_1     Position on X axis of second point
		/// @param[in] y_1     Position on Y axis of second point
		/// @param[in] color_1 A hnc::color of second point
		/// @param[in] x_2     Position on X axis of third point
		/// @param[in] y_2     Position on Y axis of third point
		/// @param[in] color_2 A hnc::color of third point
		void add
		(
			float const x_0, float const y_0, hnc::color const & color_0,
			float const x_1, float const y_1, hnc::color const & color_1,
			float const x_2, float const y_2, hnc::color const & color_2
		)
		{
			push_back(x_0, y_0, color_0);
			push_back(x_1, y_1, color_1);
			push_back(x_2, y_2, color_2);
		}
		
		/// @brief Add a triangle
		/// @param[in] x_0   Position on X axis of first point
		/// @param[in] y_0   Position on Y axis of first point
		/// @param[in] x_1   Position on X axis of second point
		/// @param[in] y_1   Position on Y axis of second point
		/// @param[in] x_2   Position on X axis of third point
		/// @param[in] y_2   Position on Y axis of third point
		/// @param[in] color A hnc::color (black by default)
		void add
		(
			float const x_0, float const y_0,
			float const x_1, float const y_1,
			float const x_2, float const y_2,
			hnc::color const & color = hnc::color::black()
		)
		{
			add(x_0, y_0, color, x_1, y_1, color, x_2, y_2, color);
		}
		
		/// @brief Add a triangle
		/// @param[in] position_0 Position of first point
		/// @param[in] color_0    A hnc::color of first point
		/// @param[in] position_1 Position of second point
		/// @param[in] color_1    A hnc::color of second point
		/// @param[in] position_2 Position of third point
		/// @param[in] color_2    A hnc::color of third point
		void add
		(
			hnc::vector2<float> const & position_0, hnc::color const & color_0,
			hnc::vector2<float> const & position_1, hnc::color const & color_1,
			hnc::vector2<float> const & position_2, hnc::color const & color_2
		)
		{
			add(position_0.x, position_0.y, color_0, position_1.x, position_1.y, color_1, position_2.x, position_2.y, color_2);
		}
		
		/// @brief Add a triangle
		/// @param[in] position_0 Position of first point
		/// @param[in] position_1 Position of second point
		/// @param[in] position_2 Position of third point
		/// @param[in] color      A hnc::color (black by default)
		void add(hnc::vector2<float> const & position_0, hnc::vector2<float> const & position_1, hnc::vector2<float> const & position_2, hnc::color const & color)
		{
			add(position_0, color, position_1, color, position_2, color);
		}
	};
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::triangles
	/// @param[in,out] window    A sf::RenderWindow
	/// @param[in]     triangles A thoth::triangles
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::triangles const & triangles)
	{
		window.draw(triangles.sfml_vertices().data(), static_cast<unsigned int>(triangles.sfml_vertices().size()), sf::Triangles);
		return window;
	}
	
	
	/**
	 * @brief Triangles strip
	 * 
	 * @code
	   #include <thoth/primitives.hpp>
	   @endcode
	 */
	class triangles_strip : public thoth::primitives
	{ };
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::triangles_strip
	/// @param[in,out] window          A sf::RenderWindow
	/// @param[in]     triangles_strip A thoth::triangles
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::triangles_strip const & triangles_strip)
	{
		window.draw(triangles_strip.sfml_vertices().data(), static_cast<unsigned int>(triangles_strip.sfml_vertices().size()), sf::TrianglesStrip);
		return window;
	}
	
	
	/**
	 * @brief Triangles fan
	 * 
	 * @code
	   #include <thoth/primitives.hpp>
	   @endcode
	 */
	class triangles_fan : public thoth::primitives
	{ };
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::triangles_fan
	/// @param[in,out] window        A sf::RenderWindow
	/// @param[in]     triangles_fan A thoth::triangles
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::triangles_fan const & triangles_fan)
	{
		window.draw(triangles_fan.sfml_vertices().data(), static_cast<unsigned int>(triangles_fan.sfml_vertices().size()), sf::TrianglesStrip);
		return window;
	}
	
	
	/**
	 * @brief Quads
	 * 
	 * @code
	   #include <thoth/primitives.hpp>
	   @endcode
	 */
	class quads : public thoth::primitives
	{
	public:
		
		/// @brief Add a quad
		/// @param[in] x_0     Position on X axis of first point
		/// @param[in] y_0     Position on Y axis of first point
		/// @param[in] color_0 A hnc::color of first point
		/// @param[in] x_1     Position on X axis of second point
		/// @param[in] y_1     Position on Y axis of second point
		/// @param[in] color_1 A hnc::color of second point
		/// @param[in] x_2     Position on X axis of third point
		/// @param[in] y_2     Position on Y axis of third point
		/// @param[in] color_2 A hnc::color of third point
		/// @param[in] x_2     Position on X axis of fourth point
		/// @param[in] y_2     Position on Y axis of fourth point
		/// @param[in] color_2 A hnc::color of fourth point
		void add
		(
			float const x_0, float const y_0, hnc::color const & color_0,
			float const x_1, float const y_1, hnc::color const & color_1,
			float const x_2, float const y_2, hnc::color const & color_2,
			float const x_3, float const y_3, hnc::color const & color_3
		)
		{
			push_back(x_0, y_0, color_0);
			push_back(x_1, y_1, color_1);
			push_back(x_2, y_2, color_2);
			push_back(x_3, y_3, color_3);
		}
		
		/// @brief Add a quad
		/// @param[in] x_0   Position on X axis of first point
		/// @param[in] y_0   Position on Y axis of first point
		/// @param[in] x_1   Position on X axis of second point
		/// @param[in] y_1   Position on Y axis of second point
		/// @param[in] x_2   Position on X axis of third point
		/// @param[in] y_2   Position on Y axis of third point
		/// @param[in] x_3   Position on X axis of fourth point
		/// @param[in] y_3   Position on Y axis of fourth point
		/// @param[in] color A hnc::color (black by default)
		void add
		(
			float const x_0, float const y_0,
			float const x_1, float const y_1,
			float const x_2, float const y_2,
			float const x_3, float const y_3,
			hnc::color const & color = hnc::color::black()
		)
		{
			add(x_0, y_0, color, x_1, y_1, color, x_2, y_2, color, x_3, y_3, color);
		}
		
		/// @brief Add a quad
		/// @param[in] position_0 Position of first point
		/// @param[in] color_0    A hnc::color of first point
		/// @param[in] position_1 Position of second point
		/// @param[in] color_1    A hnc::color of second point
		/// @param[in] position_2 Position of third point
		/// @param[in] color_2    A hnc::color of third point
		/// @param[in] position_3 Position of fourth point
		/// @param[in] color_3    A hnc::color of fourth point
		void add
		(
			hnc::vector2<float> const & position_0, hnc::color const & color_0,
			hnc::vector2<float> const & position_1, hnc::color const & color_1,
			hnc::vector2<float> const & position_2, hnc::color const & color_2,
			hnc::vector2<float> const & position_3, hnc::color const & color_3
		)
		{
			add(position_0.x, position_0.y, color_0, position_1.x, position_1.y, color_1, position_2.x, position_2.y, color_2, position_3.x, position_3.y, color_3);
		}
		
		/// @brief Add a quad
		/// @param[in] position_0 Position of first point
		/// @param[in] position_1 Position of second point
		/// @param[in] position_2 Position of third point
		/// @param[in] position_3 Position of fourth point
		/// @param[in] color      A hnc::color (black by default)
		void add
		(
			hnc::vector2<float> const & position_0,
			hnc::vector2<float> const & position_1,
			hnc::vector2<float> const & position_2,
			hnc::vector2<float> const & position_3,
			hnc::color const & color
		)
		{
			add(position_0, color, position_1, color, position_2, color, position_3, color);
		}
	};
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::quads
	/// @param[in,out] window A sf::RenderWindow
	/// @param[in]     quads  A thoth::quads
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::quads const & quads)
	{
		window.draw(quads.sfml_vertices().data(), static_cast<unsigned int>(quads.sfml_vertices().size()), sf::Quads);
		return window;
	}
}

#endif
