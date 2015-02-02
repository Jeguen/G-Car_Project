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


#ifndef THOTH_MEDIA_HPP
#define THOTH_MEDIA_HPP

#include <string>

#include <hnc/filesystem.hpp>
#include <hnc/except.hpp>


namespace thoth
{
	/**
	 * @brief Thōth media
	 * 
	 * @code
	   #include <thoth/media.hpp>
	   @endcode
	 */
	namespace media
	{
		/// @brief Return the path where are the media
		/// @return the path where are the media
		inline std::string const & path()
		{
			static std::string const path = []() -> std::string
			{
				// build directory (for the development)
				{
					std::string const path = "../share/thoth";
					if (hnc::filesystem::file_exists(path + "/README.txt")) { return path; }
				}
				
				// CMake build system
				{
					std::string const path = THOTH_MEDIA_DIR;
					if (hnc::filesystem::file_exists(path + "/README.txt")) { return path; }
				}
				
				// /usr/local/share/
				{
					std::string const path = "/usr/local/share/thoth";
					if (hnc::filesystem::file_exists(path + "/README.txt")) { return path; }
				}
				
				// /usr/share/
				{
					std::string const path = "/usr/share/thoth";
					if (hnc::filesystem::file_exists(path + "/README.txt")) { return path; }
				}
				
				// Not found
				throw hnc::except::file_not_found("Thōth media directory not found");
			}();
			
			return path;
		}
		
		/**
		 * @brief Thōth media
		 * 
		 * @code
		   #include <thoth/media.hpp>
		   @endcode
		 */
		namespace texture
		{
			/// @brief Return the path where are the textures
			/// @return the path where are the textures
			inline std::string const & path()
			{
				static std::string const path = thoth::media::path() + "/texture";
				return path;
			}
		}
		
		/**
		 * @brief Return the default texture path
		 * 
		 * @code
		   #include <thoth/media.hpp>
		   @endcode
		 * 
		 * @return the path default texture path
		 */
		inline std::string const & default_texture_path()
		{
			static std::string const path = thoth::media::texture::path() + "/dev/default_texture.png";
			return path;
		}
		
		namespace font
		{
			/// @brief Return the path where are the fonts
			/// @return the path where are the fonts
			inline std::string const & path()
			{
				static std::string const path = thoth::media::path() + "/font";
				return path;
			}
		}
		
		/**
		 * @brief Return the default font path
		 * 
		 * @code
		   #include <thoth/media.hpp>
		   @endcode
		 * 
		 * @return the path default font path
		 */
		inline std::string const & default_font_path()
		{
			static std::string const path = thoth::media::font::path() + "/dejavu/DejaVuSans.ttf";
			return path;
		}
	}
}

#endif
