// Copyright © 2012 Lénaïc Bagnères, hnc@singularity.fr
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


#ifndef HNC_OSTREAM_STD_HPP
#define HNC_OSTREAM_STD_HPP

#include "ostreamable.hpp"


namespace std
{
	/// @brief Operator << between a std::ostream and a standard container like std::vector, std::list, std::set
	/// @param[in,out] o         Output stream
	/// @param[in]     container A standard container
	/// @return the output stream
	template <class T, template <class, class Alloc = std::allocator<T>> class container_t>
	std::ostream & operator <<(std::ostream & o, container_t<T> const & container)
	{
		hnc::print_std_container(o, container);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a std::array<T, N>
	/// @param[in,out] o     Output stream
	/// @param[in]     array A std::array<T, N>
	/// @return the output stream
	template <std::size_t N, class T>
	std::ostream & operator <<(std::ostream & o, std::array<T, N> const & array)
	{
		hnc::print_std_container(o, array);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a std::set<T>
	/// @param[in,out] o   Output stream
	/// @param[in]     set A std::set<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, std::set<T> const & set)
	{
		hnc::print_std_container(o, set);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a std::map<key_t, T>
	/// @param[in,out] o   Output stream
	/// @param[in]     map A std::map<key_t, T>
	/// @return the output stream
	template <class key_t, class T>
	std::ostream & operator <<(std::ostream & o, std::map<key_t, T> const & map)
	{
		hnc::print_std_container(o, map);
		return o;
	}
	
	/// @brief Operator << between a std::ostream and a std::tuple<T ...>
	/// @param[in,out] o     Output stream
	/// @param[in]     tuple A std::tuple<T ...>
	/// @return the output stream
	template <class ... T>
	std::ostream & operator <<(std::ostream & o, std::tuple<T ...> const & tuple)
	{
		hnc::print_tuple(o, tuple);
		return o;
	}
}

#endif
