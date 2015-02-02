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


#ifndef HNC_MATH_RELATIONAL_OPERATOR_HPP
#define HNC_MATH_RELATIONAL_OPERATOR_HPP

#include <iostream>


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Relational operators for equation
		 * 
		 * @code
		   #include <hnc/math.hpp>
		   @endcode
		 * 
		 * @f$==@f$ equal_to @n
		 * @f$!=@f$ not_equal_to @n
		 * @f$>@f$ greater_than @n
		 * @f$<@f$ less_than @n
		 * @f$>=@f$ greater_than_or_equal_to @n
		 * @f$<=@f$ less_than_or_equal_to
		 */
		enum class relational_operator
		{
			equal_to, not_equal_to, greater_than, less_than, greater_than_or_equal_to, less_than_or_equal_to
		};
		
		/// @brief Operator << between a std::ostream and a hnc::math::relational_operator
		/// @param[out] o                   Output stream
		/// @param[in]  relational_operator A hnc::math::relational_operator
		/// @return the output stream
		std::ostream & operator <<(std::ostream & o, hnc::math::relational_operator const & relational_operator)
		{
			if (relational_operator == hnc::math::relational_operator::equal_to)
			{
				o << "=";
			}
			else if (relational_operator == hnc::math::relational_operator::not_equal_to)
			{
				o << "!=";
			}
			else if (relational_operator == hnc::math::relational_operator::greater_than)
			{
				o << ">";
			}
			else if (relational_operator == hnc::math::relational_operator::less_than)
			{
				o << "<";
			}
			else if (relational_operator == hnc::math::relational_operator::greater_than_or_equal_to)
			{
				o << ">=";
			}
			else if (relational_operator == hnc::math::relational_operator::less_than_or_equal_to)
			{
				o << "<=";
			}
			else
			{
				o << "??";
			}
			return o;
		}
	}
}

#endif
