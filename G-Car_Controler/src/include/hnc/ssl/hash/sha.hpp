// Copyright © 2013, 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr
// Copyright © 2013 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_SSL_HASH_SHA_HPP
#define HNC_SSL_HASH_SHA_HPP

#include <string>

#ifndef hnc_no_openssl
#include <openssl/sha.h>
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
			/// sha raw data type
			using sha_raw_data = hnc::raw_data<SHA_DIGEST_LENGTH>;
			#else
			using sha_raw_data = hnc::raw_data<1>;
			#endif
			
			#ifndef hnc_no_openssl
			/**
			 * @brief Computhe the sha
			 *
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 *
			 * @return the sha of std::string in a hnc::raw_data
			 */
			sha_raw_data sha(std::string const & s)
			{
				sha_raw_data hash;

				SHA_CTX sha;
				SHA_Init(&sha);

				SHA_Update(&sha, s.c_str(), s.size());

				SHA_Final(hash.data(), &sha);

				return hash;
			}
			#else
			sha_raw_data sha(std::string const & /*s*/)
			{
				hnc::test::warning(false, "hnc::ssl::hash::sha is not supported, please install OpenSSL and recompile this program without hnc_no_openssl define\n");
				return sha_raw_data();
			}
			#endif

			#ifndef hnc_no_openssl
			/// sha1 raw data type
			using sha1_raw_data = hnc::raw_data<SHA_DIGEST_LENGTH>;
			#else
			using sha1_raw_data = hnc::raw_data<1>;
			#endif

			#ifndef hnc_no_openssl
			/**
			 * @brief Computhe the sha1
			 *
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 *
			 * @return the sha1 of std::string in a hnc::raw_data
			 */
			sha1_raw_data sha1(std::string const & s)
			{
				sha1_raw_data hash;
				
				SHA1(reinterpret_cast<unsigned char const *>(s.c_str()), s.size(), hash.data());

				return hash;
			}
			#else
			sha1_raw_data sha1(std::string const & /*s*/)
			{
				hnc::test::warning(false, "hnc::ssl::hash::sha1 is not supported, please install OpenSSL and recompile this program without hnc_no_openssl define\n");
				return sha1_raw_data();
			}
			#endif

			#ifndef hnc_no_openssl
			/// sha224 raw data type
			using sha224_raw_data = hnc::raw_data<SHA224_DIGEST_LENGTH>;
			#else
			using sha224_raw_data = hnc::raw_data<1>;
			#endif

			#ifndef hnc_no_openssl
			/**
			 * @brief Computhe the sha224
			 *
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 *
			 * @return the sha224 of std::string in a hnc::raw_data
			 */
			sha224_raw_data sha224(std::string const & s)
			{
				sha224_raw_data hash;

				SHA224(reinterpret_cast<unsigned char const *>(s.c_str()), s.size(), hash.data());

				return hash;
			}
			#else
			sha224_raw_data sha224(std::string const & /*s*/)
			{
				hnc::test::warning(false, "hnc::ssl::hash::sha224 is not supported, please install OpenSSL and recompile this program without hnc_no_openssl define\n");
				return sha224_raw_data();
			}
			#endif

			#ifndef hnc_no_openssl
			/// sha256 raw data type
			using sha256_raw_data = hnc::raw_data<SHA256_DIGEST_LENGTH>;
			#else
			using sha256_raw_data = hnc::raw_data<1>;
			#endif

			#ifndef hnc_no_openssl
			/**
			 * @brief Computhe the sha256
			 *
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 *
			 * @return the sha256 of std::string in a hnc::raw_data
			 */
			sha256_raw_data sha256(std::string const & s)
			{
				sha256_raw_data hash;

				SHA256_CTX sha256;
				SHA256_Init(&sha256);

				SHA256_Update(&sha256, s.c_str(), s.size());

				SHA256_Final(hash.data(), &sha256);

				return hash;
			}
			#else
			sha256_raw_data sha256(std::string const & /*s*/)
			{
				hnc::test::warning(false, "hnc::ssl::hash::sha256 is not supported, please install OpenSSL and recompile this program without hnc_no_openssl define\n");
				return sha256_raw_data();
			}
			#endif

			#ifndef hnc_no_openssl
			/// sha384 raw data type
			using sha384_raw_data = hnc::raw_data<SHA384_DIGEST_LENGTH>;
			#else
			using sha384_raw_data = hnc::raw_data<1>;
			#endif

			#ifndef hnc_no_openssl
			/**
			 * @brief Computhe the sha384
			 *
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 *
			 * @return the sha384 of std::string in a hnc::raw_data
			 */
			sha384_raw_data sha384(std::string const & s)
			{
				sha384_raw_data hash;

				SHA384(reinterpret_cast<unsigned char const *>(s.c_str()), s.size(), hash.data());

				return hash;
			}
			#else
			sha384_raw_data sha384(std::string const & /*s*/)
			{
				hnc::test::warning(false, "hnc::ssl::hash::sha384 is not supported, please install OpenSSL and recompile this program without hnc_no_openssl define\n");
				return sha384_raw_data();
			}
			#endif
			
			#ifndef hnc_no_openssl
			/// sha512 raw data type
			using sha512_raw_data = hnc::raw_data<SHA512_DIGEST_LENGTH>;
			#else
			using sha512_raw_data = hnc::raw_data<1>;
			#endif
			
			#ifndef hnc_no_openssl
			/**
			 * @brief Computhe the sha512
			 *
			 * @code
			   #include <hnc/ssl.hpp>
			   @endcode
			 *
			 * @param[in] s A std::string
			 *
			 * @note If hnc_no_openssl is defined, the function returns default raw_data and displays a warning message
			 * 
			 * @return the sha512 of std::string in a hnc::raw_data
			 */
			sha512_raw_data sha512(std::string const & s)
			{
				sha512_raw_data hash;

				SHA512_CTX sha512;
				SHA512_Init(&sha512);

				SHA512_Update(&sha512, s.c_str(), s.size());

				SHA512_Final(hash.data(), &sha512);

				return hash;
			}
			#else
			sha512_raw_data sha512(std::string const & /*s*/)
			{
				hnc::test::warning(false, "hnc::ssl::hash::sha512 is not supported, please install OpenSSL and recompile this program without hnc_no_openssl define\n");
				return sha512_raw_data();
			}
			#endif
		}
	}
}

#endif
