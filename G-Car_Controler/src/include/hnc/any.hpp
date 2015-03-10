// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_ANY_HPP
#define HNC_ANY_HPP

#include <iostream>
#include <typeinfo>

#include <hnc/clone.hpp>
#include <hnc/copy_and_swap.hpp>
#include <hnc/except.hpp>
#include <hnc/string.hpp>


namespace hnc
{
	/**
	 * @brief hnc::any_value_base
	 * 
	 * @code
	   @include <hnc/any.hpp>
	   @endcode
	 * 
	 * Base class for hnc::any_value<T>
	 */
	class any_value_base
	{
	public:
		
		/// @brief Destructor
		virtual ~any_value_base() { }
		
		hnc_generate_clone_member_function(hnc::any_value_base, hnc::any_value_base)
	};
	
	// Forward declaration of hnc::any
	class any;
	
	// Forward declaration of hnc::any_cast
	template <class cast_t>
	cast_t any_cast(hnc::any const & any);
	
	// Forward declaration of hnc::any_cast_ref
	template <class cast_t>
	cast_t const & any_cast_ref(hnc::any const & any);
	template <class cast_t>
	cast_t & any_cast_ref(hnc::any & any);
	
	/**
	 * @brief hnc::any_value
	 * 
	 * @code
	   @include <hnc/any.hpp>
	   @endcode
	 * 
	 * Type erasure for hnc::any
	 */
	template <class T>
	class any_value : public any_value_base
	{
	private:
		
		/// Data
		T m_value;
		
	public:
		
		/// @brief Constructor
		/// @param[in] value Value
		any_value(T const & value) : m_value(value) { }
		
		/// @brief Destructor
		virtual ~any_value() { }
		
		hnc_generate_clone_member_function(hnc::any_value_base, hnc::any_value<T>)
		
	public:
		
		/// @brief Declare function cast_t hnc::any_cast<cast_t>(hnc::any const & any) as a friend
		template <class cast_t>
		friend cast_t hnc::any_cast(hnc::any const & any);
		
		/// @brief Declare function cast_t const & hnc::any_cast_ref<cast_t>(hnc::any const & any) as a friend
		template <class cast_t>
		friend cast_t const & hnc::any_cast_ref(hnc::any const & any);
		
		/// @brief Declare function cast_t & hnc::any_cast_ref<cast_t>(hnc::any & any) as a friend
		template <class cast_t>
		friend cast_t & hnc::any_cast_ref(hnc::any & any);
	};
	
	/**
	 * @brief hnc::any
	 * 
	 * @code
	   @include <hnc/any.hpp>
	   @endcode
	 * 
	 * hnc::any can contain any type. To get the real type use hnc::any_cast function
	 * 
	 * http://alp.developpez.com/tutoriels/type-erasure/
	 */
	class any
	{
	private:
		
		any_value_base * p_value;
		
	public:
		
		/// @brief Default constructor
		any() : p_value(nullptr) { }
		
		/// @brief Constructor
		/// @param[in] value Value
		template <class T>
		any(T const & value) : p_value(new hnc::any_value<T>(value)) { }
		
		/// @brief Copy constructor
		/// @param[in] any Value in a hnc::any
		any(hnc::any const & any) : p_value((any.p_value == nullptr) ? nullptr : any.p_value->clone().release()) { }
		
		/// @brief Move constructor
		/// @param[in] any Value in a hnc::any
		any(hnc::any && any) : p_value(any.p_value) { any.p_value = nullptr; }
		
		/// @brief Destructor
		virtual ~any() { delete p_value; p_value = nullptr; }
		
		hnc_generate_copy_and_move_assignment(hnc::any)
		
		/// @brief Swap two hnc::any
		/// @param[in] any Value
		void swap(hnc::any & any)
		{
			std::swap(p_value, any.p_value);
		}
		
		/// @brief is empty?
		/// @return true if empty, false otherwise
		bool empty() const { return p_value == nullptr; }
		
		/// @brief is empty?
		/// @return true if empty, false otherwise
		std::type_info const & type() const { return (empty() ? typeid(void) : typeid(*p_value)); }
		
	public:
		
		/// @brief Declare function cast_t hnc::any_cast<cast_t>(hnc::any const & any) as a friend
		template <class cast_t>
		friend cast_t hnc::any_cast(hnc::any const & any);
		
		/// @brief Declare function cast_t const & hnc::any_cast_ref<cast_t>(hnc::any const & any) as a friend
		template <class cast_t>
		friend cast_t const & hnc::any_cast_ref(hnc::any const & any);
		
		/// @brief Declare function cast_t & hnc::any_cast_ref<cast_t>(hnc::any & any) as a friend
		template <class cast_t>
		friend cast_t & hnc::any_cast_ref(hnc::any & any);
	};
}

hnc_overload_std_swap_with_swap_member_function_for_class(hnc::any)


namespace hnc
{
	/**
	 * @brief Return a copy of the hnc::any in the real type
	 * 
	 * @code
	   @include <hnc/any.hpp>
	   @endcode
	 * 
	 * @param[in] any A hnc::any
	 * 
	 * @exception hnc::except::bad_cast if T is not the real type
	 *
	 * @return a copy of the hnc::any in the real type
	 */
	template <class T>
	T any_cast(hnc::any const & any)
	{
		auto const * const p = dynamic_cast<hnc::any_value<T> const *>(any.p_value);
		
		if (p == nullptr)
		{
			throw hnc::except::bad_cast("Can not cast hnc::any into "_s + typeid(T).name());
		}
		else
		{
			return p->m_value;
		}
	}
	
	/**
	 * @brief Return a reference to the hnc::any in the real type
	 * 
	 * @code
	   @include <hnc/any.hpp>
	   @endcode
	 * 
	 * @param[in] any A hnc::any
	 * 
	 * @exception hnc::except::bad_cast if T is not the real type
	 *
	 * @return a reference to the hnc::any in the real type
	 */
	template <class T>
	T const & any_cast_ref(hnc::any const & any)
	{
		auto const * const p = dynamic_cast<hnc::any_value<T> const *>(any.p_value);
		
		if (p == nullptr)
		{
			throw hnc::except::bad_cast("Can not cast hnc::any into "_s + typeid(T).name());
		}
		else
		{
			return p->m_value;
		}
	}
	
	/**
	 * @brief Return a const reference to the hnc::any in the real type
	 * 
	 * @code
	   @include <hnc/any.hpp>
	   @endcode
	 * 
	 * @param[in] any A hnc::any
	 * 
	 * @exception hnc::except::bad_cast if T is not the real type
	 *
	 * @return a const reference to the hnc::any in the real type
	 */
	template <class T>
	T & any_cast_ref(hnc::any & any)
	{
		auto * const p = dynamic_cast<hnc::any_value<T> *>(any.p_value);
		
		if (p == nullptr)
		{
			throw hnc::except::bad_cast("Can not cast hnc::any into type \""_s + typeid(T).name() + "\"");
		}
		else
		{
			return p->m_value;
		}
	}
}

#endif
