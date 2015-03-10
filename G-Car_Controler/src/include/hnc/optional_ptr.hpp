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


#ifndef HNC_OPTIONAL_PTR_HPP
#define HNC_OPTIONAL_PTR_HPP

#include <iostream>

#include "copy_ptr.hpp"


namespace hnc
{
	/**
	 * @brief hnc::optional_ptr of T contains the value or not
	 * 
	 * @code
	   #include <hnc/optional_ptr.hpp>
	   @endcode
	 * 
	 * If the value is not present, the value does not exist. @n
	 * If you want not this, use hnc::optional of T
	 * 
	 * @note Consider std::optional (maybe for C++17) and boost::optional
	 */
	template <class T>
	class optional_ptr : private hnc::copy_ptr<T>
	{
	public:
		
		/// @brief Constructor by default
		optional_ptr() : hnc::copy_ptr<T>() { }
		
		/// @brief Constructor
		/// @param[in] value Value
		optional_ptr(T const & value) : hnc::copy_ptr<T>(hnc::clone_to_unique_ptr(value).release())
		{  }
		
		/// @brief Copy constrcutor
		/// @param[in] value Value
		optional_ptr(hnc::optional_ptr<T> const & value) :
			hnc::copy_ptr<T>((value) ? hnc::clone_to_unique_ptr(*value).release() : std::unique_ptr<T>().release())
		{ }
		
		/// @brief Operator = with a hnc::optional_ptr<T>
		/// @param[in] optional A hnc::optional_ptr<T>
		hnc::optional_ptr<T> & operator =(hnc::optional_ptr<T> const & optional) = default;
		
		/// @brief Operator = with a T
		/// @param[in] value Value
		template <class U>
		hnc::optional_ptr<T> & operator =(U const & value)
		{
			*this = hnc::optional_ptr<T>(value);
			return *this;
		}
		
		/// @brief Operator bool
		/// @return true is the value is present, false otherwise
		constexpr explicit operator bool() const { return hnc::copy_ptr<T>::operator bool(); }
		
		/// @brief Get the value
		/// @pre The value must be present
		/// @return the value
		T & value()
		{
			#ifndef NDEBUG
			if (bool(*this) == false) { throw std::out_of_range("value is not present in hnc::optional_ptr<T>"); }
			#endif
			return hnc::copy_ptr<T>::operator *();
		}
		
		/// @brief Get const access to the value
		/// @pre The value must be present
		/// @return a const access to the value
		T const & value() const
		{
			#ifndef NDEBUG
			if (bool(*this) == false) { throw std::out_of_range("value is not present in hnc::optional_ptr<T>"); }
			#endif
			return hnc::copy_ptr<T>::operator *();
		}
		
		/// @brief Get the value
		/// @pre The value must be present
		/// @return the value
		T & operator *() { return value(); }

		/// @brief Get const access to the value
		/// @pre The value must be present
		/// @return a const access to the value
		T const & operator *() const { return value(); }
		
		/// @brief Get the value
		/// @pre The value must be present
		/// @return the value
		T * operator ->() { return &value(); }

		/// @brief Get const access to the value
		/// @pre The value must be present
		/// @return a const access to the value
		T const * operator ->() const { return &value(); }
	};
	
	/**
	 * @brief Operator == between two hnc::optional_ptr<T>
	 * 
	 * See http://en.cppreference.com/w/cpp/experimental/optional/operator_cmp from return
	 * 
	 * @param[in] optional_0 A hnc::optional_ptr<T>
	 * @param[in] optional_1 A hnc::optional_ptr<T>
	 * 
	 * @return true if the hnc::optional_ptr<T> are equal, false otherwise
	 */
	template <class T>
	bool operator ==(hnc::optional_ptr<T> const & optional_0, hnc::optional_ptr<T> const & optional_1)
	{
		if (&optional_0 == & optional_1) { return true; }
		
		if (bool(optional_0) != bool(optional_1)) { return false; }
		
		if (bool(optional_0) == false) { return true; }
		
		return *optional_0 == *optional_1;
	}
	
	/**
	 * @brief Operator == between a hnc::optional_ptr<T> and a bool
	 * 
	 * See http://en.cppreference.com/w/cpp/experimental/optional/operator_cmp from return
	 * 
	 * @param[in] optional A hnc::optional_ptr<T>
	 * @param[in] b        A bool
	 * 
	 * @return true if bool(hnc::optional_ptr<T>) and the bool are equal, false otherwise
	 */
	template <class T>
	bool operator ==(hnc::optional_ptr<T> const & optional, bool const b)
	{
		return bool(optional) == b;
	}
	
	/**
	 * @brief Operator != between two hnc::optional_ptr<T>
	 * 
	 * See http://en.cppreference.com/w/cpp/experimental/optional/operator_cmp from return
	 * 
	 * @param[in] optional_0 A hnc::optional_ptr<T>
	 * @param[in] optional_1 A hnc::optional_ptr<T>
	 * 
	 * @return true if the hnc::optional_ptr<T> are not equal, false otherwise
	 */
	template <class T>
	bool operator !=(hnc::optional_ptr<T> const & optional_0, hnc::optional_ptr<T> const & optional_1)
	{
		return ! (optional_0 == optional_1);
	}
	
	/**
	 * @brief Operator != between a hnc::optional_ptr<T> and a bool
	 * 
	 * See http://en.cppreference.com/w/cpp/experimental/optional/operator_cmp from return
	 * 
	 * @param[in] optional A hnc::optional_ptr<T>
	 * @param[in] b        A bool
	 * 
	 * @return true if bool(hnc::optional_ptr<T>) and the bool are not equal, false otherwise
	 */
	template <class T>
	bool operator !=(hnc::optional_ptr<T> const & optional, bool const b)
	{
		return ! (optional == b);
	}
	
	/// @brief Operator << between a std::ostream and a hnc::optional_ptr<T>
	/// @param[in,out] o        Output stream
	/// @param[in]     optional A hnc::optional_ptr<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator << (std::ostream & o, hnc::optional_ptr<T> const & optional)
	{
		if (optional) { o << "{ " << *optional << " }"; }
		else { o << "{}"; }
		
		return o;
	}
}

#endif
