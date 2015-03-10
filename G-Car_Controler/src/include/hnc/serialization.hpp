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


#ifndef HNC_SERIALIZATION_HPP
#define HNC_SERIALIZATION_HPP

#include "boost_serialization_std.hpp"
#include "unused.hpp"
#include "sfinae.hpp"


// Forward declaration
namespace thoth
{
	class sfml_archive_save;
	class sfml_archive_load;
}


/**
 * @brief Generate .serialize() member functions
 *
 * This macro generate the .serialize() const and .serialize() member functions for Boost.Serialization
 *
 * @code
   	#include <hnc/serialization.hpp>
   @endcode
 *
 * @code
   class A
   {
   private:
   
   	std::string a;
   	std::string b;
   	std::string c;
   
   public:
   
   	hnc_generate_serialize_member_function(a, b, c)
   };
   @endcode
 */
#define hnc_generate_serialize_member_function(...) \
	\
	template <class archive_t> \
	void serialize(archive_t & archive, unsigned int const version = 0) const \
	{ \
		hnc::call_if_save_archive<archive_t>([&]() -> void { hnc::call_before_save_serialization_member_function_if_exist(*this); }); \
		hnc::call_if_load_archive<archive_t>([&]() -> void { hnc::call_before_load_serialization_member_function_if_exist(*this); }); \
		hnc::serialize(archive, version, __VA_ARGS__); \
		hnc::call_if_save_archive<archive_t>([&]() -> void { hnc::call_after_save_serialization_member_function_if_exist(*this); }); \
		hnc::call_if_load_archive<archive_t>([&]() -> void { hnc::call_after_load_serialization_member_function_if_exist(*this); }); \
	} \
	\
	template <class archive_t> \
	void serialize(archive_t & archive, unsigned int const version = 0) \
	{ \
		hnc::call_if_save_archive<archive_t>([&]() -> void { hnc::call_before_save_serialization_member_function_if_exist(*this); }); \
		hnc::call_if_load_archive<archive_t>([&]() -> void { hnc::call_before_load_serialization_member_function_if_exist(*this); }); \
		hnc::serialize(archive, version, __VA_ARGS__); \
		hnc::call_if_save_archive<archive_t>([&]() -> void { hnc::call_after_save_serialization_member_function_if_exist(*this); }); \
		hnc::call_if_load_archive<archive_t>([&]() -> void { hnc::call_after_load_serialization_member_function_if_exist(*this); }); \
	} \


namespace hnc
{
	// serialize
	
	/**
	 * @brief End of hnc::serialize function (do nothing)
	 * 
	 * @code
	   	#include <hnc/serialization.hpp>
	   @endcode
	 * 
	 * @param[in] archive Archive
	 * @param[in] version Version
	 */
	template <class archive_t>
	void serialize(archive_t & archive, unsigned int const version)
	{
		hnc_unused(archive);
		hnc_unused(version);
	}
	
	/**
	 * @brief hnc::serialize const function
	 * 
	 * @code
	   	#include <hnc/serialization.hpp>
	   @endcode
	 * 
	 * @param[in,out] archive Archive
	 * @param[in]     version Version
	 * @param[in]     t       A T
	 * @param[in]     args    Variadic template arguments list
	 */
	template <class archive_t, class T, class ... args_t>
	void serialize(archive_t & archive, unsigned int const version, T const & t, args_t const & ... args)
	{
		archive & t;
		hnc::serialize(archive, version, args...);
	}
	
	/**
	 * @brief hnc::serialize function
	 * 
	 * @code
	   	#include <hnc/serialization.hpp>
	   @endcode
	 * 
	 * @param[in,out] archive Archive
	 * @param[in]     version Version
	 * @param[out]    t       A T
	 * @param[out]    args    Variadic template arguments list
	 */
	template <class archive_t, class T, class ... args_t>
	void serialize(archive_t & archive, unsigned int const version, T & t, args_t & ... args)
	{
		archive & t;
		hnc::serialize(archive, version, args...);
	}
	
	// False archives
	
	namespace
	{
		/// @brief False save archive
		class false_save_archive_t
		{
		public:
			
			/// @brief Save t
			/// @param[in] t Object to be saved
			/// @return the false save archive
			template <class T>
			false_save_archive_t & operator&(T const & t) { hnc_unused(t); return *this; }
		};
		
		/// @brief False load archive
		class false_load_archive_t
		{
		public:
			
			/// @brief Load t
			/// @param[out] t Object to be loaded
			/// @return the false load archive
			template <class T>
			false_load_archive_t & operator&(T & t) { hnc_unused(t); return *this; }
		};
	}
	
	// Type traits on archives
	
	/// @brief Type is not a save archive
	template <class T>
	class is_save_archive : public std::false_type
	{ };
	
	/// @brief Type is not a load archive
	template <class T>
	class is_load_archive : public std::false_type
	{ };

	#ifndef hnc_no_boost_serialization
	
	/// @brief Type is a save archive
	template <>
	class is_save_archive<boost::archive::text_oarchive> : public std::true_type
	{ };
	
	/// @brief Type is a load archive
	template <>
	class is_load_archive<boost::archive::text_iarchive> : public std::true_type
	{ };
	
	#endif
	
	/// @brief Type is a save archive
	template <>
	class is_save_archive<hnc::false_save_archive_t> : public std::true_type
	{ };
	
	/// @brief Type is a load archive
	template <>
	class is_load_archive<hnc::false_load_archive_t> : public std::true_type
	{ };
	
	/// @brief Type is a save archive
	template <>
	class is_save_archive<thoth::sfml_archive_save> : public std::true_type
	{ };
	
	/// @brief Type is a load archive
	template <>
	class is_load_archive<thoth::sfml_archive_load> : public std::true_type
	{ };
	
	// Call fonction is save or load archive
	
	/// @brief Do not call the function
	/// @param[in] function Function to be called
	/// @param[in] tag      std::false_type
	template <class function_t>
	void call_if_save_archive(function_t const & function, std::false_type const tag)
	{
		hnc_unused(tag);
		hnc_unused(function);
	}
	
	/// @brief Call the function
	/// @param[in] function Function to be called
	/// @param[in] tag      std::true_type
	template <class function_t>
	void call_if_save_archive(function_t const & function, std::true_type const tag)
	{
		hnc_unused(tag);
		function();
	}
	
	/// @brief Call the function if save archive
	/// @param[in] function Function to be called
	template <class archive_t, class function_t>
	void call_if_save_archive(function_t const & function)
	{
		hnc::call_if_save_archive(function, hnc::is_save_archive<archive_t>());
	}
	
	/// @brief Do not call the function
	/// @param[in] function Function to be called
	/// @param[in] tag      std::false_type
	template <class function_t>
	void call_if_load_archive(function_t const & function, std::false_type const tag)
	{
		hnc_unused(tag);
		hnc_unused(function);
	}
	
	/// @brief Call the function
	/// @param[in] function Function to be called
	/// @param[in] tag      std::true_type
	template <class function_t>
	void call_if_load_archive(function_t const & function, std::true_type const tag)
	{
		hnc_unused(tag);
		function();
	}
	
	/// @brief Call the function if load archive
	/// @param[in] function Function to be called
	template <class archive_t, class function_t>
	void call_if_load_archive(function_t const & function)
	{
		hnc::call_if_load_archive(function, hnc::is_load_archive<archive_t>());
	}
	
	// have_serialize_member_function
	
	/// @brief Type does not have serialize member function
	template <class T, class sfinae_valid_type = void>
	class have_serialize_member_function : public std::false_type
	{ };
	
	/// @brief Type has serialize member function
	template <class T>
	class have_serialize_member_function<T, typename hnc::this_type<decltype(std::declval<T &>().serialize(std::declval<hnc::false_load_archive_t &>()))>::is_valid> : public std::true_type
	{ };
	
	// before_save_serialization
	
	/// @brief Type does not have the before_save_serialization const member function
	template <class T, class sfinae_valid_type = void>
	class have_before_save_serialization_member_function_const : public std::false_type
	{ };
	
	/// @brief Type has before_save_serialization const member function
	template <class T>
	class have_before_save_serialization_member_function_const<T, typename hnc::this_type<decltype(std::declval<T const &>().before_save_serialization())>::is_valid> : public std::true_type
	{ };
	
	/// @brief Do not call before_save_serialization const member function
	/// @param[in] t   Object without before_save_serialization const member function
	/// @param[in] tag std::false_type
	template <class T>
	void call_before_save_serialization_member_function_const_if_exist(T const & t, std::false_type const tag)
	{
		hnc_unused(tag);
		hnc_unused(t);
	}
	
	/// @brief Do not call before_save_serialization const member function
	/// @param[in] t   Object without before_save_serialization const member function
	/// @param[in] tag std::false_type
	template <class T>
	void call_before_save_serialization_member_function_const_if_exist(T const & t, std::true_type const tag)
	{
		hnc_unused(tag);
		t.before_save_serialization();
	}
	
	/// @brief Call before_save_serialization const member function if exist
	/// @param[in,out] t Object with or without before_save_serialization const member function
	template <class T>
	void call_before_save_serialization_member_function_const_if_exist(T const & t)
	{
		hnc::call_before_save_serialization_member_function_const_if_exist(t, hnc::have_before_save_serialization_member_function_const<T>());
	}
	
	/// @brief Type does not have the before_save_serialization member function
	template <class T, class sfinae_valid_type = void>
	class have_before_save_serialization_member_function : public std::false_type
	{ };
	
	/// @brief Type has before_save_serialization member function
	template <class T>
	class have_before_save_serialization_member_function<T, typename hnc::this_type<decltype(std::declval<T &>().before_save_serialization())>::is_valid> : public std::true_type
	{ };
	
	/// @brief Do not call before_save_serialization member function
	/// @param[in,out] t   Object without before_save_serialization member function
	/// @param[in]     tag std::false_type
	template <class T>
	void call_before_save_serialization_member_function_if_exist(T & t, std::false_type tag)
	{
		hnc_unused(tag);
		hnc_unused(t);
	}
	
	/// @brief Call before_save_serialization member function
	/// @param[in,out] t   Object with before_save_serialization member function
	/// @param[in]     tag std::true_type
	template <class T>
	void call_before_save_serialization_member_function_if_exist(T & t, std::true_type tag)
	{
		hnc_unused(tag);
		t.before_save_serialization();
	}
	
	/// @brief Call before_save_serialization member function if exist
	/// @param[in,out] t Object with or without before_save_serialization member function
	template <class T>
	void call_before_save_serialization_member_function_if_exist(T & t)
	{
		hnc::call_before_save_serialization_member_function_if_exist(t, hnc::have_before_save_serialization_member_function<T>());
	}
	
	// after_save_serialization
	
	/// @brief Type does not have the after_save_serialization const member function
	template <class T, class sfinae_valid_type = void>
	class have_after_save_serialization_member_function_const : public std::false_type
	{ };
	
	/// @brief Type has after_save_serialization const member function
	template <class T>
	class have_after_save_serialization_member_function_const<T, typename hnc::this_type<decltype(std::declval<T const &>().after_save_serialization())>::is_valid> : public std::true_type
	{ };
	
	/// @brief Do not call after_save_serialization const member function
	/// @param[in] t   Object without after_save_serialization const member function
	/// @param[in] tag std::false_type
	template <class T>
	void call_after_save_serialization_member_function_const_if_exist(T const & t, std::false_type const tag)
	{
		hnc_unused(tag);
		hnc_unused(t);
	}
	
	/// @brief Do not call after_save_serialization const member function
	/// @param[in] t   Object without after_save_serialization const member function
	/// @param[in] tag std::false_type
	template <class T>
	void call_after_save_serialization_member_function_const_if_exist(T const & t, std::true_type const tag)
	{
		hnc_unused(tag);
		t.after_save_serialization();
	}
	
	/// @brief Call after_save_serialization const member function if exist
	/// @param[in,out] t Object with or without after_save_serialization const member function
	template <class T>
	void call_after_save_serialization_member_function_const_if_exist(T const & t)
	{
		hnc::call_after_save_serialization_member_function_const_if_exist(t, hnc::have_after_save_serialization_member_function_const<T>());
	}
	
	/// @brief Type does not have the after_save_serialization member function
	template <class T, class sfinae_valid_type = void>
	class have_after_save_serialization_member_function : public std::false_type
	{ };
	
	/// @brief Type has after_save_serialization member function
	template <class T>
	class have_after_save_serialization_member_function<T, typename hnc::this_type<decltype(std::declval<T &>().after_save_serialization())>::is_valid> : public std::true_type
	{ };
	
	/// @brief Do not call after_save_serialization member function
	/// @param[in,out] t   Object without after_save_serialization member function
	/// @param[in]     tag std::false_type
	template <class T>
	void call_after_save_serialization_member_function_if_exist(T & t, std::false_type tag)
	{
		hnc_unused(tag);
		hnc_unused(t);
	}
	
	/// @brief Call after_save_serialization member function
	/// @param[in,out] t   Object with after_save_serialization member function
	/// @param[in]     tag std::true_type
	template <class T>
	void call_after_save_serialization_member_function_if_exist(T & t, std::true_type tag)
	{
		hnc_unused(tag);
		t.after_save_serialization();
	}
	
	/// @brief Call after_save_serialization member function if exist
	/// @param[in,out] t Object with or without after_save_serialization member function
	template <class T>
	void call_after_save_serialization_member_function_if_exist(T & t)
	{
		hnc::call_after_save_serialization_member_function_if_exist(t, hnc::have_after_save_serialization_member_function<T>());
	}
	
	// before_load_serialization
	
	/// @brief Type does not have the before_load_serialization const member function
	template <class T, class sfinae_valid_type = void>
	class have_before_load_serialization_member_function_const : public std::false_type
	{ };
	
	/// @brief Type has before_load_serialization const member function
	template <class T>
	class have_before_load_serialization_member_function_const<T, typename hnc::this_type<decltype(std::declval<T const &>().before_load_serialization())>::is_valid> : public std::true_type
	{ };
	
	/// @brief Do not call before_load_serialization const member function
	/// @param[in] t   Object without before_load_serialization const member function
	/// @param[in] tag std::false_type
	template <class T>
	void call_before_load_serialization_member_function_const_if_exist(T const & t, std::false_type const tag)
	{
		hnc_unused(tag);
		hnc_unused(t);
	}
	
	/// @brief Do not call before_load_serialization const member function
	/// @param[in] t   Object without before_load_serialization const member function
	/// @param[in] tag std::false_type
	template <class T>
	void call_before_load_serialization_member_function_const_if_exist(T const & t, std::true_type const tag)
	{
		hnc_unused(tag);
		t.before_load_serialization();
	}
	
	/// @brief Call before_load_serialization const member function if exist
	/// @param[in,out] t Object with or without before_load_serialization const member function
	template <class T>
	void call_before_load_serialization_member_function_const_if_exist(T const & t)
	{
		hnc::call_before_load_serialization_member_function_const_if_exist(t, hnc::have_before_load_serialization_member_function_const<T>());
	}
	
	/// @brief Type does not have the before_load_serialization member function
	template <class T, class sfinae_valid_type = void>
	class have_before_load_serialization_member_function : public std::false_type
	{ };
	
	/// @brief Type has before_load_serialization member function
	template <class T>
	class have_before_load_serialization_member_function<T, typename hnc::this_type<decltype(std::declval<T &>().before_load_serialization())>::is_valid> : public std::true_type
	{ };
	
	/// @brief Do not call before_load_serialization member function
	/// @param[in,out] t   Object without before_load_serialization member function
	/// @param[in]     tag std::false_type
	template <class T>
	void call_before_load_serialization_member_function_if_exist(T & t, std::false_type tag)
	{
		hnc_unused(tag);
		hnc_unused(t);
	}
	
	/// @brief Call before_load_serialization member function
	/// @param[in,out] t   Object with before_load_serialization member function
	/// @param[in]     tag std::true_type
	template <class T>
	void call_before_load_serialization_member_function_if_exist(T & t, std::true_type tag)
	{
		hnc_unused(tag);
		t.before_load_serialization();
	}
	
	/// @brief Call before_load_serialization member function if exist
	/// @param[in,out] t Object with or without before_load_serialization member function
	template <class T>
	void call_before_load_serialization_member_function_if_exist(T & t)
	{
		hnc::call_before_load_serialization_member_function_if_exist(t, hnc::have_before_load_serialization_member_function<T>());
	}
	
	// after_load_serialization
	
	/// @brief Type does not have the after_load_serialization const member function
	template <class T, class sfinae_valid_type = void>
	class have_after_load_serialization_member_function_const : public std::false_type
	{ };
	
	/// @brief Type has after_load_serialization const member function
	template <class T>
	class have_after_load_serialization_member_function_const<T, typename hnc::this_type<decltype(std::declval<T const &>().after_load_serialization())>::is_valid> : public std::true_type
	{ };
	
	/// @brief Do not call after_load_serialization const member function
	/// @param[in] t   Object without after_load_serialization const member function
	/// @param[in] tag std::false_type
	template <class T>
	void call_after_load_serialization_member_function_const_if_exist(T const & t, std::false_type const tag)
	{
		hnc_unused(tag);
		hnc_unused(t);
	}
	
	/// @brief Do not call after_load_serialization const member function
	/// @param[in] t   Object without after_load_serialization const member function
	/// @param[in] tag std::false_type
	template <class T>
	void call_after_load_serialization_member_function_const_if_exist(T const & t, std::true_type const tag)
	{
		hnc_unused(tag);
		t.after_load_serialization();
	}
	
	/// @brief Call after_load_serialization const member function if exist
	/// @param[in,out] t Object with or without after_load_serialization const member function
	template <class T>
	void call_after_load_serialization_member_function_const_if_exist(T const & t)
	{
		hnc::call_after_load_serialization_member_function_const_if_exist(t, hnc::have_after_load_serialization_member_function_const<T>());
	}
	
	/// @brief Type does not have the after_load_serialization member function
	template <class T, class sfinae_valid_type = void>
	class have_after_load_serialization_member_function : public std::false_type
	{ };
	
	/// @brief Type has after_load_serialization member_function
	template <class T>
	class have_after_load_serialization_member_function<T, typename hnc::this_type<decltype(std::declval<T &>().after_load_serialization())>::is_valid> : public std::true_type
	{ };
	
	/// @brief Do not call after_load_serialization member function
	/// @param[in,out] t   Object without after_load_serialization member function
	/// @param[in]     tag std::false_type
	template <class T>
	void call_after_load_serialization_member_function_if_exist(T & t, std::false_type tag)
	{
		hnc_unused(tag);
		hnc_unused(t);
	}
	
	/// @brief Call after_load_serialization member function
	/// @param[in,out] t   Object with after_load_serialization member function
	/// @param[in]     tag std::true_type
	template <class T>
	void call_after_load_serialization_member_function_if_exist(T & t, std::true_type tag)
	{
		hnc_unused(tag);
		t.after_load_serialization();
	}
	
	/// @brief Call after_load_serialization member function if exist
	/// @param[in,out] t Object with or without after_load_serialization member function
	template <class T>
	void call_after_load_serialization_member_function_if_exist(T & t)
	{
		hnc::call_after_load_serialization_member_function_if_exist(t, hnc::have_after_load_serialization_member_function<T>());
	}
}

#endif
