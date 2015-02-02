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


#ifndef HNC_VALUE_PTR_HPP
#define HNC_VALUE_PTR_HPP

#include "copy_ptr.hpp"


namespace hnc
{
	/**
	 * @brief hnc::value_ptr<T> is like a T with inclusion polymorphism
	 * 
	 * @code
	   #include <hnc/value_ptr.hpp>
	   @endcode
	 * 
	 * hnc::value_ptr performs a deep copy; it uses hnc::clone function which uses [virtual] .clone() member function if it exists @n
	 * So, copy a hnc::value_ptr of base class which olds a derived class object works and does what you think
	 * 
	 * Example:
	 * @code
	   #include <iostream>
	   
	   #include <hnc/value_ptr.hpp>
	   
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
	   	// Create a A
	   	hnc::value_ptr<A> a = A();
	   	std::cout << a << std::endl; // one_A
	   	
	   	// Create a B
	   	hnc::value_ptr<A> b = B();
	   	std::cout << b << std::endl; // one_B
	   	
	   	// Copy
	   	hnc::value_ptr<A> c = b;
	   	std::cout << c << std::endl; // one_B
	   	
	   	return 0;
	   }
	   @endcode
	 */
	template <class T>
	class value_ptr : private hnc::copy_ptr<T>
	{
	public:
		
		/// @brief Default constructor
		value_ptr() : hnc::copy_ptr<T>(hnc::make_copy_ptr<T>())
		{ }
		
		/// @brief Constructor
		/// @param[in] value Value
		value_ptr(T const & value) : hnc::copy_ptr<T>(hnc::clone_to_unique_ptr(value).release())
		{ }
		
		/// @brief Copy constrcutor
		/// @param[in] value Value
		template <class U>
		value_ptr(hnc::value_ptr<U> const & value) : hnc::copy_ptr<T>(hnc::clone_to_unique_ptr(*value).release())
		{ }
		
		/// @brief Return the stored pointer
		/// @return the stored pointer
		using hnc::copy_ptr<T>::get;
		
		/// @brief Exchange the objects stored
		using hnc::copy_ptr<T>::swap;
		
		/// @brief Return a reference to the stored object
		/// @return a reference to the stored object
		using hnc::copy_ptr<T>::operator *;
		
		/// @brief Return a reference to the stored object to access of its members
		/// @return a reference to the stored object to access of its members
		using hnc::copy_ptr<T>::operator ->;
	};

	/// @brief Equality operator between two hnc::value_ptr<T>
	/// @param[in] v0 An hnc::value_ptr<T>
	/// @param[in] v1 An hnc::value_ptr<T>
	/// @return true if hnc::value_ptr<T> are equals, false otherwise
	template <class T>
	bool operator ==(hnc::value_ptr<T> const & v0, hnc::value_ptr<T> const & v1)
	{
		if (&v0 == &v1) { return true; }
		else { return (*v0 == *v1); }
	}

	/// @brief Inequality operator between two hnc::value_ptr<T>
	/// @param[in] v0 An hnc::value_ptr<T>
	/// @param[in] v1 An hnc::value_ptr<T>
	/// @return true if hnc::value_ptr<T> are not equals, false otherwise
	template <class T>
	bool operator !=(hnc::value_ptr<T> const & v0, hnc::value_ptr<T> const & v1)
	{
		return (!(v0 == v1));
	}
	
	/// @brief Operator << between a std::ostream and a hnc::value_ptr<T>
	/// @param[in,out] o     Output stream
	/// @param[in]     value A hnc::value_ptr<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::value_ptr<T> const & value)
	{
		o << *value;
		return o;
	}
}

/// @brief std::swap between two hnc::value_ptr
hnc_overload_std_swap_with_swap_member_function_for_template_class(hnc::value_ptr<T>, class T)

#endif
