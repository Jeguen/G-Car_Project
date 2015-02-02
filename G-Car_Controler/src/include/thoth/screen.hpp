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


#ifndef THOTH_SCREEN_HPP
#define THOTH_SCREEN_HPP

#include <vector>

#include <hnc/vector2.hpp>
#include <hnc/int.hpp>
#include <hnc/except.hpp>

#include <SFML/Window.hpp>

#ifdef hnc_linux
	#include <X11/Xlib.h>
	#include <X11/extensions/Xrandr.h>
#endif

#ifdef hnc_os_x
	extern "C"
	{
		#include <CoreGraphics/CGDisplayConfiguration.h>
		#include <CoreGraphics/CGDirectDisplay.h>
	}
#endif

#ifdef hnc_windows
	#include <d2d1.h>
#endif


namespace thoth
{
	/**
	 * @brief Screen
	 * 
	 * @code
	   #include <thoth/screen.hpp>
	   @endcode
	 */
	namespace screen
	{
		/**
		 * @brief Get the size of the (logical) screen in pixels
		 * 
		 * @code
		   #include <thoth/screen.hpp>
		   @endcode
		 * 
		 * @return the the size of the screen in pixels
		 */
		inline hnc::vector2<unsigned int> size()
		{
			#ifdef hnc_linux
			
				Display * display = XOpenDisplay(nullptr);
				
				return { hnc::uint_t(DisplayWidth(display, 0)), hnc::uint_t(DisplayHeight(display, 0)) };
				
			#elif hnc_os_x
				
				return { sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
				
			#elif hnc_windows
				
				return { sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
				
			#else
				
				return { sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
				
			#endif
		}
		
		/**
		 * @brief Get the size of the (logical) screen in millimeters
		 * 
		 * @code
		   #include <thoth/screen.hpp>
		   @endcode
		 * 
		 * @return the the size of the screen in millimeters
		 */
		inline hnc::vector2<unsigned int> size_in_mm()
		{
			#ifdef hnc_linux
			
				Display * display = XOpenDisplay(nullptr);
				
				return { hnc::uint_t(DisplayWidthMM(display, 0)), hnc::uint_t(DisplayHeightMM(display, 0)) };
				
			#elif hnc_os_x
				
				CGSize const size_in_mm = CGDisplayScreenSize(0);
				
				return { hnc::uint_t(size_in_mm.width), hnc::uint_t(size_in_mm.height) };
				
			#elif hnc_windows
				
				throw hnc::except::incomplete_implementation("thoth::screen::size_in_mm is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/thoth");
				
			#else
				
				throw hnc::except::incomplete_implementation("thoth::screen::size_in_mm is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/thoth");
				
			#endif
		}
		
		/**
		 * @brief Get the size of the physical screen in pixels
		 * 
		 * @code
		   #include <thoth/screen.hpp>
		   @endcode
		 * 
		 * @return the the size of the screen in pixels
		 */
		inline std::vector<hnc::vector2<unsigned int>> sizes()
		{
			std::vector<hnc::vector2<unsigned int>> sizes;
			
			#ifdef hnc_linux
			
				// http://stackoverflow.com/questions/13706078/xrandr-related-c-programming
				// http://stackoverflow.com/questions/15186089/libxrandr-library-how-to-change-properties-of-connected-monitors
				
				Display * display = XOpenDisplay(nullptr);
				
				XRRScreenResources * screen = XRRGetScreenResources(display, DefaultRootWindow(display));
				
				for (std::size_t i = 0; i < std::size_t(screen->ncrtc); ++i)
				{
					XRRCrtcInfo * crtc_info = XRRGetCrtcInfo(display, screen, screen->crtcs[i]);
					
					sizes.emplace_back(crtc_info->width, crtc_info->height);
				}
				
			#elif hnc_os_x
				
				sizes.emplace_back(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
				
			#elif hnc_windows
				
				sizes.emplace_back(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
				
			#else
				
				sizes.emplace_back(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
				
			#endif
			
			return sizes;
		}
		
		/**
		 * @brief Get the size of the physical screen in millimeters
		 * 
		 * @code
		   #include <thoth/screen.hpp>
		   @endcode
		 * 
		 * @return the the size of the screen in millimeters
		 */
		inline std::vector<hnc::vector2<unsigned int>> sizes_in_mm()
		{
			std::vector<hnc::vector2<unsigned int>> sizes;
			
			#ifdef hnc_linux
			
				// http://stackoverflow.com/questions/13706078/xrandr-related-c-programming
				// http://stackoverflow.com/questions/15186089/libxrandr-library-how-to-change-properties-of-connected-monitors
				
				Display * display = XOpenDisplay(nullptr);
				
				XRRScreenResources * screen = XRRGetScreenResources(display, DefaultRootWindow(display));
				
				for (std::size_t i = 0; i < std::size_t(screen->ncrtc); ++i)
				{
					XRROutputInfo * output_info = XRRGetOutputInfo(display, screen, screen->outputs[i]);
					
					sizes.emplace_back(output_info->mm_width, output_info->mm_height);
				}
				
			#elif hnc_os_x
				
				throw hnc::except::incomplete_implementation("thoth::screen::sizes_in_mm is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/thoth");
				
			#elif hnc_windows
				
				throw hnc::except::incomplete_implementation("thoth::screen::sizes_in_mm is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/thoth");
				
			#else
				
				throw hnc::except::incomplete_implementation("thoth::screen::sizes_in_mm is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/thoth");
				
			#endif
			
			return sizes;
		}
		
		/**
		 * @brief Get the dpi (dots per inch)
		 * 
		 * @code
		   #include <thoth/screen.hpp>
		   @endcode
		 * 
		 * @return the dpi (dots per inch)
		 */
		static float dpi()
		{
			// 1 inch == 25.4 millimeters
			
			// http://stackoverflow.com/questions/2621439/how-to-get-screen-dpi-linux-mac-programatically
			
			// http://stackoverflow.com/questions/12652835/getting-actual-screen-dpi-ppi-under-windows
			// http://msdn.microsoft.com/en-us/library/windows/desktop/dd371316%28v=vs.85%29.aspx
			
			#if hnc_windows
				
				// http://stackoverflow.com/questions/12652835/getting-actual-screen-dpi-ppi-under-windows
				// http://msdn.microsoft.com/en-us/library/windows/desktop/dd371316%28v=vs.85%29.aspx
				
				ID2D1Factory * p_direct2d_factory;
				D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &p_direct2d_factory);
				
				FLOAT dpi_x;
				FLOAT dpi_y;
				p_direct2d_factory->GetDesktopDpi(&dpi_x, &dpi_y);
				
				return (dpi_x + dpi_y) / 2.f;
				
			#else
				
				auto const size = thoth::screen::size();
				auto const size_in_mm = thoth::screen::size_in_mm();
				
				auto const dpi_x = float(size.x) * 25.4f / float(size_in_mm.x);
				auto const dpi_y = float(size.y) * 25.4f / float(size_in_mm.y);
				
				return (dpi_x + dpi_y) / 2.f;
				
			#endif
		}
	}
}

#endif
