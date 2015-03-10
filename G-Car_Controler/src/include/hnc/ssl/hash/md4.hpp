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


#ifndef HNC_SSL_HASH_MD4_HPP
#define HNC_SSL_HASH_MD4_HPP

#include <string>

#ifndef hnc_no_openssl
#include <openssl/md4.h>
#endif

#include "../../raw_data.hpp"
#include "../../test.hpp"


namespace hnc
{
	namespace ssl
	{
		namespace hash
		{
			#ifndef hnc_no_openssl
			/// md4 raw data type
			using md4_raw_data = hnc::raw_data<MD4_DIGEST_LENGTH>;
			#else
			using md4_raw_data = hnc::raw_data<1>;
			#endif

			#ifndef hnc_no_openssl
			/**
			 * @brief Computhe the md4
			 *
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 *
			 * @return the md4 of std::string in a hnc::raw_data
			 */
			md4_raw_data md4(std::string const & s)
			{
				md4_raw_data hash;

				MD4_CTX md4;
				MD4_Init(&md4);

				MD4_Update(&md4, s.c_str(), s.size());

				MD4_Final(hash.data(), &md4);

				return hash;
			}
			#else
			md4_raw_data md4(std::string const & /*s*/)
			{
				hnc::test::warning(false, "hnc::ssl::hash::md4 is not supported, please install OpenSSL and recompile this program without hnc_no_openssl define\n");
				return md4_raw_data();
			}
			#endif
		}
	}
}

#endif
