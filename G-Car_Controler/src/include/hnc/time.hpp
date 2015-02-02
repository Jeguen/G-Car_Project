// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_TIME_HPP
#define HNC_TIME_HPP

#include <chrono>


namespace hnc
{
	/**
	 * @brief Time functions with different units
	 *
	 * @code
	   #include <hnc/time.hpp>
	   @endcode
	 */
	namespace time
	{
		/**
		 * @brief Time in ratio_t
		 * 
		   @code
		   	#include <hnc/time.hpp>
		   @endcode
		 * 
		 * @return time in ratio_t
		 */
		template <class return_t, class ratio_t>
		return_t time()
		{
			return std::chrono::duration_cast
			<
				std::chrono::duration<return_t, ratio_t>
			>
			(
				std::chrono::steady_clock::now().time_since_epoch()
			).count();
		}
		
		/**
		 * @brief Time in hours
		 * 
		   @code
		   	#include <hnc/time.hpp>
		   @endcode
		 * 
		 * @return time in hours
		 */
		template <class return_t = long double>
		return_t h()
		{
			return hnc::time::time<return_t, std::ratio<3600>>();
		}
		
		/**
		 * @brief Time in minutes
		 * 
		   @code
		   	#include <hnc/time.hpp>
		   @endcode
		 * 
		 * @return time in minutes
		 */
		template <class return_t = long double>
		return_t min()
		{
			return hnc::time::time<return_t, std::ratio<60>>();
		}
		
		/**
		 * @brief Time in seconds
		 * 
		   @code
		   	#include <hnc/time.hpp>
		   @endcode
		 * 
		 * @return time in seconds
		 */
		template <class return_t = long double>
		return_t s()
		{
			return hnc::time::time<return_t, std::ratio<1>>();
		}
		
		/**
		 * @brief Time in milliseconds
		 * 
		   @code
		   	#include <hnc/time.hpp>
		   @endcode
		 * 
		 * @return time in milliseconds
		 */
		template <class return_t = long double>
		return_t ms()
		{
			return hnc::time::time<return_t, std::milli>();
		}
		
		/**
		 * @brief Time in microseconds
		 * 
		   @code
		   	#include <hnc/time.hpp>
		   @endcode
		 * 
		 * @return time in microseconds
		 */
		template <class return_t = long double>
		return_t us()
		{
			return hnc::time::time<return_t, std::micro>();
		}
		
		/**
		 * @brief Time in nanoseconds
		 * 
		   @code
		   	#include <hnc/time.hpp>
		   @endcode
		 * 
		 * @return time in nanoseconds
		 */
		template <class return_t = long unsigned int>
		return_t ns()
		{
			return hnc::time::time<return_t, std::nano>();
		}
	}
}

#endif
