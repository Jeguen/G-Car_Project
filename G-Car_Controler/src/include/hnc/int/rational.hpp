// Copyright © 2013 Lénaïc Bagnères, hnc@singularity.fr
// Copyright © 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef HNC_RATIONAL_HPP
#define HNC_RATIONAL_HPP

#include <iostream>

#include "../math/gcd.hpp"
#include "../serialization.hpp"


namespace hnc
{
	/**
	 * @brief Rational number
	 * 
	 * @code
	   #include <hnc/rational.hpp>
	   @endcode
	 * 
	 * http://en.wikipedia.org/wiki/Rational_number
	 */
	template <class T>
	class rational
	{
	public:
		
		/// Numerator
		T m_numerator;
		
		/// Denominator
		T m_denominator;
		
	public:
		
		/// @brief Constructor
		/// @param[in] numerator   Numerator
		/// @param[in] denominator Denominator
		explicit rational(T const & numerator, T const & denominator = T(1)) :
			m_numerator(numerator),
			m_denominator(denominator)
		{
			reduce();
		}
		
		/// @brief Return the numerator
		/// @return the numerator
		T const & numerator() const { return m_numerator; }
		
		/// @brief Return the denominator
		/// @return the denominator
		T const & denominator() const { return m_denominator; }
		
		hnc_generate_serialize_member_function(m_numerator, m_denominator)
		
	private:
		
		/// @brief Reduce the fraction
		/// @return the denominator
		void reduce()
		{
			T const gcd = hnc::math::gcd_without_abs(m_numerator, m_denominator);
			m_numerator /= gcd;
			m_denominator /= gcd;
			
			if ((m_numerator >= 0 && m_denominator < 0) || (m_numerator < 0 && m_denominator < 0))
			{
				m_numerator = -m_numerator;
				m_denominator = -m_denominator;
			}
		}
	};
	
	// +
	
	/// @brief Operator + between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return a + b
	template <class T>
	hnc::rational<T> operator +(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return hnc::rational<T>
		(
			a.numerator() * b.denominator() + a.denominator() * b.numerator(),
			a.denominator() * b.denominator()
		);
	}
	
	/// @brief Operator += between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return a += b
	template <class T>
	hnc::rational<T> & operator +=(hnc::rational<T> & a, hnc::rational<T> const & b)
	{
		a = a + b;
		return a;
	}
	
	/// @brief Operator ++ (prefix) with a hnc::rational<T>
	/// @param[in] r A hnc::rational<T>
	/// @return r++
	template <class T>
	hnc::rational<T> & operator ++(hnc::rational<T> & r)
	{
		r = r + hnc::rational<T>(1);
		return r;
	}
	
	/// @brief Operator ++ (postfix) with a hnc::rational<T>
	/// @param[in] r A hnc::rational<T>
	/// @return r++
	template <class T>
	hnc::rational<T> operator ++(hnc::rational<T> & r, int)
	{
		hnc::rational<T> tmp = r;
		++r;
		return tmp;
	}
	
	// -
	
	/// @brief Operator - between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return a - b
	template <class T>
	hnc::rational<T> operator -(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return hnc::rational<T>
		(
			a.numerator() * b.denominator() - a.denominator() * b.numerator(),
			a.denominator() * b.denominator()
		);
	}
	
	/// @brief Operator -= between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return a -= b
	template <class T>
	hnc::rational<T> & operator -=(hnc::rational<T> & a, hnc::rational<T> const & b)
	{
		a = a - b;
		return a;
	}
	
	/// @brief Operator -- (prefix) with a hnc::rational<T>
	/// @param[in] r A hnc::rational<T>
	/// @return r--
	template <class T>
	hnc::rational<T> & operator --(hnc::rational<T> & r)
	{
		r = r - hnc::rational<T>(1);
		return r;
	}
	
	/// @brief Operator -- (postfix) with a hnc::rational<T>
	/// @param[in] r A hnc::rational<T>
	/// @return r--
	template <class T>
	hnc::rational<T> operator --(hnc::rational<T> & r, int)
	{
		hnc::rational<T> tmp = r;
		--r;
		return tmp;
	}
	
	// *
	
	/// @brief Operator * between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return a * b
	template <class T>
	hnc::rational<T> operator *(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return hnc::rational<T>(a.numerator() * b.numerator(), a.denominator() * b.denominator());
	}
	
	/// @brief Operator *= between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return a *= b
	template <class T>
	hnc::rational<T> & operator *=(hnc::rational<T> & a, hnc::rational<T> const & b)
	{
		a = a * b;
		return a;
	}
	
	// /
	
	/// @brief Operator / between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return a / b
	template <class T>
	hnc::rational<T> operator /(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return hnc::rational<T>(a.numerator() * b.denominator(), a.denominator() * b.numerator());
	}
	
	/// @brief Operator /= between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return a /= b
	template <class T>
	hnc::rational<T> & operator /=(hnc::rational<T> & a, hnc::rational<T> const & b)
	{
		a = a / b;
		return a;
	}
	
	// ==, !=, <, >, <=, >=
	
	/// @brief Operator == between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return true if the hnc::rational<T> are equal, false otherwise
	template <class T>
	bool operator ==(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return a.numerator() == b.numerator() && a.denominator() == b.denominator();
	}
	
	/// @brief Operator != between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return true if the hnc::rational<T> are different, false otherwise
	template <class T>
	bool operator !=(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return a.numerator() != b.numerator() || a.denominator() != b.denominator();
	}
	
	/// @brief Operator < between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return true if a < b, false otherwise
	template <class T>
	bool operator <(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return a.numerator() * b.denominator() < a.denominator() * b.numerator();
	}
	
	/// @brief Operator > between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return true if a > b, false otherwise
	template <class T>
	bool operator >(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return a.numerator() * b.denominator() > a.denominator() * b.numerator();
	}
	
	/// @brief Operator <= between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return true if a <= b, false otherwise
	template <class T>
	bool operator <=(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return a.numerator() * b.denominator() <= a.denominator() * b.numerator();
	}
	
	/// @brief Operator > between two hnc::rational<T>
	/// @param[in] a A hnc::rational<T>
	/// @param[in] b A hnc::rational<T>
	/// @return true if a >= b, false otherwise
	template <class T>
	bool operator >=(hnc::rational<T> const & a, hnc::rational<T> const & b)
	{
		return a.numerator() * b.denominator() >= a.denominator() * b.numerator();
	}
	
	// <<
	
	/// @brief Operator << between a std::ostream and a hnc::rational<T>
	/// @param[in,out] o Output stream
	/// @param[in]     r A hnc::rational<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::rational<T> const & r)
	{
		o << r.numerator();
		if (r.denominator() != T(1)) { o << "/" << r.denominator(); }
		return o;
	}
}

#endif
