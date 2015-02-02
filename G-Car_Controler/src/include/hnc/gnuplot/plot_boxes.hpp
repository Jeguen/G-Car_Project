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


#ifndef HNC_GNUPLOT_PLOT_BOXES_HPP
#define HNC_GNUPLOT_PLOT_BOXES_HPP

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
		 * @brief Plot with boxes
		 * 
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://www.manpagez.com/info/gnuplot/gnuplot-4.4.3/gnuplot_124.php#boxes
		 */
		class plot_boxes : public hnc::gnuplot::plot
		{
		public:

			/**
			 * @brief Fill patern
			 *
			 * @image html hnc_gnuplot_plot_boxes_fill_pattern.png
			 * @image latex hnc_gnuplot_plot_boxes_fill_pattern.eps
			 */
			enum class fill_pattern : int
			{
				/// No fill
				empty = 0,
				/// Fill with diagonals and anti-diagonals
				X = 1,
				/// Fill with little diagonals and anti-diagonals
				x = 2,
				/// Fill
				solid = 3,
				/// Fill with diagonals
				diagonal = 4,
				/// Fill with anti-diagonals
				anti_diagonal = 5,
				/// Fill with diagonals @f$ - \frac{\Pi}{3} @f$
				diagonal_v2 = 6,
				/// Fill with anti-diagonals @f$ \frac{\Pi}{3} @f$
				anti_diagonal_v2 = 7
			};
			
			/// @brief Constructor
			/// @param[in] data_filename Data filename (no filename by default)
			/// @param[in] box_width     Width of the boxes (ratio) (0.73 by default)
			plot_boxes(std::string const & data_filename = "", double const box_width = 0.73) :
				plot(data_filename)
			{
				// using 0:2:(1.0):xtic(1) with boxes
				set_using(0, 2u, "(" + hnc::to_string(box_width) + ")");
				set_x_tick_labels(1);
				set_with("boxes fill solid 1");
			}

			/// @brief Constructor
			/// @param[in] box_width Width of the boxes (ratio)
			plot_boxes(double const box_width) : plot_boxes("", box_width)
			{ }

			/// @brief Fill the box
			/// @param[in] density Fill density (between 0 and 1)
			/// @return the plot
			plot_boxes & fill(double const density = 1)
			{
				set_with("boxes fill solid " + hnc::to_string((density >= 0 && density <= 1) ? density : 1.));
				return *this;
			}

			/// @brief No fill the box
			/// @return the plot
			plot_boxes & no_fill()
			{
				set_with("boxes fill");
				return *this;
			}

			/// @brief Fill the box
			/// @param[in] pattern A hnc::gnuplot::plot_boxes::fill_pattern
			/// @return the plot
			plot_boxes & pattern(hnc::gnuplot::plot_boxes::fill_pattern const pattern)
			{ set_with("boxes fill pattern " + hnc::to_string(int(pattern))); return *this; }

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
			plot_boxes set_data(std::map<std::string, numeric_t> const & data)
			{
				static_assert(std::numeric_limits<numeric_t>::is_specialized, "hnc::gnuplot::plot_boxes::set_data works for numeric types only");

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
