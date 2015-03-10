// Copyright © 2013 Lénaïc Bagnères, hnc@singularity.fr
// Copyright © 2013 David Guinehut, dvdg@singularity.fr
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


#ifndef HNC_MATH_LINEAR_EQUATION_HPP
#define HNC_MATH_LINEAR_EQUATION_HPP

#include <iostream>
#include <vector>

#include "relational_operator.hpp"


namespace hnc
{
	namespace math
	{
		/**
		 * @brief Linear equation
		 * @code
		   #include <hnc/math/linear_equation.hpp>
		   @endcode
		 * 
		 * http://en.wikipedia.org/wiki/Linear_equation
		 * 
		 * Default linear equation
		 * @code
		   hnc::math::linear_equation<int> eq;
		   std::cout << eq << std::endl; // 0 = 0
		   @endcode
		 * 
		 * Equation without parameter
		 * @code
		   hnc::math::linear_equation<int> eq({1}, {}, 42);
		   std::cout << eq << std::endl; // i + 42 = 0
		   @endcode
		 * 
		 * Equation with 0 coefficients
		 * @code
		   hnc::math::linear_equation<int> eq({1, 0, 2}, {0, 0, 1}, 73, hnc::math::relational_operator::greater_than_or_equal_to);
		   std::cout << eq << std::endl; // i + 2k + P + 73 >= 0
		   @endcode
		 * 
		 * Equation with double
		 * @code
		   hnc::math::linear_equation<double> eq({21.73, 2, 7.1}, {42.21}, 0, hnc::math::relational_operator::less_than);
		   std::cout << eq << std::endl; // 21.73i + 2j + 7.1k + 42.21N < 0
		   @endcode
		 * 
		 */
		template <class T>
		class linear_equation
		{
		public:
			
			/// Unknown variables (x, y, z) coefficients
			std::vector<T> unknown_variables_coeff;
			
			/// Parameters (N, M) coefficients
			std::vector<T> parameters_coeff;
			
			/// Constant
			T constant;
			
			/// Relational operator
			hnc::math::relational_operator relational_operator;
			
			/// @brief Constructor
			/// @param[in] unknown_variables_coeff Unknown variables (x, y, z) coefficients (empty by default)
			/// @param[in] parameters_coeff        Parameters (N, M) coefficients (empty by default)
			/// @param[in] constant                Constant  (T(0) by default)
			/// @param[in] relational_operator     Relational operator (hnc::math::relational_operator::equal_to by default)
			linear_equation
			(
				std::vector<T> const & unknown_variables_coeff = std::vector<T>(),
				std::vector<T> const & parameters_coeff = std::vector<T>(),
				T const constant = T(0),
				hnc::math::relational_operator const relational_operator = hnc::math::relational_operator::equal_to
			) :
				unknown_variables_coeff(unknown_variables_coeff),
				parameters_coeff(parameters_coeff),
				constant(constant),
				relational_operator(relational_operator)
			{ }
		};
		
		/// @brief Operator == between two hnc::math::linear_equation<T>
		/// @param[in] linear_equation_0 A hnc::math::linear_equation<T>
		/// @param[in] linear_equation_1 A hnc::math::linear_equation<T>
		/// @return true if the hnc::math::linear_equation<T> are equal, false otherwise
		template <class T>
		bool operator ==(hnc::math::linear_equation<T> const & linear_equation_0, hnc::math::linear_equation<T> const & linear_equation_1)
		{
			if (&linear_equation_0 == &linear_equation_1)
			{
				return true;
			}
			else
			{
				return
				(
					linear_equation_0.unknown_variables_coeff == linear_equation_1.unknown_variables_coeff &&
					linear_equation_0.parameters_coeff == linear_equation_1.parameters_coeff &&
					linear_equation_0.constant == linear_equation_1.constant &&
					linear_equation_0.relational_operator == linear_equation_1.relational_operator
				);
			}
		}
		
		/// @brief Operator != between two hnc::math::linear_equation<T>
		/// @param[in] linear_equation_0 A hnc::math::linear_equation<T>
		/// @param[in] linear_equation_1 A hnc::math::linear_equation<T>
		/// @return true if the hnc::math::linear_equation<T> are not equal, false otherwise
		template <class T>
		bool operator !=(hnc::math::linear_equation<T> const & linear_equation_0, hnc::math::linear_equation<T> const & linear_equation_1)
		{
			return ! (linear_equation_0 == linear_equation_1);
		}
		
		/// @brief Operator << between a std::ostream and a hnc::math::linear_equation<T>
		/// @param[in,out] o               Output stream
		/// @param[in]     linear_equation A hnc::math::linear_equation<T>
		/// @return the output stream
		template <class T>
		std::ostream & operator <<(std::ostream & o, hnc::math::linear_equation<T> const & linear_equation)
		{
			// Only first write do not print " + "
			bool first_write = true;
			
			// Unknown variables
			for (std::size_t i = 0; i < linear_equation.unknown_variables_coeff.size(); ++i)
			{
				T const & coeff = linear_equation.unknown_variables_coeff[i];
				
				if (coeff != T(0))
				{
					if (first_write == false)
					{
						o << " + ";
					}
					
					if (coeff == T(1))
					{
						o << char('i' + i);
						first_write = false;
					}
					else
					{
						o << coeff << char('i' + i);
						first_write = false;
					}
				}
			}
			
			// Parameters
			for (std::size_t i = 0; i < linear_equation.parameters_coeff.size(); ++i)
			{
				T const & coeff = linear_equation.parameters_coeff[i];
				
				if (coeff != T(0))
				{
					if (first_write == false)
					{
						o << " + ";
					}
					
					if (coeff == T(1))
					{
						o << char('N' + i);
						first_write = false;
					}
					else
					{
						o << coeff << char('N' + i);
						first_write = false;
					}
				}
			}
			
			// Constant
			if (first_write)
			{
				o << linear_equation.constant;
			}
			else if (linear_equation.constant != T(0))
			{
				o << " + " << linear_equation.constant;
			}
			
			// Relational operator
			o << " " << linear_equation.relational_operator << " " << 0;
			
			// Return stream
			return o;
		}
	}
}

#endif
