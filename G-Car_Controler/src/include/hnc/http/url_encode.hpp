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


#ifndef HNC_HTTP_URL_ENCODE_HPP
#define HNC_HTTP_URL_ENCODE_HPP

#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>


namespace hnc
{
	namespace http
	{
		/**
		 * @brief Perform a Percent-encoding (for ASCII characters (upgrade needed)), also known as URL encoding, on std::string
		 *
		 * @code
		   #include <hnc/html.hpp>
		   @endcode
		 *
		 * http://en.wikipedia.org/wiki/Percent-encoding
		 * http://rosettacode.org/wiki/URL_encoding#C
		 *
		 * @param[in] data Input data
		 *
		 * @pre std::string contains only ASCII character (upgrade needed)
		 *
		 * @return the percent-encoded data
		 */
		std::string url_encode(std::string const & data)
		{
			// Result
			std::string r;

			// Encode one char
			auto encode = [](char const c) -> std::string
			{
				std::stringstream s;
				s << "%" << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << static_cast<int>(static_cast<unsigned char>(c));
				return s.str();
			};

			// Encode the data
			for (char const c : data)
			{
				if (std::isalnum(c) || c == '~' || c == '-' || c == '.' || c == '_') { r.push_back(c); }
				else { r += encode(c); }
			}

			// Return
			return r;
		}
	}
}

#endif
