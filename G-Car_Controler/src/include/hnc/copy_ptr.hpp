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


#ifndef HNC_COPY_PTR_HPP
#define HNC_COPY_PTR_HPP

#include <type_traits>
#include <memory>
#include <utility>

#include "clone.hpp"
#include "copy_and_swap.hpp"


namespace hnc
{
	namespace
	{
		/// @brief Transform a std::unique_ptr of base_t to std::unique_ptr of derived_t
		/// @param[in,out] p   A std::unique_ptr of base_t
		/// @param[in]     tag std::false_type
		/// @return a std::unique_ptr of derived_t
		template <class derived_t, class base_t>
		std::unique_ptr<derived_t> unique_ptr_static_cast(std::unique_ptr<base_t> && p, std::false_type const /*tag*/)
		{
			std::unique_ptr<derived_t> r(static_cast<derived_t *>(p.get()));
			p.release();
			return r;
		}
		
		/// @brief Return a std::unique_ptr of base_t
		/// @param[in] p   A std::unique_ptr of base_t
		/// @param[in] tag std::true_type
		/// @return a std::unique_ptr of base_t
		template <class base_t>
		std::unique_ptr<base_t> unique_ptr_static_cast(std::unique_ptr<base_t> && p, std::true_type)
		{
			return std::move(p);
		}
	}
	
	/// @brief Transform a std::unique_ptr of base_t to std::unique_ptr of derived_t
	/// @param[in,out] p A std::unique_ptr of base_t
	/// @return a std::unique_ptr of derived_t
	template <class derived_t, class base_t>
	std::unique_ptr<derived_t> unique_ptr_static_cast(std::unique_ptr<base_t> && p)
	{
		return unique_ptr_static_cast<derived_t>(std::move(p), typename std::is_same<base_t, derived_t>::type());
	}
	
	/**
	 * @brief hnc::copy_ptr is like std::unique_ptr with copy
	 * 
	 * @code
	   #include <hnc/copy_ptr.hpp>
	   @endcode
	 * 
	 * hnc::copy_ptr performs a deep copy; it uses hnc::clone function which uses [virtual] .clone() member function if it exists @n
	 * So, copy a hnc::copy_ptr of base class which olds a derived class object works and does what you think
	 * 
	 * Example:
	 * @code
	   #include <iostream>
	   
	   #include <hnc/copy_ptr.hpp>
	   
	   class A
	   {
	   public:
	   	
	   	virtual ~A() { }
	   	
	   	hnc_generate_clone_member_function(A, A)
	   	
	   	virtual void display(std::ostream & o) const { o << "one_A"; }
	   };
	   
	   class B : public A
	   {
	   public:
	   	
	   	virtual ~B() { }
	   	
	   	hnc_generate_clone_member_function(A, B)
	   	
	   	virtual void display(std::ostream & o) const override { o << "one_B"; }
	   };
	   
	   std::ostream & operator <<(std::ostream & o, A const & v) { v.display(o); return o; }
	   
	   int main()
	   {
	   	// Default constructor
	   	hnc::copy_ptr<A> p;
	   	std::cout << p << std::endl; // nullptr
	   	
	   	// Create a A
	   	p = hnc::make_copy_ptr<A>();
	   	std::cout << p << std::endl; // one_A
	   	
	   	// Create a B
	   	p = hnc::make_copy_ptr<B>();
	   	std::cout << p << std::endl; // one_B
	   	
	   	// Copy the pointer
	   	hnc::copy_ptr<A> p_copy = p;
	   	std::cout << p_copy << std::endl; // one_B
	   	
	   	return 0;
	   }
	   @endcode
	 * 
	 * @note Do not use hnc::copy_ptr:
	 * - If you want copy a std::unique_ptr, add .clone() member function to your classe and use it (see hnc_generate_clone_member_function and hnc::clone)
	 * - If you want value semantic with base ad derived class, use hnc::value_ptr
	 */
	template <class T>
	class copy_ptr : private std::unique_ptr<T>
	{
	public:
		
		/// @brief Default constructor
		copy_ptr() : std::unique_ptr<T>() { }
		
		/// @brief Copy constructor
		/// @param[in] p A hnc::copy_ptr
		copy_ptr(hnc::copy_ptr<T> const & p) : std::unique_ptr<T>()
		{
			if (p)
			{
				std::unique_ptr<T>::operator =
				(
					hnc::is_cloneable<T>()
					?
						std::unique_ptr<T>(hnc::unique_ptr_static_cast<T>(hnc::clone_to_unique_ptr(*p)))
					:
						std::unique_ptr<T>(new T(*p))
				);
			}
			else
			{
				reset();
			}
		}
		
		/// @brief Constructor from a hnc::copy_ptr of derived_t
		/// @param[in] p A hnc::copy_ptr of derived_t
		template <class derived_t>
		copy_ptr(hnc::copy_ptr<derived_t> const & p) : std::unique_ptr<T>()
		{
			if (p)
			{
				std::unique_ptr<T>::operator =
				(
					hnc::is_cloneable<T>()
					?
						std::unique_ptr<T>(hnc::unique_ptr_static_cast<T>(hnc::clone_to_unique_ptr(*p)))
					:
						std::unique_ptr<T>(new T(*p))
				);
			}
			else
			{
				reset();
			}
		}
		
		/// @brief Move constructor
		/// @param[in] p A rvalue reference to a hnc::copy_ptr
		template <class U>
		copy_ptr(hnc::copy_ptr<U> && p) : std::unique_ptr<T>(p.release())
		{ }
		
		/// @brief Constructor from T
		/// @param[in] value Value
		copy_ptr(T const & value) : hnc::copy_ptr<T>(hnc::clone_to_unique_ptr(value).release())
		{ }
		
		/// @brief Copy and move assignment
		hnc_generate_copy_and_move_assignment(copy_ptr<T>);
		
		/// @brief Return the stored pointer
		/// @pre The pointer is not nullptr
		/// @return the stored pointer
		using std::unique_ptr<T>::get;
		
		/// @brief Return true if the pointer is not empty, false otherwise
		/// @return true if the pointer is not empty, false otherwise
		using std::unique_ptr<T>::operator bool;
		
		/// @brief Release the stored pointer and replace it by nullptr
		/// @return the stored pointer released
		using std::unique_ptr<T>::release;
		
		/// @brief Destroy the object pointed and replace it by nullptr
		using std::unique_ptr<T>::reset;
		
		/// @brief Exchange the objects stored
		using std::unique_ptr<T>::swap;
		
		/// @brief Return a reference to the stored object
		/// @pre The pointer is not nullptr
		/// @return a reference to the stored object
		using std::unique_ptr<T>::operator *;
		
		/// @brief Return a reference to the stored object to access of its members
		/// @pre The pointer is not nullptr
		/// @return a reference to the stored object to access of its members
		using std::unique_ptr<T>::operator ->;
		
	protected:
		
		/// @brief Constructor from a raw pointer
		/// @param[in] p A raw pointer
		copy_ptr(T * const p) : std::unique_ptr<T>(p) { }
		
	public:
		
		/// @brief hnc::make_copy_ptr function is friend with class hnc::copy_ptr
		template <class U, class ... args_list>
		friend hnc::copy_ptr<U> make_copy_ptr(args_list && ... args);
	};
	
	/// @brief Operator << between a std::ostream and a hnc::copy_ptr<T>
	/// @param[in,out] o Output stream
	/// @param[in]     p A hnc::copy_ptr<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator << (std::ostream & o, hnc::copy_ptr<T> const & p)
	{
		if (p) { o << *p; }
		else { o << "nullptr"; }
		return o;
	}
	
	/**
	 * @brief Create a hnc::copy_ptr of T
	 * 
	 * @code
	   #include <hnc/copy_ptr.hpp>
	   @endcode
	 * 
	 * @param[in] args Arguments for T constructor
	 *
	 * @return A hnc::copy_ptr of T
	 */
	template <class T, class ... args_list>
	hnc::copy_ptr<T> make_copy_ptr(args_list && ... args)
	{
		return hnc::copy_ptr<T>(new T(args ...));
	}
}

/// @brief std::swap between two hnc::copy_ptr
hnc_overload_std_swap_with_swap_member_function_for_template_class(hnc::copy_ptr<T>, class T)

#endif
