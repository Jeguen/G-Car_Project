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


#ifndef HNC_HTTP_GET_HPP
#define HNC_HTTP_GET_HPP

#include <string>
#include <vector>
#include <algorithm>

#ifndef hnc_no_boost_asio
#include <boost/asio.hpp>
#endif

#include "../url.hpp"
#include "../to_string.hpp"
#include "url_encode.hpp"
#include "../test.hpp"
#include "../filesystem.hpp"


namespace hnc
{
	namespace http
	{
		/**
		 * @brief Build a HTTP GET request
		 *
		 * @code
		   #include <hnc/http.hpp>
		   @endcode
		 *
		 * Exemple:
		 * @code
		   // Basic
		   {
		   	hnc::url url("www.boost.org", "/", "http");
		   	hnc::http::get http_get_request(url);
		   	std::vector<std::string> result = http_get_request.request();
		   }
		   // Basic with user agent
		   {
		   	hnc::url url("www.boost.org", "/", "http");
		   	hnc::http::get http_get_request(url, "user_agent");
		   	std::vector<std::string> result = http_get_request.request();
		   }
		   // With parameters (?fragment=xhtml_code&output=soap12&verbose=1) and user agent (user_agent)
		   {
		   	hnc::url url("localhost", "/w3c-validator/check", "http");
		   	hnc::http::get http_get_request(url, "fragment", "xhtml_code", "output", "soap12", "verbose", 1, "user_agent");
		   	std::vector<std::string> result = http_get_request.request();
		   }
		   @endcode
		 */
		class get
		{
		private:

			/// Server host and path
			hnc::url m_host_and_path;

			/// Parameter
			std::string m_parameters;

			/// User agent
			std::string m_user_agent;

		public:

			/// @brief Constructor
			/// @param[in] host_and_path A hnc::url witch contains server name and path
			/// @param[in] user_agent    User agent http://en.wikipedia.org/wiki/User_agent http://en.wikipedia.org/wiki/User_agent#Format (empty by default)
			get
			(
				hnc::url const & host_and_path,
				std::string const & user_agent = ""
			) :
				m_host_and_path(host_and_path),
				m_parameters(""),
				m_user_agent(user_agent)
			{ }

			/// @brief Do the HTTP request
			/// @todo 302 Found redirection does not work(?)
			std::vector<std::string> request() const
			{
				// Return
				std::vector<std::string> r;

				// Boost.Asio for TCP/IP communication
				#ifndef hnc_no_boost_asio
				
					// Connexion
					boost::asio::ip::tcp::iostream http_stream(host(), "http");

					// Connexion is ok
					if (http_stream)
					{
						// Get
						http_stream << this->to_string();
						http_stream.flush();

						// Get the response
						{
							std::string line;
							while (std::getline(http_stream, line))
							{
								r.push_back(line);
							}
						}
					}
					// Error in connexion
					else
					{
						throw http_stream.error().message();
					}

					// It is an redirection // FIXME ?
					if (r.empty() == false && r[0].find("302 Found") != std::string::npos)
					{
						// Search the "Location:" line
						std::string const prefix = "Location: ";
						// Search
						for (std::string const & line : r)
						{
							if (line.find(prefix) == 0)
							{
								// Get location
								std::string location = line.substr(prefix.size(), line.size() - prefix.size() - 1);
// 								std::remove(location.begin(), location.end(), '\n');
// 								std::remove(location.begin(), location.end(), '\r');
								
								// Use filesystem to get host and path
								std::string const path = hnc::filesystem::filename(location);
								std::string const host = hnc::filesystem::filename(hnc::filesystem::dirname(location));
								
								// Create the new HTTP GET
								hnc::http::get http_get_request(hnc::url(host, "/" + path, "http"), m_user_agent);
								r = http_get_request.request();

								break;
							}
						}
					}
				
				// No Boost.Asio
				#else
				
					hnc::test::warning(false, "Boost.Asio is not supported, please install Boost.Asio (and Boost.System) and recompile this program without hnc_no_boost_asio define\n");
					
				#endif

				// Return
				return r;
			}

			/// @brief Constructor
			/// @param[in] host_and_path                           A hnc::url witch contains server name and path
			/// @param[in] key_and_value_parameters_and_user_agent Parameters (?key0=value0&key1=value1&key2=value2), User agent http://en.wikipedia.org/wiki/User_agent http://en.wikipedia.org/wiki/User_agent#Format (empty by default) http://en.wikipedia.org/wiki/User_agent#Format (empty by default)
			template <class ... key_and_value_parameters_and_user_agent_t>
			get
			(
				hnc::url const & host_and_path,
				key_and_value_parameters_and_user_agent_t ... key_and_value_parameters_and_user_agent
			) :
				m_host_and_path(host_and_path)
			{
				set_parameters(key_and_value_parameters_and_user_agent...);
			}

			/// @brief Get the host
			/// @return the host
			std::string const & host() const { return m_host_and_path.server_name(); }

			/// @brief Get the path
			/// @return the path
			std::string const & path() const { return m_host_and_path.path(); }

			/// @brief Get the HTTP GET request in a std::string
			/// @return the HTTP GET request in a std::string
			std::string const to_string() const
			{
				// Return
				std::string r;

				// End line
				std::string const endl = "\r\n";

				// GET
				r += "GET " + ((path() == "") ? std::string("/") : path()) + m_parameters + " " "HTTP/1.0" + endl;

				// Host
				r += "Host: " + host() + endl;

				// Accept
				r += "Accept: */*" + endl;

				// User agent
				if (m_user_agent != "")
				{
					r += "User-Agent:" + m_user_agent + endl;
				}

				// Connexion
				r += "Connection: close" + endl + endl;
				
				// Return
				return r;
			}

		private:

			/// @brief Create GET parameters (?key0=value0&key1=value1&key2=value2)
			/// @param[in] key                                     Key of the first parameter
			/// @param[in] value                                   Value of the first parameter
			/// @param[in] key_and_value_parameters_and_user_agent Other parameters and user agent
			template <class value_t, class ... key_and_value_parameters_and_user_agent_t>
			void set_parameters
			(
				std::string const & key,
				value_t const & value,
				key_and_value_parameters_and_user_agent_t ... key_and_value_parameters_and_user_agent)
			{
				// ? or &
				if (m_parameters.empty()) { m_parameters += "?"; }
				else { m_parameters += "&"; }

				// Key and value
				m_parameters += hnc::http::url_encode(key) + "=" + hnc::to_string(hnc::http::url_encode(hnc::to_string(value)));

				// Next
				set_parameters(key_and_value_parameters_and_user_agent...);
			}
			
			/// @brief Final function to hnc::http::get::set_parameters(std::string const &,value_t const &,key_and_value_parameters_t...)
			/// @param[in] user_agent User agent http://en.wikipedia.org/wiki/User_agent http://en.wikipedia.org/wiki/User_agent#Format (empty by default)
			void set_parameters(std::string const & user_agent = "") { m_user_agent = user_agent; }
		};
		
		/// @brief Operator << between a std::ostream and a hnc::http::get
		/// @param[in,out] o                Output stream
		/// @param[in]     http_get_request A hnc::http::get
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::http::get const & http_get_request)
		{
			o << http_get_request.to_string();
			return o;
		}
	}
}

#endif
