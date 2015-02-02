// Copyright © 2013, 2014 Lénaïc Bagnères, hnc@singularity.fr

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


/**
 * @file
 * @brief Provides Boost Serialization for std (std::vector, std::list, ...)
 * 
 * @code
   #include <hnc/boost_serialization_std.hpp>
   @endcode
 *
 * To use Boost.Serialization, you can add this in your CMakeLists.txt
 * @code
   find_package(hnc REQUIRED)
   
   # ...
   
   # Create the executable
   add_executable(your_exe your_exe.cpp)
   target_link_libraries(your_exe ${HNC_BOOST_SERIALIZATION_LIBRARY})
   @endcode
 *
 * For quick test, if you use GCC from the command line and Boost is installed, you can link directly with:
 * @code
   -lboost_serialization
   @endcode
 *
 * On Debian GNU/Linux distribution you can install the package:
 * @code
   libboost-serialization-dev
   @endcode
 *
 * If you want compile without Boost.Serialization, you can define the macro
 * @code
   #define hnc_no_boost_serialization
   @endcode
 * or use CMake variable
 * @code
   add_definition("-D${HNC_NO_BOOST_SERIALIZATION_MACRO}")
   @endcode
 */

#ifndef HNC_BOOST_SERIALIZATION_STD_HPP
#define HNC_BOOST_SERIALIZATION_STD_HPP


#ifndef hnc_no_boost_serialization

	#include <boost/archive/text_oarchive.hpp>
	#include <boost/archive/text_iarchive.hpp>

	#include <boost/serialization/export.hpp>
	
	#include <boost/serialization/array.hpp>
	#include <boost/serialization/bitset.hpp>
	#include <boost/serialization/complex.hpp>
	#include <boost/serialization/deque.hpp>
	#include <boost/serialization/list.hpp>
	#include <boost/serialization/map.hpp>
	#include <boost/serialization/factory.hpp>
	#include <boost/serialization/set.hpp>
	#include <boost/serialization/string.hpp>
	#include <boost/serialization/utility.hpp>
	#include <boost/serialization/valarray.hpp>
	#define STD std
	#include <boost/serialization/vector.hpp>
	#undef STD

#endif

#endif
