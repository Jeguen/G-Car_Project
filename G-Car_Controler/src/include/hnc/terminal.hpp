// Copyright © 2012, 2014 Lénaïc Bagnères, hnc@singularity.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef HNC_TERMINAL_HPP
#define HNC_TERMINAL_HPP

#include <string>
#include <iostream>

#include "to_string.hpp"


namespace hnc
{
	/**
	 * @brief Control the terminal (clear, delete current line, colors)
	 *
	 * @code
	   #include <hnc/terminal.hpp>
	   @endcode
	 *
	 * @note bold + color = light color
	 * @warning hnc::terminal::color::reset, hnc::terminal::background_color::reset and hnc::terminal::bold_end are the same: they reset color and bold text
	 */
	namespace terminal
	{
		/**
		 * @brief Return the string to clear terminal
		 * 
		 * @code
		   #include <hnc/terminal.hpp>
		   @endcode
		   
		   @return the string to clear terminal
		 */
		inline std::string clear_string() { return "\033[H\033[2J"; }
		
		/**
		 * @brief Clear the terminal
		 * 
		 * @code
		   #include <hnc/terminal.hpp>
		   @endcode
		 */
		void clear() { std::cout << hnc::terminal::clear_string(); }
		
		/**
		 * @brief Font color
		 * 
		 * @code
		   #include <hnc/terminal.hpp>
		   @endcode
		 */
		namespace color // TODO inline function
		{
			std::string const reset         = "\033[0m";  ///< Color by default
			std::string const black         = "\033[30m"; ///< Color black
			std::string const red           = "\033[31m"; ///< Color red
			std::string const light_red     = "\033[1;31m"; ///< Color light red
			std::string const green         = "\033[32m"; ///< Color green
			std::string const light_green   = "\033[1;32m"; ///< Color light green
			std::string const orange        = "\033[33m"; ///< Color orange
			std::string const light_orange  = "\033[1;33m"; ///< Color light orange
			std::string const blue          = "\033[34m"; ///< Color blue
			std::string const light_blue    = "\033[1;34m"; ///< Color light blue
			std::string const magenta       = "\033[35m"; ///< Color magenta
			std::string const light_magenta = "\033[1;35m"; ///< Color light magenta
			std::string const cyan          = "\033[36m"; ///< Color cyan
			std::string const light_cyan    = "\033[1;36m"; ///< Color light cyan
			std::string const white         = "\033[37m"; ///< Color white
		}
		
		/**
		 * @brief Background color
		 * 
		 * @code
		   #include <hnc/terminal.hpp>
		   @endcode
		 */
		namespace background_color // TODO inline function
		{
			std::string const reset   = "\033[0m";  ///< Color by default
			std::string const black   = "\033[40m"; ///< Color black
			std::string const red     = "\033[41m"; ///< Color red
			std::string const green   = "\033[42m"; ///< Color green
			std::string const orange  = "\033[43m"; ///< Color orange
			std::string const blue    = "\033[44m"; ///< Color blue
			std::string const magenta = "\033[45m"; ///< Color magenta
			std::string const cyan    = "\033[46m"; ///< Color cyan
			std::string const white   = "\033[47m"; ///< Color white
		}

		/// Color & background color by default
		std::string const color_reset = hnc::terminal::color::reset + hnc::terminal::background_color::reset;
		/// Color error
		std::string const error   = hnc::terminal::color::red;
		/// Color warning
		std::string const warning = hnc::terminal::color::orange;
		/// Color info
		std::string const info    = hnc::terminal::color::cyan;
		/// Color result
		std::string const result  = hnc::terminal::color::green;
		/// Color debug
		std::string const debug   = hnc::terminal::color::magenta;

		/// Bold
		std::string const bold = "\033[1m";
		/// Bold end
		std::string const bold_end = "\033[0m";

		/// Underline
		std::string const underline = "\033[4m";
		/// Underline end
		std::string const underline_end = "\033[24m";

		/// Color & background color by default & bold end & underline end
		std::string const reset = hnc::terminal::color_reset + hnc::terminal::bold_end + hnc::terminal::underline_end;

		/**
		 * @brief String to erase the end of the current line in terminal
		 * 
		 * @code
		   #include <hnc/terminal.hpp>
		   @endcode
		 *
		 * @param[in] nb_char number of chars to delete (1 char by default)
		 *
		 * @return the good chars to delete the line
		 */
		inline std::string back_string(unsigned int const nb_char = 1)
		{
			// http://www.termsys.demon.co.uk/vtansi.htm
			// <ESC>[1K - Erases from the current cursor position to the start of the current line
			std::string r = "\033[1K";
			// <ESC>[{COUNT}D - Moves the cursor backward by COUNT columns; the default count is 1
			r += "\033[" + hnc::to_string(nb_char) + "D";
			return r;
		}
		
		/**
		 * @brief Erase the end of the current line in the terminal
		 * 
		 * @code
		   #include <hnc/terminal.hpp>
		   @endcode
		 *
		 * @param[in] nb_char number of chars to delete (1 char by default)
		 */
		inline void back(unsigned int const nb_char = 1)
		{
			std::cout << hnc::terminal::back_string(nb_char);
		}

		/**
		 * @brief String to erase lines in terminal
		 * 
		 * @code
		   #include <hnc/terminal.hpp>
		   @endcode
		 *
		 * @param[in] nb_line number of lines to delete (1 by default)
		 * 
		 * @return the good chars to delete lines
		 */
		inline std::string delete_line_string(unsigned int const nb_line = 1)
		{
			std::string r = "";
			// Delete line by line to erase data
			r += "\033[K" + hnc::terminal::back_string(4096 * 2 * 2);
			for (unsigned int i = 1; i < nb_line; ++i)
			{
				r += "\033[1A";
				r += "\033[K" + hnc::terminal::back_string(4096 * 2 * 2);
			}
			// Return
			return r;
		}
		
		/**
		 * @brief Erase lines in the terminal
		 * 
		 * @code
		   #include <hnc/terminal.hpp>
		   @endcode
		 *
		 * @param[in] nb_line number of lines to delete (1 by default)
		 */
		inline void delete_line(unsigned int const nb_line = 1)
		{
			std::cout << hnc::terminal::delete_line_string(nb_line);
		}
	}
}

#endif
