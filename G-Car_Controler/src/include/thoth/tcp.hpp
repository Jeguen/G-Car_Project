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


#ifndef THOTH_TCP_HPP
#define THOTH_TCP_HPP

#include <memory>
#include <functional>
#include <thread>

#include <hnc/unused.hpp>

#include <SFML/Network.hpp>

#include "serialization.hpp"


namespace thoth
{
	// Forward declaration
	class tcp_listener;
	
	/// @brief Operator << between a std::ostream and a sf::Socket::Status
	/// @param[in,out] o      Output stream
	/// @param[in]     status A sf::Socket::Status
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, sf::Socket::Status const status)
	{
		if (status == sf::Socket::Done)
		{
			o << "The socket has sent / received the data";
		}
		else if (status == sf::Socket::NotReady)
		{
			o << "The socket is not ready to send / receive data yet";
		}
		else if (status == sf::Socket::Disconnected)
		{
			o << "The TCP socket has been disconnected";
		}
		else if (status == sf::Socket::Error)
		{
			o << "An unexpected error happened";
		}
		
		return o;
	}
	
	/**
	 * @brief TCP socket
	 * 
	 * @code
	   #include <thoth/tcp.hpp>
	   @endcode
	 */
	class tcp
	{
	public:
		
		/// thoth::tcp_listener is friend
		friend class thoth::tcp_listener;
		
	private:
		
		/// Port
		unsigned short int m_port;
		
		/// TCP socket
		sf::TcpSocket m_socket;
		
		/// Function to be called after connection
		std::function<void (thoth::tcp & socket)> m_function;
		
		/// To run function
		std::thread m_thread;
		
	public:
		
		/// @brief Default constructor
		tcp() = default;
		
		/// @brief Constructor
		/// @param[in] ip       Ip of the server
		/// @param[in] port     Port of the server
		/// @param[in] function Function to be called after connection (nullptr by default)
		tcp
		(
			std::string const & ip, unsigned short int const port,
			std::function<void (thoth::tcp & socket)> function = nullptr
		) :
			m_port(port),
			m_socket(),
			m_function(function),
			m_thread
			(
				[&]() -> void
				{
					auto const r = m_socket.connect(sf::IpAddress(ip), m_port);
					
					if (r != sf::Socket::Done)
					{
						std::cerr << "thoth::tcp: " << r << std::endl;
						return;
					}
					
					if (m_function)
					{
						m_function(*this);
					}
				}
			)
		{ }
		
		/// @brief Destructor
		~tcp()
		{
			if (m_thread.joinable()) { m_thread.join(); }
			disconnect();
		}
		
		/// @brief Disconnect
		void disconnect() { m_socket.disconnect(); }
		
		/// @brief Send data
		/// @param[in] args Data
		template <class ... args_t>
		void send(args_t const & ... args)
		{
			sf::Packet packet;
			send(packet, args...);
		}
		
		/// @brief Receive data
		/// @param[in] args Data
		template <class ... args_t>
		void receive(args_t & ... args)
		{
			sf::Packet packet;
			m_socket.receive(packet);
			receive(packet, args...);
		}
		
	private:
		
		/// @brief Send data
		/// @param[in] packet Data
		void send(sf::Packet & packet)
		{
			m_socket.send(packet);
		}
		
		/// @brief Send data
		/// @param[in] packet Data
		/// @param[in] args   Data
		template <class T, class ... args_t>
		void send(sf::Packet & packet, T const & t, args_t const & ... args)
		{
			packet << t;
			send(packet, args...);
		}
		
		/// @brief Receive data (end of thoth::tcp::receive)
		/// @param[in] packet Data (unused in this method)
		void receive(sf::Packet & packet)
		{
			hnc_unused(packet);
		}
		
		/// @brief Receive data
		/// @param[in] packet Data
		/// @param[in] args   Data
		template <class T, class ... args_t>
		void receive(sf::Packet & packet, T & t, args_t & ... args)
		{
			packet >> t;
			receive(packet, args...);
		}
	};
	
	/**
	 * @brief TCP listener
	 * 
	 * @code
	   #include <thoth/tcp.hpp>
	   @endcode
	 */
	class tcp_listener
	{
	public:
		
		/// Port
		unsigned short int m_port;
		
		/// TCP listener
		sf::TcpListener m_listener;
		
		/// TCP sockets
		std::vector<std::unique_ptr<thoth::tcp>> m_sockets;
		
		/// Max number of connections
		std::size_t const m_max_connection;
		
		/// Function to be called for one connection
		std::function<void (thoth::tcp & socket)> m_function;
		
		/// To run functions
		std::vector<std::thread> m_threads;
		
		/// Can accept connection
		bool m_can_accept;
		
		/// To accept connections
		std::thread m_thread_accept;
		
	public:
		
		/// @brief Constructor
		/// @param[in] port           Port of the server
		/// @param[in] function       Function to be called for one connection (nullptr by default)
		/// @param[in] max_connection Max number of connections
		tcp_listener
		(
			unsigned short int const port,
			std::function<void (thoth::tcp & socket)> function = nullptr,
			std::size_t const max_connection = 1138
		) :
			m_port(port),
			m_listener(),
			m_sockets(),
			m_max_connection(max_connection),
			m_function(function),
			m_threads(),
			m_can_accept(true),
			m_thread_accept
			(
				[&]() -> void
				{
					auto const & r = m_listener.listen(m_port);
					if (r == sf::Socket::Done)
					{
						while (can_accept()) { accept(); }
					}
					else
					{
						std::cerr << "thoth::tcp_listener: " << r << std::endl;
					}
				}
			)
		{ }
		
		/// @brief Destructor
		~tcp_listener()
		{
			refuse_new_connection();
			
			m_thread_accept.join();
			
			for (auto & thread : m_threads) { thread.join(); }
			
			for (auto & socket : m_sockets) { socket->disconnect(); }
			
			m_listener.close();
		}
		
		/// @brief Can accept a new client?
		/// @return true if can accept a new client, false otherwise
		bool can_accept() const
		{
			return (m_can_accept && m_sockets.size() < m_max_connection);
		}
		
	private:
		
		/// @brief Accept one client and run the function
		void accept()
		{
			m_sockets.emplace_back(new thoth::tcp()); // TODO hnc::make_unique
			thoth::tcp & socket = *m_sockets.back();
			
			auto const r = m_listener.accept(socket.m_socket);
			
			if (r == sf::Socket::Done && m_can_accept)
			{
				if (m_function)
				{
					m_threads.emplace_back
					(
						[&]() -> void
						{
							m_function(socket);
						}
					);
				}
			}
			else
			{
				m_sockets.erase(m_sockets.end() - 1);
			}
		}
		
		/// @brief Refuse futur client
		void refuse_new_connection()
		{
			if (can_accept())
			{
				m_can_accept = false;
				thoth::tcp socket("127.0.0.1", m_port);
				socket.disconnect();
			}
		}
	};
}

#endif
