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


#ifndef HNC_SSL_HPP
#define HNC_SSL_HPP

#include "ssl/hash/md2.hpp"
#include "ssl/hash/md4.hpp"
#include "ssl/hash/md5.hpp"
#include "ssl/hash/mdc2.hpp"
#include "ssl/hash/rmd160.hpp"
#include "ssl/hash/sha.hpp"


namespace hnc
{
	/**
	 * @brief Minimal encapsulation of OpenSSL library
	 *
	 * @code
	   #include <hnc/ssl.hpp>
	   @endcode
	 *
	 * @b From @b Wikipedia http://en.wikipedia.org/wiki/OpenSSL
	 * OpenSSL is an open-source implementation of the SSL and TLS protocols. The core library, written in the C programming language, implements the basic cryptographic functions and provides various utility functions. Wrappers allowing the use of the OpenSSL library in a variety of computer languages are available.
	 * Versions are available for most Unix-like operating systems (including Solaris, Linux, Mac OS X and the various open source BSD operating systems), OpenVMS and Microsoft Windows
	 *
	 * @b From @b Wikipedia http://en.wikipedia.org/wiki/OpenSSL#Algorithms
	 * OpenSSL supports a number of different cryptographic algorithms:
	 * - Ciphers: @n
	 * AES, Blowfish, Camellia, SEED, CAST-128, DES, IDEA, RC2, RC4, RC5, Triple DES, GOST 28147-89
	 * - Cryptographic hash functions: @n
	 * MD5, MD2, SHA-1, SHA-2, RIPEMD-160, MDC-2, GOST R 34.11-94
	 * - Public-key cryptography: @n
	 * RSA, DSA, Diffie–Hellman key exchange, Elliptic curve, GOST R 34.10-2001 @n
	 * - (Perfect forward secrecy is supported using elliptic curve Diffie-Hellman since version 1.0.)
	 *
	 * To use hnc::ssl, you need OpenSSL @n
	 * You can add this in your CMakeLists.txt
	 * @code
	   find_package(hnc REQUIRED)
	  
	   # ...
	  
	   # Create the executable
	   add_executable(your_exe your_exe.cpp)
	   target_link_libraries(your_exe ${HNC_OPENSSL_LIBRARY})
	   @endcode
	 *
	 * For quick test, if you use GCC from the command line and Boost is installed, you can link directly with:
	 * @code
	   -lssl -lcrypto
	   @endcode
	 *
	 * On Debian GNU/Linux distribution you can install the package:
	 * @code
	   libssl-dev
	   @endcode
	 *
	 * If you want compile without OpenSSL, you can define the macro
	 * @code
	   #define hnc_no_openssl
	   @endcode
	 * or use CMake variable
	 * @code
	   add_definition("-D${HNC_NO_OPENSSL_MACRO}")
	   @endcode
	 */
	namespace ssl
	{
		// For Doxygen only

		/**
		 * @brief Ciphers (AES, Blowfish, Camellia, SEED, CAST-128, DES, IDEA, RC2, RC4, RC5, Triple DES, GOST 28147-89)
		 * 
		 * @code
		   #include <hnc/ssl.hpp>
		   @endcode
		 */
		namespace cipher
		{
			// For Doxygen only
		}

		/**
		 * @brief Cryptographic hash functions (MD5, MD2, SHA-1, SHA-2, RIPEMD-160, MDC-2, GOST R 34.11-94)
		 * 
		 * @code
		   #include <hnc/ssl.hpp>
		   @endcode
		 */
		namespace hash
		{
			// For Doxygen only
		}

		/**
		 * @brief Public-key cryptography (RSA, DSA, Diffie–Hellman key exchange, Elliptic curve, GOST R 34.10-2001)
		 * 
		 * @code
		   #include <hnc/ssl.hpp>
		   @endcode
		 */
		namespace public_key
		{
			// For Doxygen only
		}
	}
}

#endif
