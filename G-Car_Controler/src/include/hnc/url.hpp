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


#ifndef HNC_URL_HPP
#define HNC_URL_HPP

#include <iostream>

#include "to_string.hpp"


namespace hnc
{
	/**
	 * @brief URL (Uniform Resource Locator)
	 *
	 * @code
	   #include <hnc/url.hpp>
	   @endcode
	 *
	 * http://en.wikipedia.org/wiki/Uniform_resource_locator
	 * http://www.commentcamarche.net/contents/542-url
	 *
	 * @code
	   hnc::url("serveur_name", "/path", "http", 80)                // http://serveur_name:80/path
	   hnc::url("serveur_name", "/path", "git", 0, "login")         // git://login@serveur_name/path
	   hnc::url("serveur_name", "/path", "ftp", 21, "login", "pwd") // ftp://login:pwd@serveur_name:21/path
	   @endcode
	 */
	class url
	{
	private:

		/// Protocol name
		std::string m_protocol_name;

		/// User
		std::string m_user;

		/// Password
		std::string m_password;

		/// Server name
		std::string m_server_name;

		/// Port
		unsigned int m_port;

		/// Path
		std::string m_path;

	public:

		/// @brief Constructor
		/// @param[in] server_name   Name of server (empty by default)
		/// @param[in] path          Path of server (empty by default)
		/// @param[in] protocol_name Name of protocol (empty by default)
		/// @param[in] port          Port (0 by default)
		/// @param[in] user          User (login) (empty by default)
		/// @param[in] password      Password (empty by default)
		url
		(
			std::string const & server_name = "",
			std::string const & path = "",
			std::string const & protocol_name = "",
			unsigned int const port = 0,
			std::string const & user = "",
			std::string const & password = ""
		) :
			m_protocol_name(protocol_name),
			m_user(user),
			m_password(password),
			m_server_name(server_name),
			m_port(port),
			m_path(path)
		{ }

		/// @brief Get the protocol name
		/// @return the protocol name
		std::string const & protocol_name() const { return m_protocol_name; }

		/// @brief Get the user
		/// @return the user
		std::string const & user() const { return m_user; }

		/// @brief Get the password
		/// @return the password
		std::string const & password() const { return m_password; }

		/// @brief Get the port
		/// @return the port
		unsigned int port() const { return m_port; }

		/// @brief Get the server name
		/// @return the server name
		std::string const & server_name() const { return m_server_name; }

		/// @brief Get the path
		/// @return the path
		std::string const & path() const { return m_path; }

		/// @brief Get the URL in a std::string
		/// @return the URL in a std::string
		std::string to_string() const
		{
			// Return
			std::string r;

			// Protocol name
			if (protocol_name() != "")
			{
				r += protocol_name() + "://";
			}

			// User and password
			if (user() != "")
			{
				r += user();
				if (password() != "") { r += ":" + password(); }
				r += "@";
			}

			// Server name
			r += server_name();

			// Port
			if (port() != 0) { r += ":" + hnc::to_string(port()); }

			// Path
			r += path();

			// Return
			return r;
		}
	};
	
	/// @brief Operator << between a std::ostream and a hnc::url
	/// @param[in,out] o   Output stream
	/// @param[in]     url A hnc::url
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, hnc::url const & url)
	{
		o << url.to_string();
		return o;
	}
}

#endif
