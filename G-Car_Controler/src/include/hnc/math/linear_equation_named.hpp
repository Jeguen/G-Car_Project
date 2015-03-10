// Copyright © 2014 David Guinehut, dvdg@singularity.fr

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


#ifndef HNC_MATH_LINEAR_EQUATION_NAMED_HPP
#define HNC_MATH_LINEAR_EQUATION_NAMED_HPP

#include <iostream>
#include <vector>

#include "linear_equation.hpp"

namespace hnc
{
	namespace math
	{
		/**
		 * @brief Linear equation named
		 * @code
		   #include <hnc/math/linear_equation_named.hpp>
		   @endcode
		 * 
		 * http://en.wikipedia.org/wiki/Linear_equation
		 * 
		 * Default linear equation named
		 * @code
		   hnc::math::linear_equation_named<int> eq;
		   std::cout << eq << std::endl; // 0 = 0
		   @endcode
		 * 
		 * Equation without parameter
		 * @code
		   hnc::math::linear_equation_named<int> eq({1}, {"x"}, {}, {}, 42);
		   std::cout << eq << std::endl; // x + 42 = 0
		   @endcode
		 * 
		 * Equation with 0 coefficients
		 * @code
		   hnc::math::linear_equation_named<int> eq({1, 0, 2}, {"x", "x'", "x''"}, {0, 0, 1}, {"A", "A'", "A''"}, 73, hnc::math::relational_operator::greater_than_or_equal_to);
		   std::cout << eq << std::endl; // x + 2x'' + A'' + 73 >= 0
		   @endcode
		 * 
		 * Equation with double
		 * @code
		   hnc::math::linear_equation_named<double> eq({21.73, 2, 7.1}, {"x", "y", "z"}, {42.21}, {"NP"}, 0, hnc::math::relational_operator::less_than);
		   std::cout << eq << std::endl; // 21.73x + 2y + 7.1z + 42.21NP < 0
		   @endcode
		 * 
		 * Equation from std::istream
		 * @code
		   hnc::math::linear_equation_named<double> eq;
		   std::cout << eq << std::endl; // 0 = 0
		   
		   std::istringstream i("21.73x + 2y + 7.1z + 42.21NP < 0");
		   i >> eq;
		   std::cout << eq << std::endl; // 21.73x + 2y + 7.1z + 42.21NP < 0
		   @endcode
		 *
		 * Get a hnc::math::linear_equation<T> from a hnc::math::linear_equation_named<T>
		 * @code
		   hnc::math::linear_equation_named<double> eq({21.73, 2, 7.1}, {"x", "y", "z"}, {42.21}, {"NP"}, 0, hnc::math::relational_operator::less_than);
		   std::cout << eq << std::endl; 			// 21.73x + 2y + 7.1z + 42.21NP < 0
		   
		   hnc::math::linear_equation<double> linear_eq = eq.linear_equation();
		   std::cout << linear_eq << std::endl; 	// 21.73i + 2j + 7.1k + 42.21N < 0
		 * @endcode
		 * 
		 */
		template <class T>
		class linear_equation_named 
		{
		private:
			
			/// Linear equation
			/// @copydoc linear_equation
			hnc::math::linear_equation<T> m_linear_equation;
			
			/// Unknown variables (x, y, z) names
			std::vector<std::string> m_unknown_variables_name;
			
			/// Parameters (N, M) names
			std::vector<std::string> m_parameters_name;
		
		public:
			
			/// @brief Constructor
			/// @param[in] unknown_variables_coeff Unknown variables (x, y, z) coefficients (empty by default)
			/// @param[in] unknown_variables_name  Unknown variables (x, y, z) names (empty by default)
			/// @param[in] parameters_coeff        Parameters (N, M) coefficients (empty by default)
			/// @param[in] parameters_name         Parameters (N, M) names (empty by default)
			/// @param[in] constant                Constant  (T(0) by default)
			/// @param[in] relational_operator     Relational operator (hnc::math::relational_operator::equal_to by default)
			linear_equation_named
			(
				std::vector<T> const & unknown_variables_coeff = std::vector<T>(),
				std::vector<std::string> const & unknown_variables_name = std::vector<std::string>(),
				std::vector<T> const & parameters_coeff = std::vector<T>(),
				std::vector<std::string> const & parameters_name = std::vector<std::string>(),
				T const constant = T(0),
				hnc::math::relational_operator const relational_operator = hnc::math::relational_operator::equal_to
			) :
				m_linear_equation(unknown_variables_coeff, parameters_coeff, constant, relational_operator),
				m_unknown_variables_name(unknown_variables_name),
				m_parameters_name(parameters_name)
			{ }
			
			/// @brief Return the linear equation
			/// @return the linear equation
			hnc::math::linear_equation<T> const & linear_equation() const { return m_linear_equation; }
			
			/// @brief Return the names of unknown variables
			/// @return the names of unknown variables
			std::vector<std::string> const & unknown_variables_name() const { return m_unknown_variables_name; }
			
			/// @brief Return the names of parameters
			/// @return the names of the parameters
			std::vector<std::string> const & parameters_name() const { return m_parameters_name; }
		};
		
		/// @brief Operator << between a std::ostream and a hnc::math::linear_equation_named<T>
		/// @param[in,out] o                     Output stream
		/// @param[in]     linear_equation_named A hnc::math::linear_equation_named<T>
		/// @return the output stream
		template <class T>
		std::ostream & operator <<(std::ostream & o, hnc::math::linear_equation_named<T> const & linear_equation_named)
		{
			// Only first write do not print " + "
			bool first_write = true;
			
			// Unknown variables
			for (std::size_t i = 0; i < linear_equation_named.unknown_variables_name().size(); ++i)
			{
				// unknown_variables_coeff is empty, so we don't have any unknown_variables_name to print
				if (linear_equation_named.linear_equation().unknown_variables_coeff.size() > i)
				{
					T const & coeff = linear_equation_named.linear_equation().unknown_variables_coeff[i];
				
					if (coeff != T(0))
					{
						if (first_write == false)
						{
							o << " + ";
						}
						
						if (coeff == T(1))
						{
							o << linear_equation_named.unknown_variables_name()[i];
							first_write = false;
						}
						else
						{
							o << coeff << linear_equation_named.unknown_variables_name()[i];
							first_write = false;
						}
					}
				}
			}
			
			// Parameters
			for (std::size_t i = 0; i < linear_equation_named.parameters_name().size(); ++i)
			{
				// parameters_coeff is empty, so we don't have any parameters_name to print
				if (linear_equation_named.linear_equation().parameters_coeff.size() > i)
				{
					T const & coeff = linear_equation_named.linear_equation().parameters_coeff[i];
				
					if (coeff != T(0))
					{
						if (first_write == false)
						{
							o << " + ";
						}
						
						if (coeff == T(1))
						{
							o << linear_equation_named.parameters_name()[i];
							first_write = false;
						}
						else
						{
							o << coeff << linear_equation_named.parameters_name()[i];
							first_write = false;
						}
					}
				}
			}
			
			// Constant
			if (first_write)
			{
				o << linear_equation_named.linear_equation().constant;
			}
			else if (linear_equation_named.linear_equation().constant != T(0))
			{
				o << " + " << linear_equation_named.linear_equation().constant;
			}
			
			// Relational operator
			o << " " << linear_equation_named.linear_equation().relational_operator << " " << 0;
			
			// Return stream
			return o;
		}
		
		/// @brief Operator >> between a std::istream and a hnc::math::linear_equation_named<T>
		/// @param[in,out] i  Input stream
		/// @param[in]     eq A hnc::math::linear_equation_named<T>
		/// @return the input stream
		template <class T>
		std::istream & operator >>(std::istream & i, hnc::math::linear_equation_named<T> & eq)
		{
			// Tmp variables for get from istream
			T coeff = T(0);
			std::string name;
			
			std::vector<T> unknown_variables_coeff;
			std::vector<std::string> unknown_variables_name;
			std::vector<T> parameters_coeff;
			std::vector<std::string> parameters_name;
			hnc::math::relational_operator relational_operator = hnc::math::relational_operator::equal_to;
			T constant = T(0);
			
			while (i.good())
			{
				// Extract character
				char c = char(i.peek());
				
				// Ignore spaces
				while (c == ' ') { i.get(c); c = char(i.peek());}
				
				// Check operator
				if (c == '+' || c == '-' || c == '/' || c == '*') 
				{ 
					// Coeff
					i.get(c); c = char(i.peek()); while (c == ' ') { i.get(c); c = char(i.peek()); }
					
					// Unknown variable or Paramater
					if (!isdigit(c))
					{
						coeff = T(1);
						
						// Name
						i >> name;
						
						// Unknown variable
						if (std::islower(name[0])) 
						{ 
							if (coeff != T(0)) 
							{ 
								unknown_variables_coeff.push_back(coeff);
								unknown_variables_name.push_back(name);
							}
						}
					
						// Parameter
						else if (std::isupper(name[0])) 
						{ 
							if (coeff != T(0)) 
							{ 
								parameters_name.push_back(name);
								parameters_coeff.push_back(coeff); 
							} 
						}
					}
					
					// Constant or Unknown variable or Paramater
					else 
					{
						T tmp;
						i >> tmp; 
						
						c = char(i.peek()); while (c == ' ') { i.get(c); c = char(i.peek()); }
						
						// Constant
						if (c == '=' || c == '<' || c == '>') { constant = tmp; }
						
						// Unknown variable or Paramater
						else 
						{
							coeff = tmp;
							
							// Name
							i >> name;
							
							// Unknown variable
							if (std::islower(name[0])) 
							{ 
								if (coeff != T(0)) 
								{ 
									unknown_variables_coeff.push_back(coeff);
									unknown_variables_name.push_back(name);
								}
							}
						
							// Parameter
							else if (std::isupper(name[0])) 
							{ 
								if (coeff != T(0)) 
								{ 
									parameters_coeff.push_back(coeff);
									parameters_name.push_back(name); 
								} 
							}
						}
					}
				}
				
				// Relational operator
				else if (c == '=' || c == '<' || c == '>')
				{	
					if (c == '=') { relational_operator = hnc::math::relational_operator::equal_to; }
					
					else if (c == '>')
					{
						i.get(c); c = char(i.peek());
						
						// >=
						if (c == '=') { relational_operator = hnc::math::relational_operator::greater_than_or_equal_to; }
						
						// >
						else { relational_operator = hnc::math::relational_operator::greater_than; }
					}
				
					else if (c == '<')
					{
						i.get(c); c = char(i.peek());
						
						// <=
						if (c == '=') { relational_operator = hnc::math::relational_operator::less_than_or_equal_to; }
						
						// <
						else { relational_operator = hnc::math::relational_operator::less_than; }
					}
					
					i.get(c);
				}
				
				// Unknown variable or Paramater
				else
				{
					if (!isdigit(c)) { coeff = T(1); }
					else { i >> coeff; }
					
					// Name
					i >> name;
					
					// Unknown variable
					if (std::islower(name[0])) 
					{ 
						if (coeff != T(0)) 
						{ 
							unknown_variables_coeff.push_back(coeff);
							unknown_variables_name.push_back(name);
						} 
					}
				
					// Parameter
					else if (std::isupper(name[0])) 
					{ 
						if (coeff != T(0)) 
						{ 
							parameters_coeff.push_back(coeff);
							parameters_name.push_back(name);
						} 
					} 
				}
			}

			// Write the equation
			eq = hnc::math::linear_equation_named<T>(unknown_variables_coeff, unknown_variables_name, parameters_coeff, parameters_name, constant, relational_operator);

			// Return stream
			return i;
		} 
	}
}

#endif
