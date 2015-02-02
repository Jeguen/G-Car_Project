// Copyright © 2013, 2014 Lénaïc Bagnères, hnc@singularity.fr

// This file is part of hnc.

// hnc is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// hnc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with hnc. If not, see <http://www.gnu.org/licenses/>


#ifndef HNC_MPI_HPP
#define HNC_MPI_HPP


#include "mpi/future.hpp"


namespace hnc
{
	/**
	 * @brief MPI (Message Passing Interface) functions
	 *
	 * @code
	   #include <hnc/mpi.hpp>
	   @endcode
	 *
	 * With MPI you can write distributed program to:
	 * - increase performances
	 * - solve a bigger problem who can do with only one computer
	 *
	 * @b From @b Wikipedia http://en.wikipedia.org/wiki/Message_Passing_Interface @n
	 * Message Passing Interface (MPI) is a standardized and portable message-passing system designed by a group of researchers from academia and industry to function on a wide variety of parallel computers. The standard defines the syntax and semantics of a core of library routines useful to a wide range of users writing portable message-passing programs in Fortran 77 or the C programming language. Several well-tested and efficient implementations of MPI include some that are free and in the public domain. These fostered the development of a parallel software industry, and there encouraged development of portable and scalable large-scale parallel applications.
	 *
	 * To use MPI, you need Boost.MPI, Boost.Serialization, mpic++ and mpirun @n
	 * You can add this in your CMakeLists.txt
	 * @code
	   find_package(hnc REQUIRED)
	   if (HNC_COMPILER_MPI_CPP)
	   	set(CMAKE_CXX_COMPILER "${HNC_COMPILER_MPI_CPP}")
	   endif()
	   
	   # ...
	  
	   # Create the executable
	   add_executable(your_exe your_exe.cpp)
	   target_link_libraries(your_exe ${HNC_BOOST_MPI_LIBRARY} ${HNC_BOOST_SERIALIZATION_LIBRARY})
	   @endcode
	 * 
	 * For quick test, if you use GCC from the command line and Boost is installed, you can link directly with:
	 * @code
	   -lboost_mpi -lboost_serialization
	   @endcode
	 *
	 * On Debian GNU/Linux distribution you can install the packages:
	 * @code
	   openmpi-bin openmpi-dev libboost-serialization-dev libboost-mpi-dev
	   @endcode
	 *
	 * To run a program with MPI, you need to use mpirun:
	 * @code
	   mpirun -np number_of_processors your_exe
	   @endcode
	 * mpirun executable name is in HNC_MPIRUN_EXE CMake variable
	 *
	 * If you want compile without Boost.MPI, you can define the macro
	 * @code
	   #define hnc_no_boost_mpi
	   @endcode
	 * or use CMake variable
	 * @code
	   add_definition("-D${HNC_NO_BOOST_MPI_MACRO}")
	   @endcode
	 */
	namespace mpi
	{
		// For Doxygen only
	}
}

#endif
