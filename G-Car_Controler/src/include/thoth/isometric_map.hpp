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


#ifndef THOTH_ISOMETRIC_MAP_HPP
#define THOTH_ISOMETRIC_MAP_HPP

#include <vector>
#include <unordered_map>
#include <cmath>

#include <hnc/optional.hpp>

#include "sprite_centered.hpp"


namespace thoth
{
	/**
	 * @brief Isometric map
	 * 
	 * @code
	   #include <thoth/isometric_map.hpp>
	   @endcode
	 */
	class isometric_map
	{
	private:
		
		/// Tile width
		std::size_t m_tile_width;
		
		/// Tile height
		std::size_t m_tile_height;
		
		/// Half of tile width
		std::size_t m_tile_width_half;
		
		/// Half of tile height
		std::size_t m_tile_height_half;
		
		/// Number of lines
		std::size_t m_nb_line;
		
		/// Tiles per size
		std::unordered_map<std::intmax_t, std::unordered_map<std::intmax_t, std::size_t>> m_sizes_i_tiles;
		
	public:
		
		/// Tiles
		std::vector<thoth::sprite_centered> tiles;
		
	public:
		
		/// @brief Default constructor
		isometric_map() = default;
		
		/// @brief Constructor
		/// @param[in] default_texture Default texture for all tile
		/// @param[in] tile_width      Width of a tile (example: 222)
		/// @param[in] tile_height     Height of a tile (example: 128)
		/// @param[in] nb_line         Approximate number of lines wanted
		isometric_map
		(
			thoth::texture const & default_texture,
			std::size_t const tile_width,
			std::size_t const tile_height,
			std::size_t const nb_line
		) :
			m_tile_width(tile_width),
			m_tile_height(tile_height),
			m_tile_width_half(tile_width / 2),
			m_tile_height_half(tile_height / 2),
			m_nb_line(nb_line + nb_line % 2)
		{
			// Tiles
			for (std::size_t line = 0; line < m_nb_line; ++line)
			{
				std::size_t nb_column = std::min(line, m_nb_line - line);
				
				for (std::size_t column = 0; column < nb_column; ++column)
				{
					tiles.emplace_back
					(
						// Texture
						default_texture,
						// x
						float(column * tile_width)
						+ float(((m_nb_line / 2) - nb_column + 1) * tile_width_half()),
						// y
						float(line * tile_height_half())
					);
					
					//std::cout << tiles.back().position() << std::endl;
				}
			}
			tiles.shrink_to_fit();
			
			// Tiles per size
			for (std::size_t i = 0; i < tiles.size(); ++i)
			{
				m_sizes_i_tiles[std::intmax_t(tiles[i].position().x)][std::intmax_t(tiles[i].position().y)] = i;
			}
		}
		
		/// @brief Get tile width
		/// @return tile width
		std::size_t tile_width() const { return m_tile_width; }
		
		/// @brief Get tile height
		/// @return tile height
		std::size_t tile_height() const { return m_tile_height; }
		
		/// @brief Get half of tile width
		/// @return half of tile width
		std::size_t tile_width_half() const { return m_tile_width_half; }
		
		/// @brief Get half of tile height
		/// @return half of tile height
		std::size_t tile_height_half() const { return m_tile_height_half; }
		
		/// @brief Get iterator on closer sprite
		/// @param[in] position Position in view
		/// @return iterator on closer sprite
		template <class vector2_t>
		std::vector<thoth::sprite_centered>::iterator get_sprite_it(vector2_t const & position)
		{
			// TODO Optimize with math
			
			using x_y_t = decltype(position.x);
			
			auto x_round = std::intmax_t(std::round(position.x / x_y_t(m_tile_width_half)) * m_tile_width_half);
			auto y_round = std::intmax_t(std::round(position.y / x_y_t(m_tile_height_half)) * m_tile_height_half);
			
			auto x_trunc = std::intmax_t(std::trunc(position.x / x_y_t(m_tile_width_half)) * m_tile_width_half);
			auto y_trunc = std::intmax_t(std::trunc(position.y / x_y_t(m_tile_height_half)) * m_tile_height_half);
			
			auto is_selectioned_tile = [&](std::intmax_t const x, std::intmax_t const y) -> std::vector<thoth::sprite_centered>::iterator
			{
				std::vector<thoth::sprite_centered>::iterator it = tiles.end();
				
				// Tile exists
				if (m_sizes_i_tiles.find(x) != m_sizes_i_tiles.end())
				{
					if (m_sizes_i_tiles.at(x).find(y) != m_sizes_i_tiles.at(x).end())
					{
						// Collision
						if (true) // TODO
						{
							it = tiles.begin() + std::ptrdiff_t(m_sizes_i_tiles.at(x).at(y));
						}
					}
				}
				
				return it;
			};
			
			// x_round, y_round
			{
				auto const it = is_selectioned_tile(x_round, y_round);
				if (it != tiles.end()) { return it; }
			}
			
			// x_round, y_trunc
			{
				auto const it = is_selectioned_tile(x_round, y_trunc);
				if (it != tiles.end()) { return it; }
			}
			
			// x_trunc, y_round
			{
				auto const it = is_selectioned_tile(x_trunc, y_round);
				if (it != tiles.end()) { return it; }
			}
			
			// x_trunc, y_trunc
			{
				auto const it = is_selectioned_tile(x_trunc, y_trunc);
				if (it != tiles.end()) { return it; }
			}
			
			return tiles.end();
		}
	};
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::isometric_map
	/// @param[in,out] window        A sf::RenderWindow
	/// @param[in]     isometric_map A thoth::isometric_map
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::isometric_map const & isometric_map)
	{
		for (auto const & tile : isometric_map.tiles)
		{
			window << tile;
		}
		
		return window;
	}
}

#endif
