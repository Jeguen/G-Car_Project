// Copyright © 2013, 2014 Lénaïc Bagnères, hnc@singularity.fr

// This file is part of hnc.

// hnc is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// hnc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with hnc. If not, see <http://www.gnu.org/licenses/>


#ifndef HNC_EXCEPT_HPP
#define HNC_EXCEPT_HPP

#include <exception>
#include <stdexcept>


namespace hnc
{
	/**
	 * @brief Extends std::exception, std::logic_error and std::runtime_error
	 *
	 * @code
	   #include <hnc/except.hpp>
	   @endcode
	 *
	 * std::exception @n
	 * http://www.cplusplus.com/reference/exception/exception/ @n
	 * http://en.cppreference.com/w/cpp/error/exception
	 *
	 * std::logic_error @n
	 * http://www.cplusplus.com/reference/stdexcept/logic_error/ @n
	 * http://en.cppreference.com/w/cpp/error/logic_error
	 *
	 * std::runtime_error @n
	 * http://www.cplusplus.com/reference/stdexcept/runtime_error/ @n
	 * http://en.cppreference.com/w/cpp/error/runtime_error
	 */
	namespace except
	{
		/**
		 * @brief Exception to report incomplete implementation
		 * 
		 * @code
		   #include <hnc/except.hpp>
		   @endcode
		 */
		class incomplete_implementation : public std::logic_error
		{
		public:
			
			/// @brief Constructor
			/// @param[in] what_arg Description of the error
			explicit incomplete_implementation(std::string const & what_arg) :
				std::logic_error(what_arg)
			{ }
			
			/// @copydoc hnc::except::incomplete_implementation::incomplete_implementation(std::string const &)
			explicit incomplete_implementation(char const * const what_arg) :
				std::logic_error(what_arg)
			{ }
			
			/// @brief Return the description of the error
			/// @return the description of the error
			virtual char const * what() const noexcept
			{
				return std::logic_error::what();
			}
			
			/// @brief Destructor
			virtual ~incomplete_implementation() noexcept { }
		};
		
		/**
		 * @brief Exception "file not found"
		 * 
		 * @code
		   #include <hnc/except.hpp>
		   @endcode
		 */
		class file_not_found : public std::runtime_error
		{
		public:
			
			/// @brief Constructor
			/// @param[in] what_arg Description of the error
			explicit file_not_found(std::string const & what_arg) :
				std::runtime_error(what_arg)
			{ }
			
			/// @copydoc hnc::except::file_not_found::file_not_found(std::string const &)
			explicit file_not_found(char const * const what_arg) :
				std::runtime_error(what_arg)
			{ }
			
			/// @brief Return the description of the error
			/// @return the description of the error
			virtual char const * what() const noexcept
			{
				return std::runtime_error::what();
			}
			
			/// @brief Destructor
			virtual ~file_not_found() noexcept { }
		};
		
		/**
		 * @brief Exception "parse error"
		 * 
		 * @code
		   #include <hnc/except.hpp>
		   @endcode
		 */
		class parse_error : public std::logic_error
		{
		protected:
			
			/// @brief Line number
			unsigned int m_line_number;
			
			/// @brief Column number
			unsigned int m_column_number;
			
		public:

			/// @brief Constructor
			/// @param[in] what_arg      Description of the error
			/// @param[in] line_number   Line number
			/// @param[in] column_number Column number
			explicit parse_error(std::string const & what_arg, unsigned int line_number = 0, unsigned int column_number = 0) :
				std::logic_error(what_arg),
				m_line_number(line_number),
				m_column_number(column_number)
			{ }
			
			/// @copydoc hnc::except::parse_error::parse_error(std::string const &)
			explicit parse_error(char const * const what_arg, unsigned int line_number = 0, unsigned int column_number = 0) :
				std::logic_error(what_arg),
				m_line_number(line_number),
				m_column_number(column_number)
			{ }
			
			/// @brief Return the description of the error
			/// @return the description of the error
			virtual char const * what() const noexcept
			{
				return std::logic_error::what();
			}
			
			/// @brief Return the line number of the error
			/// @return the line number of the error
			virtual unsigned int line_number() const { return m_line_number; }
			
			/// @brief Return the column number of the error
			/// @return the column number of the error
			virtual unsigned int column_number() const { return m_column_number; }

			/// @brief Destructor
			virtual ~parse_error() noexcept { }
		};
		
		/**
		 * @brief Exception "bad cast"
		 * 
		 * @code
		   #include <hnc/except.hpp>
		   @endcode
		 */
		class bad_cast : public std::runtime_error
		{
		public:
			
			/// @brief Constructor
			/// @param[in] what_arg Description of the error
			explicit bad_cast(std::string const & what_arg) :
				std::runtime_error(what_arg)
			{ }
			
			/// @copydoc hnc::except::bad_cast::bad_cast(std::string const &)
			explicit bad_cast(char const * const what_arg) :
				std::runtime_error(what_arg)
			{ }
			
			/// @brief Return the description of the error
			/// @return the description of the error
			virtual char const * what() const noexcept
			{
				return std::runtime_error::what();
			}
			
			/// @brief Destructor
			virtual ~bad_cast() noexcept { }
		};
	}
}

#endif
