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


#ifndef HNC_COPY_AND_SWAP_HPP
#define HNC_COPY_AND_SWAP_HPP

#include <algorithm>

#include "sfinae.hpp"


namespace hnc
{
	/// @brief Type is not swappable with .swap(T &) member function
	template <class T, class sfinae_valid_type = void>
	class is_swappable_with_swap_member_function : public std::false_type
	{ };
	
	/// @brief Type is swappable with .swap(T &) member function
	template <class T>
	class is_swappable_with_swap_member_function<T, typename hnc::this_type<decltype(std::declval<T &>().swap(std::declval<T &>()))>::is_valid> : public std::true_type
	{ };
}

/**
 * @brief Generate copy and move assignement (operator =) with copy and swap idiom
 * 
 * @code
   #include <hnc/copy_and_swap.hpp>
   @endcode
 *
 * If the copy and move assignement is not automatically generated, you can generate them if copy and move constructor and .swap(T &) member function exist
 *
 * @pre copy and move constructor exist
 * @pre .swap(T &) member function exist
 *
 * Example:
 * @code
   class A
   {
   public:
   	
   	int v;
   	
   	A(int const v = 0) : v(v) { }
   	
   	A(A const & a) : v(a.v) { }
   	
   	A(A && a) : v(a.v) { a.v = 0; }
   	
   	hnc_generate_copy_and_move_assignment(A)
   	
   	void swap(A & a) { std::swap(v, a.v); }
   };
   
   hnc_overload_std_swap_with_swap_member_function_for_class(A)
   @endcode
 *
 * @note For no base class, consider hnc_generate_copy_and_move_assignment
 * @note For base class, consider hnc_generate_virtual_copy_and_move_assignment
 */
#define hnc_generate_copy_and_move_assignment(T) \
	T & operator =(T const & t) \
	{ \
		if (&t != this) \
		{ \
			T copy(t); \
			swap(copy); \
		} \
		return *this; \
	} \
	\
	T & operator =(T && t) \
	{ \
		if (&t != this) \
		{ \
			T moved(std::move(t)); \
			swap(moved); \
		} \
		return *this; \
	}

/**
 * @brief Generate virtual (for base class) copy and move assignement (operator =) with copy and swap idiom
 *
 * @code
   #include <hnc/copy_and_swap.hpp>
   @endcode
 *
 * If the copy and move assignement is not automatically generated, you can generate them if copy and move constructor and .swap(T &) member function exist
 *
 * @pre copy and move constructor exist
 * @pre .swap(T &) member function exist
 *
 * Example:
 * @code
   class A
   {
   public:
   	
   	int v;
   	
   	A(int const v = 0) : v(v) { }
   	
   	A(A const & a) : v(a.v) { }
   	
   	A(A && a) : v(a.v) { a.v = 0; }
   	
   	virtual ~A() { }
   	
   	hnc_generate_virtual_copy_and_move_assignment(A)
   	
   	void swap(A & a) { std::swap(v, a.v); }
   };
   
   hnc_overload_std_swap_with_swap_member_function_for_class(A)
   @endcode
 *
 * @note For no base class, consider hnc_generate_copy_and_move_assignment
 * @note For base class, consider hnc_generate_virtual_copy_and_move_assignment
 */
#define hnc_generate_virtual_copy_and_move_assignment(T) \
	virtual T & operator =(T const & t) \
	{ \
		if (&t != this) \
		{ \
			T copy(t); \
			swap(copy); \
		} \
		return *this; \
	} \
	\
	virtual T & operator =(T && t) \
	{ \
		if (&t != this) \
		{ \
			T moved(std::move(t)); \
			swap(moved); \
		} \
		return *this; \
	}

/**
 * @brief Overload std::swap function with .swap(T &) member function
 * 
 * @code
   #include <hnc/copy_and_swap.hpp>
   @endcode
 *
 * @param[in] T Class name
 *
 * Example:
 * @code
   class A
   {
   public:
   	
   	int v;
   	
   	void swap(A & a) { std::swap(v, a.v); }
   };
   
   hnc_overload_std_swap_with_swap_member_function_for_class(A)
   @endcode
 * 
 * @note Use hnc_overload_std_swap_with_swap_member_function_for_template_class if your class has template arguments
 */
#define hnc_overload_std_swap_with_swap_member_function_for_class(T) \
namespace std \
{ \
	void swap(T & a, T & b) noexcept \
	{ \
		a.swap(b); \
	} \
}

/**
 * @brief Overload std::swap function with .swap(T &) member function
 * 
 * @code
   #include <hnc/copy_and_swap.hpp>
   @endcode
 *
 * @param[in] T                          Class name
 * @param[in] template_types_declaration Template types declarations (class T, class U, ...)
 *
 * Example:
 * @code
   template <class T>
   class A
   {
   public:
   	
   	T v;
   	
   	void swap(A<T> & a) { std::swap(v, a.v); }
   };
   
   hnc_overload_std_swap_with_swap_member_function_for_template_class(A<T>, class T)
   @endcode
 * 
 * @note Use hnc_overload_std_swap_with_swap_member_function_for_class if your class does not have template arguments
 */
#define hnc_overload_std_swap_with_swap_member_function_for_template_class(T, template_types_declaration) \
namespace std \
{ \
	template <template_types_declaration> \
	void swap(T & a, T & b) noexcept \
	{ \
		a.swap(b); \
	} \
}

#endif
