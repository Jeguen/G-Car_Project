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


#ifndef HNC_GNUPLOT_GNUPLOT_BOXES_HPP
#define HNC_GNUPLOT_GNUPLOT_BOXES_HPP

#include "gnuplot.hpp"
#include "plot_boxes.hpp"


namespace hnc
{
	namespace gnuplot
	{
		/**
		 * @brief Gnuplot with boxes
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * @image html hnc_gnuplot_gnuplot_boxes.png
		 * @image latex hnc_gnuplot_gnuplot_boxes.eps
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
		   
		   hnc::gnuplot::gnuplot_boxes gp
		   (
		   	hnc::gnuplot::output_terminal_png("hnc_gnuplot_gnuplot_boxes").size(640, 480),
		   	data
		   );
		   gp.plot().fill();
		   gp.plot().set_title("boxes legend");
		   
		   gp.set_title("hnc::gnuplot::gnuplot\\_boxes");
		   gp.y_range.range(0, gp.max_data_value() + 1);
		   @endcode
		 */
		class gnuplot_boxes : public hnc::gnuplot::gnuplot
		{
		private:

			/// Plot
			hnc::gnuplot::plot_boxes m_plot;

			/// Minimum data value
			double m_min_data_value;

			/// Maximum data value
			double m_max_data_value;
			
		public:

			/**
			 * @brief Constructor
			 * 
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
			 * @endcode
			 */
			template <class terminal_output_t, class numeric_t>
			gnuplot_boxes(terminal_output_t const & terminal_output, std::map<std::string, numeric_t> const & data) :
				hnc::gnuplot::gnuplot(terminal_output),
				m_plot(m_output_filename + ".data"),
				m_min_data_value(std::numeric_limits<double>::max()),
				m_max_data_value(std::numeric_limits<double>::min())
			{
				this->set_data(data);
			}

			/// @copydoc hnc::gnuplot::plot_boxes::set_data(std::map<std::string, numeric_t> const &)
			template <class numeric_t>
			void set_data(std::map<std::string, numeric_t> const & data)
			{
				// Set data
				m_plot.set_data(data);
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
					m_min_data_value = double(min_max_it.first->second);
					m_max_data_value = double(min_max_it.second->second);
				}
			}

			/// @brief Return the plot boxes
			/// @return the plot boxes
			hnc::gnuplot::plot_boxes & plot()
			{
				return m_plot;
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
				if (m_plots.empty()) { m_plots.push_back(m_plot); }
				else { m_plots[0] = m_plot; }
				// Return the plot
				return hnc::gnuplot::gnuplot::gnuplot_plots();
			}
		};
	}
}

#endif
