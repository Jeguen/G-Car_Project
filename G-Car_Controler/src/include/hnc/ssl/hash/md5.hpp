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


#ifndef HNC_SSL_HASH_MD5_HPP
#define HNC_SSL_HASH_MD5_HPP

#include <string>

#ifndef hnc_no_openssl
#include <openssl/md5.h>
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
			/// md5 raw data type
			using md5_raw_data = hnc::raw_data<MD5_DIGEST_LENGTH>;
			#else
			using md5_raw_data = hnc::raw_data<1>;
			#endif

			#ifndef hnc_no_openssl
			/**
			 * @brief Computhe the md5
			 *
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 *
			 * @return the md5 of std::string in a hnc::raw_data
			 */
			md5_raw_data md5(std::string const & s)
			{
				md5_raw_data hash;

				MD5_CTX md5;
				MD5_Init(&md5);

				MD5_Update(&md5, s.c_str(), s.size());

				MD5_Final(hash.data(), &md5);

				return hash;
			}
			#else
			md5_raw_data md5(std::string const & /*s*/)
			{
				hnc::test::warning(false, "hnc::ssl::hash::md5 is not supported, please install OpenSSL and recompile this program without hnc_no_openssl define\n");
				return md5_raw_data();
			}
			#endif
		}
	}
}

#endif
