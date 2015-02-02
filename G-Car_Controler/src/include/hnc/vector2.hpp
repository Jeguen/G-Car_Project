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


#ifndef HNC_VECTOR2_HPP
#define HNC_VECTOR2_HPP

#include <iostream>

#include "serialization.hpp"


namespace hnc
{
	/**
	 * @brief Container for 2 values (x and y)
	 * 
	 * @code
	   #include <hnc/vector2.hpp>
	   @endcode
	 */
	template <class T>
	class vector2
	{
	public:

		/// x
		T x;

		/// y
		T y;
		
		/// @brief Default constructor
		vector2() : x(), y() { }

		/// @brief Constructor 
		/// @param[in] x x
		/// @param[in] y y
		vector2<T>(T const & x, T const & y) :
			x(x), y(y)
		{ }
		
		hnc_generate_serialize_member_function(x, y)
		
		/// @brief Equality operator
		/// @param[in] v A hnc::vector2
		/// @return true if hnc::vector2 have same values, false otherwise
		bool operator ==(vector2 const & v) const { return (x == v.x && y == v.y); }
		
		/// @brief Inequality operator
		/// @param[in] v A hnc::vector2
		/// @return true if hnc::vector2 have different values, false otherwise
		bool operator !=(vector2 const & v) const { return (! ((*this) == v)); }
	};
	
	/// @brief Operator << between a std::ostream and a hnc::vector2<T>
	/// @param[in,out] o       Output stream
	/// @param[in]     vector2 A hnc::vector2<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::vector2<T> const & vector2)
	{
		o << "{ " << vector2.x << ", " << vector2.y << " }";
		return o;
	}
}

#endif
