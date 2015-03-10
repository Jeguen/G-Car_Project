// Copyright © 2013, 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_SSL_HASH_MD2_HPP
#define HNC_SSL_HASH_MD2_HPP

#include <string>

#include "../../raw_data.hpp"
#include "../../test.hpp"
#include "../../unused.hpp"


namespace hnc
{
	namespace ssl
	{
		namespace hash
		{
			/// md2 raw data type
			using md2_raw_data = hnc::raw_data<1>;

			/**
			 * @brief Computhe the md2
			 * 
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 *
			 * @return the md2 of std::string in a hnc::raw_data
			 */
			md2_raw_data md2(std::string const & s)
			{
				hnc_unused(s);
				hnc::test::warning(false, "hnc::ssl::hash::md2 is not supported, OpenSSL md2 is deprecated and removed in Debian\n");
				return md2_raw_data();
			}
		}
	}
}

#endif
