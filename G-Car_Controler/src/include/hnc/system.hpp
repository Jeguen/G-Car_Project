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


#ifndef HNC_SYSTEM_HPP
#define HNC_SYSTEM_HPP

#include <cstdlib>

#include "to_string.hpp"


namespace hnc
{
	/**
	 * @brief Execute a command
	 *
	 * @code
	   #include <hnc/system.hpp>
	   @endcode
	 *
	 * @return a implementation-defined value (it is generally expected to be the status code returned by the called command, if supported)
	 */
	inline int system(std::string const & cmd)
	{
		// Run the command
		return std::system(cmd.c_str());
	}

	/**
	 * @brief Execute a command with arguments
	 *
	 * @code
	   #include <hnc/system.hpp>
	   @endcode
	 *
	 * @return a implementation-defined value (it is generally expected to be the status code returned by the called command, if supported)
	 */
	template <class arg_t, class ... args_t>
	int system(std::string const & cmd, arg_t const & arg, args_t ... args)
	{
		return hnc::system(cmd + " \"" + hnc::to_string(arg) + "\"", args...);
	}
}

#endif
