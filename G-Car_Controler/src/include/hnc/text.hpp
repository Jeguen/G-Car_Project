// Copyright © 2013, 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef HNC_TEXT_HPP
#define HNC_TEXT_HPP

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "vector2D_minimal.hpp"
#include "to_string.hpp"
#include "terminal.hpp"


namespace hnc
{
	/**
	 * @brief Text manipulation
	 *
	 * @code
	   #include <hnc/text.hpp>
	   @endcode
	 */
	namespace text
	{
		/**
		 * @brief String to vector of lines
		 * 
		 * @code
		   #include <hnc/text.hpp>
		   @endcode
		 * 
		 * @param[in] text  Text in a a std::string
		 * @param[in] delim Line separator ('\\n' by default)
		 * 
		 * @return the vector of lines
		 */
		std::vector<std::string> string_to_vector_of_lines(std::string const & text, char const delim = '\n')
		{
			std::vector<std::string> lines;
			
			// Put text in a stream
			std::istringstream is(text);
			
			// Get each line
			std::string line;
			while (std::getline(is, line, delim))
			{
				// Save line
				lines.push_back(line);
			}
			
			return lines;
		}
		
		/// Tags for hnc::text::diff: equal, insertion, deletion
		enum class diff_tag { equal, insertion, deletion };
		
		// http://en.wikipedia.org/wiki/Longest_common_subsequence_problem
		/**
		 * @brief Return the vector of differences to compare texts
		 * 
		 * @code
		   #include <hnc/text.hpp>
		   @endcode
		 * 
		 * The vector of diffrences is a vector of hnc::text::diff_tag
		 * 
		 * @code
		   // Original texts
		   std::vector<std::string> const text0 = {"lorem ", "ipsum, ", "dolor ", "sit, ", "amet, ", "consectetur, ", "adipisci ", "elit, ", "sed ", "eius ", "mod ", "tempor ", "incidunt, ", "ut ", "labore ", "et ", "dolore ", "magna ", "aliqua"};
		   std::vector<std::string> const text1 = {"dolorem ", "ipsum, ", "quia ", "dolor ", "sit, ", "amet, ", "consectetur, ", "adipisci ", "velit, ", "sed ", "quia non ", "numquam ", "eius ", "modi ", "tempora ", "incidunt, ", "ut ", "labore ", "et ", "dolore ", "magnam ", "aliquam"};
		   
		   // Compute the diff
		   auto diff = hnc::text::diff(text0, text1);
		   
		   // Display the diff
		   hnc::text::display_diff(text0, text1, diff);
		   // -               | + dolorem 
		   // + lorem         | - 
		   // = ipsum,        | = ipsum, 
		   // -               | + quia 
		   // = dolor         | = dolor 
		   // = sit,          | = sit, 
		   // = amet,         | = amet, 
		   // = consectetur,  | = consectetur, 
		   // = adipisci      | = adipisci 
		   // -               | + velit, 
		   // + elit,         | - 
		   // = sed           | = sed 
		   // -               | + quia non 
		   // -               | + numquam 
		   // = eius          | = eius 
		   // -               | + modi 
		   // -               | + tempora 
		   // + mod           | - 
		   // + tempor        | - 
		   // = incidunt,     | = incidunt, 
		   // = ut            | = ut 
		   // = labore        | = labore 
		   // = et            | = et 
		   // = dolore        | = dolore 
		   // -               | + magnam 
		   // -               | + aliquam
		   // + magna         | - 
		   // + aliqua        | -
		   @endcode
		 * 
		 * @param[in] text0 First text
		 * @param[in] text1 Second text
		 * 
		 * @return the vector of differences
		 */
		template <class T>
		std::vector<hnc::text::diff_tag> diff
		(
			std::vector<T> const & text0, std::vector<T> const & text1
		)
		{
			// Texts are empty
			if (text0.empty() && text1.empty())
			{
				return std::vector<hnc::text::diff_tag>();
			}
			// First text is empty
			else if (text0.empty())
			{
				return std::vector<hnc::text::diff_tag>(text1.size(), hnc::text::diff_tag::deletion);
			}
			// Second text is empty
			else if (text1.empty())
			{
				return std::vector<hnc::text::diff_tag>(text0.size(), hnc::text::diff_tag::insertion);
			}
			
			// Array to compute the length of the longuest common subsequence
			hnc::vector2D_minimal<std::size_t> array(text0.size() + 1, text1.size() + 1, 0);
			
			// Compute the array
			for (std::size_t i = 1; i < array.nb_row(); ++i)
			{
				for (std::size_t j = 1; j < array.nb_col(); ++j)
				{
					if (text0[i-1] == text1[j-1]) { array[i][j] = array[i-1][j-1] + 1; }
					else { array[i][j] = std::max(array[i-1][j], array[i][j-1]); }
				}
			}
			
			// Return
			std::vector<hnc::text::diff_tag> diff;
			diff.reserve(array[array.nb_row()-1][array.nb_col()-1]);
			
			// Read the array
			{
				std::size_t i = array.nb_row() - 1;
				std::size_t j = array.nb_col() - 1;
				
				while (i != 0 && j != 0)
				{
					if (text0[i-1] == text1[j-1])
					{
						diff.insert(diff.begin(), hnc::text::diff_tag::equal);
						--i; --j;
					}
					else
					{
						if (array[i][j-1] > array[i-1][j])
						{
							diff.insert(diff.begin(), hnc::text::diff_tag::deletion);
							--j;
						}
						else
						{
							diff.insert(diff.begin(), hnc::text::diff_tag::insertion);
							--i;
						}
					}
				}
				
				while (i != 0 || j != 0)
				{
					if (i > j) { diff.insert(diff.begin(), hnc::text::diff_tag::insertion); --i; }
					else { diff.insert(diff.begin(), hnc::text::diff_tag::deletion); --j; }
				}
			}
			
			// Return
			return diff;
		}
		
		/**
		 * @brief Display a vector of differences with compared texts
		 * 
		 * @code
		   #include <hnc/text.hpp>
		   @endcode
		 * 
		 * The vector of difference is computed by hnc::text::diff
		 * 
		 * @param[in] text0           First text
		 * @param[in] text1           Second text
		 * @param[in] diff            A vector of difference computed by hnc::text::diff
		 * @param[in] o               A std::ostream for the output (std::cout by default)
		 * @param[in] equal_color     Color for equal symbol (=) (hnc::terminal::color::cyan for example) (empty by default)
		 * @param[in] insertion_color Color for insertion symbol (+) (hnc::terminal::color::green for example) (empty by default)
		 * @param[in] deletion_color  Color for deletion symbol (-) (hnc::terminal::color::red for example) (empty by default)
		 * @param[in] reset_color     String to reset color (hnc::terminal::reset for example) (empty by default)
		 */
		template <class T>
		void display_diff_no_color
		(
			std::vector<T> const & text0, std::vector<T> const & text1,
			std::vector<hnc::text::diff_tag> diff,
			std::ostream & o = std::cout,
			std::string const & equal_color = "",
			std::string const & insertion_color = "",
			std::string const & deletion_color = "",
			std::string const & reset_color = ""
		)
		{
			{
				// Get max size of lines of first text
				std::size_t const max_text0_line_size = [&text0]() -> std::size_t
				{
					std::size_t max = 0;
					for (T const & e : text0) { max = std::max(max, hnc::to_string(e).size()); }
					return max;
				}();
				
				// Index of texts
				std::size_t i_text0 = 0;
				std::size_t i_text1 = 0;
			
				// Display separator alone
				auto display_separator_alone = [&]() -> void
				{
					o << std::string(max_text0_line_size, ' ');
					o << " | ";
				};
			
				// Display separator after text0 line
				auto display_separator_after_text0_line = [&]() -> void
				{
					if (i_text0 < text0.size())
					{
						o << std::string(max_text0_line_size - text0[i_text0].size(), ' ');
					}
					else
					{
						display_separator_alone();
					}
					o << " | ";
				};
				
				// Display a first text line
				auto display_text0_line = [&]() -> void
				{
					if (i_text0 < text0.size()) { o << text0[i_text0]; }
					display_separator_after_text0_line();
					++i_text0;
				};
				
				// Display a second text line
				auto display_text1_line = [&]() -> void
				{
					if (i_text1 < text1.size()) { o << text1[i_text1]; }
					++i_text1;
				};
				
				for (std::size_t i = 0; i < diff.size(); ++i)
				{
					// Equal
					if (diff[i] == hnc::text::diff_tag::equal)
					{
						o << equal_color << "= " << reset_color;
						display_text0_line();
						o << equal_color << "= " << reset_color;
						display_text1_line();
					}
					// Insertion
					else if (diff[i] == hnc::text::diff_tag::insertion)
					{
						o << insertion_color << "+ " << reset_color;
						display_text0_line();
						o << deletion_color << "- " << reset_color;
					}
					// Deletion
					else // if (diff[i] == hnc::text::diff_tag::deletion)
					{
						o << deletion_color << "- " << reset_color;
						display_separator_alone();
						o << insertion_color << "+ " << reset_color;
						display_text1_line();
					}
					o << "\n";
				}
			}
		}
		
		/**
		 * @brief Display a vector of differences with compared texts
		 * 
		 * @code
		   #include <hnc/text.hpp>
		   @endcode
		 * 
		 * The vector of difference is computed by hnc::text::diff
		 * 
		 * @param[in] text0           First text
		 * @param[in] text1           Second text
		 * @param[in] diff            A vector of difference computed by hnc::text::diff
		 * @param[in] o               A std::ostream for the output (std::cout by default)
		 */
		template <class T>
		void display_diff
		(
			std::vector<T> const & text0, std::vector<T> const & text1,
			std::vector<hnc::text::diff_tag> diff,
			std::ostream & o = std::cout
		)
		{
			hnc::text::display_diff_no_color
			(
				text0, text1,
				diff,
				o,
				hnc::terminal::color::cyan,
				hnc::terminal::color::green,
				hnc::terminal::color::red,
				hnc::terminal::reset
			);
		}
	}
}

#endif
