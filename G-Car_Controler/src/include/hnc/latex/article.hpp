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


#ifndef HNC_LATEX_ARTICLE_HPP
#define HNC_LATEX_ARTICLE_HPP

#include <string>
#include <vector>


namespace hnc
{
	namespace latex
	{
		/**
		 * @brief LaTeX article code generation
		 * 
		 * @code
		   #include <hnc/latex.hpp>
		   @endcode
		 */
		class article
		{
		private:

			/// Language
			std::string m_lang;

			/// Title
			std::string m_title;

			/// Author
			std::string m_author;

			/// Date
			std::string m_date;

			/// Packages
			std::vector<std::string> m_packages;

			/// Data (LaTeX code) (inside the document)
			std::string m_data = "\\section{Default data}" "\n"
			                     "\n"
			                     "\t" "No data in your LaTeX document. Please use hnc::latex::article::set\\_data(std::string const \\& data) to add LaTeX in your document";

		public:

			/// @brief Constructor
			/// @param[in] title  Title
			/// @param[in] author Author
			/// @param[in] date   Date
			article
			(
				std::string const & title,
				std::string const & author,
				std::string const & date = ""
			) :
				m_lang(""),
				m_title(title),
				m_author(author),
				m_date(date)
			{ }

			/// @brief Use package
			/// @param[in] package_name Name of the package
			/// @return the article
			article & use_package(std::string const & package_name) { m_packages.push_back(package_name); return *this; }

			/// @brief Use packages
			/// @param[in] package_name      Name of the package
			/// @param[in] package_name_list Other packages
			/// @return the article
			template <class ... string>
			article & use_package(std::string const & package_name, string ... package_name_list)
			{
				use_package(package_name);
				use_package(package_name_list...);
				return *this;
			}

			/// @brief Language = english (by default)
			/// @return the article
			article & english() { m_lang = ""; return *this; }

			/// @brief Language = french
			/// @return the article
			article & french() { m_lang = "\\usepackage[francais]{babel}" "\n"; return *this; }

			/// @brief Set the data (LaTeX code) (inside the document)
			/// @param[in] data Data (LaTeX code in a std::string) to put inside the document
			void set_data(std::string const & data) { m_data = data; }

			/// @brief Get LaTeX code
			/// @return the LaTeX code
			std::string latex() const
			{
				// Return
				std::string r;

				// Document class
				r += "\\documentclass[a4paper]{article}" "\n" "\n";

				// utf-8, font and lang
				r += "\\usepackage[utf8]{inputenc}" "\n";
				r += "\\usepackage[T1]{fontenc}" "\n";
				r += m_lang;
				r += "\n";

				// Hyperref and geometry
				//r += "\\usepackage[bookmarks=true,colorlinks,linkcolor=blue]{hyperref}" "\n";
				//r += "\\usepackage[top=2cm,bottom=2cm,left=2.5cm,right=2.5cm]{geometry}" "\n" "\n";

				// User packages
				for (std::string const & package_name : m_packages)
				{
					r += "\\usepackage{" + package_name + "}" "\n";
				}
				if (m_packages.empty() == false) { r += "\n"; }

				// Document
				r += "\\begin{document}" "\n" "\n";

				// Data
				r += m_data + "\n" "\n";

				// End document
				r += "\\end{document}";

				// Return
				return r;
			}
		};
		
		/// @brief Operator << between a std::ostream and a hnc::latex::article
		/// @param[in,out] o             Output stream
		/// @param[in]     latex_article A hnc::latex::article
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::latex::article const & latex_article)
		{
			o << latex_article.latex();
			return o;
		}
	}
}

#endif
