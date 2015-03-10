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


#ifndef HNC_GNUPLOT_PLOT_LINES_HPP
#define HNC_GNUPLOT_PLOT_LINES_HPP

#include <string>
#include <map>
#include <limits>

#include "plot.hpp"
#include "../to_string.hpp"


namespace hnc
{
	namespace gnuplot
	{
		/**
		 * @brief Plot with lines
		 * 
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://www.manpagez.com/info/gnuplot/gnuplot-4.4.3/gnuplot_141.php#lines
		 */
		class plot_lines : public hnc::gnuplot::plot
		{
		public:

			/// @brief Constructor
			/// @param[in] data_filename Data filename (no filename by default)
			plot_lines(std::string const & data_filename = "") :
				plot(data_filename)
			{
				// using 0:2:xtic(1) with lines
				set_using(0, 2u);
				set_x_tick_labels(1);
				set_with("lines");
			}

			/**
			 * @brief Set data
			 *
			 * @param[in] data A std::map with std::string as key (x tick) and a numeric as value (y value)
			 *
			 * @code
			   std::map<std::string, int> data;
			   data["A"] = 1;
			   data["B"] = 2;
			   data["C"] = 5;
			   data["D"] = 3;
			   @endcode
			 * 
			 * @return the plot
			 */
			template <class numeric_t>
			plot_lines set_data(std::map<std::string, numeric_t> const & data)
			{
				static_assert(std::numeric_limits<numeric_t>::is_specialized, "hnc::gnuplot::plot_lines::set_data works for numeric types only");

				// Get data
				std::string r;
				for (auto const key_value : data)
				{
					std::string const & x_tick = key_value.first;
					numeric_t const & y_value = key_value.second;
					r += "\"" + x_tick + "\" " + hnc::to_string(y_value) + "\n";
				}

				// Set data
				hnc::gnuplot::plot::set_data(r);

				// Return
				return *this;
			}
		};
	}
}

#endif
