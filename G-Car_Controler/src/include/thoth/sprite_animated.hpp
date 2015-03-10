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


#ifndef THOTH_SPRITE_ANIMATED_HPP
#define THOTH_SPRITE_ANIMATED_HPP

#include <string>
#include <unordered_map>

#include "sprite_centered.hpp"


namespace thoth
{
	/**
	 * @brief Animated sprite
	 * 
	 * @code
	   #include <thoth/sprite_animated.hpp>
	   @endcode
	 */
	class sprite_animated : public thoth::sprite_centered
	{
	private:
		
		/// Default texture
		thoth::sprite m_default_texture;
		
		/// Animations
		std::unordered_map<std::string, std::pair<float, std::vector<thoth::sprite>>> m_animations;
		
		/// Actual animation
		std::string m_actual_animation;
		
		/// Time elapsed
		float m_time_elapsed;
		
		/// Sprite is animated or not
		bool m_is_animated;
		

	public:
		
		/// @brief Constructor
		/// @param[in] texture Default texture (thoth::default_texture() by default)
		sprite_animated(thoth::texture const & texture = thoth::default_texture()) :
			thoth::sprite_centered(texture),
			m_default_texture(texture),
			m_animations(),
			m_actual_animation(),
			m_time_elapsed(0.f),
			m_is_animated(false)
		{ }
		
		/// @brief Add an animation
		/// @param[in] key                     Name of the animation
		/// @param[in] time_between_two_frames Time between two frames
		/// @param[in] textures                Texture in a std::vector<thoth::sprite>
		void add(std::string const & key, float const time_between_two_frames, std::vector<thoth::sprite> const & textures)
		{
			m_animations[key] = { time_between_two_frames, textures };
		}
		
		/// @brief Animate
		/// @param[in] key Name of the animation
		void animate(std::string const & key)
		{
			m_is_animated = true;
			
			if (key != m_actual_animation)
			{
				m_actual_animation = key;
				m_time_elapsed = 0.f;
			}
		}
		
		/// @brief Update
		/// @param[in] elapsed Time elapsed in the loop in seconds
		void update(float const elapsed)
		{
			if (m_is_animated)
			{
				m_time_elapsed += elapsed;
				
				auto const & animations = m_animations.at(m_actual_animation);
				auto const & time_between_two_frames = animations.first;
				auto const & textures = animations.second;
				
				set_texture(textures[std::size_t(m_time_elapsed / time_between_two_frames) % textures.size()].texture());
			}
		}
		
		/// @brief Reset the sprite (the sprite is not animated)
		void reset()
		{
			m_is_animated = false;
			set_texture(m_default_texture.texture());
		}
		
		/// @brief Return if the sprite is animated or not
		/// @return true is the sprite is animated, false otherwise
		bool is_animated() const
		{
			return m_is_animated;
		}
		
		/// @brief Set m_is_animated false
		void pause()
		{
			m_is_animated = false;
		}
		
		/// @brief Set m_is_animated true
		void resume()
		{
			m_is_animated = true;
		}
		
		/// @brief Return the sprite's actual position
		/// @return key corresponding for the actual position
		std::string animation() const
		{
			return m_actual_animation;
		}
		
	};
}

#endif
