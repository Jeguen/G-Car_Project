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


#ifndef HNC_GNUPLOT_STYLE_HPP
#define HNC_GNUPLOT_STYLE_HPP

#include <string>
#include <vector>

#include "../unused.hpp"


namespace hnc
{
	namespace gnuplot
	{
		// TODO
		
		/**
		 * @brief The commands ‘set style data‘ and ‘set style function‘ change the default plotting style for subsequent ‘plot‘ and ‘splot‘ commands
		 * 
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node231.html
		 *
		 * @warning This class is not implemented yet
		 */
		class style
		{
		};

		/**
		 * @brief Display a hnc::gnuplot::style
		 *
		 * @param[out] o     Out stream
		 * @param[in]  style A hnc::gnuplot::style
		 *
		 * @return the out stream
		 */
		
		/// @brief Operator << between a std::ostream and a hnc::gnuplot::style
		/// @param[in,out] o     Output stream
		/// @param[in]     style A hnc::gnuplot::style
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::style const & style)
		{
			hnc_unused(style);
			return o;
		}
	}
}

#endif
