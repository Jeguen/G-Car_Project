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


#ifndef HNC_GNUPLOT_X_RANGE_HPP
#define HNC_GNUPLOT_X_RANGE_HPP

#include <string>
#include <vector>

#include "../to_string.hpp"


namespace hnc
{
	namespace gnuplot
	{
		/**
		 * @brief Synxtax for xrange (and yrange, zrange, x2range, y2range, cbrange, rrange, trange, urange, vrrange)
		 * 
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 * 
		 * @b From http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 * - In 2-d, xrange and yrange determine the extent of the axes, trange determines the range of the parametric variable in parametric mode or the range of the angle in polar mode. Similarly in parametric 3-d, xrange, yrange, and zrange govern the axes and urange and vrange govern the parametric variables
		 * - In polar mode, rrange determines the radial range plotted. 5#5rmin6#6 acts as an additive constant to the radius, whereas 5#5rmax6#6 acts as a clip to the radius -- no point with radius greater than 5#5rmax6#6 will be plotted. xrange and yrange are affected -- the ranges can be set as if the graph was of r(t)-rmin, with rmin added to all the labels
		 */
		class axis_range
		{
		private:

			/// axis_name
			std::string const m_axis_name;

			/// range
			std::string m_range = "set " + m_axis_name + "range [] ";

			/// reverse / noreverse
			std::string m_reverse;

			/// writeback / nowriteback
			std::string m_writeback;

		public:

			/// @brief Constructor
			/// @param[in] axis_name Name of the axis (x, y, z, x2, y2, cb, r, t, u, vr)
			axis_range(std::string const & axis_name) : m_axis_name(axis_name) { }

			/// @brief Destructor
			virtual ~axis_range() = 0;

			/// @brief Set the range
			/// @param[in] min Minimum value
			/// @param[in] max Maximum value
			/// @return the axis_range
			axis_range & range(double const min, double const max)
			{
				m_range = "set " + m_axis_name + "range [" + hnc::to_string(min) + ":" + hnc::to_string(max) + "] ";
				return *this;
			}

			/**
			 * @brief Set the reverse
			 * 
			 * The reverse option reverses the direction of the axis, e.g., set xrange [0:1] reverse will produce an axis with 1 on the left and 0 on the right. This is identical to the axis produced by set xrange [1:0], of course. reverse is intended primarily for use with autoscale
			 * 
			 * @return the axis_range
			 */
			axis_range & reverse() { m_reverse = "reverse "; return *this; }

			/**
			 * @brief Unset the reverse
			 * 
			 * The reverse option reverses the direction of the axis, e.g., set xrange [0:1] reverse will produce an axis with 1 on the left and 0 on the right. This is identical to the axis produced by set xrange [1:0], of course. reverse is intended primarily for use with autoscale
			 * 
			 * @return the axis_range
			 */
			axis_range & no_reverse() { m_reverse = "noreverse "; return *this; }

			/**
			 * @brief Set the writeback
			 *
			 * The writeback option essentially saves the range found by autoscale in the buffers that would be filled by set xrange. This is useful if you wish to plot several functions together but have the range determined by only some of them. The writeback operation is performed during the plot execution, so it must be specified before that command. To restore, the last saved horizontal range use set xrange restore
			 * 
			 * @return the axis_range
			 */
			axis_range & writeback() { m_writeback = "writeback "; return *this; }

			/**
			 * @brief Unset the writeback
			 *
			 * The writeback option essentially saves the range found by autoscale in the buffers that would be filled by set xrange. This is useful if you wish to plot several functions together but have the range determined by only some of them. The writeback operation is performed during the plot execution, so it must be specified before that command. To restore, the last saved horizontal range use set xrange restore
			 * 
			 * @return the axis_range
			 */
			axis_range & no_writeback() { m_writeback = "nowriteback "; return *this; }

			/**
			 * @brief Return the axis range (for a Gnuplot script)
			 * @return the axis range (for a Gnuplot script)
			 */
			std::string to_string() const
			{
				return m_range + m_reverse + m_writeback + "\n";
			}
		};
		
		inline hnc::gnuplot::axis_range::~axis_range() { }
		
		/// @brief Operator << between a std::ostream and a hnc::gnuplot::axis_range
		/// @param[in,out] o          Output stream
		/// @param[in]     axis_range A hnc::gnuplot::axis_range
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::axis_range const & axis_range)
		{
			o << axis_range.to_string();
			return o;
		}
		
		/**
		 * @brief Synxtax for xrange
		 * 
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class x_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			x_range() : hnc::gnuplot::axis_range("x") { }
		};

		/**
		 * @brief Synxtax for yrange
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class y_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			y_range() : hnc::gnuplot::axis_range("y") { }
		};

		/**
		 * @brief Synxtax for zrange
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class z_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			z_range() : hnc::gnuplot::axis_range("z") { }
		};

		/**
		 * @brief Synxtax for x2range
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class x2_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			x2_range() : hnc::gnuplot::axis_range("x2") { }
		};

		/**
		 * @brief Synxtax for y2range
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class y2_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			y2_range() : hnc::gnuplot::axis_range("y2") { }
		};

		/**
		 * @brief Synxtax for cbrange
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class cb_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			cb_range() : hnc::gnuplot::axis_range("cb") { }
		};

		/**
		 * @brief Synxtax for rrange
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class r_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			r_range() : hnc::gnuplot::axis_range("r") { }
		};

		/**
		 * @brief Synxtax for trange
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class t_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			t_range() : hnc::gnuplot::axis_range("t") { }
		};

		/**
		 * @brief Synxtax for urange
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class u_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			u_range() : hnc::gnuplot::axis_range("u") { }
		};

		/**
		 * @brief Synxtax for vrrange
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node294.html
		 */
		class vr_range : public hnc::gnuplot::axis_range
		{
		public:

			/// @brief Constructor
			vr_range() : hnc::gnuplot::axis_range("vr") { }
		};
	}
}

#endif
