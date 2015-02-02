// Copyright © 2012, 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_TEST_HPP
#define HNC_TEST_HPP

#include <iostream>
#include <string>
#include <stdexcept>

#include "terminal.hpp"


namespace hnc
{
	/// @brief Provides some functions to do tests
	namespace test
	{
		/**
		 * @brief Display a warning what message into the output flux if the expression is false
		 *
		 * @code
		   #include <hnc/test.hpp>
		   @endcode
		 * 
		 * If the expression is false:
		 * - we display the what message with hnc::terminal::warning into the output flux
		 * - return 0
		 *
		 * Else (expression is true):
		 * - return 1
		 *
		 * One way to use hnc::test::warning
		 * @code
		 * int nb_test = 0;
		 * ++nb_test;
		 * nb_test -= hnc::test::warning(1 == 1, "1 must be equal to 1\n");
		 * // if nb_test == 0, test succed
		 * @endcode
		 *
		 * @param[in]     expression The test (a bool)
		 * @param[in]     what       The message if the test is false
		 * @param[in,out] o          The output flux (std::cout by default)
		 *
		 * @return 1 if test succed, else 0
		 */
		int warning(bool const expression, std::string const & what, std::ostream & o = std::cout)
		{
			if (expression == false)
			{
				o << hnc::terminal::warning << what << hnc::terminal::color_reset; o.flush();
				return 0;
			}
			return 1;
		}

		/**
		 * \brief Display the what message as an error into the output flux and send a exception if the expression is false
		 *
		 * @code
		   #include <hnc/test.hpp>
		   @endcode
		 * 
		 * If the expression is false:
		 * - we display the what message with hnc::terminal::error into the output flux
		 * - throw a std::runtime_error with the what message
		 *
		 * Else (expression is true):
		 * - return 1
		 *
		 * @exception std::runtime_error(what) if the expression is false
		 *
		 * @param[in]     expression The test (a bool)
		 * @param[in]     what       The message if the test is false
		 * @param[in,out] o          The output flux (std::cout by default)
		 *
		 * @return 1 if test succed, else 0
		 */
		int error(bool const expression, std::string const & what, std::ostream & o = std::cerr)
		{
			if (expression == false)
			{
				o << hnc::terminal::error << what << hnc::terminal::color_reset; o.flush();
				throw std::runtime_error(what);
			}
			return 1;
		}
	}
}

#endif
