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


#ifndef HNC_GNUPLOT_GNUPLOT_LINES_HPP
#define HNC_GNUPLOT_GNUPLOT_LINES_HPP

#include "gnuplot.hpp"
#include "plot_lines.hpp"


namespace hnc
{
	namespace gnuplot
	{
		/**
		 * @brief Gnuplot with lines
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * @image html hnc_gnuplot_gnuplot_lines.png
		 * @image latex hnc_gnuplot_gnuplot_lines.eps
		 *
		 * @code
		   std::map<std::string, int> data;
		   data["A"] = 1;
		   data["B"] = 2;
		   data["C"] = 5;
		   data["D"] = 3;
		   data["E"] = 4;
		   data["F"] = 2;
		   data["G"] = 1;
		   
		   hnc::gnuplot::gnuplot_lines gp
		   (
		   	hnc::gnuplot::output_terminal_png("hnc_gnuplot_gnuplot_lines").size(640, 480),
		   	data
		   );
		   gp.plot().set_title("lines legend");
		   
		   gp.set_title("hnc::gnuplot::gnuplot\\_lines");
		   gp.y_range.range(0, gp.max_data_value() + 1);
		   @endcode
		 *
		 * @image html hnc_gnuplot_gnuplot_lines_with_multilines.png
		 * @image latex hnc_gnuplot_gnuplot_lines_with_multilines.eps
		 *
		 * @code
		   std::map<std::string, int> data_0;
		   data_0["A"] = 1;
		   data_0["B"] = 2;
		   data_0["C"] = 5;
		   data_0["D"] = 3;
		   data_0["E"] = 4;
		   data_0["F"] = 2;
		   data_0["G"] = 1;
		   
		   std::map<std::string, int> data_1;
		   data_1["A"] = 3;
		   data_1["B"] = 6;
		   data_1["C"] = 2;
		   data_1["D"] = 1;
		   data_1["E"] = 2;
		   data_1["F"] = 3;
		   data_1["G"] = 2;
		   
		   std::map<std::string, int> data_2;
		   data_2["A"] = 2;
		   data_2["B"] = 3;
		   data_2["C"] = 4;
		   data_2["D"] = 3;
		   data_2["E"] = 4;
		   data_2["F"] = 7;
		   data_2["G"] = 3;
		   
		   hnc::gnuplot::gnuplot_lines gp
		   (
		   	hnc::gnuplot::output_terminal_png("hnc_gnuplot_gnuplot_lines_with_multilines").size(640, 480)
		   );
		   gp.add_line(data_0, "First line");
		   gp.add_line(data_1, "Second line");
		   gp.add_line(data_2, "Third line");
		   
		   gp.set_title("hnc::gnuplot::gnuplot\\_lines\\_with\\_multilines");
		   gp.y_range.range(0, gp.max_data_value() + 2);
		   @endcode
		 */
		class gnuplot_lines : public hnc::gnuplot::gnuplot
		{
		private:

			/// Plots
			std::vector<hnc::gnuplot::plot_lines> m_plots;

			/// Minimum data value
			double m_min_data_value;

			/// Maximum data value
			double m_max_data_value;
			
		public:

			/// @brief Constructor
			/// @param[in] terminal_output Terminal output hnc::gnuplot::output_terminal_pdf, hnc::gnuplot::output_terminal_svg, hnc::gnuplot::output_terminal_png
			template <class terminal_output_t>
			gnuplot_lines(terminal_output_t const & terminal_output) :
				hnc::gnuplot::gnuplot(terminal_output),
				m_plots(),
				m_min_data_value(std::numeric_limits<double>::max()),
				m_max_data_value(std::numeric_limits<double>::min())
			{ }

			/**
			 * @brief Constructor
			 * @param[in] terminal_output Terminal output hnc::gnuplot::output_terminal_pdf, hnc::gnuplot::output_terminal_svg, hnc::gnuplot::output_terminal_png
			 * @param[in] data            A std::map with std::string as key (x tick) and a numeric as value (y value)
			 *
			 * Data example:
			 * @code
			   std::map<std::string, int> data;
			   data["A"] = 1;
			   data["B"] = 2;
			   data["C"] = 5;
			   data["D"] = 3;
			   @endcode
			 */
			template <class terminal_output_t, class numeric_t>
			gnuplot_lines(terminal_output_t const & terminal_output, std::map<std::string, numeric_t> const & data) :
				hnc::gnuplot::gnuplot_lines(terminal_output)
			{
				add_line(data);
			}

			/**
			 * @brief Add a line
			 * 
			 * @param[in] data  A std::map with std::string as key (x tick) and a numeric as value (y value)
			 * @param[in] title Title for this line
			 *
			 * Data example:
			 * @code
			   std::map<std::string, int> data;
			   data["A"] = 1;
			   data["B"] = 2;
			   data["C"] = 5;
			   data["D"] = 3;
			   @endcode
			 */
			template <class numeric_t>
			void add_line(std::map<std::string, numeric_t> const & data, std::string const title = "")
			{
				// Add line
				m_plots.emplace_back(m_output_filename + "." + hnc::to_string(m_plots.size()) + ".data");
				m_plots.back().set_data(data);
				if (title.empty() == false) { m_plots.back().set_title(title); }
				// Get min and max
				if (data.empty() == false)
				{
					auto min_max_it = std::minmax_element
					(
						data.begin(), data.end(),
						[]
						(
							std::pair<std::string, numeric_t> const & key_value_0,
							std::pair<std::string, numeric_t> const & key_value_1
						) -> bool
						{ return key_value_0.second < key_value_1.second; }
					);
					m_min_data_value = std::min(m_min_data_value, double(min_max_it.first->second));
					m_max_data_value = std::max(m_max_data_value, double(min_max_it.second->second));
				}
			}

			/// @brief Return the first plot lines
			/// @return the first plot lines
			hnc::gnuplot::plot_lines & plot()
			{
				return m_plots.front();
			}

			/// @brief Return the plots lines
			/// @return the plots lines
			std::vector<hnc::gnuplot::plot_lines> & plots()
			{
				return m_plots;
			}

			/// @copydoc hnc::gnuplot::gnuplot::min_data_value()
			double min_data_value() const override { return m_min_data_value; }

			/// @copydoc hnc::gnuplot::gnuplot::max_data_value()
			double max_data_value() const override { return m_max_data_value; }

		protected:
			
			/// @copydoc hnc::gnuplot::gnuplot::gnuplot_plots()
			std::vector<hnc::gnuplot::plot> & gnuplot_plots() override
			{
				// Save the good plot
				hnc::gnuplot::gnuplot::m_plots.resize(0);
				for (auto const & plot : m_plots) { hnc::gnuplot::gnuplot::m_plots.push_back(plot); }
				// Return the plot
				return hnc::gnuplot::gnuplot::gnuplot_plots();
			}
		};
	}
}

#endif
