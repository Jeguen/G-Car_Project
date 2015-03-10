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


#ifndef HNC_GNUPLOT_PLOT_HPP
#define HNC_GNUPLOT_PLOT_HPP

#include <string>

#include "../to_string.hpp"


namespace hnc
{
	namespace gnuplot
	{
		/**
		 * @brief Plot informations (file, using, xtic, ytic, with, title) for Gnuplot plot command
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 * 
		 * hnc::gnuplot::plot contains the information for one plot. It does not include the plot keyword
		 *
		 * http://www.manpagez.com/info/gnuplot/gnuplot-4.4.0/gnuplot_190.php
		 */
		class plot
		{
		private:

			/// Data filename
			std::string m_data_filename;

			/// using
			std::string m_using;

			/// xtic
			std::string m_xtic;

			/// ytic
			std::string m_ytic;

			/// with
			std::string m_with;

			/// title
			std::string m_title;

			/// Data
			std::string m_data;

		public:

			/// @brief Constructor
			/// @param[in] data_filename Data filename (no filename by default)
			plot(std::string const & data_filename = "") :
				m_data_filename(data_filename)
			{ }

			// Data filename
			
			/// @brief Set the data filename
			/// @param[in] data_filename Data filename
			/// @return the plot
			plot & set_data_filename(std::string const & data_filename) { m_data_filename = data_filename; return *this; }

			/// @brief The data filename is the same as the previous plot
			/// @return the plot
			plot & same_data_filename() { m_data_filename = ""; return *this; }

			// title

			/// @brief Return the title
			/// @return the title
			std::string const & title() const { return m_title; }

			/// @brief Set the title
			/// @param[in] title Title
			/// @return the plot
			plot & set_title(std::string const & title) { m_title = "title '" + title + "'"; return *this; }

			/// @brief No title
			/// @return the plot
			plot & no_title() { m_title = "notitle"; return *this; }

			// to_string

			/// @brief Return the output terminal (for a Gnuplot script)
			/// @return the output terminal (for a Gnuplot script)
			std::string plot_line() const
			{
				return "'" + m_data_filename + "' " + m_using + m_xtic + m_ytic + " " + m_with + m_title;
			}

			/// @brief Return the data filename
			/// @return the data filename
			std::string const & data_filename() const
			{
				return m_data_filename;
			}


			/// @brief Return the data
			/// @return the data
			std::string const & data() const
			{
				return m_data;
			}

		protected:

			// x tick labels and y tick labels

			/// @brief Set the x tick labels
			/// @param[in] i Column id to get the x tick labels
			/// @return the plot
			plot & set_x_tick_labels(unsigned int const i) { m_xtic = ":xtic(" + hnc::to_string(i) + ")"; return *this; }

			/// @brief Set the y tick labels
			/// @param[in] i Column id to get the y tick labels labels
			/// @return the plot
			plot & set_y_tick_labels(unsigned int const i) { m_ytic = ":ytic(" + hnc::to_string(i) + ")"; return *this; }

			// using
			
			/// @brief Using the column id to get data
			/// @param[in] i First column id to get data
			/// @param[in] l Rest of column ids to get data and controls
			/// @return the plot
			template <class ... ids_column_and_controls_list>
			plot & set_using(unsigned int const i, ids_column_and_controls_list ... l)
			{
				m_using = "using " + hnc::to_string(i) + using_list_to_string("", l...);
				return *this;
			}

			/// @brief Using the column id to get data
			/// @param[in] c A control for using
			/// @param[in] l Rest of column ids to get data and controls
			/// @return the plot
			template <class ... ids_column_and_controls_list>
			plot & set_using(std::string const & c, ids_column_and_controls_list ... l)
			{
				m_using = "using " + c + using_list_to_string("", l...);
				return *this;
			}

			// Data

			/// @brief Set the data
			/// @param[in] data Data
			/// @return the plot
			plot & set_data(std::string const & data) { m_data = data; return *this; }

			// with

			/// @brief Set the plot style
			/// @param[in] plot_with A plot with style for with (a std::string)
			/// @return the plot
			plot & set_with(std::string const & plot_with) { m_with = "with " + plot_with + " "; return *this; }
			
		private:

			/// @brief Transform column id for using
			/// @param[in] s std::string for the return
			/// @param[in] i One column id to get data
			/// @param[in] l Rest of column ids to get data and controls
			/// @return the string for using
			template <class ... ids_column_and_controls_list>
			std::string using_list_to_string(std::string const & s, unsigned int const i, ids_column_and_controls_list ... l)
			{
				return using_list_to_string(s + ":" + hnc::to_string(i), l...);
			}
			
			/// @brief Transform control for using
			/// @param[in] s std::string for the return
			/// @param[in] c A control for using
			/// @param[in] l Rest of column ids to get data and controls
			/// @return the string for using
			template <class ... ids_column_and_controls_list>
			std::string using_list_to_string(std::string const & s, std::string const & c, ids_column_and_controls_list ... l)
			{
				return using_list_to_string(s + ":" + c, l...);
			}
			
			/// @brief Transform column id for using (specialization for the end)
			/// @return the string for using
			std::string using_list_to_string(std::string const & s)
			{
				return s;
			}
		};
		
		/// @brief Operator << between a std::ostream and a hnc::gnuplot::plot
		/// @param[in,out] o    Output stream
		/// @param[in]     plot A hnc::gnuplot::plot
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::plot const & plot)
		{
			o << plot.plot_line();
			return o;
		}
	}
}

#endif
