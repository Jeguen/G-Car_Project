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


#ifndef HNC_HTML_DOCTYPE_HPP
#define HNC_HTML_DOCTYPE_HPP

#include <string>
#include <iostream>


namespace hnc
{
	namespace html
	{
		/**
		 * @brief HTML doctypes
		 *
		 * @code
		   #include <hnc/html.hpp>
		   @endcode
		 *
		 * http://www.w3schools.com/tags/tag_doctype.asp
		 */
		namespace doctype
		{
			/**
			 * @brief HTML doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			class html
			{
			protected:

				/// Doctype
				std::string m_doctype;

			public:

				/// @brief Constructor
				html() :
					m_doctype(R"(<!DOCTYPE html>)")
				{ }

				/// Destructor
				virtual ~html() { }

				/// @brief Return the doctype (HTML code)
				/// @return the doctype (HTML code)
				std::string const & doctype() const { return m_doctype; }

			protected:

				/// @brief Constructor
				/// @param[in] doctype Doctype as string
				html(std::string const & doctype) :
					m_doctype(doctype)
				{ }
			};
			
			/// @brief Operator << between a std::ostream and a hnc::html::doctype::html
			/// @param[in,out] o            Output stream
			/// @param[in]     html_doctype A hnc::html::doctype::html
			/// @return the output stream
			inline std::ostream & operator <<(std::ostream & o, hnc::html::doctype::html const & html_doctype)
			{
				o << html_doctype.doctype();
				return o;
			}
			
			/**
			 * @brief HTML 5 doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			using html_5 = hnc::html::doctype::html;

			/**
			 * @brief XHTML 1.0 Strict doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			class xhtml_1d0_strict : public hnc::html::doctype::html
			{
			public:

				/// Constructor
				xhtml_1d0_strict() :
					hnc::html::doctype::html(R"(<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">)")
				{ }
			};

			/**
			 * @brief XHTML 1.0 Transitional doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			class xhtml_1d0_transitional : public hnc::html::doctype::html
			{
			public:

				/// Constructor
				xhtml_1d0_transitional() :
					hnc::html::doctype::html(R"(<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">)")
				{ }
			};

			/**
			 * @brief XHTML 1.0 Frameset doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			class xhtml_1d0_frameset : public hnc::html::doctype::html
			{
			public:

				/// Constructor
				xhtml_1d0_frameset() :
					hnc::html::doctype::html(R"(<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Frameset//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd">)")
				{ }
			};

			/**
			 * @brief XHTML 1.1 doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			class xhtml_1d1 : public hnc::html::doctype::html
			{
			public:

				/// Constructor
				xhtml_1d1() :
					hnc::html::doctype::html(R"(<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">)")
				{ }
			};

			/**
			 * @brief HTML 4.01 Strict doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			class html_4d01_strict : public hnc::html::doctype::html
			{
			public:

				/// Constructor
				html_4d01_strict() :
					hnc::html::doctype::html(R"(<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">)")
				{ }
			};

			/**
			 * @brief HTML 4.01 Transitional doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			class html_4d01_transitional : public hnc::html::doctype::html
			{
			public:

				/// Constructor
				html_4d01_transitional() :
					hnc::html::doctype::html(R"(<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">)")
				{ }
			};

			/**
			 * @brief HTML 4.01 Frameset doctype
			 *
			 * @code
			   #include <hnc/html.hpp>
			   @endcode
			 */
			class html_4d01_frameset : public hnc::html::doctype::html
			{
			public:

				/// Constructor
				html_4d01_frameset() :
					hnc::html::doctype::html(R"(<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN" "http://www.w3.org/TR/html4/frameset.dtd">)")
				{ }
			};
		}
	}
}

#endif
