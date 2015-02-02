// Copyright © 2013, 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef HNC_CONTAINER_HPP
#define HNC_CONTAINER_HPP

#include <vector>
#include <type_traits>

#include "ostream_std.hpp"


// Pre-declare hnc::container for operator <<
namespace hnc
{
	template <class T>
	class container;
	
	// Declarate this function for hnc::container can be friend with
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::container<T> const & c);
}


namespace hnc
{
	
	/**
	 * @brief Basic container (encapsulate std::vector)
	 * 
	 * @code
	   #include <hnc/container.hpp>
	   @endcode
	 *
	 * hnc::container is like std::vector @n
	 * (You can create derivated class of hnc::container)
	 *
	 * http://www.cplusplus.com/reference/vector/vector/?kw=vector
	 * 
	 * @note It is a (almost) useless class! Use std::vector instead.
	 */
	template <class T>
	class container : private std::vector<T>
	{
	public:

		// Member types

		using typename std::vector<T>::value_type;

		using typename std::vector<T>::allocator_type;

		using typename std::vector<T>::reference;

		using typename std::vector<T>::const_reference;

		using typename std::vector<T>::pointer;

		using typename std::vector<T>::const_pointer;

		using typename std::vector<T>::iterator;

		using typename std::vector<T>::const_iterator;

		using typename std::vector<T>::reverse_iterator;

		using typename std::vector<T>::const_reverse_iterator;

		using typename std::vector<T>::difference_type;

		using typename std::vector<T>::size_type;

		// Member functions

		/// @brief Constructor with size and default value
		/// @param[in] size          Number of element in the container
		/// @param[in] default_value default_value for the element of the container
		explicit container(std::size_t const size = 0, T const & default_value = T()) :
			std::vector<T>(size, default_value)
		{ }

		/// @brief Copy constructor
		/// @param[in] c A hnc::container<T>
		container(container<T> const & c) :
			std::vector<T>(c.begin(), c.end())
		{ }

		/// @brief Constructor with input iterator
		/// @param[in] first Iterator of first element
		/// @param[in] last  Iterator of last element (not included)
		template
		<
			class input_iterator,
			class = typename std::iterator_traits<input_iterator>::iterator_category
		>
		container(input_iterator const & first, input_iterator const & last) :
			std::vector<T>(first, last)
		{ }

		/// @brief Constructor with std::vector
		/// @param[in] v A std::vector<T>
		container(std::vector<T> const & v) :
			std::vector<T>(v)
		{ }

		/// @brief Constructor with std::initializer_list
		/// @param[in] il A std::initializer_list<T>
		container(std::initializer_list<T> const & il) :
			std::vector<T>(il)
		{ }

		/// @brief Destructor
		virtual ~container() { }

		// Iterators

		using std::vector<T>::begin;

		using std::vector<T>::end;

		using std::vector<T>::rbegin;

		using std::vector<T>::rend;

		using std::vector<T>::cbegin;

		using std::vector<T>::cend;

		using std::vector<T>::crbegin;

		using std::vector<T>::crend;

		// Capacity

		using std::vector<T>::size;

		using std::vector<T>::max_size;

		using std::vector<T>::resize;

		using std::vector<T>::capacity;

		using std::vector<T>::empty;

		using std::vector<T>::reserve;

		using std::vector<T>::shrink_to_fit;

		// Element access

		using std::vector<T>::at;

		using std::vector<T>::operator[];

		using std::vector<T>::front;

		using std::vector<T>::back;

		using std::vector<T>::data;

		// Modifiers

		using std::vector<T>::assign;

		using std::vector<T>::push_back;

		using std::vector<T>::pop_back;

		using std::vector<T>::insert;

		using std::vector<T>::erase;

		using std::vector<T>::swap;

		using std::vector<T>::clear;

		using std::vector<T>::emplace;

		using std::vector<T>::emplace_back;

		// Allocator
		
		using std::vector<T>::get_allocator;

		// Operator == != < <= > >=

		/// @brief Equality test for each elements of two containers
		/// @return true if each element of the container are equals, else false
		bool operator ==(container<T> const & c) const
		{ return static_cast<std::vector<T>>(*this) == static_cast<std::vector<T>>(c); }

		/// @brief Inequality test for each elements of two containers
		/// @return true if one element of the container is not equals, else false
		bool operator !=(container<T> const & c) const
		{ return static_cast<std::vector<T>>(*this) != static_cast<std::vector<T>>(c); }

		/// @brief < test for each elements of two containers
		/// @return true if each element of the container are <, else false
		bool operator <(container<T> const & c) const
		{ return static_cast<std::vector<T>>(*this) < static_cast<std::vector<T>>(c); }

		/// @brief <= test for each elements of two containers
		/// @return true if each element of the container are <=, else false
		bool operator <=(container<T> const & c) const
		{ return static_cast<std::vector<T>>(*this) <= static_cast<std::vector<T>>(c); }

		/// @brief > test for each elements of two containers
		/// @return true if each element of the container are >, else false
		bool operator >(container<T> const & c) const
		{ return static_cast<std::vector<T>>(*this) > static_cast<std::vector<T>>(c); }

		/// @brief >= test for each elements of two containers
		/// @return true if each element of the container are >=, else false
		bool operator >=(container<T> const & c) const
		{ return static_cast<std::vector<T>>(*this) >= static_cast<std::vector<T>>(c); }

		// ostream

		/// @brief Declare operator << with std::ostream as a friend
		friend std::ostream & operator << <>(std::ostream & o, hnc::container<T> const & c);
	};
	
	/// @brief Operator << between a std::ostream and a hnc::container<T>
	/// @param[in,out] o Output stream
	/// @param[in]     c A hnc::container<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::container<T> const & c)
	{
		o << static_cast<std::vector<T>>(c);
		return o;
	}
}

#endif
