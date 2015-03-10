// Copyright © 2013, 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef HNC_HTTP_HPP
#define HNC_HTTP_HPP

#include "http/url_encode.hpp"
#include "http/get.hpp"

#include "http/w3c_validator.hpp"


namespace hnc
{
	/**
	 * @brief Utilization of Web-services
	 *
	 * @code
	   #include <hnc/http.hpp>
	   @endcode
	 *
	 * To use hnc::http, you need Boost.Asio and Boost.System @n
	 * You can add this in your CMakeLists.txt
	 * @code
	   find_package(hnc REQUIRED)
	  
	   # ...
	  
	   # Create the executable
	   add_executable(your_exe your_exe.cpp)
	   target_link_libraries(your_exe ${HNC_BOOST_SYSTEM_LIBRARY})
	   @endcode
	 *
	 * For quick test, if you use GCC from the command line and Boost is installed, you can link directly with:
	 * @code
	   -lboost_system
	   @endcode
	 *
	 * On Debian GNU/Linux distribution you can install the packages:
	 * @code
	   libboost-system-dev libboost-asio-dev
	   @endcode
	 *
	 * If you want compile without Boost.Asio, you can define the macro
	 * @code
	   #define hnc_no_boost_asio
	   @endcode
	 * or use CMake variable
	 * @code
	   add_definition("-D${HNC_NO_BOOST_ASIO_MACRO}")
	   @endcode
	 */
	namespace http
	{
		// For Doxygen only
	}
}

#endif
