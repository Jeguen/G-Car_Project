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


#ifndef HNC_RAW_DATA_HPP
#define HNC_RAW_DATA_HPP

#include <array>
#include <iostream>
#include <iomanip>


// Pre-declare hnc::raw_data for operator <<
namespace hnc
{
	template <std::size_t N>
	class raw_data;
	
	// Declarate this function for hnc::raw_data can be friend with
	template <std::size_t N>
	std::ostream & operator <<(std::ostream & o, hnc::raw_data<N> const & c);
}

namespace hnc
{
	/**
	 * @brief Raw data is an encapsulation of std::array of unsigned char (with hexidecimal as display)
	 * 
	 * @code
	   #include <hnc/raw_data.hpp>
	   @endcode
	 *
	 * hnc::raw_data is an std::array<unsigned char, N>
	 *
	 * http://www.cplusplus.com/reference/array/array/
	 */
	template <std::size_t N>
	class raw_data : private std::array<unsigned char, N>
	{
	public:
		
		// Member types
		using typename std::array<unsigned char, N>::value_type;
		using typename std::array<unsigned char, N>::reference;
		using typename std::array<unsigned char, N>::const_reference;
		using typename std::array<unsigned char, N>::pointer;
		using typename std::array<unsigned char, N>::const_pointer;
		using typename std::array<unsigned char, N>::iterator;
		using typename std::array<unsigned char, N>::const_iterator;
		using typename std::array<unsigned char, N>::reverse_iterator;
		using typename std::array<unsigned char, N>::const_reverse_iterator;
		using typename std::array<unsigned char, N>::size_type;
		using typename std::array<unsigned char, N>::difference_type;
		
		// Iterators
		using std::array<unsigned char, N>::begin;
		using std::array<unsigned char, N>::end;
		using std::array<unsigned char, N>::rbegin;
		using std::array<unsigned char, N>::rend;
		using std::array<unsigned char, N>::cbegin;
		using std::array<unsigned char, N>::cend;
		using std::array<unsigned char, N>::crbegin;
		using std::array<unsigned char, N>::crend;

		// Capacity
		using std::array<unsigned char, N>::size;
		using std::array<unsigned char, N>::max_size;
		using std::array<unsigned char, N>::empty;

		// Element access
		using std::array<unsigned char, N>::operator[];
		using std::array<unsigned char, N>::at;
		using std::array<unsigned char, N>::front;
		using std::array<unsigned char, N>::back;
		using std::array<unsigned char, N>::data;

		// Modifiers
		using std::array<unsigned char, N>::fill;
		using std::array<unsigned char, N>::swap;
		void swap(raw_data<N> & c) { static_cast<std::array<unsigned char, N>>(*this).swap(c); }

		// Operator == != < <= > >=

		/// @brief Equality test for each elements of two raw_data
		/// @return true if each element of the raw_data are equals, else false
		bool operator ==(raw_data<N> const & c) const
		{ return static_cast<std::array<unsigned char, N>>(*this) == static_cast<std::array<unsigned char, N>>(c); }

		/// @brief Inequality test for each elements of two raw_data
		/// @return true if one element of the raw_data is not equals, else false
		bool operator !=(raw_data<N> const & c) const
		{ return static_cast<std::array<unsigned char, N>>(*this) != static_cast<std::array<unsigned char, N>>(c); }

		/// @brief < test for each elements of two raw_data
		/// @return true if each element of the raw_data are <, else false
		bool operator <(raw_data<N> const & c) const
		{ return static_cast<std::array<unsigned char, N>>(*this) < static_cast<std::array<unsigned char, N>>(c); }

		/// @brief <= test for each elements of two raw_data
		/// @return true if each element of the raw_data are <=, else false
		bool operator <=(raw_data<N> const & c) const
		{ return static_cast<std::array<unsigned char, N>>(*this) <= static_cast<std::array<unsigned char, N>>(c); }

		/// @brief > test for each elements of two raw_data
		/// @return true if each element of the raw_data are >, else false
		bool operator >(raw_data<N> const & c) const
		{ return static_cast<std::array<unsigned char, N>>(*this) > static_cast<std::array<unsigned char, N>>(c); }

		/// @brief >= test for each elements of two raw_data
		/// @return true if each element of the raw_data are >=, else false
		bool operator >=(raw_data<N> const & c) const
		{ return static_cast<std::array<unsigned char, N>>(*this) >= static_cast<std::array<unsigned char, N>>(c); }

		// ostream

		/// @brief Declare operator << with std::ostream as a friend
		friend std::ostream & operator << <>(std::ostream & o, hnc::raw_data<N> const & c);
	};
	
	/// @brief Operator << between a std::ostream and a hnc::raw_data<N>
	/// @param[in,out] o Output stream
	/// @param[in]     c A hnc::raw_data<N>
	/// @return the output stream
	template <std::size_t N>
	std::ostream & operator <<(std::ostream & o, hnc::raw_data<N> const & c)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			o << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c[i]);
		}
		return o;
	}
}

#endif
