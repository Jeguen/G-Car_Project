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


#ifndef HNC_CLONE_HPP
#define HNC_CLONE_HPP

#include <memory>

#include "sfinae.hpp"
#include "unused.hpp"


namespace hnc
{
	/// @brief Type is not cloneable
	template <class T, class sfinae_valid_type = void>
	class is_cloneable : public std::false_type
	{ };
	
	/// @brief Type is cloneable
	template <class T>
	class is_cloneable<T, typename hnc::this_type<decltype(std::declval<T &>().clone())>::is_valid> : public std::true_type
	{ };
}

/**
 * @brief Generate .clone() member function
 *
 * This macro generate the .clone() const member function which return a std::unique_ptr of the base class
 *
 * @code
   class B
   {
   public:
   	virtual ~B() { }
   	hnc_generate_clone_member_function(B, B)
   };
   
   class D
   {
   public:
  	virtual ~D() { }
   	hnc_generate_clone_member_function(B, D)
   };
   @endcode
 *
 * @param[in] base_t    Type of the base class
 * @param[in] derived_t Type of the derived class
 *
 * @note Consider hnc::cloneable(base_t, derived_t) for template and inheritance solution
 */
#define hnc_generate_clone_member_function(base_t, derived_t) \
	virtual std::unique_ptr<base_t> clone() const \
	{ \
		return std::unique_ptr<base_t>(new derived_t(*this)); \
	}

namespace hnc
{
	/**
	 * @brief Base class for cloneable
	 *
	 * hnc::cloneable takes two template arguments: the base and the derived class
	 *
	 * Add a clone member function to the derived class
	 * @code
	   class B : public hnc::cloneable<B, B>
	   {
	   public:
	   	virtual ~B() { }
	   };
	 * @endcode
	 *
	 * @warning If the class have already a clone member function, you must specify which one to use
	 * @code
	   class D : public B, public hnc::cloneable<B, D>
	   {
	   public:
	   	virtual ~D() { }
	   	using hnc::cloneable<B, D>::clone();
	   };
	 * @endcode
	 *
	 * @note Consider hnc_generate_clone_member_function(base_t, derived_t) macro to generate .clone() member function
	 */
	template <class base_t, class derived_t>
	class cloneable
	{
	public:
		
		/// Destructor
		virtual ~cloneable() { }
		
		/// @brief Clone the derived_t object and return a base_t
		/// @return A std::unique_ptr of base_t
		virtual std::unique_ptr<base_t> clone() const
		{
			return std::unique_ptr<base_t>(new derived_t(*static_cast<derived_t const *>(this)));
		}
	};
}

namespace hnc
{
	/// @brief Clone the object with copy constructor
	/// @param[in] v   An object
	/// @param[in] tag std::false_type
	/// @return a clone of the object
	template <class T>
	T clone(T const & v, std::false_type const tag)
	{
		hnc_unused(tag);
		return T(v);
	}
	
	/// @brief Clone the object with .clone() member function
	/// @param[in] v   An object
	/// @param[in] tag std::true_type
	/// @return a clone of the object
	template <class T>
	auto clone(T const & v, std::true_type const tag) -> decltype(v.clone())
	{
		hnc_unused(tag);
		return v.clone();
	}
	
	/// @brief Clone the object
	/// @param[in] v An object
	/// @return a clone of the object
	template <class T>
	auto clone(T const & v) -> decltype(hnc::clone(v, hnc::is_cloneable<T>()))
	{
		return hnc::clone(v, hnc::is_cloneable<T>());
	}
}

namespace hnc
{
	/// @brief Clone the object with copy constructor
	/// @param[in] v   An object
	/// @param[in] tag std::false_type
	/// @return a clone of the object in a std::unique_ptr
	template <class T>
	std::unique_ptr<T> clone_to_unique_ptr(T const & v, std::false_type const tag)
	{
		hnc_unused(tag);
		return std::unique_ptr<T>(new T(v));
	}
	
	/// @brief Clone the object with .clone() member function
	/// @param[in] v   An object
	/// @param[in] tag std::true_type
	/// @return a clone of the object in a std::unique_ptr
	template <class T>
	auto clone_to_unique_ptr(T const & v, std::true_type const tag) -> decltype(v.clone())
	{
		hnc_unused(tag);
		return v.clone();
	}
	
	/// @brief Clone the object
	/// @param[in] v An object
	/// @return a clone of the object in a std::unique_ptr
	template <class T>
	auto clone_to_unique_ptr(T const & v) -> decltype(hnc::clone_to_unique_ptr(v, hnc::is_cloneable<T>()))
	{
		return hnc::clone_to_unique_ptr(v, hnc::is_cloneable<T>());
	}
}

#endif
