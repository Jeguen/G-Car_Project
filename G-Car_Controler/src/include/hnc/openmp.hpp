// Copyright © 2012-2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_OPENMP_HPP
#define HNC_OPENMP_HPP


#if defined(_OPENMP)
	#include <omp.h>
#endif


namespace hnc
{
	/**
	 * @brief hnc OpenMP functions
	 *
	 * @code
	   #include <hnc/openmp.hpp>
	   @endcode
	 *
	 * TODO What is OpenMP ?
	 * 
	 * TODO Link to (simple) OpenMP Tutorial
	 */
	namespace openmp
	{
		/**
		 * @brief Get the id of OpenMP thread
		 * 
		 * @code
		   #include <hnc/openmp.h>
		   @endcode
		 * 
		 * 
		 * @return the id of OpenMP thread
		 */
		std::size_t thread_id()
		{
			#if defined(_OPENMP)
				return std::size_t(omp_get_thread_num());
			#else
				return 0;
			#endif
		}
		
		/**
		 * @brief Get the actual number of OpenMP threads
		 * 
		 * @code
		   #include <hnc/openmp.h>
		   @endcode
		 * 
		 * 
		 * @return the actual number of OpenMP threads
		 */
		std::size_t nb_thread_actual()
		{
			#if defined(_OPENMP)
				return std::size_t(omp_get_num_threads());
			#else
				return 0;
			#endif
		}
		
		/**
		 * @brief Get the maximum number of OpenMP threads
		 * 
		 * @code
		   #include <hnc/openmp.h>
		   @endcode
		 * 
		 * 
		 * @return the maximum number of OpenMP threads
		 */
		std::size_t nb_thread_max()
		{
			#if defined(_OPENMP)
				return std::size_t(omp_get_max_threads());
			#else
				return 0;
			#endif
		}
	}
}

#include "openmp/run_at_same_time.hpp"
#include "openmp/run_parallel.hpp"

#endif
