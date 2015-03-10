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


#ifndef HNC_HTTP_W3C_VALIDATOR_HPP
#define HNC_HTTP_W3C_VALIDATOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "../url.hpp"
#include "../html/webpage.hpp"
#include "get.hpp"
#include "../test.hpp"
#include "../to_type.hpp"
#include "../to_string.hpp"


namespace hnc
{
	namespace http
	{
		/**
		 * @brief W3C validator
		 *
		 * @code
		   #include <hnc/http.hpp>
		   @endcode
		 *
		 * http://validator.w3.org/
		 * http://validator.w3.org/docs/api.html
		 *
		 * @warning Actually, hnc::http::get member function does not work with redirection. So, hnc::http::w3c_validator uses hnc::http::w3c_validator::server_local. On Debian GNU/Linux distribution you can install the package:
		 * @code
		   w3c-markup-validator
		   @endcode
		 *
		 * Default: the local server http://localhost/w3c-validator/ hnc::http::w3c_validator::server_local
		 *
		 * Alternative: the public server http://validator.w3.org/ hnc::http::w3c_validator::server_public
		 *
		 * @todo Only the local server works
		 * @todo Extract all informations
		 */
		class w3c_validator
		{
		public:

			/**
			 * @brief W3C validator error or warning
			 *
			 * @code
			   #include <hnc/http.hpp>
			   @endcode
			 */
			class error
			{
			private:

				/// Line
				unsigned int m_line;

				/// Column
				unsigned int m_column;

				/// Source
				std::string m_source;

				/// Explanation
				std::string m_explanation;

				/// Message (id and message)
				std::pair<int, std::string> m_message;

			public:

				/// @brief Constructor
				/// @param[in] line        Line of the error/warning
				/// @param[in] column      Column of the error/warning
				/// @param[in] source      Source (chunck of code) with the error/warning
				/// @param[in] explanation Explanation (description) of the error/warning
				/// @param[in] message     Id message and message of the error/warning
				error
				(
					unsigned int line = 0,
					unsigned int column = 0,
					std::string const & source = "",
					std::string const & explanation = "",
					std::pair<int, std::string> const & message = { 0, std::string("") }
				) :
					m_line(line),
					m_column(column),
					m_source(source),
					m_explanation(explanation),
					m_message(message)
				{ }

				/// @brief Get the error in a std::string
				/// @param[in] indent Identation string (empty by default)
				/// @return the error in a std::string
				std::string to_string(std::string const & indent = "") const
				{
					// Return
					std::string r;

					// Line and column
					r += indent + "line = " + hnc::to_string(m_line) + ", column = " + hnc::to_string(m_column) + "\n";

					// Source
					r += indent + "source:" "\n";
					{
						std::istringstream iss(m_source);
						std::string line;
						while (std::getline(iss, line)) { r += indent + indent + line + "\n"; }
					}

					// Explanation
					r += indent + "explanation:" "\n";
					{
						std::istringstream iss(m_explanation);
						std::string line;
						while (std::getline(iss, line)) { r += indent + indent + line + "\n"; }
					}

					// Message
					r += indent + "message: " + hnc::to_string(m_message.first) + ": " + m_message.second + "\n";

					// Return
					return r;
				}
			};
			
			/**
			 * @brief W3C validator server
			 *
			 * @code
			   #include <hnc/http.hpp>
			   @endcode
			 *
			 * Base class for w3c_validator server :
			 * - hnc::http::w3c_validator::server_local (by default)
			 * - hnc::http::w3c_validator::server_public
			 */
			class server
			{
			private:

				/// URL
				hnc::url m_url;

			public:

				/// @brief Constructor
				server() :
					server("127.0.0.1", "/w3c-validator/check")
				{ }

				/// Destructor
				virtual ~server() { }


				/// @brief Get the url of the server
				/// @return the url of the server
				hnc::url const & url() const { return m_url; }

			protected:

				/// @brief Constructor
				/// @param[in] server_host    Server host
				/// @param[in] server_webpage Server webpage
				server
				(
					std::string const & server_host,
					std::string const & server_webpage
				) :
					m_url(server_host, server_webpage, "http", 80)
				{ }
			};
			
			/**
			 * @brief W3C validator public server http://validator.w3.org/
			 *
			 * @code
			   #include <hnc/http.hpp>
			   @endcode
			 *
			 * Server host :
			 * - validator.w3.org
			 *
			 * Server webpage
			 * - /check
			 *
			 * @b Note @b from http://validator.w3.org/docs/api.html @n
			 * If you wish to call the validator programmatically for a batch of documents, please make sure that your script will sleep for @b at @b least @b 1 @b second between requests. The Markup Validation service is a free, public service for all, your respect is appreciated. thanks.
			 */
			class server_public : public hnc::http::w3c_validator::server
			{
			public:

				/// Constructor
				server_public() :
					hnc::http::w3c_validator::server("validator.w3.org", "/check")
				{ }
			};

			/**
			 * @brief W3C validator local server http://localhost/w3c-validator/
			 *
			 * @code
			   #include <hnc/http.hpp>
			   @endcode
			 *
			 * Server host :
			 * - 127.0.0.1
			 *
			 * Server webpage
			 * - /w3c-validator/check
			 *
			 * On Debian GNU/Linux distribution you can install the package:
			 * @code
			   w3c-markup-validator
			   @endcode
			 */
			class server_local : public hnc::http::w3c_validator::server
			{
			public:

				/// @brief Constructor
				server_local() :
					hnc::http::w3c_validator::server("127.0.0.1", "/w3c-validator/check")
				{ }
			};
			
		private:

			/// Server
			hnc::http::w3c_validator::server m_validator_server;

			/// Doctype
			std::string m_doctype;

			/// Charset
			std::string m_charset;

			/// Errors
			std::vector<hnc::http::w3c_validator::error> m_errors;

			/// Warnings
			std::vector<hnc::http::w3c_validator::error> m_warnings;

			/// Raw result (std::vector of lines)
			std::vector<std::string> m_raw_result;

		public:

			/// @brief Constructor from std::string
			/// @param[in] html             HTML to validate
			/// @param[in] validator_server Validator server (hnc::http::w3c_validator::server_local by default)
			w3c_validator
			(
				std::string const & html,
				hnc::http::w3c_validator::server const & validator_server = hnc::http::w3c_validator::server_local()
			) :
				m_validator_server(validator_server)
			{
				// HTTP GET request
				hnc::http::get http_get_request(validator_server.url(), "fragment", html, "output", "soap12", "hnc_http_w3c_validator");

				// Get result
				try
				{
					// Result
					m_raw_result = http_get_request.request();

					std::string const prefix_nb_error = "X-W3C-Validator-Errors: ";
					std::string const prefix_nb_warning = "X-W3C-Validator-Warnings: ";

					// Get errors and warning
					for (std::string const & line : m_raw_result)
					{
						//std::cout << line << std::endl;
						
						// Save error or warning
						// TODO
						auto save_error_or_warning = [&]
						(
							std::string const & prefix,
							std::vector<hnc::http::w3c_validator::error> & errors_or_warnings
						) -> void
						{
							std::size_t const nb = hnc::to_<std::size_t>(line.substr(prefix.size(), line.size() - prefix.size()));
							errors_or_warnings.resize(nb, hnc::http::w3c_validator::error(0, 0, "Source extraction is not implemented yet", "Explanation extraction is not implemented yet", std::make_pair(0, "Message extraction is not implemented yet")));
						};
						
						// Errors
						if (line.find(prefix_nb_error) == 0)
						{
							save_error_or_warning(prefix_nb_error, m_errors);
						}
						// Warnings
						else if (line.find(prefix_nb_warning) == 0)
						{
							save_error_or_warning(prefix_nb_warning, m_warnings);
						}
					}
				}
				// Error
				catch (std::string const & e)
				{
					hnc::test::warning(false, "hnc::http::w3c_validator: Can not connect: " + e + "\n");
				}
			}
			
			/// @brief Constructor from std::string
			/// @param[in] html             HTML to validate
			/// @param[in] validator_server Validator server (hnc::http::w3c_validator::server_local by default)
			w3c_validator
			(
				hnc::html::webpage const & html,
				hnc::http::w3c_validator::server const & validator_server = hnc::http::w3c_validator::server_local()
			) :
				w3c_validator(html.html(), validator_server)
			{ }

			/// @brief Return true if the html is valid, false otherwise
			/// @return true if the html is valid, false otherwise
			bool validity() const { return m_errors.empty(); }

			/// @brief Return the validator server
			/// @return the validator server
			hnc::http::w3c_validator::server const & validator_server() const { return m_validator_server; }

			/// @brief Return the doctype
			/// @return the doctype
			std::string const & doctype() const { return m_doctype; }

			/// @brief Return the charset
			/// @return the charset
			std::string const & charset() const { return m_charset; }

			/// @brief Return the errors
			/// @return the errors
			std::vector<hnc::http::w3c_validator::error> const & errors() const { return m_errors; }

			/// @brief Return the warnings
			/// @return the warnings
			std::vector<hnc::http::w3c_validator::error> const & warnings() const { return m_warnings; }

			/// @brief Return the raw result (std::vector of lines)
			/// @return the raw result (std::vector of linse)
			std::vector<std::string> const & raw_result() const { return m_raw_result; }
		};
			
		/// @brief Operator << between a std::ostream and a hnc::http::w3c_validator::error
		/// @param[in,out] o     Output stream
		/// @param[in]     error A hnc::http::w3c_validator::error
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::http::w3c_validator::error const & error)
		{
			o << error.to_string();
			return o;
		}
		
		/// @brief Operator << between a std::ostream and a hnc::http::w3c_validator::server
		/// @param[in,out] o                    Output stream
		/// @param[in]     w3c_validator_server A hnc::http::w3c_validator::server
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::http::w3c_validator::server const & w3c_validator_server)
		{
			o << w3c_validator_server.url();
			return o;
		}
		
		/// @brief Operator << between a std::ostream and a hnc::http::w3c_validator
		/// @param[in,out] o             Output stream
		/// @param[in]     w3c_validator A hnc::http::w3c_validator
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::http::w3c_validator const & w3c_validator)
		{
			// TODO
			o << "W3C validator (" << w3c_validator.validator_server() << "):" << "\n";
			o << "- validity = " << std::boolalpha << w3c_validator.validity() << "\n";
			o << "- errors   = " << w3c_validator.errors().size() << "\n";
			for (hnc::http::w3c_validator::error const & error : w3c_validator.errors())
			{
				o << error.to_string("  ");
			}
			o << "- warnings = " << w3c_validator.warnings().size() << "\n";
			for (hnc::http::w3c_validator::error const & error : w3c_validator.warnings())
			{
				o << error.to_string("  ");
			}
			o << "- doctype  = " << w3c_validator.doctype() << "\n";
			o << "- charset  = " << w3c_validator.charset() << "\n";
			return o;
		}
	}
}

#endif
