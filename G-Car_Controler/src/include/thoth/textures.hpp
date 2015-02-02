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


#ifndef THOTH_TEXTURES_HPP
#define THOTH_TEXTURES_HPP

#include <string>
#include <unordered_map>

#include <hnc/vector2.hpp>
#include <hnc/vector2D.hpp>
#include <hnc/color.hpp>
#include <hnc/optional.hpp>
#include <hnc/filesystem.hpp>
#include <hnc/except.hpp>
#include <hnc/serialization.hpp>

#include <SFML/Graphics/Texture.hpp>

#include "media.hpp"
#include "to_hnc.hpp"
#include "to_sfml.hpp"


namespace thoth
{
	// Forward declaration
	inline hnc::vector2D<hnc::color> textures_get_image(std::string const & key);
	
	/**
	 * @brief Texture
	 * 
	 * @code
	   #include <thoth/texture.hpp>
	   @endcode
	 */
	class texture
	{
	private:
		
		/// Key for thoth::textures()
		std::string m_key;
		
		/// Filename of the texture
		std::string m_filename;
		
		/// Texture
		sf::Texture m_texture;
		
		/// Image
		hnc::optional<hnc::vector2D<hnc::color>> m_image;
		
	public:
		
		/// @brief Default constructor
		texture() = default;
		
		/// @brief Constructor from filename
		/// @param[in] key              Key for thoth::textures()
		/// @param[in] texture_filename Filename of the texture
		texture
		(
			std::string const & key,
			std::string const & texture_filename
		) :
			m_key(key),
			m_filename(texture_filename),
			m_texture(),
			m_image()
		{
			m_texture.loadFromFile(texture_filename);
			m_texture.setSmooth(true);
		}
		
		/// @brief Constructor from image
		/// @param[in] key   Key for thoth::textures()
		/// @param[in] image A hnc::vector2D<hnc::color>
		texture
		(
			std::string const & key,
			hnc::vector2D<hnc::color> const & image
		) :
			m_key(key),
			m_filename(),
			m_texture(),
			m_image()
		{
			sf::Image image_sfml = thoth::to_sfml(image);
			m_texture.loadFromImage(image_sfml);
			m_texture.setSmooth(true);
		}
		
		// Getter
		
		/// @brief Return the size
		/// @return the size
		hnc::vector2<unsigned int> size() const
		{
			return { m_texture.getSize().x, m_texture.getSize().y };
		}
		
		/// @brief Return the key for thoth::textures()
		/// @return the key for thoth::textures()
		std::string const & key() const
		{
			return m_key;
		}
		
		/// @brief Return the orginal filename
		/// @return the orginal filename
		std::string const & filename() const
		{
			return m_filename;
		}
		
		/// @brief Return the SFML texture
		/// @return the SFML texture
		sf::Texture const & texture_sfml() const
		{
			return m_texture;
		}
		
		/// @brief Return the image, a hnc::vector2D<hnc::color>
		/// @return the image
		hnc::vector2D<hnc::color> const & image() const
		{
			if (bool(m_image) == false)
			{
				thoth::textures_get_image(key());
			}
			
			return *m_image;
		}
		
		// Load
		
		/// @brief Load the image from the texture
		/// @return the image
		hnc::vector2D<hnc::color> load_image()
		{
			if (bool(m_image) == false)
			{
				sf::Image image_sfml; image_sfml.loadFromFile(m_filename);
				m_image = thoth::to_hnc(image_sfml);
			}
			
			return *m_image;
		}
		
		// Serialization
		
		hnc_generate_serialize_member_function(m_key, m_image)
		
		void before_save_serialization() const
		{
			std::cout << "- before_save_serialization const" << std::endl;
			image();
		}
		
		void after_load_serialization() const
		{
			std::cout << "- after_load_serialization const" << std::endl;
			//m_texture.loadFromImage(hnc::to_sfml(*m_image));
		}
	};
	
	/**
	 * @brief Textures
	 * 
	 * @code
	   #include <thoth/textures.hpp>
	   @endcode
	 */
	class textures_t
	{
	private:
		
		/// Textures
		std::unordered_map<std::string, thoth::texture> m_textures;
		
	public:
		
		/// @brief Add a texture from filename
		/// @param[in] key              Key of the texture
		/// @param[in] texture_filename Filename of the texture
		/// @return the texture
		thoth::texture const & load_extern(std::string const & key, std::string const & texture_filename)
		{
// 			auto const it_bool = m_textures.emplace(key, texture_filename);
// 			return it_bool.first->second;
			
			thoth::texture const & texture = m_textures[key] = thoth::texture(key, texture_filename);
			return texture;
		}
		
		/// @brief Add a texture from filename
		/// @param[in] key                    Key of the texture
		/// @param[in] thoth_texture_filename Filename of the texture in Thōth textures
		/// @return the texture
		thoth::texture const & load(std::string const & key, std::string const & thoth_texture_filename)
		{
			return load_extern(key, thoth::media::texture::path() + thoth_texture_filename);
		}
		
		/// @brief Add a texture from a image
		/// @param[in] key   Key of the texture
		/// @param[in] image A hnc::vector2D<hnc::color>
		/// @return the texture
		thoth::texture const & load(std::string const & key, hnc::vector2D<hnc::color> const & image)
		{
			thoth::texture & texture = m_textures[key] = thoth::texture(key, image);
			return texture;
		}
		
		/// @brief Texture exists?
		/// @param[in] key Key of the texture
		/// @return true if the texture exists, false otherwise
		bool is_exists(std::string const & key) const
		{
			return m_textures.find(key) != m_textures.end();
		}
		
		/// @brief Return the texture
		/// @param[in] key Key of the texture
		/// @return the texture
		thoth::texture const & at(std::string const & key) const
		{
			return m_textures.at(key);
		}
		
		/// @brief Return the image form the texture
		/// @param[in] key Key of the texture
		/// @return the image of the texture
		hnc::vector2D<hnc::color> get_image(std::string const & key)
		{
			return m_textures.at(key).load_image();
		}
	};
	
	/**
	 * @brief Textures
	 * 
	 * @code
	   #include <thoth/textures.hpp>
	   @endcode
	 */
	inline thoth::textures_t & textures()
	{
		static thoth::textures_t textures;
		return textures;
	}
	
	/**
	 * @brief Return the default texture
	 * 
	 * @code
	   #include <thoth/textures.hpp>
	   @endcode
	 *
	 * @return the default texture
	 */
	inline thoth::texture const & default_texture()
	{
		static thoth::texture const & default_texture = thoth::textures().load_extern("thoth_default_texture", thoth::media::default_texture_path());
		return default_texture;
	}
	
	/**
	 * @brief Return the image form the texture
	 * 
	 * @code
	   #include <thoth/textures.hpp>
	   @endcode
	 *
	 * @param[in] key Key of the texture
	 *
	 * @return the image of the texture
	 */
	inline hnc::vector2D<hnc::color> textures_get_image(std::string const & key)
	{
		return thoth::textures().get_image(key);
	}
}

#endif
