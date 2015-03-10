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


#ifndef HNC_HTML_HEAD_HPP
#define HNC_HTML_HEAD_HPP

#include <iostream>
#include <string>
#include <vector>

#include "../character_encoding.hpp"
#include "../to_string.hpp"


namespace hnc
{
	namespace html
	{
		/**
		 * @brief HTML head markup
		 *
		 * @code
		   #include <hnc/html.hpp>
		   @endcode
		 *
		 * http://www.w3schools.com/html/html_head.asp
		 */
		class head
		{
		public:

			/// Head HTML version enum
			enum class html_version_t { html5, xhtml, html4 };
			
		private:

			/// Title
			std::string m_title;

			/// HTML version
			hnc::html::head::html_version_t m_html_version;

			/// Character encoding (charset)
			hnc::character_encoding::encoding m_charset;

			/// Keywords
			std::vector<std::string> m_keywords;

			/// Description
			std::string m_description;

			/// Author
			std::string m_author;

		public:

			/// @brief Constructor
			/// @param[in] title        Title
			/// @param[in] html_version A hnc::html::head::html_version_t
			/// @param[in] charset      Character encoding (charset) (default value hnc::character_encoding::utf8)
			head
			(
				std::string const & title,
				hnc::html::head::html_version_t const html_version = hnc::html::head::html_version_t::html5,
				hnc::character_encoding::encoding const & charset = hnc::character_encoding::utf8()
			) :
				m_title(title),
				m_html_version(html_version),
				m_charset(charset)
			{ }

			/// @brief Set the tile
			/// @param[in] title Title
			/// @return The HTML head
			head & set_tile(std::string const & title) { m_title = title; return *this; }

			/// @brief Set the Character encoding (charset)
			/// @param[in] charset Character encoding (charset)
			/// @return The HTML head
			head & set_charset(hnc::character_encoding::encoding const & charset) { m_charset = charset; return *this; }

			/// @brief Return the HTML version (a hnc::html::head::html_version_t)
			/// @return the HTML version (a hnc::html::head::html_version_t)
			hnc::html::head::html_version_t html_version() const { return m_html_version; }

			/**
			 * @brief Use HTML 5 version (by default)
			 *
			 * @code
			    <meta charset="utf-8">
			   @endcode
			 *
			 * @return The HTML head
			 */
			head & use_html5() { m_html_version = hnc::html::head::html_version_t::html5; return *this; }

			/**
			 * @brief Use xHTML version
			 *
			 * @code
			   <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
			   @endcode
			 * 
			 * @return The HTML head 
			 */
			head & use_xhtml() { m_html_version = hnc::html::head::html_version_t::xhtml; return *this; }

			/**
			 * @brief Use HTML 4 version
			 *
			 * @code
			   <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
			   @endcode
			 *
			 * @return The HTML head
			 */
			head & use_html4() { m_html_version = hnc::html::head::html_version_t::html4; return *this; }

			/// @brief Set the keywords
			/// @param[in] keywords Keywords (a std::vector of std::string)
			/// @return The HTML head
			head & set_keywords(std::vector<std::string> const & keywords) { m_keywords = keywords; return *this; }

			/// @brief Add a keyword
			/// @param[in] keyword Keyword to add
			/// @return The HTML head
			head & add_keyword(std::string const & keyword) { m_keywords.push_back(keyword); return *this; }

			/// @brief Set the description
			/// @param[in] description Description
			/// @return The HTML head
			head & set_description(std::string const & description) { m_description = description; return *this; }

			/// @brief Set the author
			/// @param[in] author Author
			/// @return The HTML head
			head & set_author(std::string const & author) { m_author = author; return *this; }

			/// @brief Return the head HTML code
			/// @param[in] tab Tabulation ("\t" by default)
			/// @return the head HTML code
			std::string html(std::string const & tab = "\t") const
			{
				std::string head;

				head += "<head>" "\n";

				// Title
				head += tab + "<title>" + m_title + "</title>\n";

				// End meta markup
				std::string const end_meta_markup = (m_html_version == hnc::html::head::html_version_t::xhtml) ? std::string(" />") : std::string(">");

				// Charset
				if (m_html_version == hnc::html::head::html_version_t::xhtml or m_html_version == hnc::html::head::html_version_t::html4)
				{
					head += tab + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=" + m_charset.code() + "\""+ end_meta_markup +"\n";
				}
				else
				{
					head += tab + "<meta charset=\"" + m_charset.code() + "\""+ end_meta_markup +"\n";
				}

				// Keywords
				if (m_keywords.empty() == false)
				{
					head += tab + "<meta name=\"keywords\" content=\"";
					head += m_keywords.front();
					for (auto keyword_it = m_keywords.begin() + 1; keyword_it != m_keywords.end(); ++keyword_it)
					{
						head += ", " + *keyword_it;
					}
					head += "\""+ end_meta_markup +"\n";
				}

				// Description
				if (m_description.empty() == false)
				{
					head += tab + "<meta name=\"description\" content=\"" + m_description + "\""+ end_meta_markup +"\n";
				}

				// Author
				if (m_author.empty() == false)
				{
					head += tab + "<meta name=\"author\" content=\"" + m_author + "\""+ end_meta_markup +"\n";
				}

				head += "</head>";
				
				return head;
			}
		};
		
		/// @brief Operator << between a std::ostream and a hnc::html::head
		/// @param[in,out] o         Output stream
		/// @param[in]     html_head A hnc::html::head
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::html::head const & html_head)
		{
			o << html_head.html();
			return o;
		}
	}
}

#endif
