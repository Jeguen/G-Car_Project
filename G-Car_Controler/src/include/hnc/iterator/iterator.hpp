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


#ifndef HNC_ITERATOR_ITERATOR_HPP
#define HNC_ITERATOR_ITERATOR_HPP

#include <algorithm>


namespace hnc
{
	/**
	 * @brief Random access iterator
	 * 
	 * @code
	   #include <hnc/iterator.hpp>
	   @endcode
	 */
	template <class T, class Container>
	class iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	protected:

		/// Pointer to the data
		Container * p_data;

		/// Actual index
		std::size_t m_i;

	public:

		/**
		 * @brief Constructor
		 * 
		 * Iterator is on the first element
		 * 
		 * @param[in] c A Container<T>
		 * @param[in] i Index
		 */
		iterator(Container & c, std::size_t const i = 0) :
			p_data(&c),
			m_i((i < c.size()) ? (i) : (c.size()))
		{ }

		// All categories

		// Can be copied and copy-constructed
		// X b(a);
		// b = a;

		// -> Copy constructor and affectation operator are by default

		// Can be incremented
		// ++a
		// a++
		// *a++

		/// @brief Pre-incrementation of the iterator
		/// @return the iterator
		iterator & operator ++()
		{
			m_i = std::min(m_i + 1, p_data->size());
			return *this;
		}

		/// @brief Post-incrementation of the iterator
		/// @return a copy of the iterator before the incrementation
		iterator operator ++(int)
		{
			iterator copy = *this;
			++(*this);
			return copy;
		}

		// Input

		// Accepts equality/inequality comparisons
		// a == b
		// a != b

		/// @brief Equality operator
		/// @return true if operator are equals, else false
		bool operator ==(iterator const & it) const
		{
			return (p_data == it.p_data && m_i == it.m_i);
		}

		/// @brief Not equality operator
		/// @return true if operator are not equals, else false
		bool operator !=(iterator const & it) const
		{
			return (! ((*this) == it));
		}

		// Can be dereferenced as an rvalue
		// *a
		// a->m

		/// @brief Return the const element pointed by the iterator
		/// @return the const element pointed by the iterator
		T const & operator *() const
		{
			return ((*p_data)[m_i]);
		}

		/// @brief Return the const element pointed by the iterator
		/// @return the const element pointed by the iterator
		T const * operator ->() const
		{
			return (&((*p_data)[m_i]));
		}

		// Output

		// Can be dereferenced to be the left side of an assignment operation
		// *a = t
		// *a++ = t

		/// @brief Return the element pointed by the iterator
		/// @return the element pointed by the iterator
		T & operator *()
		{
			return ((*p_data)[m_i]);
		}

		/// @brief Return the element pointed by the iterator
		/// @return the element pointed by the iterator
		T * operator ->()
		{
			return (&((*p_data)[m_i]));
		}

		// Forward

		// Can be default-constructed
		// X a;
		// X()

		/// @brief Default constructor
		iterator() : p_data(nullptr), m_i(0) { }

		// Bidirectional

		// Can be decremented
		// --a
		// a--
		// *a--

		/// @brief Pre-decrementation of the iterator
		/// @return the iterator
		iterator & operator --()
		{
			if (m_i == 0) { m_i = p_data->size(); }
			else { --m_i; }
			return *this;
		}

		/// @brief Post-decrementation of the iterator
		/// @return a copy of the iterator before the incrementation
		iterator operator --(int)
		{
			iterator copy = *this;
			--(*this);
			return copy;
		}

		// Random Access

		// Supports arithmetic operators + and -
		// a + n
		// n + a
		// a - n
		// a - b

		/// @brief Operator +
		/// @param[in] n Number to add
		/// @return a copy of the iterator after operation
		iterator operator +(std::size_t const n) const
		{
			std::size_t i = m_i + n;
			if (i > p_data->size()) { i = p_data->size(); }
			return iterator(*p_data, i);
		}

		/// @brief Operator -
		/// @param[in] n Number to sub
		/// @return a copy of the iterator after operation
		iterator operator -(std::size_t const n) const
		{
			std::size_t i = m_i - n;
			if (i > p_data->size()) { i = p_data->size(); }
			return iterator(*p_data, i);
		}

		/// @brief Operator -
		/// @param[in] it Iterator
		/// @return the difference between the iterators
		typename iterator::difference_type operator -(iterator const & it) const
		{
			using diff_t = typename iterator::difference_type;
			return diff_t(m_i - it.m_i);
		}

		// Supports inequality comparisons (<, >, <= and >=) between iterators
		// a < b
		// a > b
		// a <= b
		// a >= b

		/// @brief < operator (iterator < it)
		/// @param[in] it Iterator for comparaison
		/// @return true the iterator < it, else false
		bool operator <(iterator const & it) const
		{
			if (p_data != it.p_data) { return p_data < it.p_data; }
			else { return m_i < it.m_i; }
		}

		/// @brief > operator (iterator > it)
		/// @param[in] it Iterator for comparaison
		/// @return true the iterator > it, else false
		bool operator >(iterator const & it) const
		{
			if (p_data != it.p_data) { return p_data > it.p_data; }
			else { return m_i > it.m_i; }
		}

		/// @brief <= operator (iterator <= it)
		/// @param[in] it Iterator for comparaison
		/// @return true the iterator <= it, else false
		bool operator <=(iterator const & it) const
		{
			if (p_data != it.p_data) { return p_data <= it.p_data; }
			else { return m_i <= it.m_i; }
		}

		/// @brief >= operator (iterator >= it)
		/// @param[in] it Iterator for comparaison
		/// @return true the iterator >= it, else false
		bool operator >=(iterator const & it) const
		{
			if (p_data != it.p_data) { return p_data >= it.p_data; }
			else { return m_i >= it.m_i; }
		}

		// Supports compound assignment operations += and -=
		// a += n
		// a -= n

		/// @brief Operator +=
		/// @param[in] n Number to add
		/// @return the iterator after operation
		iterator & operator +=(std::size_t const n)
		{
			m_i += n;
			if (m_i > p_data->size()) { m_i = p_data->size(); }
			return *this;
		}

		/// @brief Operator -=
		/// @param[in] n Number to sub
		/// @return the iterator after operation
		iterator & operator -=(std::size_t const n)
		{
			m_i -= n;
			if (m_i > p_data->size()) { m_i = p_data->size(); }
			return *this;
		}

		// Supports offset dereference operator ([])
		// a[n]

		/// @brief Return the const element pointed by the iterator
		/// @param[in] i Index to add
		/// @return the ith const element pointed by the iterator
		T const & operator[](std::size_t const i) const
		{
			return *(*this + i);
		}

		/// @brief Return the element pointed by the iterator
		/// @param[in] i Index to add
		/// @return the ith element pointed by the iterator
		T & operator[](std::size_t const i)
		{
			return *(*this + i);
		}
	};
}

#endif
