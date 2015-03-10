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


#ifndef HNC_HTML_WEBPAGE_HPP
#define HNC_HTML_WEBPAGE_HPP

#include <iostream>

#include "doctype.hpp"
#include "head.hpp"
#include "../lang.hpp"
#include "../to_string.hpp"


namespace hnc
{
	namespace html
	{
		/**
		 * @brief HTML Web page
		 *
		 * @code
		   #include <hnc/html.hpp>
		   @endcode
		 */
		class webpage
		{
		private:

			/// Doctype
			hnc::html::doctype::html m_doctype;

			/// Head
			hnc::html::head m_head;

			/// Language
			hnc::lang::lang_code m_lang_code;

			/// HTML code
			std::vector<std::string> m_codes;

			/// Data (html code) (inside the body)
			std::string m_data;

		public:

			/// @brief Constructor
			/// @param[in] html_doctype HTML doctype
			/// @param[in] html_head    HTML head
			/// @param[in] lang_code    Language
			webpage
			(
				hnc::html::head const & html_head,
				hnc::html::doctype::html const & html_doctype = hnc::html::doctype::html(),
				hnc::lang::lang_code const & lang_code = hnc::lang::lang_code()
			) :
				m_doctype(html_doctype),
				m_head(html_head),
				m_lang_code(lang_code),
				m_data("<p>No data in your HTML Webpage. Please use hnc::html::webpage::set_data(std::string const &amp; data) to add HTML code in your webpage</p>")
			{
				// Set the HTML version
				// TODO trait on HTML doctype
				if (m_doctype.doctype().find("HTML 4") != std::string::npos)
				{
					m_head.use_html4();
				}
				else if (m_doctype.doctype().find("XHTML") != std::string::npos)
				{
					m_head.use_xhtml();
				}
				else
				{
					m_head.use_html5();
				}
			}

			/// @brief Set the data (html code) (inside the body)
			/// @param[in] data Data (html code in a std::string) to put inside the body
			void set_data(std::string const & data) { m_data = data; }

			/// @brief Get the HTML code
			/// @return the HTML code
			std::string html() const
			{
				// Return
				std::string page;

				// Doctype
				page += m_doctype.doctype() + "\n" "\n";

				// <html>
				if (m_head.html_version() == hnc::html::head::html_version_t::html5)
				{
					page += (m_lang_code.no_lang()) ? (std::string("<html>\n")) : (std::string("<html lang=\"" + m_lang_code.html() + "\">"));
				}
				else if (m_head.html_version() == hnc::html::head::html_version_t::xhtml)
				{
					page += "<html xmlns=\"http://www.w3.org/1999/xhtml\"";
					if (m_lang_code.no_lang() == false)
					{
						page += "xml:lang=\"" + m_lang_code.html() + "\" lang=\"" + m_lang_code.html() + "\"";
					}
					page += ">";
				}
				else
				{
					page += "<html>";
				}
				page += "\n" "\n";

				// <head>
				page += m_head.html() + "\n" "\n";
				
				// <body>
				page += "<body>" "\n" "\n";

				// Data
				page += m_data + "\n" "\n";

				// </body>
				page += "</body>" "\n" "\n";

				// </html>
				page += "</html>";

				// Return
				return page;
			}
		};

		/// @brief Operator << between a std::ostream and a hnc::html::webpage
		/// @param[in,out] o            Output stream
		/// @param[in]     html_webpage A hnc::html::webpage
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::html::webpage const & html_webpage)
		{
			o << html_webpage.html();
			return o;
		}
	}
}

#endif
