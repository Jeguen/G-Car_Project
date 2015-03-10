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


#ifndef HNC_OPTIONAL_HPP
#define HNC_OPTIONAL_HPP

#include <iostream>
#include <stdexcept>


namespace hnc
{
	/**
	 * @brief hnc::optional of T contains the value or not
	 * 
	 * @code
	   #include <hnc/optional.hpp>
	   @endcode
	 * 
	 * Even if the value is not present, the value exists with the default value. @n
	 * If you want not this, use hnc::optional_ptr of T
	 * 
	 * @note Consider std::optional (maybe for C++17) and boost::optional
	 */
	template <class T>
	class optional
	{
	private:
		
		/// True if value exists, false otherwise
		bool m_is_present;
		
		/// Value
		T m_value;
		
	public:
		
		/// @brief Constructor by default
		optional() : m_is_present(false), m_value() { }
		
		/// @brief Constructor
		/// @param[in] value Value
		optional(T const & value) : m_is_present(true), m_value(value) { }
		
		/// @brief Operator = with a hnc::optional<T>
		/// @param[in] optional A hnc::optional<T>
		hnc::optional<T> & operator =(hnc::optional<T> const & optional) = default;
		
		/// @brief Operator = with a T
		/// @param[in] value Value
		template <class U>
		hnc::optional<T> & operator =(U const & value)
		{
			m_is_present = true;
			m_value = value;
			
			return *this;
		}
		
		/// @brief Operator bool
		/// @return true is the value is present, false otherwise
		constexpr explicit operator bool() const { return m_is_present; }
		
		/// @brief Get the value
		/// @pre The value must be present
		/// @return the value
		T & value()
		{
			#ifndef NDEBUG
			if (m_is_present == false) { throw std::out_of_range("value is not present in hnc::optional<T>"); }
			#endif
			return m_value;
		}
		
		/// @brief Get const access to the value
		/// @pre The value must be present
		/// @return a const access to the value
		T const & value() const
		{
			#ifndef NDEBUG
			if (m_is_present == false) { throw std::out_of_range("value is not present in hnc::optional<T>"); }
			#endif
			return m_value;
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
	
	// Specialization for T &
	template <class T>
	class optional<T &>
	{
	private:
		
		bool m_is_present;
		
		typename std::remove_reference<T>::type m_default;
		
		T & m_value;
		
	public:
		
		// Only this constructor is different
		optional() : m_is_present(false), m_default(), m_value(m_default) { }
		
		optional(T const & value) : m_is_present(true), m_value(value) { }
		
		//hnc::optional<T> & operator =(hnc::optional<T> const & optional) = default;
		
		template <class U>
		hnc::optional<T> & operator =(U const & value)
		{
			m_is_present = true;
			m_value = value;
			
			return *this;
		}
		
		constexpr explicit operator bool() const { return m_is_present; }
		
		T & value()
		{
			#ifndef NDEBUG
			if (m_is_present == false) { throw std::out_of_range("value is not present in hnc::optional<T>"); }
			#endif
			return m_value;
		}
		
		T const & value() const
		{
			#ifndef NDEBUG
			if (m_is_present == false) { throw std::out_of_range("value is not present in hnc::optional<T>"); }
			#endif
			return m_value;
		}
		
		T & operator *() { return value(); }
		
		T const & operator *() const { return value(); }
		
		T * operator ->() { return &value(); }
		
		T const * operator ->() const { return &value(); }
	};
	
	/**
	 * @brief Operator == between two hnc::optional<T>
	 * 
	 * See http://en.cppreference.com/w/cpp/experimental/optional/operator_cmp from return
	 * 
	 * @param[in] optional_0 A hnc::optional<T>
	 * @param[in] optional_1 A hnc::optional<T>
	 * 
	 * @return true if the hnc::optional<T> are equal, false otherwise
	 */
	template <class T>
	bool operator ==(hnc::optional<T> const & optional_0, hnc::optional<T> const & optional_1)
	{
		if (&optional_0 == & optional_1) { return true; }
		
		if (bool(optional_0) != bool(optional_1)) { return false; }
		
		if (bool(optional_0) == false) { return true; }
		
		return *optional_0 == *optional_1;
	}
	
	/**
	 * @brief Operator == between a hnc::optional<T> and a bool
	 * 
	 * See http://en.cppreference.com/w/cpp/experimental/optional/operator_cmp from return
	 * 
	 * @param[in] optional A hnc::optional<T>
	 * @param[in] b        A bool
	 * 
	 * @return true if bool(hnc::optional<T>) and the bool are equal, false otherwise
	 */
	template <class T>
	bool operator ==(hnc::optional<T> const & optional, bool const b)
	{
		return bool(optional) == b;
	}
	
	/**
	 * @brief Operator != between two hnc::optional<T>
	 * 
	 * See http://en.cppreference.com/w/cpp/experimental/optional/operator_cmp from return
	 * 
	 * @param[in] optional_0 A hnc::optional<T>
	 * @param[in] optional_1 A hnc::optional<T>
	 * 
	 * @return true if the hnc::optional<T> are not equal, false otherwise
	 */
	template <class T>
	bool operator !=(hnc::optional<T> const & optional_0, hnc::optional<T> const & optional_1)
	{
		return ! (optional_0 == optional_1);
	}
	
	/**
	 * @brief Operator != between a hnc::optional<T> and a bool
	 * 
	 * See http://en.cppreference.com/w/cpp/experimental/optional/operator_cmp from return
	 * 
	 * @param[in] optional A hnc::optional<T>
	 * @param[in] b        A bool
	 * 
	 * @return true if bool(hnc::optional<T>) and the bool are not equal, false otherwise
	 */
	template <class T>
	bool operator !=(hnc::optional<T> const & optional, bool const b)
	{
		return ! (optional == b);
	}
	
	/// @brief Operator << between a std::ostream and a hnc::optional<T>
	/// @param[in,out] o        Output stream
	/// @param[in]     optional A hnc::optional<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator << (std::ostream & o, hnc::optional<T> const & optional)
	{
		if (optional) { o << "{ " << *optional << " }"; }
		else { o << "{}"; }
		
		return o;
	}
}

#endif
