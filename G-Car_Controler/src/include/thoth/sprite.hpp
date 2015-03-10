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


#ifndef THOTH_SPRITE_HPP
#define THOTH_SPRITE_HPP

#include <functional>
#include <tuple>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "textures.hpp"
#include "transformable.hpp"


namespace thoth
{
	/**
	 * @brief Sprite
	 * 
	 * @code
	   #include <thoth/sprite.hpp>
	   @endcode
	 */
	class sprite : public thoth::transformable
	{
	private:
		
		/// Texture
		std::reference_wrapper<thoth::texture const> m_texture;
		
		/// Sprite
		sf::Sprite m_sprite;
		
		/// For serialization
		std::tuple<std::string> m_serialization;
		
	public:
		
		/// @brief Constructor
		/// @param[in] texture Texture (thoth::default_texture() by default)
		/// @param[in] x       Position x of the left top (0 by default)
		/// @param[in] y       Position x of the left top (0 by default)
		sprite
		(
			thoth::texture const & texture = thoth::default_texture(),
			float const x = 0.f,
			float const y = 0.f
		) :
			m_texture(texture),
			m_sprite(m_texture.get().texture_sfml())
		{
			set_position(x, y);
		}
		
		/// @brief Constructor
		/// @param[in] texture  Texture
		/// @param[in] position Position x and y of the left
		sprite(thoth::texture const & texture, hnc::vector2<float> const & position) :
			thoth::sprite(texture, position.x, position.y)
		{ }
		
		/// @brief Destructor
		virtual ~sprite() { }
		
		// Serialization
		
		template <class archive_t>
		void serialize(archive_t & archive, unsigned int const /*version*/ = 0) const
		{
			hnc::call_if_save_archive<archive_t>
			(
				[&]() -> void
				{
					archive & position();
					archive & rotation();
					archive & origin();
					archive & texture().key();
					archive & texture().image();
				}
			);
		}
		
		template <class archive_t>
		void serialize(archive_t & archive, unsigned int const /*version*/ = 0)
		{
			hnc::call_if_load_archive<archive_t>
			(
				[&]() -> void
				{
					hnc::vector2<float> position;
					archive & position;
					set_position(position);
					
					hnc::degree<float> rotation;
					archive & rotation;
					set_rotation(rotation);
					
					hnc::vector2<float> origin;
					archive & origin;
					set_origin(origin);
					
					std::string texture_key;
					archive & texture_key;
					
					hnc::vector2D<hnc::color> image;
					archive & image;
					
					if (thoth::textures().is_exists(texture_key) == false)
					{
						thoth::textures().load(texture_key, image);
					}
					
					set_texture(thoth::textures().at(texture_key));
				}
			);
		}
		
		// Sprite
		
		/// @brief Get the SFML sprite
		/// @return the SFML sprite
		sf::Sprite const & sfml_sprite() const { return m_sprite; }
		
		// Texture
		
		/// @brief Get the texture
		/// @return the texture
		thoth::texture const & texture() const { return m_texture.get(); }
		
		/// @brief Set texture
		/// @param[in] texture Texture
		void set_texture(thoth::texture const & texture)
		{
			m_texture = std::cref(texture);
			m_sprite.setTexture(m_texture.get().texture_sfml(), true);
		}
		
		// Transformable
		
		/// @copydoc thoth::transformable::position()
		virtual hnc::vector2<float> position() const override { return thoth::transformable::position_sfml(m_sprite); }
		
		/// @copydoc thoth::transformable::set_position(float const, float const)
		virtual void set_position(float const x, float const y) override { thoth::transformable::set_position_sfml(m_sprite, x, y); }
		
		using thoth::transformable::set_position;
		
		/// @copydoc thoth::transformable::move(float const, float const)
		virtual void move(float const d_x, float const d_y) override { thoth::transformable::move(m_sprite, d_x, d_y); }
		
		/// @copydoc thoth::transformable::rotation()
		virtual hnc::degree<float> rotation() const override { return thoth::transformable::rotation_sfml(m_sprite); }
		
		/// @copydoc thoth::transformable::set_rotation(hnc::degree<float> const &)
		virtual void set_rotation(hnc::degree<float> const & angle) override { thoth::transformable::set_rotation_sfml(m_sprite, angle); }
		
		using thoth::transformable::set_rotation;
		
		/// @copydoc thoth::transformable::rotate(hnc::degree<float> const &)
		virtual void rotate(hnc::degree<float> const & angle) override { thoth::transformable::rotate_sfml(m_sprite, angle); }
		
		using thoth::transformable::rotate;
		
		/// @copydoc thoth::transformable::origin()
		virtual hnc::vector2<float> origin() const override { return thoth::transformable::origin_sfml(m_sprite); }
		
		/// @copydoc thoth::transformable::set_origin(float const, float const)
		virtual void set_origin(float const x, float const y) override { thoth::transformable::set_origin_sfml(m_sprite, x, y); }
		
		using thoth::transformable::set_origin;
		
		/// @copydoc thoth::transformable::bounds_global()
		virtual hnc::geometry::rectangle<float> bounds_global() const override { return thoth::transformable::bounds_global_sfml(m_sprite); }
	};
	
	/// @brief Operator << between a sf::RenderWindow and a thoth::sprite
	/// @param[in,out] window A sf::RenderWindow
	/// @param[in]     sprite A thoth::sprite
	/// @return the output stream
	inline sf::RenderWindow & operator <<(sf::RenderWindow & window, thoth::sprite const & sprite)
	{
		window.draw(sprite.sfml_sprite());
		return window;
	}
}

#endif
