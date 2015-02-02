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


#ifndef HNC_COLOR_HPP
#define HNC_COLOR_HPP

#include <iostream>
#include <iomanip>
#include <ios>
#include <string>

#include "int.hpp"
#include "to_string.hpp"
#include "algo/to_upper.hpp"

#include "serialization.hpp"


namespace hnc
{
	/**
	 * @brief hnc::color
	 * 
	 * @code
	   #include <hnc/color.hpp>
	   @endcode
	 */
	class color
	{
	public:
		
		/// Red level
		hnc::uint8 r;
		
		/// Green level
		hnc::uint8 g;
		
		/// Blue level
		hnc::uint8 b;
		
		/// Alpha level (transparency)
		hnc::uint8 a;
		
		/// @brief Default constructor
		color() : r(0), g(0), b(0), a(255) { }
		
		/// @brief Constructor
		/// @param[in] r Red level
		/// @param[in] g Green level
		/// @param[in] b Blue level
		/// @param[in] a Alpha level (transparency)
		color
		(
			hnc::uint8 const & r,
			hnc::uint8 const & g,
			hnc::uint8 const & b,
			hnc::uint8 const & a = 255
		) :
			r(r), g(g), b(b), a(a)
		{ }
		
		/// @brief HTML code of the color
		/// @return HTML code of the color
		std::string html()
		{
			return hnc::algo::to_upper_copy
			(
				std::string("#") +
				hnc::to_string(r, std::setw(2), std::setfill('0'), std::hex) +
				hnc::to_string(g, std::setw(2), std::setfill('0'), std::hex) +
				hnc::to_string(b, std::setw(2), std::setfill('0'), std::hex)
			);
		}
		
		hnc_generate_serialize_member_function(r, g, b, a)
		
		// Basic colors
		
		/// @brief Black color
		/// @return Black color
		static hnc::color black() { return { 0, 0, 0 }; }
	
		/// @brief White color
		/// @return White color
		static hnc::color white() { return { 255, 255, 255 }; }
	
		/// @brief Grey color
		/// @return Grey color
		static hnc::color grey() { return { 128, 128, 128 }; }
		
		// LaTeX colors
		
		#ifndef hnc_no_color_latex
			#include "color/latex.hpp"
		#endif
	};
	
	/// @brief Operator == between two hnc::color
	/// @param[in] a A hnc::color
	/// @param[in] b A hnc::color
	/// @return true if the hnc::color are equal, false otherwise
	inline bool operator ==(hnc::color const & a, hnc::color const & b)
	{
		return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
	}
	
	/// @brief Operator != between two hnc::color
	/// @param[in] a A hnc::color
	/// @param[in] b A hnc::color
	/// @return true if the hnc::color are different, false otherwise
	inline bool operator !=(hnc::color const & a, hnc::color const & b)
	{
		return !(a == b);
	}
	
	/// @brief Operator << between a std::ostream and a hnc::color
	/// @param[in,out] o     Output stream
	/// @param[in]     color A hnc::color
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, hnc::color const & color)
	{
		o << "{ " << color.r << ", " << color.g << ", " << color.b << ", " << color.a << " }";
		return o;
	}
}

#endif
