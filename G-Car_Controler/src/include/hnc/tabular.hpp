// Copyright © 2013, 22014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef HNC_TABULAR_HPP
#define HNC_TABULAR_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "to_string.hpp"
#include "terminal.hpp"


namespace hnc
{
	/**
	 * @brief Table with LaTeX or HTML output
	 *
	 * @code
	   #include <hnc/tabular.hpp>
	   @endcode
	 *
	 * Example: Simple tabular
	 * @code
	   std::vector<std::vector<double>> data
	   ({
	   	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	   	{20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
	   	{40, 41, 42, 43, 44, 45, 46, 47, 48, 49},
	   	{60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
	   	{80, 81, 82, 83, 84, 85, 86, 87, 88, 89},
	   	{100, 101, 102, 103, 104, 105, 106, 107, 108, 109}
	   });
	   std::vector<std::string> header({"h0", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9"});
	   std::vector<std::string> footer({"f0", "f1", "f2", "..."});
	   
	   hnc::tabular tabular(data, "Simple tabular", header, footer);
	  
	   // Txt
	   std::cout << tabular << std::endl;
	   std::cout << std::endl;
	   // Simple tabular
	   // -------------------------------------------------------------
	   // | h0  | h1  | h2  | h3  | h4  | h5  | h6  | h7  | h8  | h9  |
	   // -------------------------------------------------------------
	   // | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   |
	   // -------------------------------------------------------------
	   // | 20  | 21  | 22  | 23  | 24  | 25  | 26  | 27  | 28  | 29  |
	   // -------------------------------------------------------------
	   // | 40  | 41  | 42  | 43  | 44  | 45  | 46  | 47  | 48  | 49  |
	   // -------------------------------------------------------------
	   // | 60  | 61  | 62  | 63  | 64  | 65  | 66  | 67  | 68  | 69  |
	   // -------------------------------------------------------------
	   // | 80  | 81  | 82  | 83  | 84  | 85  | 86  | 87  | 88  | 89  |
	   // -------------------------------------------------------------
	   // | 100 | 101 | 102 | 103 | 104 | 105 | 106 | 107 | 108 | 109 |
	   // -------------------------------------------------------------
	   // | f0  | f1  | f2  | ... |     |     |     |     |     |     |
	   // -------------------------------------------------------------
	   
	   // LaTeX
	   std::cout << tabular.latex() << std::endl;
	   std::cout << std::endl;
	   // \begin{table}
	   // 	\caption{Simple tabular}
	   // 	\centering
	   // 	\begin{tabular}{ | c | c | c | c | c | c | c | c | c | c | }
	   // 		\hline
	   // 		h0 & h1 & h2 & h3 & h4 & h5 & h6 & h7 & h8 & h9 \\
	   // 		\hline
	   // 		0 & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9 \\
	   // 		\hline
	   // 		20 & 21 & 22 & 23 & 24 & 25 & 26 & 27 & 28 & 29 \\
	   // 		\hline
	   // 		40 & 41 & 42 & 43 & 44 & 45 & 46 & 47 & 48 & 49 \\
	   // 		\hline
	   // 		60 & 61 & 62 & 63 & 64 & 65 & 66 & 67 & 68 & 69 \\
	   // 		\hline
	   // 		80 & 81 & 82 & 83 & 84 & 85 & 86 & 87 & 88 & 89 \\
	   // 		\hline
	   // 		100 & 101 & 102 & 103 & 104 & 105 & 106 & 107 & 108 & 109 \\
	   // 		\hline
	   // 		f0 & f1 & f2 & ... &  &  &  &  &  &  \\
	   // 		\hline
	   // 	\end{tabular}
	   // \end{table}
	   
	   // HTML
	   std::cout << tabular.html() << std::endl;
	   std::cout << std::endl;
	   // <table border="1">
	   // 	<caption>Simple tabular</caption>
	   // 	<tr>
	   // 		<th>h0</th> <th>h1</th> <th>h2</th> <th>h3</th> <th>h4</th> <th>h5</th> <th>h6</th> <th>h7</th> <th>h8</th> <th>h9</th>
	   // 	</tr>
	   // 	<tr>
	   // 		<td>0</td> <td>1</td> <td>2</td> <td>3</td> <td>4</td> <td>5</td> <td>6</td> <td>7</td> <td>8</td> <td>9</td>
	   // 	</tr>
	   // 	<tr>
	   // 		<td>20</td> <td>21</td> <td>22</td> <td>23</td> <td>24</td> <td>25</td> <td>26</td> <td>27</td> <td>28</td> <td>29</td>
	   // 	</tr>
	   // 	<tr>
	   // 		<td>40</td> <td>41</td> <td>42</td> <td>43</td> <td>44</td> <td>45</td> <td>46</td> <td>47</td> <td>48</td> <td>49</td>
	   // 	</tr>
	   // 	<tr>
	   // 		<td>60</td> <td>61</td> <td>62</td> <td>63</td> <td>64</td> <td>65</td> <td>66</td> <td>67</td> <td>68</td> <td>69</td>
	   // 	</tr>
	   // 	<tr>
	   // 		<td>80</td> <td>81</td> <td>82</td> <td>83</td> <td>84</td> <td>85</td> <td>86</td> <td>87</td> <td>88</td> <td>89</td>
	   // 	</tr>
	   // 	<tr>
	   // 		<td>100</td> <td>101</td> <td>102</td> <td>103</td> <td>104</td> <td>105</td> <td>106</td> <td>107</td> <td>108</td> <td>109</td>
	   // 	</tr>
	   // 	<tr>
	   // 		<td>f0</td> <td>f1</td> <td>f2</td> <td>...</td> <td></td> <td></td> <td></td> <td></td> <td></td> <td></td>
	   // 	</tr>
	   // </table>
	   @endcode
	 *
	 * Example: Row and column merge
	 * @code
	   std::vector<std::vector<std::string>> data
	   ({
	   	{"A-B", "",    "C|F|I"},
	   	{"D",   "E|H", ""},
	   	{"G",   "",    ""}
	   });
	   std::vector<std::string> header({"header"});
	   std::vector<std::string> footer({"footer"});
	   
	   hnc::tabular tabular(data, "Row and column merge", header, footer);
	   tabular.header().at(0).merge_row(3);
	   tabular.data().at(0).at(0).merge_row(2); // "A-B"
	   tabular.data().at(1).at(1).merge_col(2); // "E|H"
	   tabular.data().at(0).at(2).merge_col(3); // "C|F|I"
	   tabular.footer().at(0).merge_row(3);
	  
	   // Txt
	   std::cout << tabular << std::endl;
	   std::cout << std::endl;
	   // Row and column merge
	   // ------------------------
	   // | header               |
	   // ------------------------
	   // | A-B          | C|F|I |
	   // ---------------        -
	   // | D      | E|H |       |
	   // ---------              -
	   // | G      |     |       |
	   // ------------------------
	   // | footer               |
	   // ------------------------
	  
	   // LaTeX
	   std::cout << tabular.latex() << std::endl;
	   std::cout << std::endl;
	   // \begin{table}
	   // 		\caption{Row and column merge}
	   // 		\centering
	   // 		\begin{tabular}{ | c | c | c | }
	   // 				\hline
	   // 				\multicolumn{3}{|c|}{ header } \\
	   // 				\hline
	   // 				\multicolumn{2}{|c|}{ A-B } & \multirow{3}{*}{ C|F|I } \\
	   // 				\cline{1-1} \cline{2-2}
	   // 				D & \multirow{2}{*}{ E|H } &  \\
	   // 				\cline{1-1}
	   // 				G &  &  \\
	   // 				\hline
	   // 				\multicolumn{3}{|c|}{ footer } \\
	   // 				\hline
	   // 		\end{tabular}
	   // \end{table}
	  
	   // HTML
	   std::cout << tabular.html() << std::endl;
	   std::cout << std::endl;
	   // <table border="1">
	   // 		<caption>Row and column merge</caption>
	   // 		<tr>
	   // 				<th colspan="3">header</th>
	   // 		</tr>
	   // 		<tr>
	   // 				<td colspan="2">A-B</td> <td rowspan="3">C|F|I</td>
	   // 		</tr>
	   // 		<tr>
	   // 				<td>D</td> <td rowspan="2">E|H</td>
	   // 		</tr>
	   // 		<tr>
	   // 				<td>G</td>
	   // 		</tr>
	   // 		<tr>
	   // 				<td colspan="3">footer</td>
	   // 		</tr>
	   // </table>
	   @endcode
	 */
	class tabular
	{
	public:

		/**
		 * @brief Tag to merge cells in the row for hnc::tabular
		 *
		 * @code
		   #include <hnc/tabular.hpp>
		   @endcode
		 */
		class in_row_merge
		{
		public:

			/// Number of cells to merge
			std::size_t nb_merge;

			/// @brief Constructor
			/// @param[in] nb_merge Number of cells to merge (1 = no merge, 2 = merge with the next cell on the right)
			in_row_merge(std::size_t const nb_merge = 0) : nb_merge(nb_merge)
			{ }
		};

		/**
		 * @brief Tag to merge cells in the column for hnc::tabular
		 *
		 * @code
		   #include <hnc/tabular.hpp>
		   @endcode
		 */
		class in_col_merge
		{
		public:

			/// Number of cells to merge
			std::size_t nb_merge;

			/// @brief Constructor
			/// @param[in] nb_merge Number of cells to merge (1 = no merge, 2 = merge with the bottom cell)
			in_col_merge(std::size_t const nb_merge = 0) : nb_merge(nb_merge)
			{ }
		};
		
	private:

		/**
		 * @brief Class to save cell type
		 * 
		 * @code
		   #include <hnc/tabular.hpp>
		   @endcode
		 */
		class cell_t
		{
		public:

			/// Data
			std::string data;

			/// Merge cells in the row
			hnc::tabular::in_row_merge in_row_merge;

			/// Merge cells in the column
			hnc::tabular::in_col_merge in_col_merge;

			/// @brief Default constructor
			cell_t() = default;

			/// @brief Constructor
			/// @param[in] data Data for the cell
			template <class T>
			cell_t (T const & data) : data(hnc::to_string(data)) { }

			/// @brief Affectation operator with data
			/// @param[in] data Data for the cell
			/// @return The cell
			template <class T>
			cell_t & operator =(T const & data)
			{
				this->data = hnc::to_string(data);
				return *this;
			}

			/// @brief Merge in row
			/// @param[in] nb_cell_in_row_merge Number of cells to merge in the row
			/// @return the cell
			cell_t & merge_row(std::size_t const nb_cell_in_row_merge) { in_row_merge = nb_cell_in_row_merge; return *this; }

			/// @brief Merge in column
			/// @param[in] nb_cell_in_col_merge Number of cells to merge in the column
			/// @return the cell
			cell_t & merge_col(std::size_t const nb_cell_in_col_merge) { in_col_merge = nb_cell_in_col_merge; return *this; }
		};

	private:

		/// Number of rows
		std::size_t m_nb_row;

		/// Number of columns
		std::size_t m_nb_col;

		/// Title
		std::string m_title;

		/// Data
		std::vector<std::vector<cell_t>> m_data;

		/// Header
		std::vector<cell_t> m_header;

		/// Footer
		std::vector<cell_t> m_footer;

	public:

		/**
		 * @brief Constructor
		 *
		 * Give raw data, without control like cells merge or alignment
		 *
		 * @param[in] data   A 2D vector with data (a std::vector of std::vector of T for example)
		 * @param[in] title  Title (or caption) of the tabular [with a description]
		 * @param[in] header First row of the tabular
		 * @param[in] footer Last row of the tabular
		 */
		template <class vector2D_of_data_t, class header_t = std::string, class footer_t = std::string>
		tabular
		(
			vector2D_of_data_t const & data,
			std::string const title,
			std::vector<header_t> const & header = std::vector<header_t>(),
			std::vector<footer_t> const & footer = std::vector<footer_t>()
		) :
			m_nb_row(data.size()),
			m_nb_col((data.size() != 0) ? data.at(0).size() : 0),
			m_title(title),
			m_data(m_nb_row, std::vector<cell_t>(m_nb_col)),
			m_header((header.size() != 0) ? m_nb_col : 0),
			m_footer((footer.size() != 0) ? m_nb_col : 0)
		{
			// Data
			for (std::size_t i = 0; i < nb_row(); ++i)
			{
				for (std::size_t j = 0; j < nb_col(); ++j)
				{
					m_data[i][j] = data[i][j];
				}
			}
			// Header
			if (m_header.empty() == false)
			{
				for (std::size_t i = 0; i < std::min(m_header.size(), header.size()); ++i)
				{
					m_header[i] = hnc::to_string(header[i]);
				}
			}
			// Footer
			if (m_footer.empty() == false)
			{
				for (std::size_t i = 0; i < std::min(m_footer.size(), footer.size()); ++i)
				{
					m_footer[i] = hnc::to_string(footer[i]);
				}
			}
		}

		/// @brief Return the title
		/// @return the title
		std::string const & title() const { return m_title; }

		/// @brief Return the number of rows
		/// @return the number of rows
		std::size_t nb_row() const { return m_nb_row; }

		/// @brief Return the number of rows
		/// @return the number of rows
		std::size_t size() const { return nb_row(); }

		/// @brief Return the number of columns
		/// @return the number of columns
		std::size_t nb_col() const { return m_nb_col; }

		// Data, header and footer

		/// @brief Const data access
		/// @return the data
		std::vector<std::vector<cell_t>> const & data() const { return m_data; }

		/// @brief Data access
		/// @return the data
		std::vector<std::vector<cell_t>> & data() { return m_data; }

		/// @brief Const header access
		/// @return the header
		std::vector<cell_t> const & header() const { return m_header; }

		/// @brief Header access
		/// @return the header
		std::vector<cell_t> & header() { return m_header; }

		/// @brief Const footer access
		/// @return the footer
		std::vector<cell_t> const & footer() const { return m_footer; }

		/// @brief Header access
		/// @return the footer
		std::vector<cell_t> & footer() { return m_footer; }

		// Display

		/// @brief Get tabular in std::string (for the terminal)
		/// @return the tabular in string
		std::string to_string() const
		{
			std::string r;
			
			// Title
			r += m_title + "\n";

			// Get cell size (2 if empty " |", +3 otherwise " word |")
			auto get_cell_size = [](cell_t const & c) -> std::size_t
			{
				return ((c.data.size() == 0) ? (2) : (c.data.size() + 3));
			};

			// Get max size for one column
			auto get_max_size_for_one_column = [&](std::size_t const j) -> std::size_t
			{
				std::size_t max_size = 0;

				if (j >= nb_col()) { return max_size; }

				// Data
				for (std::vector<cell_t> const & data_row : m_data)
				{
					max_size = std::max(max_size, get_cell_size(data_row[j]));
				}
				// Header
				if (m_header.empty() == false) { max_size = std::max(max_size, get_cell_size(m_header[j])); }
				// Footer
				if (m_footer.empty() == false) { max_size = std::max(max_size, get_cell_size(m_footer[j])); }

				return max_size;
			};

			// Get max row size
			std::size_t const max_row_size = [&]() -> std::size_t
			{
				std::size_t max_row_size = 0;

				// For each column
				for (std::size_t column = 0; column < nb_col(); ++column)
				{
					max_row_size += get_max_size_for_one_column(column);
				}

				return max_row_size;
			}();

			// Add horizontal final line (without \n)
			auto add_full_line = [&]() -> void
			{
				// Full line
				r.insert(r.size(), max_row_size + 1, '-');
			};

			// Add horizontal line
			auto add_full_line_endl = [&]() -> void
			{
				add_full_line(); r += "\n";
			};

			// Add horizontal final line (without \n)
			auto add_line = [&](std::size_t const id_row) -> void
			{
				// Full line
				//r.insert(r.size(), max_row_size + 1, '-');

				// For each column
				for (std::size_t column = 0; column < nb_col(); ++column)
				{
					// Detect if merge
					bool merge = false;
					for (auto i = std::intmax_t(id_row); i >= 0; --i)
					{
						if (m_data[std::size_t(i)][column].in_col_merge.nb_merge > id_row - std::size_t(i)) { merge = true; break; }
					}

					// Choose the horizontal separator
					char const horizontal_separator = (merge) ? ' ' : '-';

					// Add a chunk of line
					r.insert(r.size(), get_max_size_for_one_column(column), horizontal_separator);
				}

				// Last
				r.insert(r.size(), 1, '-');
			};

			// Add horizontal line
			auto add_line_endl = [&](std::size_t const id_row) -> void
			{
				add_line(id_row); r += "\n";
			};

			// Add line with data
			auto add_line_data = [&](std::vector<cell_t> const & row, std::string const & color) -> void
			{
				r += "|";

				std::size_t nb_in_row_merge = 0;
				
				for (std::size_t i = 0; i < row.size(); ++i)
				{
					std::string word = row[i].data;

					std::size_t column_size = get_max_size_for_one_column(i);

					nb_in_row_merge = std::max(nb_in_row_merge, row[i].in_row_merge.nb_merge);

					std::string const vertical_separator = (nb_in_row_merge <= 1) ? std::string("|") : std::string(" ");
					
					if (word.size() != 0)
					{
						std::string fill(column_size - word.size() - 3, ' ');
						word = " " + color + word + hnc::terminal::reset + fill + " " + vertical_separator;
					}
					else
					{
						word = std::string(column_size - 1, ' ');
						word += vertical_separator;
					}
					r += word;

					if (nb_in_row_merge != 0) { --nb_in_row_merge; }
				}
				r += "\n";
			};

			// Header
			if (m_header.empty() == false)
			{
				add_full_line_endl();
				add_line_data(m_header, hnc::terminal::info);
			}
			add_full_line_endl();

			// Data
			for (std::size_t i = 0; i < m_data.size(); ++i)
			{
				std::vector<cell_t> const & data_row = m_data[i];
				
				if (data_row.empty() == false)
				{
					add_line_data(data_row, "");
					if (i != m_data.size() - 1) { add_line_endl(i); }
				}
			}

			// Footer
			if (m_footer.empty() == false)
			{
				add_full_line_endl();
				add_line_data(m_footer, hnc::terminal::info);
			}
			// Final line
			add_full_line();

			// Return
			return r;
		}

		/// @brief Get tabular in LaTeX format
		/// @param[in] tab Tabulation string
		/// @return the tabular in LaTeX format
		std::string latex(std::string const & tab = "\t") const
		{
			std::string r;

			// Add horizontal line
			auto add_full_line = [&r, &tab]() -> void
			{
				r += tab + tab + "\\hline" "\n";
			};

			// For cell merge
			std::vector<std::intmax_t> skip_hline(nb_col(), 0);
			std::intmax_t skip_col = 0;

			// Add horizontal line
			auto add_line = [&]() -> void
			{
				// Full line
				if (std::find_if(skip_hline.begin(), skip_hline.end(), [](long int const i) { return i > 0; }) == skip_hline.end())
				{
					add_full_line();
				}
				// cline
				else
				{
					r += tab + tab;
					// For each column
					for (std::size_t column = 0; column < nb_col(); ++column)
					{
						if (skip_hline[column] <= 0)
						{ r += "\\cline{" + hnc::to_string(column + 1) + "-" + hnc::to_string(column + 1) + "} "; }
					}
					r += "\n";
				}
			};

			// Add line with data
			auto add_line_data = [&](std::vector<cell_t> const & row) -> void
			{
				r += tab + tab;
				for (std::size_t i = 0; i < row.size(); ++i)
				{
					cell_t const & cell = row[i];
					
					// No previous in row merge
					if (skip_col <= 0)
					{
						// Next column
						if (&cell != &row.front()) { r += " & "; }

						// merge ?
						bool merge = false;

						// In row merge
						if (cell.in_row_merge.nb_merge > 1)
						{
							skip_col = std::intmax_t(cell.in_row_merge.nb_merge);
							r += "\\multicolumn{" + hnc::to_string(cell.in_row_merge.nb_merge) + "}{|c|}{ " + cell.data + " }";
							merge = true;
						}
						
						// In row merge
						if (cell.in_col_merge.nb_merge > 1)
						{
							skip_hline[i] = std::intmax_t(cell.in_col_merge.nb_merge);
							r += "\\multirow{" + hnc::to_string(cell.in_col_merge.nb_merge) + "}{*}{ " + cell.data + " }";
							merge = true;
						}
						
						// No merge
						if (merge == false)
						{
							r += cell.data;
						}
					}
					--skip_col;
					--skip_hline[i];
				}
				r += " \\\\\n";
				add_line();
			};

			// table
			r += "\\begin{table}" "\n";

			// Title
			r += tab + "\\caption{" + m_title + "}" "\n";

			// Centering
			r += tab + "\\centering" "\n";

			// tabular
			r += tab + "\\begin{tabular}" "{";
			for (std::size_t i = 0; i < nb_col(); ++i) { r += " | c"; }
			r += " | }" "\n";
			
			// Header
			if (m_header.empty() == false)
			{
				add_full_line();
				add_line_data(m_header);
			}

			// Data
			for (std::vector<cell_t> const data_row : m_data)
			{
				if (data_row.empty() == false)
				{
					add_line_data(data_row);
				}
			}

			// Footer
			if (m_footer.empty() == false)
			{
				add_line_data(m_footer);
			}

			// tabular
			r += tab + "\\end{tabular}" "\n";

			// table
			r += "\\end{table}";

			return r;
		}

		/// @brief Get tabular in HTLM format
		/// @param[in] tab Tabulation string
		/// @return the tabular in HTLM format
		std::string html(std::string const & tab = "\t") const
		{
			std::string r;

			// table
			r += "<table border=\"1\">" "\n";

			// Title
			r += tab + "<caption>" + m_title + "</caption>" "\n";

			// For cell merge
			std::vector<std::intmax_t> skip_tr(nb_col(), 0);
			std::intmax_t skip_th_or_td = 0;

			// Add line with data
			auto add_line_data = [&](std::vector<cell_t> const & row, std::string const th_or_td) -> void
			{
				r += tab + "<tr>\n";
				r += tab + tab;
				for (std::size_t i = 0; i < row.size(); ++i)
				{
					cell_t const & cell = row[i];
					
					// No previous in row merge
					if (skip_th_or_td <= 0)
					{
						// No previous in col merge
						if (skip_tr[i] <= 0)
						{
							// th or td
							r += "<" + th_or_td;
							// In column merge (rowspan)
							if (cell.in_col_merge.nb_merge > 1)
							{
								skip_tr[i] = std::intmax_t(cell.in_col_merge.nb_merge);
								r += " rowspan=\"" + hnc::to_string(cell.in_col_merge.nb_merge) + "\"";
							}
							// In row merge (colspan)
							if (cell.in_row_merge.nb_merge > 1)
							{
								skip_th_or_td = std::intmax_t(cell.in_row_merge.nb_merge);
								r += " colspan=\"" + hnc::to_string(cell.in_row_merge.nb_merge) + "\"";
							}
							r += ">";

							// Data
							r += cell.data;

							// end of th or td
							r += "</" + th_or_td + "> ";
						}
						--skip_tr[i];
					}
					--skip_th_or_td;
				}
				r += "\n" + tab + "</tr>" "\n";
			};

			// Header
			if (m_header.empty() == false)
			{
				add_line_data(m_header, "th");
			}

			// Data
			for (std::vector<cell_t> const data_row : m_data)
			{
				if (data_row.empty() == false)
				{
					add_line_data(data_row, "td");
				}
			}

			// Footer
			if (m_footer.empty() == false)
			{
				add_line_data(m_footer, "td");
			}
			
			// table
			r += "</table>";
			
			return r;
		}
	};
	
	/// @brief Operator << between a std::ostream and a hnc::tabular
	/// @param[in,out] o       Output stream
	/// @param[in]     tabular A hnc::tabular
	/// @return the output stream
	std::ostream & operator <<(std::ostream & o, hnc::tabular const & tabular)
	{
		o << tabular.to_string();
		return o;
	}
}

#endif
