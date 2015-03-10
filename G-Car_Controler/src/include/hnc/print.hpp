// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_PRINT_HPP
#define HNC_PRINT_HPP

#include <iostream>
#include <mutex>


namespace hnc
{
	/**
	 * @brief End of hnc::print (call std::flush)
	 * 
	 * @code
	   	#include <hnc/print.hpp>
	   @endcode
	 */
	inline void print()
	{
		std::cout << std::flush;
	}
	
	/**
	 * @brief Print all arguments with std::cout
	 * 
	 * @code
	   	#include <hnc/print.hpp>
	   @endcode
	 * 
	 * @param[in] arg  First argument
	 * @param[in] args Others arguments
	 */
	template <class T, class ... args_t>
	void print(T const & arg, args_t const & ... args)
	{
		std::cout << arg;
		hnc::print(args...);
	}
	
	/**
	 * @brief Print all arguments with std::cout
	 * 
	 * @note This function is like hnc::print but it is thread-safe
	 * 
	 * @code
	   	#include <hnc/print.hpp>
	   @endcode
	 * 
	 * @param[in] arg  First argument
	 * @param[in] args Others arguments
	 */
	template <class ... args_t>
	void print_mutex(args_t const & ... args)
	{
		static std::mutex mutex;
		mutex.lock();
		hnc::print(args...);
		mutex.unlock();
	}
}

#endif
