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


#ifndef HNC_GNUPLOT_OUTPUT_TERMINAL_HPP
#define HNC_GNUPLOT_OUTPUT_TERMINAL_HPP

#include <string>

#include "../to_string.hpp"


namespace hnc
{
	namespace gnuplot
	{
		/**
		 * @brief Output terminal png for hnc::gnuplot::gnuplot
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 */
		class output_terminal_png
		{
		private:

			/// Output filename without the extension
			std::string m_output_filename;

			/// Size
			std::string m_size = "size 800,600 ";

			/// Enhanced, The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			std::string m_enhanced = "enhanced ";

			/// Font (name and size)
			std::string m_font = "";
			
		public:

			/// @brief Constructor
			/// @param[in] output_filename Output filename without the extension
			output_terminal_png(std::string const & output_filename) : m_output_filename(output_filename + ".png") { }

			/// @brief Return the output filename
			/// @return the output filename
			std::string output_filename() const { return m_output_filename; }

			/// @brief Set the size
			/// @param[in] width  Width
			/// @param[in] height Height
			/// @return the output terminal
			output_terminal_png & size(std::size_t const width, std::size_t const height)
			{
				m_size = "size " + hnc::to_string(width) + "," + hnc::to_string(height) + " ";
				return *this;
			}

			/**
			 * @brief Enhanced
			 *
			 * The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			 *
			 * @return the output terminal
			 */
			output_terminal_png & enhanced()
			{
				m_enhanced = "enhanced ";
				return *this;
			}

			/**
			 * @brief No enhanced
			 *
			 * The terminal does not interprets the text. For exemple n_1 give n_1 (and not @f$ n_1 @f$).
			 *
			 * @return the output terminal
			 */
			output_terminal_png & no_enhanced()
			{
				m_enhanced = "";
				return *this;
			}

			/// @brief Set the font
			/// @param[in] name Name of the font
			/// @param[in] size Size of the font
			/// @return the output terminal
			output_terminal_png & font(std::string const & name, unsigned int size)
			{
				m_font = "font '" + name + "," + hnc::to_string(size) + "' ";
				return *this;
			}
			
			/// @brief Use the default font
			/// @return the output terminal
			output_terminal_png & no_font()
			{
				m_font = "";
				return *this;
			}

			/// @brief Return the output terminal (for a Gnuplot script)
			/// @return the output terminal (for a Gnuplot script)
			std::string to_string() const
			{
				return "set terminal png " + m_size + m_enhanced + m_font + "\n"
				       "set output '" + m_output_filename + "'";
			}
		};

		/// @brief Operator << between a std::ostream and a  hnc::gnuplot::output_terminal_png
		/// @param[in,out] o               Output stream
		/// @param[in]     output_terminal A  hnc::gnuplot::output_terminal_png
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::output_terminal_png const & output_terminal)
		{
			o << output_terminal.to_string();
			return o;
		}

		/**
		 * @brief Output terminal svg for hnc::gnuplot::gnuplot
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 */
		class output_terminal_svg
		{
		private:

			/// Output filename without the extension
			std::string m_output_filename;

			/// Size
			std::string m_size = "size 800,600 ";

			/// Enhanced, The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			std::string m_enhanced = "enhanced ";

			/// Font (name and size)
			std::string m_font = "";

		public:

			/// @brief Constructor
			/// @param[in] output_filename Output filename without the extension
			output_terminal_svg(std::string const & output_filename) : m_output_filename(output_filename + ".svg") { }

			/// @brief Return the output filename
			/// @return the output filename
			std::string output_filename() const { return m_output_filename; }

			/// @brief Set the size
			/// @param[in] width  Width
			/// @param[in] height Height
			/// @return the output terminal
			output_terminal_svg & size(std::size_t const width, std::size_t const height)
			{
				m_size = "size " + hnc::to_string(width) + "," + hnc::to_string(height) + " ";
				return *this;
			}

			/**
			 * @brief Enhanced
			 *
			 * The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			 *
			 * @return the output terminal
			 */
			output_terminal_svg & enhanced()
			{
				m_enhanced = "enhanced ";
				return *this;
			}

			/**
			 * @brief No enhanced
			 *
			 * The terminal does not interprets the text. For exemple n_1 give n_1 (and not @f$ n_1 @f$).
			 *
			 * @return the output terminal
			 */
			output_terminal_svg & no_enhanced()
			{
				m_enhanced = "";
				return *this;
			}

			/// @brief Set the font
			/// @param[in] name Name of the font
			/// @param[in] size Size of the font
			/// @return the output terminal
			output_terminal_svg & font(std::string const & name, unsigned int size)
			{
				m_font = "fname '" + name + "' fsize '" + hnc::to_string(size) + "' ";
				return *this;
			}

			/// @brief Use the default font
			/// @return the output terminal
			output_terminal_svg & no_font()
			{
				m_font = "";
				return *this;
			}

			/// @brief Return the output terminal (for a Gnuplot script)
			/// @return the output terminal (for a Gnuplot script)
			std::string to_string() const
			{
				return "set terminal svg " + m_size + m_enhanced + m_font + "\n"
				       "set output '" + m_output_filename;
			}
		};

		/// @brief Operator << between a std::ostream and a  hnc::gnuplot::output_terminal_svg
		/// @param[in,out] o               Output stream
		/// @param[in]     output_terminal A  hnc::gnuplot::output_terminal_svg
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::output_terminal_svg const & output_terminal)
		{
			o << output_terminal.to_string();
			return o;
		}

		/**
		 * @brief Output terminal pdf for hnc::gnuplot::gnuplot
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 */
		class output_terminal_pdf
		{
		private:

			/// Output filename without the extension
			std::string m_output_filename;

			/// Size
			std::string m_size = "size 10cm,7.5cm ";

			/// Enhanced, The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			std::string m_enhanced = "enhanced ";

			/// Font (name and size)
			std::string m_font = "";

		public:

			/**
			 * @brief Constructor
			 * @param[in] output_filename Output filename without the extension
			 */
			output_terminal_pdf(std::string const & output_filename) : m_output_filename(output_filename + ".pdf") { }

			/// @brief Return the output filename
			/// @return the output filename
			std::string output_filename() const { return m_output_filename; }

			/// @brief Set the size in cm
			/// @param[in] width  Width in cm
			/// @param[in] height Height in cm
			/// @return the output terminal
			output_terminal_pdf & size_in_cm(double const width, double const height)
			{
				m_size = "size " + hnc::to_string(width) + "cm," + hnc::to_string(height) + "cm ";
				return *this;
			}

			/// @brief Set the size in inches
			/// @param[in] width  Width in inches
			/// @param[in] height Height in inchess
			/// @return the output terminal
			output_terminal_pdf & size_in_inches(double const width, double const height)
			{
				m_size = "size " + hnc::to_string(width) + "," + hnc::to_string(height) + " ";
				return *this;
			}

			/**
			 * @brief Enhanced
			 *
			 * The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			 *
			 * @return the output terminal
			 */
			output_terminal_pdf & enhanced()
			{
				m_enhanced = "enhanced ";
				return *this;
			}

			/**
			 * @brief No enhanced
			 *
			 * The terminal does not interprets the text. For exemple n_1 give n_1 (and not @f$ n_1 @f$).
			 *
			 * @return the output terminal
			 */
			output_terminal_pdf & no_enhanced()
			{
				m_enhanced = "";
				return *this;
			}

			/// @brief Set the font
			/// @param[in] name Name of the font
			/// @param[in] size Size of the font
			/// @return the output terminal
			output_terminal_pdf & font(std::string const & name, unsigned int size)
			{
				m_font = "fname '" + name + "' fsize '" + hnc::to_string(size) + "' ";
				return *this;
			}

			/// @brief Use the default font
			/// @return the output terminal
			output_terminal_pdf & no_font()
			{
				m_font = "";
				return *this;
			}

			/// @brief Return the output terminal (for a Gnuplot script)
			/// @return the output terminal (for a Gnuplot script)
			std::string to_string() const
			{
				return "set terminal pdf " + m_size + m_enhanced + m_font + "\n"
				       "set output '" + m_output_filename;
			}
		};
		
		/// @brief Operator << between a std::ostream and a  hnc::gnuplot::output_terminal_pdf
		/// @param[in,out] o               Output stream
		/// @param[in]     output_terminal A  hnc::gnuplot::output_terminal_pdf
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::output_terminal_pdf const & output_terminal)
		{
			o << output_terminal.to_string();
			return o;
		}
		
		/**
		 * @brief Output terminal postscript for hnc::gnuplot::gnuplot
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 */
		class output_terminal_postscript
		{
		private:

			/// Output filename without the extension
			std::string m_output_filename;

			/// Size
			std::string m_size = "size 10cm,7.5cm ";

			/// Enhanced, The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			std::string m_enhanced = "enhanced ";

			/// Font (name and size)
			std::string m_font = "";

		public:

			/// @brief Constructor
			/// @param[in] output_filename Output filename without the extension
			output_terminal_postscript(std::string const & output_filename) : m_output_filename(output_filename + ".eps") { }

			/// @brief Return the output filename
			/// @return the output filename
			std::string output_filename() const { return m_output_filename; }

			/// @brief Set the size in cm
			/// @param[in] width  Width in cm
			/// @param[in] height Height in cm
			/// @return the output terminal
			output_terminal_postscript & size_in_cm(double const width, double const height)
			{
				m_size = "size " + hnc::to_string(width) + "cm," + hnc::to_string(height) + "cm ";
				return *this;
			}

			/// @brief Set the size in inches
			/// @param[in] width  Width in inches
			/// @param[in] height Height in inchess
			/// @return the output terminal
			output_terminal_postscript & size_in_inches(double const width, double const height)
			{
				m_size = "size " + hnc::to_string(width) + "," + hnc::to_string(height) + " ";
				return *this;
			}

			/// @brief No size
			/// @return the output terminal
			output_terminal_postscript & no_size()
			{
				m_size = "";
				return *this;
			}

			/**
			 * @brief Enhanced
			 *
			 * The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			 *
			 * @return the output terminal
			 */
			output_terminal_postscript & enhanced()
			{
				m_enhanced = "enhanced ";
				return *this;
			}

			/**
			 * @brief No enhanced
			 *
			 * The terminal does not interprets the text. For exemple n_1 give n_1 (and not @f$ n_1 @f$).
			 *
			 * @return the output terminal
			 */
			output_terminal_postscript & no_enhanced()
			{
				m_enhanced = "";
				return *this;
			}

			/// @brief Set the font
			/// @param[in] name      Name of the font
			/// @param[in] size      Size of the font
			/// @param[in] linewidth In eps mode the whole plot, including the fonts, is reduced to half of the default size. Use linewidth to multiply line with by a factor of linewidth. http://www.gnuplotting.org/output-terminals/
			/// @return the output terminal
			output_terminal_postscript & font(std::string const & name, unsigned int size, unsigned int const linewidth = 2)
			{
				m_font = "font '" + name + "," + hnc::to_string(size) + "' linewidth " + hnc::to_string(linewidth) + " ";
				return *this;
			}

			/// @brief Use the default font
			/// @return the output terminal
			output_terminal_postscript & no_font()
			{
				m_font = "";
				return *this;
			}

			/// @brief Return the output terminal (for a Gnuplot script)
			/// @return the output terminal (for a Gnuplot script)
			std::string to_string() const
			{
				return "set terminal postscript eps " + m_size + m_enhanced + "color " + m_font + "\n"
				       "set output '" + m_output_filename;
			}
		};
		
		/// @brief Operator << between a std::ostream and a  hnc::gnuplot::output_terminal_postscript
		/// @param[in,out] o               Output stream
		/// @param[in]     output_terminal A  hnc::gnuplot::output_terminal_postscript
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::output_terminal_postscript const & output_terminal)
		{
			o << output_terminal.to_string();
			return o;
		}

		/**
		 * @brief Output terminal epslatex for hnc::gnuplot::gnuplot
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 */
		class output_terminal_epslatex
		{
		private:

			/// Output filename without the extension
			std::string m_output_filename;

			/// Size
			std::string m_size = "size 10cm,7.5cm ";

			/// standalone
			std::string m_standalone = "";

		public:

			/// @brief Constructor
			/// @param[in] output_filename Output filename without the extension
			output_terminal_epslatex(std::string const & output_filename) : m_output_filename(output_filename + ".tex") { }

			/// @brief Return the output filename
			/// @return the output filename
			std::string output_filename() const { return m_output_filename; }

			/// @brief Set the size in cm
			/// @param[in] width  Width in cm
			/// @param[in] height Height in cm
			/// @return the output terminal
			output_terminal_epslatex & size_in_cm(double const width, double const height)
			{
				m_size = "size " + hnc::to_string(width) + "cm," + hnc::to_string(height) + "cm ";
				return *this;
			}

			/// @brief Set the size in inches
			/// @param[in] width  Width in inches
			/// @param[in] height Height in inchess
			/// @return the output terminal
			output_terminal_epslatex & size_in_inches(double const width, double const height)
			{
				m_size = "size " + hnc::to_string(width) + "," + hnc::to_string(height) + " ";
				return *this;
			}

			/**
			 * @brief standalone
			 *
			 * If you have not any LaTeX document, but want only to produce a figure with LaTeX labels, you can use the standalone mode
			 *
			 * @return the output terminal
			 */
			output_terminal_epslatex & standalone()
			{
				m_standalone = "standalone ";
				return *this;
			}

			/**
			 * @brief No standalone
			 *
			 * If you have not any LaTeX document, but want only to produce a figure with LaTeX labels, you can use the standalone mode
			 *
			 * @return the output terminal
			 */
			output_terminal_epslatex & no_standalone()
			{
				m_standalone = "";
				return *this;
			}

			/// @brief Return the output terminal (for a Gnuplot script)
			/// @return the output terminal (for a Gnuplot script)
			std::string to_string() const
			{
				return "set terminal epslatex " + m_size + m_standalone + "color colortext\n"
				       "set output '" + m_output_filename;
			}
		};
		
		/// @brief Operator << between a std::ostream and a  hnc::gnuplot::output_terminal_epslatex
		/// @param[in,out] o               Output stream
		/// @param[in]     output_terminal A  hnc::gnuplot::output_terminal_epslatex
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::output_terminal_epslatex const & output_terminal)
		{
			o << output_terminal.to_string();
			return o;
		}
		
		/**
		 * @brief Output terminal wxt for hnc::gnuplot::gnuplot
		 *
		 * @code
		   #include <hnc/gnuplot.hpp>
		   @endcode
		 */
		class output_terminal_wxt
		{
		private:

			/// Size
			std::string m_size = "size 800,600 ";

			/// Enhanced, The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			std::string m_enhanced = "enhanced ";

			/// Font (name and size)
			std::string m_font = "";

		public:

			/// @brief Set the size
			/// @param[in] width  Width
			/// @param[in] height Height
			/// @return the output terminal
			output_terminal_wxt & size(std::size_t const width, std::size_t const height)
			{
				m_size = "size " + hnc::to_string(width) + "," + hnc::to_string(height) + " ";
				return *this;
			}

			/**
			 * @brief Enhanced
			 *
			 * The enhanced option tells the terminal interprets the text. For exemple n_1 give @f$ n_1 @f$.
			 *
			 * @return the output terminal
			 */
			output_terminal_wxt & enhanced()
			{
				m_enhanced = "enhanced ";
				return *this;
			}

			/**
			 * @brief No enhanced
			 *
			 * The terminal does not interprets the text. For exemple n_1 give n_1 (and not @f$ n_1 @f$).
			 *
			 * @return the output terminal
			 */
			output_terminal_wxt & no_enhanced()
			{
				m_enhanced = "";
				return *this;
			}

			/// @brief Set the font
			/// @param[in] name Name of the font
			/// @param[in] size Size of the font
			/// @return the output terminal
			output_terminal_wxt & font(std::string const & name, unsigned int size)
			{
				m_font = "font '" + name + "," + hnc::to_string(size) + "' ";
				return *this;
			}

			/// @brief Use the default font
			/// @return the output terminal
			output_terminal_wxt & no_font()
			{
				m_font = "";
				return *this;
			}

			/// @brief Return the output terminal (for a Gnuplot script)
			/// @return the output terminal (for a Gnuplot script)
			std::string to_string() const
			{
				return "set terminal wxt " + m_size + m_enhanced + m_font + "persit";
			}
		};
		
		/// @brief Operator << between a std::ostream and a  hnc::gnuplot::output_terminal_wxt
		/// @param[in,out] o               Output stream
		/// @param[in]     output_terminal A  hnc::gnuplot::output_terminal_wxt
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::gnuplot::output_terminal_wxt const & output_terminal)
		{
			o << output_terminal.to_string();
			return o;
		}
	}
}

#endif
