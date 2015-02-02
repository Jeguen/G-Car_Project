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


#ifndef HNC_GEOMETRY_RECTANGLE_HPP
#define HNC_GEOMETRY_RECTANGLE_HPP

#include <iostream>

#include "../serialization.hpp"


namespace hnc
{
	namespace geometry
	{
		/**
		* @brief Rectangle (left, top, width, size)
		* 
		* @code
		  	#include <hnc/geometry.hpp>
		  @endcode
		*/
		template <class T>
		class rectangle
		{
		public:
			
			/// Left coordinate
			T left;
			
			/// Top coordinate
			T top;
			
			/// Width
			T width;
			
			/// Height
			T height;
			
			/// @brief Default constructor
			rectangle() : left(), top(), width(), height() { }
			
			/// @brief Constructor
			/// @param[in] left   Left
			/// @param[in] top    Top
			/// @param[in] width  Width
			/// @param[in] height Height
			rectangle<T>(T const & left, T const & top, T const & width, T const & height) :
				left(left), top(top), width(width), height(height)
			{ }
			
			hnc_generate_serialize_member_function(left, top, width, height)
			
			/// @brief Return right coordinate
			/// @return right
			T right() const { return left + width; }
			
			/// @brief Return bottom coordinate
			/// @return bottom
			T bottom() const { return top + height; }
		};
		
		/// @brief Equality operator between two hnc::geometry::rectangle<T>
		/// @param[in] rectangle_a A hnc::geometry::rectangle<T>
		/// @param[in] rectangle_b A hnc::geometry::rectangle<T>
		/// @return true if hnc::geometry::rectangle<T> have same values, false otherwise
		template <class T>
		bool operator ==(hnc::geometry::rectangle<T> const & rectangle_a, hnc::geometry::rectangle<T> const & rectangle_b)
		{
			return
			(
				rectangle_a.left == rectangle_b.left &&
				rectangle_a.top == rectangle_b.top &&
				rectangle_a.width == rectangle_b.width &&
				rectangle_a.height == rectangle_b.height
			);
		}
		
		/// @brief Inequality operator between two hnc::geometry::rectangle<T>
		/// @param[in] rectangle_a A hnc::geometry::rectangle<T>
		/// @param[in] rectangle_b A hnc::geometry::rectangle<T>
		/// @return true if hnc::geometry::rectangle<T> have different values, false otherwise
		template <class T>
		bool operator !=(hnc::geometry::rectangle<T> const & rectangle_a, hnc::geometry::rectangle<T> const & rectangle_b)
		{
			return !(rectangle_a == rectangle_b);
		}
		
		/// @brief Operator << between a std::ostream and a hnc::geometry::rectangle<T>
		/// @param[in,out] o         Output stream
		/// @param[in]     rectangle A hnc::geometry::rectangle<T>
		/// @return the output stream
		template <class T>
		std::ostream & operator <<(std::ostream & o, hnc::geometry::rectangle<T> const & rectangle)
		{
			o << "{ left = " << rectangle.left << ", top = " << rectangle.top << ", width = " << rectangle.width << ", height = " << rectangle.height << " }";
			return o;
		}
	}
}

#endif
