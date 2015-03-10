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


#ifndef HNC_CHARACTER_ENCODING_HPP
#define HNC_CHARACTER_ENCODING_HPP

#include <string>


namespace hnc
{
	/**
	 * @brief Character encoding
	 *
	 * @code
	   #include <hnc/character_encoding.hpp>
	   @endcode
	 *
	 * http://en.wikipedia.org/wiki/Character_encoding
	 *
	 * hnc::character_encoding::utf8, hnc::character_encoding::ascii, ...
	 */
	namespace character_encoding
	{
		/**
		 * @brief Character encoding
		 *
		 * @code
		   #include <hnc/character_encoding.hpp>
		   @endcode
		 *
		 * Default encoding if utf-8 hnc::character_encoding::utf8
		 */
		class encoding
		{
		protected:

			/// Code
			std::string m_code;

			/// Description
			std::string m_description;

		public:

			/// @brief Default contructor
			encoding() :
				m_code("utf-8"),
				m_description("UTF-8 has become the dominant character encoding for the World-Wide Web, accounting for more than half of all Web pages. Variable-width encoding. Backward compatibility with ASCII. Avoid the complications of endianness and byte order marks in UTF-16 and UTF-32.")
			{ }

			/// @brief Destructor
			virtual ~encoding() { }

			/// @brief Return the code of the character encoding
			/// @return the code of the character encoding
			std::string const & code() const { return m_code; }

			/// @brief Return the description of the character encoding
			/// @return the description of the character encoding
			std::string const & description() const { return m_description; }

		protected:

			/// @brief Constructor
			/// @param[in] code        Code of the character encoding
			/// @param[in] description Description of the character encoding
			encoding
			(
				std::string const & code,
				std::string const & description
			) :
				m_code(code),
				m_description(description)
			{ }
		};
		
		/// @brief Operator << between a std::ostream and a hnc::character_encoding::encoding
		/// @param[in,out] o                       Output stream
		/// @param[in]     character_encoding_code A hnc::character_encoding::encoding
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::character_encoding::encoding const & character_encoding_code)
		{
			o << character_encoding_code.code();
			return o;
		}
		
		// Unicode

		/**
		 * @brief UTF-8, UTF-8 has become the dominant character encoding for the World-Wide Web, accounting for more than half of all Web pages. Variable-width encoding. Backward compatibility with ASCII. Avoid the complications of endianness and byte order marks in UTF-16 and UTF-32.
		 *
		 * @code
		   #include <hnc/character_encoding.hpp>
		   @endcode
		 */
		using utf8 = hnc::character_encoding::encoding;

		/**
		 * @brief UTF-16, Variable-width encoding (one or two 16-bit code units).
		 *
		 * @code
		   #include <hnc/character_encoding.hpp>
		   @endcode
		 */
		class utf16 : public hnc::character_encoding::encoding
		{
		public:

			/// @brief Constructor
			utf16() : hnc::character_encoding::encoding("utf-16", "Variable-width encoding (one or two 16-bit code units).") { }
		};

		/**
		 * @brief UTF-32, Exactly 32-bit code units. The main advantage of UTF-32, versus variable length encodings, is that the Unicode code points are directly indexable. Examining the n'th code point is a constant time operation.
		 *
		 * @code
		   #include <hnc/character_encoding.hpp>
		   @endcode
		 */
		class utf32 : public hnc::character_encoding::encoding
		{
		public:

			/// Constructor
			utf32() : hnc::character_encoding::encoding("utf-32", "Exactly 32-bit code units. The main advantage of UTF-32, versus variable length encodings, is that the Unicode code points are directly indexable. Examining the n'th code point is a constant time operation.") { }
		};

		// Ascii

		/**
		 * @brief ASCII, American Standard Code for Information Interchange.
		 *
		 * @code
		   #include <hnc/character_encoding.hpp>
		   @endcode
		 */
		class ascii : public hnc::character_encoding::encoding
		{
		public:

			/// @brief Constructor
			ascii() : hnc::character_encoding::encoding("us-ascii", "American Standard Code for Information Interchange.") { }
		};

		/**
		 * @brief ASCII, American Standard Code for Information Interchange
		 *
		 * @code
		   #include <hnc/character_encoding.hpp>
		   @endcode
		 */
		using us_ascii = hnc::character_encoding::ascii;

		// ISO 8859

		/**
		 * @brief ISO 8859-15, Western Europe and Euro sign and other rationalisations.
		 *
		 * @code
		   #include <hnc/character_encoding.hpp>
		   @endcode
		 */
		class iso_8859_15 : public hnc::character_encoding::encoding
		{
		public:

			/// @brief Constructor
			iso_8859_15() : hnc::character_encoding::encoding("iso-8859-15", "Western Europe and Euro sign and other rationalisations.") { }
		};

		// Microsoft Windows character sets

		/**
		 * @brief Windows-1252, Microsoft Windows character sets for Western languages.
		 *
		 * @code
		   #include <hnc/character_encoding.hpp>
		   @endcode
		 */
		class windows_1252 : public hnc::character_encoding::encoding
		{
		public:

			/// @brief Constructor
			windows_1252() : hnc::character_encoding::encoding("windows-1252", "Microsoft Windows character sets for Western languages.") { }
		};
	}
}

#endif
