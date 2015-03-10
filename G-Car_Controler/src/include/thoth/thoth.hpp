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


#ifndef THOTH_HPP
#define THOTH_HPP

#include <string>

#ifdef hnc_linux
	#include <X11/Xlib.h>
#endif


/*! @mainpage Thōth https://gitorious.org/thoth
 * 
 * https://gitorious.org/thoth
 *
 * @section section_introduction Introduction
 *
 * Thōth is a library that uses SFML. @n
 * The main part of Thōth is a isometric engine. @n
 * Thōth also contains generic SFML classes and functions such as centered sprite, animated sprite, texture management and collision detection.
 * 
 * Thōth is developed under GNU Affero General Public License 3+
 * 
 * @section section_system_requirement System requirement for hnc
 * 
 * Thōth uses CMake build system.
 * 
 * The required packages are: @n
 * build-essential cmake git doxygen
 * 
 * The optional packages (but recommended) are: @n
 * build-essential cmake libglew-dev libx11-dev libxext-dev libgl-dev libxrandr-dev libfreetype6-dev libjpeg-dev libsndfile-dev libopenal-dev
 * 
 * SFML 2.1 and hnc are required: @n
 * http://www.sfml-dev.org/ @n
 * https://gitorious.org/hnc
 * 
 * To install SFML 2.1 and hnc, you can download and execute: @n
 * https://gitorious.org/install_project/install_project/source/master:example/install_project_SFML_2.1.py @n
 * https://gitorious.org/install_project/install_project/source/master:example/install_project_hnc.py @n
 * from https://gitorious.org/install_project
 * 
 * @section section_installation Installation of hnc
 * 
 * @subsection subsection_installation_with_cmake With CMake
 * 
 * Your C++ compiler must support common features of C++11 @n
 * GCC 4.7 works (GCC 4.7.2 is in Debian Wheezy)
 * 
 * Use CMake to build hnc:
 * @code
   mkdir build
   cd build
   cmake .. #-DCMAKE_INSTALL_PREFIX=/path/to/install/Thōth
   make
   # make doc
   # make test
   make install # su -c "make install" # sudo make install
   @endcode
 * 
 * @subsection subsection_installation_without_cmake Without CMake
 * 
 * Thōth is an header-only library, you can copy the include directory in /usr/local or in your project.
 * 
 * @section section_use Use Thōth
 * 
 * If you use CMake, add these lines in your CMakeLists.txt:
 * @code
   # Thōth
   message(STATUS "---")
   find_package(thoth REQUIRED)
   # See /Thōth/installation/path/lib/thoth/thoth-config.cmake for CMake variables
   @endcode
 * 
 * If you have make the documentation, the doxygen is in: @n
 * /Thōth/installation/path/share/thoth/doxygen/
 * 
 */


/// @brief Thōth
namespace thoth
{
	/// @brief Version of Thōth
	inline std::string version() { return "0.0.0"; }

	/// @brief Codename of Thōth
	inline std::string codename() { return "hope ;)"; }
	
	
	/// @brief Automatic initialization of Thōth
	class initialization
	{
	private:
		
		/// @brief Constructor
		initialization()
		{
			#ifdef hnc_linux
				XInitThreads();
			#endif
		}
	public:
		
		friend inline thoth::initialization const & init();
	};
	
	/// @brief Create a thoth::initialization
	inline thoth::initialization const & init()
	{
		static thoth::initialization initialization;
		return initialization;
	}
}

#endif
