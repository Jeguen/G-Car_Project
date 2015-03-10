// Copyright © 2012, 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_LOG_LEVEL_HPP
#define HNC_LOG_LEVEL_HPP

#include <iostream>


namespace hnc
{
	namespace
	{
		/// A std::ostream with default constructor for no output @author Lénaïc Bagnères
		class no_ostream : public std::ostream
		{ };

		/// Equivalent of an instance of a std::ostream witout output @author Lénaïc Bagnères
		no_ostream no_out;
	}

	/**
	 * @brief Do output if log level <= log level max
	 *
	 * @code
	   #include <hnc/log_level.hpp>
	   @endcode
	 * 
	 * How it works?
	 *
	 * If the log level <= log level max:
	 * - return the output stream
	 *
	 * Else:
	 * - return hnc::no_out. hnc::no_out is like a output stream but it does nothing
	 *
	 * An example:
	 * @code
	   hnc::out(0, 0) << "Output" << std::endl;
	   hnc::out(0, 1) << "No output" << std::endl;
	   @endcode
	 *
	 * @param[in]  log_level_max Log level max
	 * @param[in]  log_level     Data's log level
	 * @param[out] o             Output stream (if output) (std::cout by default)
	 *
	 * @return the output stream if output, else a do-nothing output stream (if no output)
	 */
	template <class log_level_t>
	std::ostream & out(log_level_t const & log_level_max, log_level_t const & log_level, std::ostream & o = std::cout)
	{
		return (log_level <= log_level_max) ? o : hnc::no_out;
	}
}


#endif
