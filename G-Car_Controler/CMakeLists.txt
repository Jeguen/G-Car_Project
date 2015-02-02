# Copyright © 2013, 2014 Lénaïc Bagnères, hnc@singularity.fr
# Copyright © 2015 Rodolphe Cargnello, rodolphe.cargnello@gmail.com

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


cmake_minimum_required(VERSION 2.6)


# Release / Debug flags

	if (RELEASE STREQUAL "FALSE" OR RELEASE STREQUAL "DEBUG")
		set(RELEASE "FALSE")
	else()
		set(RELEASE "TRUE")
	endif()

	if (RELEASE)
		set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG -march=native -ffast-math")
	else()
		set(CMAKE_CXX_FLAGS "-O0 -g3")
	endif()

# User's settings - General C++ Flags
	# General
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic")
	# Thread support
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
	endif()

# SFML

	find_file(SFML_CMAKE_DIR "cmake/Modules/FindSFML.cmake")
	if (NOT SFML_CMAKE_DIR)
		find_file(SFML_CMAKE_DIR "SFML/cmake/Modules/FindSFML.cmake")
	endif()
	if (NOT SFML_CMAKE_DIR)
		find_file(SFML_CMAKE_DIR "share/SFML/cmake/Modules/FindSFML.cmake")
	endif()

	if (SFML_CMAKE_DIR)
		string(REPLACE "FindSFML.cmake" "" SFML_CMAKE_DIR ${SFML_CMAKE_DIR})
		set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${SFML_CMAKE_DIR}")
	endif()

	find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

	message(STATUS "SFML found =)")
	message(STATUS "SFML libraries = ${SFML_LIBRARIES} =)")
	message(STATUS "SFML include   = ${SFML_INCLUDE_DIR} =)")
	include_directories(${SFML_INCLUDE_DIR})

# Thōth
	message(STATUS "---")
	find_package(thoth REQUIRED)
	
# TGUI
	message(STATUS "---")
	find_library(TGUI_LIBRARY NAMES tgui)
	if (TGUI_LIBRARY)
		message(STATUS "TGUI library found =) ${TGUI_LIBRARY}")
	else()
		message(FATAL_ERROR "TGUI library not found :(")
	endif()

# G-Car Project
	message(STATUS "---")
	set(g-car_INCLUDE "./src/include")
	message(STATUS "Include G-Car Project = ${g-car_INCLUDE}")
	include_directories("${g-car_INCLUDE}")

	
# Executable
	message(STATUS "---")
	
	# Tests
	file(
		GLOB_RECURSE
		tests
		tests/*.cpp
	)
	foreach(test_source ${tests})
	
		# Get test name and source
		string(REPLACE ".cpp" "" test_name ${test_source})
		string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/tests/" "test__" test_name ${test_name})
		
		message(STATUS "Add test ${test_name}")
		
		add_executable(${test_name} ${test_source})
		target_link_libraries(${test_name} ${TGUI_LIBRARY} ${THOTH_SFML_LIBRARY})
		
	endforeach()


# Little help
	message(STATUS "---")
	message(STATUS "You can execute:")
	message(STATUS "    make         # To compile")

	message(STATUS "---")
