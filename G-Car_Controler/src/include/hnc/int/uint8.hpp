// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_UINT8_HPP
#define HNC_UINT8_HPP

#include <iostream>
#include <stdexcept>
#include <climits>

#include "../serialization.hpp"


namespace hnc
{
	/**
	 * @brief unsigned int with values between 0 and 255
	 * 
	 * @code
	   #include <hnc/int.hpp>
	   @endcode
	 * 
	 * @note This class is not a typedef, the display and the overload of this type do what you think
	 */
	class uint8
	{
	public:
		
		/// int
		#if (CHAR_BIT == 8)
			unsigned char i;
		#else
			unsigned char i:8;
		#endif
		
	public:
		
		/// @brief Constructor from unsigned char
		/// @param[in] i Integer between 0 and 255
		uint8(unsigned char const i = 0) : i(i) { }
		
		/// @brief Constructor from unsigned int
		/// @param[in] i Integer between 0 and 255
		uint8(unsigned int const i) : i(static_cast<unsigned char>(i)) { }
		
		/// @brief Constructor from int
		/// @param[in] i Integer between 0 and 255
		uint8(int const i) : i(static_cast<unsigned char>(i)) { }
		
		hnc_generate_serialize_member_function(i)
	};
	
	// +
	
	/// @brief Operator + between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return a + b
	inline hnc::uint8 operator +(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i + b.i;
	}
	
	/// @brief Operator += between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return a += b
	inline hnc::uint8 & operator +=(hnc::uint8 & a, hnc::uint8 const b)
	{
		a = a + b;
		return a;
	}
	
	/// @brief Operator ++ (prefix) with a hnc::uint8
	/// @param[in] i A hnc::uint8
	/// @return i++
	inline hnc::uint8 & operator ++(hnc::uint8 & i)
	{
		++i.i;
		return i;
	}
	
	/// @brief Operator ++ (postfix) with a hnc::uint8
	/// @param[in] i A hnc::uint8
	/// @return i++
	inline hnc::uint8 operator ++(hnc::uint8 & i, int)
	{
		hnc::uint8 tmp = i;
		++i;
		return tmp;
	}
	
	// -
	
	/// @brief Operator - between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return a - b
	inline hnc::uint8 operator -(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i - b.i;
	}
	
	/// @brief Operator -= between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return a -= b
	inline hnc::uint8 & operator -=(hnc::uint8 & a, hnc::uint8 const b)
	{
		a = a - b;
		return a;
	}
	
	/// @brief Operator -- (prefix) with a hnc::uint8
	/// @param[in] i A hnc::uint8
	/// @return i--
	inline hnc::uint8 & operator --(hnc::uint8 & i)
	{
		--i.i;
		return i;
	}
	
	/// @brief Operator -- (postfix) with a hnc::uint8
	/// @param[in] i A hnc::uint8
	/// @return i--
	inline hnc::uint8 operator --(hnc::uint8 & i, int)
	{
		hnc::uint8 tmp = i;
		--i;
		return tmp;
	}
	
	// *
	
	/// @brief Operator * between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return a * b
	inline hnc::uint8 operator *(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i * b.i;
	}
	
	/// @brief Operator *= between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return a *= b
	inline hnc::uint8 & operator *=(hnc::uint8 & a, hnc::uint8 const b)
	{
		a = a * b;
		return a;
	}
	
	// /
	
	/// @brief Operator / between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return a / b
	inline hnc::uint8 operator /(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i / b.i;
	}
	
	/// @brief Operator /= between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return a /= b
	inline hnc::uint8 & operator /=(hnc::uint8 & a, hnc::uint8 const b)
	{
		a = a / b;
		return a;
	}
	
	// ==, !=, <, >, <=, >=
	
	/// @brief Operator == between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return true if the hnc::uint8 are equal, false otherwise
	inline bool operator ==(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i == b.i;
	}
	
	/// @brief Operator != between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return true if the hnc::uint8 are different, false otherwise
	inline bool operator !=(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i != b.i;
	}
	
	/// @brief Operator < between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return true if a < b, false otherwise
	inline bool operator <(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i < b.i;
	}
	
	/// @brief Operator > between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return true if a > b, false otherwise
	inline bool operator >(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i > b.i;
	}
	
	/// @brief Operator <= between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return true if a <= b, false otherwise
	inline bool operator <=(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i <= b.i;
	}
	
	/// @brief Operator > between two hnc::uint8
	/// @param[in] a A hnc::uint8
	/// @param[in] b A hnc::uint8
	/// @return true if a >= b, false otherwise
	inline bool operator >=(hnc::uint8 const a, hnc::uint8 const b)
	{
		return a.i >= b.i;
	}
	
	// <<, >>
	
	/// @brief Operator << between a std::ostream and a hnc::uint8
	/// @param[in,out] o    Output stream
	/// @param[in]     uint8 A hnc::uint8
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, hnc::uint8 const uint8)
	{
		o << static_cast<int>(uint8.i);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a hnc::uint8
	/// @param[in,out] i    Input stream
	/// @param[out]    uint8 A hnc::uint8
	/// @return the output stream
	inline std::istream & operator >>(std::istream & i, hnc::uint8 & uint8)
	{
		int tmp;
		i >> tmp;
		uint8 = tmp;
		return i;
	}
}

#endif
