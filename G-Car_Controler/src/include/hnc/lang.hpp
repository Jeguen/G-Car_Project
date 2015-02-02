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


/**
 * @file
 * @brief Just for operator <<(std::ostream & o, hnc::lang::lang_code const & lang_code)
 */

#ifndef HNC_LANG_HPP
#define HNC_LANG_HPP

#include <string>


namespace hnc
{
	/**
	 * @brief Language codes
	 *
	 * @code
	   #include <hnc/lang.hpp>
	   @endcode
	 *
	 * http://en.wikipedia.org/wiki/ISO_639
	 * http://en.wikipedia.org/wiki/List_of_ISO_639-2_codes
	 * http://en.wikipedia.org/wiki/List_of_ISO_639-3_codes
	 */
	namespace lang
	{

		/**
		 * @brief No lang language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 *
		 * Base class for language code
		 */
		class lang_code
		{
		protected:

			/// Name
			std::string m_name;

			/// ISO 639-1 language code
			std::string m_iso_639_1;

			/// ISO 639-2 language code
			std::string m_iso_639_2;

			/// ISO 639-3 language code
			std::string m_iso_639_3;

		public:

			/// @brief Default contructor
			lang_code() = default;

			/// @brief Destructor
			virtual ~lang_code() { }

			/// @brief Return true if no language is specified, false otherwise
			/// @return true if no language is specified, false otherwise
			bool no_lang() const { return m_name == ""; }

			/// @brief Return the name of the language
			/// @return the name of the language
			std::string const & name() const { return m_name; }

			/// @brief Return the ISO 639-1 language code
			/// @return the ISO 639-1 language code
			std::string const & iso_639_1() const { return m_iso_639_1; }

			/// @brief Return the ISO 639-2 language code
			/// @return the ISO 639-2 language code
			std::string const & iso_639_2() const { return m_iso_639_2; }

			/// @brief Return the ISO 639-3 language code
			/// @return the ISO 639-3 language code
			std::string const & iso_639_3() const { return m_iso_639_3; }

			/// @brief Return the HTML language code (same as ISO 639-1)
			/// @return the HTML language code (same as ISO 639-1)
			std::string const & html() const { return iso_639_1(); }

		protected:

			/// @brief Constructor
			/// @param[in] name      Name of the language
			/// @param[in] iso_639_1 ISO 639-1 language code
			/// @param[in] iso_639_2 ISO 639-2 language code
			/// @param[in] iso_639_3 ISO 639-3 language code
			lang_code
			(
				std::string const & name,
				std::string const & iso_639_1,
				std::string const & iso_639_2,
				std::string const & iso_639_3
			) :
				m_name(name),
				m_iso_639_1(iso_639_1),
				m_iso_639_2(iso_639_2),
				m_iso_639_3(iso_639_3)
			{ }
		};
		
		/// @brief Operator << between a std::ostream and a hnc::lang::lang_code
		/// @param[in,out] o         Output stream
		/// @param[in]     lang_code A hnc::lang::lang_code
		/// @return the output stream
		inline std::ostream & operator <<(std::ostream & o, hnc::lang::lang_code const & lang_code)
		{
			o << lang_code.name();
			return o;
		}
		
		// ISO 639-1

		// A

		/**
		 * @brief Afar language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class afar : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			afar() : hnc::lang::lang_code("Afar", "aa", "aar", "aar") { }
		};

		/**
		 * @brief Abkhazian language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class abkhazian : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			abkhazian() : hnc::lang::lang_code("Abkhazian", "ab", "abk", "abk") { }
		};

		/**
		 * @brief Afrikaans language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class afrikaans : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			afrikaans() : hnc::lang::lang_code("Afrikaans", "af", "afr", "afr") { }
		};

		/**
		 * @brief Akan language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class akan : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			akan() : hnc::lang::lang_code("Akan", "ak", "aka", "aka") { }
		};

		/**
		 * @brief Albanian language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class albanian : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			albanian() : hnc::lang::lang_code("Albanian", "sq", "sqi", "sqi") { }
		};

		/**
		 * @brief Amharic language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class amharic : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			amharic() : hnc::lang::lang_code("Amharic", "am", "amh", "amh") { }
		};

		/**
		 * @brief Arabic language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class arabic : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			arabic() : hnc::lang::lang_code("Arabic", "ar", "ara", "ara") { }
		};

		/**
		 * @brief Aragonese language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class aragonese : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			aragonese() : hnc::lang::lang_code("Aragonese", "an", "arg", "arg") { }
		};

		// D

		/**
		 * @brief German language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class german : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			german() : hnc::lang::lang_code("German", "de", "deu", "deu") { }
		};

		// E

		/**
		 * @brief English language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class english : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			english() : hnc::lang::lang_code("English", "en", "eng", "eng") { }
		};

		// F

		/**
		 * @brief French language code
		 *
		 * @code
		   #include <hnc/lang.hpp>
		   @endcode
		 */
		class french : public hnc::lang::lang_code
		{
		public:

			/// @brief Constructor
			french() : hnc::lang::lang_code("French", "fr", "fra", "fra") { }
		};
	}
}

#endif
