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


#ifndef HNC_VIEW_PTR_HPP
#define HNC_VIEW_PTR_HPP

#include <iostream>


namespace hnc
{
	/**
	 * @brief hnc::view_ptr is like std::reference_wrapper but it can be nullptr
	 * 
	 * @code
	   #include <hnc/view_ptr.hpp>
	   @endcode
	 */
	template <class T>
	class view_ptr
	{
	public:
		
		/// Pointer to object
		T * m_ptr;
		
	public:
		
		/// @brief Default constructor
		view_ptr() : m_ptr(nullptr) { }
		
		/// @brief Constructor
		view_ptr(T & t) : m_ptr(&t) { }
		
		/// @brief Return the stored pointer
		/// @pre The pointer is not nullptr
		/// @return the stored pointer
		T const & get() const { return *m_ptr; }
		
		/// @brief Return the stored pointer
		/// @pre The pointer is not nullptr
		/// @return the stored pointer
		T & get() { return *m_ptr; }
		
		/// @brief Return true if the pointer is not empty, false otherwise
		/// @return true if the pointer is not empty, false otherwise
		operator bool() const { return m_ptr != nullptr; }
		
		/// @brief Return a reference to the stored object
		/// @pre The pointer is not nullptr
		/// @return a reference to the stored object
		T const & operator *() const { return *m_ptr; }
		
		/// @brief Return a reference to the stored object
		/// @pre The pointer is not nullptr
		/// @return a reference to the stored object
		T & operator *() { return *m_ptr; }
		
		/// @brief Return a reference to the stored object to access of its members
		/// @pre The pointer is not nullptr
		/// @return a reference to the stored object to access of its members
		T const * operator ->() const { return m_ptr; }
		
		/// @brief Return a reference to the stored object to access of its members
		/// @pre The pointer is not nullptr
		/// @return a reference to the stored object to access of its members
		T * operator ->() { return m_ptr; }
	};
	
	/// @brief Operator << between a std::ostream and a hnc::view_ptr<T>
	/// @param[in,out] o Output stream
	/// @param[in]     p A hnc::view_ptr<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator << (std::ostream & o, hnc::view_ptr<T> const & p)
	{
		if (p) { o << *p; }
		else { o << "nullptr"; }
		return o;
	}
}

#endif
