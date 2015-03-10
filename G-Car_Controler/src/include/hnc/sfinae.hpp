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


#ifndef HNC_SFINAE_HPP
#define HNC_SFINAE_HPP

#include <type_traits>


namespace hnc
{
	// http://stackoverflow.com/questions/9530928/checking-a-member-exists-possibly-in-a-base-class-c11-version
	
	/**
	 * @brief Type for SFINAE
	 *
	 * @code
	   #include <hnc/sfinae.hpp>
	   @endcode
	 * 
	 * http://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
	 *
	 * In a partial template specialization, you can check if the type is valid:
	 * @code
	   template <class T, typename hnc::this_type<your_type>::is_valid>
	   class
	   {
	   	// ...
	   };
	   @endcode
	 * 
	 * For example (see hnc/clone.hpp), you can check is a type has the .clone() member function:
	 * @code
	   // Valid fonctor (return false) for all types
	   template <class T, class sfinae_valid_type = void>
	   class is_cloneable : public std::false_type
	   { };
	   
	   // This partial template specialization fonctor (return true) is created only if
	   // the type "decltype(std::declval<T &>().clone())" is valid i.e. T::clone() exists
	   template <class T>
	   class is_cloneable<T, typename hnc::this_type<decltype(std::declval<T &>().clone())>::is_valid> : public std::true_type
	   { };
	   @endcode
	 */
	template <class>
	class this_type
	{
	public:
		
		/// is_valid type
		using is_valid = void;
	};
}

#endif
