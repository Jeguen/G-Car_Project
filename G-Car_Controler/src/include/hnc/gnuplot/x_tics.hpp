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


#ifndef HNC_GNUPLOT_X_TICS_HPP
#define HNC_GNUPLOT_X_TICS_HPP

#include <string>
#include <vector>

#include "../system_of_measurement.hpp"
#include "../to_string.hpp"


namespace hnc
{
	namespace gnuplot
	{
		/**
		 * @brief Synxtax for xtics (and ytics, ztics, x2tics, y2tics)
		 * 
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 * 
		 * @b From http://gnuplot.sourceforge.net/docs_4.2/node295.html
		 * Fine control of the major (labelled) tics on the x axis is possible with the set xtics command. The tics may be turned off with the unset xtics command, and may be turned on (the default state) with set xtics. Similar commands control the major tics on the y, z, x2 and y2 axes.
		 */
		class axis_tics
		{
		private:

			/// axis_name
			std::string const m_axis_name;

			/// axis or border
			std::string m_axis_or_border;

			/// mirror, nomirror
			std::string m_mirror;

			/// in or out
			std::string m_in_or_out;

			/// scale
			std::string m_scale;

			/// rotate
			std::string m_rotate;

			/// offset, nooffset
			std::string m_offset;

			/// font
			std::string m_font;

		public:

			/// @brief Constructor
			/// @param[in] axis_name Name of the axis (x, y, z, x2, y2)
			axis_tics(std::string const & axis_name) : m_axis_name(axis_name) { }

			/// @brief Destructor
			virtual ~axis_tics() = 0;

			// axis or border

			/**
			 * @brief Set axis (for axis or border)
			 *
			 * axis or border tells gnuplot to put the tics (both the tics themselves and the accompanying labels) along the axis or the border, respectively. If the axis is very close to the border, the axis option will move the tic labels to outside the border. The relevant margin settings will usually be sized badly by the automatic layout algorithm in this case
			 * 
			 * @return the axis_tics
			 */
			axis_tics & axis()
			{
				m_axis_or_border = "axis";
				return *this;
			}

			/**
			 * @brief Set border (for axis or border)
			 *
			 * axis or border tells gnuplot to put the tics (both the tics themselves and the accompanying labels) along the axis or the border, respectively. If the axis is very close to the border, the axis option will move the tic labels to outside the border. The relevant margin settings will usually be sized badly by the automatic layout algorithm in this case
			 *
			 * @return the axis_tics
			 */
			axis_tics & border()
			{
				m_axis_or_border = "border";
				return *this;
			}

			/**
			 * @brief Unset axis or border
			 *
			 * axis or border tells gnuplot to put the tics (both the tics themselves and the accompanying labels) along the axis or the border, respectively. If the axis is very close to the border, the axis option will move the tic labels to outside the border. The relevant margin settings will usually be sized badly by the automatic layout algorithm in this case
			 *
			 * @return the axis_tics
			 */
			axis_tics & axis_or_border_default()
			{
				m_axis_or_border = "";
				return *this;
			}

			// mirror, nomirror

			/**
			 * @brief Set mirror
			 *
			 * mirror tells gnuplot to put unlabelled tics at the same positions on the opposite border. nomirror does what you think it does
			 *
			 * @return the axis_tics
			 */
			axis_tics & mirror()
			{
				m_mirror = "mirror";
				return *this;
			}

			/**
			 * @brief Set no mirror (nomirror)
			 *
			 * mirror tells gnuplot to put unlabelled tics at the same positions on the opposite border. nomirror does what you think it does
			 *
			 * @return the axis_tics
			 */
			axis_tics & no_mirror()
			{
				m_mirror = "nomirror";
				return *this;
			}

			/**
			 * @brief Unset mirror,no mirror
			 *
			 * mirror tells gnuplot to put unlabelled tics at the same positions on the opposite border. nomirror does what you think it does
			 *
			 * @return the axis_tics
			 */
			axis_tics & mirror_default()
			{
				m_mirror = "";
				return *this;
			}

			// in or out

			/**
			 * @brief Change in tic marks to be drawn inwards
			 *
			 * in and out change the tic marks to be drawn inwards or outwards
			 *
			 * @return the axis_tics
			 */
			axis_tics & tic_marks_in()
			{
				m_in_or_out = "in";
				return *this;
			}

			/**
			 * @brief Change in tic marks to be drawn outwards
			 *
			 * in and out change the tic marks to be drawn inwards or outwards
			 *
			 * @return the axis_tics
			 */
			axis_tics & tic_marks_out()
			{
				m_in_or_out = "out";
				return *this;
			}

			/**
			 * @brief Unset if the tic marks to be drawn inwards or outwards
			 *
			 * in and out change the tic marks to be drawn inwards or outwards
			 *
			 * @return the axis_tics
			 */
			axis_tics & tic_marks_in_or_out_default()
			{
				m_in_or_out = "";
				return *this;
			}

			// scale

			/**
			 * @brief Set the scale for major tics
			 *
			 * With scale, the size of the tic marks can be adjusted. The default size 1.0 for major tics and 0.5 for minor tics is requested by scale default
			 *
			 * @param[in] scale_for_major_tics Scale for major tics
			 *
			 * @return the axis_tics
			 */
			axis_tics & scale(double const scale_for_major_tics)
			{
				m_scale = "scale " + hnc::to_string(scale_for_major_tics);
				return *this;
			}

			/**
			 * @brief Set the scale for major and minor tics
			 *
			 * With scale, the size of the tic marks can be adjusted. The default size 1.0 for major tics and 0.5 for minor tics is requested by scale default
			 *
			 * @param[in] scale_for_major_tics Scale for major tics
			 * @param[in] scale_for_minor_tics Scale for minor tics
			 *
			 * @return the axis_tics
			 */
			axis_tics & scale(double const scale_for_major_tics, double const scale_for_minor_tics)
			{
				m_scale = "scale " + hnc::to_string(scale_for_major_tics) + "," + hnc::to_string(scale_for_minor_tics);
				return *this;
			}

			/**
			 * @brief Unset the scale for major and minor tics
			 *
			 * With scale, the size of the tic marks can be adjusted. The default size 1.0 for major tics and 0.5 for minor tics is requested by scale default
			 *
			 * @return the axis_tics
			 */
			axis_tics & scale_default()
			{
				m_scale = "";
				return *this;
			}

			/**
			 * @brief Set the default scale for major and minor tics
			 *
			 * With scale, the size of the tic marks can be adjusted. The default size 1.0 for major tics and 0.5 for minor tics is requested by scale default
			 *
			 * @return the axis_tics
			 */
			axis_tics & scale_default_keyword()
			{
				m_scale = "scale default";
				return *this;
			}

			// rotate

			/**
			 * @brief Rotate the tics
			 *
			 * With scale, the size of the tic marks can be adjusted. The default size 1.0 for major tics and 0.5 for minor tics is requested by scale default
			 *
			 * @param[in] angle_degree A angle (hnc::degree)
			 *
			 * @return the axis_tics
			 */
			axis_tics & rotate(hnc::degree<double> const & angle_degree)
			{
				m_rotate = "rotate by " + hnc::to_string(angle_degree.value());
				return *this;
			}
			
			/**
			 * @brief Unset the rotation of the tics
			 *
			 * With scale, the size of the tic marks can be adjusted. The default size 1.0 for major tics and 0.5 for minor tics is requested by scale default
			 *
			 * @return the axis_tics
			 */
			axis_tics & rotate_default()
			{
				m_rotate = "";
				return *this;
			}

			// offset, nooffset

			/**
			 * @brief Set the offset
			 *
			 * The offset is specified by either x,y or x,y,z, and may be preceded by first, second, graph, screen, or character to select the coordinate system. offset is the offset of the tics texts from their default positions, while the default coordinate system is character. See coordinates (http://gnuplot.sourceforge.net/docs_4.2/node49.html#coordinates) for details. nooffset switches off the offset
			 *
			 * @param[in] x x offset
			 * @param[in] y y offset
			 *
			 * @return the axis_tics
			 */
			axis_tics & offset(double const x, double const y)
			{
				m_offset = "offset " + hnc::to_string(x) + "," + hnc::to_string(y);
				return *this;
			}

			/**
			 * @brief Set the offset
			 *
			 * The offset is specified by either x,y or x,y,z, and may be preceded by first, second, graph, screen, or character to select the coordinate system. offset is the offset of the tics texts from their default positions, while the default coordinate system is character. See coordinates (http://gnuplot.sourceforge.net/docs_4.2/node49.html#coordinates) for details. nooffset switches off the offset
			 *
			 * @param[in] x x offset
			 * @param[in] y y offset
			 * @param[in] z z offset
			 *
			 * @return the axis_tics
			 */
			axis_tics & offset(double const x, double const y, double const z)
			{
				m_offset = "offset " + hnc::to_string(x) + "," + hnc::to_string(y) + "," + hnc::to_string(z);
				return *this;
			}

			/**
			 * @brief No offset
			 *
			 * The offset is specified by either x,y or x,y,z, and may be preceded by first, second, graph, screen, or character to select the coordinate system. offset is the offset of the tics texts from their default positions, while the default coordinate system is character. See coordinates (http://gnuplot.sourceforge.net/docs_4.2/node49.html#coordinates) for details. nooffset switches off the offset
			 *
			 * @return the axis_tics
			 */
			axis_tics & no_offset()
			{
				m_offset = "nooffset";
				return *this;
			}

			/**
			 * @brief Default offset
			 *
			 * The offset is specified by either x,y or x,y,z, and may be preceded by first, second, graph, screen, or character to select the coordinate system. offset is the offset of the tics texts from their default positions, while the default coordinate system is character. See coordinates (http://gnuplot.sourceforge.net/docs_4.2/node49.html#coordinates) for details. nooffset switches off the offset
			 *
			 * @return the axis_tics
			 */
			axis_tics & offset_default()
			{
				m_offset = "";
				return *this;
			}

			// font

			/// @brief Change the font (by font name)
			/// @param[in] font_name Name of the font
			/// @return the axis_tics
			axis_tics & font(std::string const & font_name)
			{
				m_font = "font \"" + font_name + "\"";
				return *this;
			}

			/// @brief Change the font (by font name) and the size
			/// @param[in] font_name Name of the font
			/// @param[in] font_size Size of the font
			/// @return the axis_tics
			axis_tics & font(std::string const & font_name, unsigned int const font_size)
			{
				m_font = "font \"" + font_name + "," + hnc::to_string(font_size) + "\"";
				return *this;
			}

			/// @brief Default font
			/// @return the axis_tics
			axis_tics & font_default()
			{
				m_font = "";
				return *this;
			}

			// to_string
			
			/// @brief Return the axis tics (for a Gnuplot script)
			/// @return the axis tics (for a Gnuplot script)
			std::string to_string() const
			{
				std::string r;

				std::string const prefix = "set " + m_axis_name + "tics ";

				if (m_axis_or_border != "") { if (r.empty() == false) { r += "\n"; } r += prefix + m_axis_or_border; }
				if (m_mirror != "")         { if (r.empty() == false) { r += "\n"; } r += prefix + m_mirror; }
				if (m_in_or_out != "")      { if (r.empty() == false) { r += "\n"; } r += prefix + m_in_or_out; }
				if (m_scale != "")          { if (r.empty() == false) { r += "\n"; } r += prefix + m_scale; }
				if (m_rotate != "")         { if (r.empty() == false) { r += "\n"; } r += prefix + m_rotate; }
				if (m_offset != "")         { if (r.empty() == false) { r += "\n"; } r += prefix + m_offset; }
				if (m_font != "")           { if (r.empty() == false) { r += "\n"; } r += prefix + m_font; }
				
				return r;
			}
		};
		
		inline hnc::gnuplot::axis_tics::~axis_tics() { }
		
		/// @brief Operator << between a std::ostream and a hnc::gnuplot::axis_tics
		/// @param[in,out] o         Output stream
		/// @param[in]     axis_tics A hnc::gnuplot::axis_tics
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::axis_tics const & axis_tics)
		{
			o << axis_tics.to_string();
			return o;
		}
		
		/**
		 * @brief Synxtax for xtics
		 * 
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node295.html
		 */
		class x_tics : public hnc::gnuplot::axis_tics
		{
		public:

			/// @brief Constructor
			x_tics() : hnc::gnuplot::axis_tics("x") { }
		};

		/**
		 * @brief Synxtax for ytics
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node295.html
		 */
		class y_tics : public hnc::gnuplot::axis_tics
		{
		public:

			/// @brief Constructor
			y_tics() : hnc::gnuplot::axis_tics("y") { }
		};

		/**
		 * @brief Synxtax for ztics
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node295.html
		 */
		class z_tics : public hnc::gnuplot::axis_tics
		{
		public:

			/// @brief Constructor
			z_tics() : hnc::gnuplot::axis_tics("z") { }
		};

		/**
		 * @brief Synxtax for x2tics
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node295.html
		 */
		class x2_tics : public hnc::gnuplot::axis_tics
		{
		public:

			/// @brief Constructor
			x2_tics() : hnc::gnuplot::axis_tics("x2") { }
		};

		/**
		 * @brief Synxtax for y2tics
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 *
		 * http://gnuplot.sourceforge.net/docs_4.2/node295.html
		 */
		class y2_tics : public hnc::gnuplot::axis_tics
		{
		public:

			/// @brief Constructor
			y2_tics() : hnc::gnuplot::axis_tics("y2") { }
		};
	}
}

#endif
