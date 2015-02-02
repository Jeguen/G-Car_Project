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


#ifndef HNC_OSTREAMABLE_HPP
#define HNC_OSTREAMABLE_HPP

#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>


namespace hnc
{
	// std::vector, std::list, std::set (and default)
	
	/// @brief Wrapper to display objects with std::ostream
	/// @note See hnc::ostreamable
	template <class T>
	class ostreamable_t
	{
	public:
		
		/// Raw object
		T const & raw;
		
		/// @brief Constructor
		/// @param[in] raw Raw object
		ostreamable_t(T const & raw) : raw(raw) { }
	};
	
	/**
	 * @brief Create a hnc::ostreamable_t<T>
	 * 
	 * Exemple:
	 * @code
	   std::vector<std::string> v;
	   v.push_back("Hello");
	   v.push_back("new world!");
	   std::cout << hnc::ostreamable(v) << std::endl; // { Hello, new world! }
	   @endcode
	 */
	template <class T>
	hnc::ostreamable_t<T> ostreamable(T const & raw)
	{
		return hnc::ostreamable_t<T>(raw);
	}
	
	/// @brief Operator << between a std::ostream and a hnc::ostreamable_t<T>
	/// @param[in,out] o           Output stream
	/// @param[in]     ostreamable A hnc::ostreamable_t<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::ostreamable_t<T> const & ostreamable)
	{
		o << ostreamable.raw;
		return o;
	}
	
	namespace
	{
		/// @brief Print a standard container
		/// @param[in,out] o         Output stream
		/// @param[in]     container A container
		template <class container_t>
		void print_std_container(std::ostream & o, container_t const & container)
		{
			o << "{";
				
			for (auto const & e : container)
			{
				o << " " << e;
				if (&e != &(*container.crbegin())) { o << ","; }
			}
			
			o << " " << "}";
		}
		
		/// @brief Print a std::map<key_t, T>
		/// @param[in,out] o   Output stream
		/// @param[in]     map A std::map<key_t, T>
		template <class key_t, class T>
		void print_std_container(std::ostream & o, std::map<key_t, T> const & map)
		{
			o << "{";
			
			for (auto key_value_it = map.begin(); key_value_it != map.end(); ++key_value_it)
			{
				key_t const & key = key_value_it->first;
				T const & value = key_value_it->second;
				
				if (key_value_it != map.begin()) { o << ","; }
				o << " " << key << ": " << value;
			}
			
			o << " " << "}";
		}
	}
	
	/// @brief Operator << between a std::ostream and a hnc::ostreamable_t<std::vector<T>>
	/// @param[in,out] o           Output stream
	/// @param[in]     ostreamable A hnc::ostreamable_t<std::vector<T>>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::ostreamable_t<std::vector<T>> const & ostreamable)
	{
		hnc::print_std_container(o, ostreamable.raw);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a hnc::ostreamable_t<std::array<T, N>>
	/// @param[in,out] o           Output stream
	/// @param[in]     ostreamable A hnc::ostreamable_t<std::array<T, N>>
	/// @return the output stream
	template <std::size_t N, class T>
	std::ostream & operator <<(std::ostream & o, hnc::ostreamable_t<std::array<T, N>> const & ostreamable)
	{
		hnc::print_std_container(o, ostreamable.raw);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a hnc::ostreamable_t<std::list<T>>
	/// @param[in,out] o           Output stream
	/// @param[in]     ostreamable A hnc::ostreamable_t<std::list<T>>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::ostreamable_t<std::list<T>> const & ostreamable)
	{
		hnc::print_std_container(o, ostreamable.raw);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a hnc::ostreamable_t<std::set<T>>
	/// @param[in,out] o           Output stream
	/// @param[in]     ostreamable A hnc::ostreamable_t<std::set<T>>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::ostreamable_t<std::set<T>> const & ostreamable)
	{
		hnc::print_std_container(o, ostreamable.raw);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a hnc::ostreamable_t<std::map<key_t, T>>
	/// @param[in,out] o           Output stream
	/// @param[in]     ostreamable A hnc::ostreamable_t<std::map<key_t, T>>
	/// @return the output stream
	template <class key_t, class T>
	std::ostream & operator <<(std::ostream & o, hnc::ostreamable_t<std::map<key_t, T>> const & ostreamable)
	{
		hnc::print_std_container(o, ostreamable.raw);
		return o;
	}
	
	// std::tuple
	
	/// @brief Wrapper to display std::tuple with std::ostream
	/// @note See hnc::ostreamable
	template <class ... T>
	class ostreamable_tuple_t
	{
	public:
		
		/// Raw object
		std::tuple<T ...> const & tuple;
		
		/// @brief Constructor from std::tuple
		/// @param[in] tuple A tuple
		ostreamable_tuple_t(std::tuple<T ...> const & tuple) : tuple(tuple) { }
	};
	
	/**
	 * @brief Create a hnc::ostreamable_tuple_t<T>
	 * 
	 * Exemple:
	 * @code
	   auto t = std::make_tuple(std::string("string"), 21, 42, 73, 'c', 3.14);
	   std::cout << hnc::ostreamable(t) << std::endl; // (string, 21, 42, 73, c, 3.14)
	   @endcode
	 */
	template <class ... T>
	hnc::ostreamable_tuple_t<T ...> ostreamable(std::tuple<T ...> const & tuple)
	{
		return hnc::ostreamable_tuple_t<T ...>(tuple);
	}
	
	namespace
	{
		/// @brief Compile-time counter
		template <std::size_t>
		class static_int_counter_ostreamable { };

		/// @brief Print element n of a tuple_t
		/// @param[in,out] o     Output stream
		/// @param[in]     tuple Tuple
		template <class tuple_t, std::size_t n>
		void print_tuple(std::ostream & o, tuple_t const & tuple, static_int_counter_ostreamable<n>)
		{
			print_tuple(o, tuple, static_int_counter_ostreamable<n - 1>());
			o << ", " << std::get<n>(tuple);
		}

		/// @brief Print last element of a tuple_t
		/// @param[in,out] o     Output stream
		/// @param[in]     tuple Tuple
		template <class tuple_t>
		void print_tuple(std::ostream & o, tuple_t const & tuple, static_int_counter_ostreamable<0>)
		{
			o << std::get<0>(tuple);
		}

		/// @brief Print a std::tuple<T ...>
		/// @param[in,out] o     Output stream
		/// @param[in]     tuple A std::tuple<T ...>
		template <class ... T>
		void print_tuple(std::ostream & o, std::tuple<T ...> const & tuple)
		{
			o << "(";
			hnc::print_tuple(o, tuple, static_int_counter_ostreamable<sizeof...(T) - 1>());
			o << ")";
		}
	}
	
	/// @brief Operator << between a std::ostream and a hnc::ostreamable_tuple_t<T ...>
	/// @param[in,out] o           Output stream
	/// @param[in]     ostreamable A hnc::ostreamable_tuple_t<T ...>
	/// @return the output stream
	template <class ... T>
	std::ostream & operator <<(std::ostream & o, hnc::ostreamable_tuple_t<T ...> const & ostreamable)
	{
		hnc::print_tuple(o, ostreamable.tuple);
		return o;
	}
}

namespace std
{
	
}

#endif
