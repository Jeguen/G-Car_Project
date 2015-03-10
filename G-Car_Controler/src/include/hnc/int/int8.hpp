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


#ifndef HNC_INT8_HPP
#define HNC_INT8_HPP

#include <iostream>
#include <stdexcept>
#include <climits>

#include "../serialization.hpp"


namespace hnc
{
	/**
	 * @brief int with values between -128 and 127
	 * 
	 * @code
	   #include <hnc/int.hpp>
	   @endcode
	 * 
	 * @note This class is not a typedef, the display and the overload of this type do what you think
	 */
	class int8
	{
	public:
		
		/// int
		#if (CHAR_BIT == 8)
			signed char i;
		#else
			signed char i:8;
		#endif
		
	public:
		
		/// @brief Constructor from signed char
		/// @param[in] i Integer between -128 and 127
		int8(signed char const i = 0) : i(i) { }
		
		/// @brief Constructor from int
		/// @param[in] i Integer between -128 and 127
		int8(int const i) : i(static_cast<signed char>(i)) { }
		
		hnc_generate_serialize_member_function(i)
	};
	
	// +
	
	/// @brief Operator + between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return a + b
	inline hnc::int8 operator +(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i + b.i;
	}
	
	/// @brief Operator += between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return a += b
	inline hnc::int8 & operator +=(hnc::int8 & a, hnc::int8 const b)
	{
		a = a + b;
		return a;
	}
	
	/// @brief Operator ++ (prefix) with a hnc::int8
	/// @param[in] i A hnc::int8
	/// @return i++
	inline hnc::int8 & operator ++(hnc::int8 & i)
	{
		++i.i;
		return i;
	}
	
	/// @brief Operator ++ (postfix) with a hnc::int8
	/// @param[in] i A hnc::int8
	/// @return i++
	inline hnc::int8 operator ++(hnc::int8 & i, int)
	{
		hnc::int8 tmp = i;
		++i;
		return tmp;
	}
	
	// -
	
	/// @brief Operator - between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return a - b
	inline hnc::int8 operator -(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i - b.i;
	}
	
	/// @brief Operator -= between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return a -= b
	inline hnc::int8 & operator -=(hnc::int8 & a, hnc::int8 const b)
	{
		a = a - b;
		return a;
	}
	
	/// @brief Operator -- (prefix) with a hnc::int8
	/// @param[in] i A hnc::int8
	/// @return i--
	inline hnc::int8 & operator --(hnc::int8 & i)
	{
		--i.i;
		return i;
	}
	
	/// @brief Operator -- (postfix) with a hnc::int8
	/// @param[in] i A hnc::int8
	/// @return i--
	inline hnc::int8 operator --(hnc::int8 & i, int)
	{
		hnc::int8 tmp = i;
		--i;
		return tmp;
	}
	
	// *
	
	/// @brief Operator * between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return a * b
	inline hnc::int8 operator *(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i * b.i;
	}
	
	/// @brief Operator *= between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return a *= b
	inline hnc::int8 & operator *=(hnc::int8 & a, hnc::int8 const b)
	{
		a = a * b;
		return a;
	}
	
	// /
	
	/// @brief Operator / between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return a / b
	inline hnc::int8 operator /(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i / b.i;
	}
	
	/// @brief Operator /= between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return a /= b
	inline hnc::int8 & operator /=(hnc::int8 & a, hnc::int8 const b)
	{
		a = a / b;
		return a;
	}
	
	// ==, !=, <, >, <=, >=
	
	/// @brief Operator == between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return true if the hnc::int8 are equal, false otherwise
	inline bool operator ==(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i == b.i;
	}
	
	/// @brief Operator != between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return true if the hnc::int8 are different, false otherwise
	inline bool operator !=(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i != b.i;
	}
	
	/// @brief Operator < between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return true if a < b, false otherwise
	inline bool operator <(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i < b.i;
	}
	
	/// @brief Operator > between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return true if a > b, false otherwise
	inline bool operator >(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i > b.i;
	}
	
	/// @brief Operator <= between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return true if a <= b, false otherwise
	inline bool operator <=(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i <= b.i;
	}
	
	/// @brief Operator > between two hnc::int8
	/// @param[in] a A hnc::int8
	/// @param[in] b A hnc::int8
	/// @return true if a >= b, false otherwise
	inline bool operator >=(hnc::int8 const a, hnc::int8 const b)
	{
		return a.i >= b.i;
	}
	
	// <<, >>
	
	/// @brief Operator << between a std::ostream and a hnc::int8
	/// @param[in,out] o    Output stream
	/// @param[in]     int8 A hnc::int8
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, hnc::int8 const int8)
	{
		o << static_cast<int>(int8.i);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a hnc::int8
	/// @param[in,out] i    Input stream
	/// @param[out]    int8 A hnc::int8
	/// @return the output stream
	inline std::istream & operator >>(std::istream & i, hnc::int8 & int8)
	{
		int tmp;
		i >> tmp;
		int8 = tmp;
		return i;
	}
}

#endif
