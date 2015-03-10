// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

// This file is part of Thōth.

// Thōth is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Thōth is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with Thōth. If not, see <http://www.gnu.org/licenses/>


#ifndef THOTH_SERIALIZATION_HPP
#define THOTH_SERIALIZATION_HPP

#include <cstdint>
#include <vector>

#include <hnc/int.hpp>

#include <SFML/Network.hpp>


namespace thoth
{
	/**
	 * @brief Serialization save archive with sf::Packet
	 * 
	 * @code
	   	#include <thoth/serialization.hpp>
	   @endcode
	 */
	class sfml_archive_save
	{
	public:
		
		/// Packet
		sf::Packet & packet;
		
		/// @brief Constructor
		/// @param[in] packet A sf::Packet
		sfml_archive_save(sf::Packet & packet) : packet(packet) { }
		
		/// @brief Operator& with a T
		/// @param[in] t a T
		/// @return the save archive
		template <class T>
		sfml_archive_save & operator&(T const & t)
		{
			packet << t;
			return *this;
		}
	};
	
	/**
	 * @brief Serialization load archive with sf::Packet
	 * 
	 * @code
	   	#include <thoth/serialization.hpp>
	   @endcode
	 */
	class sfml_archive_load
	{
	public:
		
		/// Packet
		sf::Packet & packet;
		
		/// @brief Constructor
		/// @param[in] packet A sf::Packet
		sfml_archive_load(sf::Packet & packet) : packet(packet) { }
		
		/// @brief Operator& with a T
		/// @param[out] t a T
		/// @return the load archive
		template <class T>
		sfml_archive_load & operator&(T & t)
		{
			packet >> t;
			return *this;
		}
	};
}

namespace sf
{
	/**
	 * @brief Operator<< between a sf::Packet and T
	 * 
	 * @code
	 	#include <thoth/serialization.hpp>
	 @endcode
	 * 
	 * @param[in] packet A sf::Packet
	 * @param[in] t      A T
	 * 
	 * @return the packet
	 */
	template <class T>
	sf::Packet & operator <<(sf::Packet & packet, T const & t)
	{
		thoth::sfml_archive_save archive(packet);
		t.serialize(archive);
		return packet;
	}
	
	// Specialization for long unsigned int
	inline sf::Packet & operator <<(sf::Packet & packet, long unsigned int const i)
	{
		packet << std::uint32_t(i);
		return packet;
	}
	
	// Specialization for std::vector
	template <class T>
	sf::Packet & operator <<(sf::Packet & packet, std::vector<T> const & v)
	{
		packet << std::uint32_t(v.size());
		for (T const & e : v)
		{
			packet << e;
		}
		return packet;
	}
	
	/**
	 * @brief Operator>> between a sf::Packet and T
	 * 
	 * @code
	 	#include <thoth/serialization.hpp>
	 @endcode
	 * 
	 * @param[in]  packet A sf::Packet
	 * @param[out] t      A T
	 * 
	 * @return the packet
	 */
	template <class T>
	sf::Packet & operator >>(sf::Packet & packet, T & t)
	{
		thoth::sfml_archive_load archive(packet);
		t.serialize(archive);
		return packet;
	}
	
	// Specialization for long unsigned int
	inline sf::Packet & operator >>(sf::Packet & packet, long unsigned int & i)
	{
		std::uint32_t tmp;
		packet >> tmp;
		i = hnc::luint_t(tmp);
		return packet;
	}
	
	// Specialization for std::vector
	template <class T>
	sf::Packet & operator >>(sf::Packet & packet, std::vector<T> & v)
	{
		std::uint32_t size;
		packet >> size;
		v.resize(std::size_t(size));
		for (T & e : v)
		{
			packet >> e;
		}
		return packet;
	}
}

#endif
