// Copyright © 2012, 2014 Lénaïc Bagnères, hnc@singularity.fr

// This file is part of hnc.

// hnc is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// hnc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with hnc. If not, see <http://www.gnu.org/licenses/>


#ifndef HNC_MPI_FUTURE_HPP
#define HNC_MPI_FUTURE_HPP


#include <future>
#include <stdexcept>

#ifndef hnc_no_boost_mpi
	#include <boost/mpi.hpp>
#endif

#include "../boost_serialization_std.hpp"
#include "../unused.hpp"


namespace hnc
{
	namespace mpi
	{
		namespace
		{
			/// MPI tag for the functor
			int const tag_functor = 0;
		}

		/**
		 * @brief Base class to send functor to a slave with a hnc::mpi::future
		 *
		 * @code
		   #include <hnc/mpi/future.hpp>
		   @endcode
		 * 
		 * To send a function to a hnc::mpi::future slave, you need derivate this class
		 * 
		 * @pre
		 * Your class must:
		 * - be serializable with Boost Serialization http://www.boost.org/doc/libs/release/libs/serialization/ (friend class boost::serialization::access, serialize function, default constructor)
		 * - have result_t type
		 * - have "result_t move_result()" function (possible implementation is "return std::move(your_result_data_member);")
		 * - have "void get(int const tag_result) override const" function (possible implementation is "send_result(your_result_data_member, tag_result);")
		 * - have "void operator()() override" function (contains the computation)
		 * You must BOOST_CLASS_EXPORT your class
		 *
		 * @note You can use the hnc_no_boost_serialization define if you want compile without Boost Serialization (and without Boost MPI)
		 *
		 * Exemple: no data member, no return
		 * @code
		   // Just a display, no return
		   // You need override the operator()
		   class remote_compute_display : public hnc::mpi::functor
		   {
		   public:
		   
		   	// Function
		   	void operator()() override
		   	{
		   		std::cout << "remote_compute_display\n";
		   	}
		   
		   private:
		   
		   	#ifndef hnc_no_boost_serialization
		   
		   	friend class boost::serialization::access;
		   
		   	template<class Archive>
		   	void serialize(Archive & ar, unsigned int const) // unsigned int const version
		   	{
		   		ar & boost::serialization::base_object<hnc::mpi::functor>(*this);
		   	}
		   
		   	#endif
		   };
		   
		   #ifndef hnc_no_boost_serialization
		   BOOST_CLASS_EXPORT(remote_compute_display)
		   #endif
		   @endcode
		 *
		 * Exemple: no data member, return a int
		   @code
		   // Compute a int
		   // You need:
		   //   - have result_t type
		   //   - override the operator()
		   //   - overload "result_t move_result()" to send your result with std::move
		   class remote_compute_int : public hnc::mpi::functor
		   {
		   public:
		   
		   	// Result type
		   	using result_t = int;
		   
		   private:
		   
		   	// Result
		   	result_t r;
		   
		   public:
		   
		   	// Function
		   	void operator()() override
		   	{
		   		std::cout << "remote_compute_int\n";
		   		r = 21 * 42 * 73;
		   	}
		   
		   	// Return the result with std::move
		   	result_t move_result() { return std::move(r); }
		   
		   	// Send the result with send_result(T)
		   	void get(int const tag_result) const override { send_result(r, tag_result); }
		   
		   private:
		   
		   	#ifndef hnc_no_boost_serialization
		   
		   	friend class boost::serialization::access;
		   
		   	template<class Archive>
		   	void serialize(Archive & ar, unsigned int const) // unsigned int const version
		   	{
		   		ar & boost::serialization::base_object<hnc::mpi::functor>(*this);
		   		ar & r;
		   	}
		   
		   	#endif
		   };
		   
		   #ifndef hnc_no_boost_serialization
		   BOOST_CLASS_EXPORT(remote_compute_int)
		   #endif
		 * @endcode
		 *
		 * Exemple: one int data member, return factorial n
		 * @code
		   // Compute factorial n
		   // You need:
		   //   - have result_t type
		   //   - override the operator()
		   //   - overload "result_t move_result()" to send your result with std::move
		   //   - default constructor (for Boost Serialization)
		   class remote_compute_factorial : public hnc::mpi::functor
		   {
		   public:
		   
		   	// Result type
		   	using result_t = int;
		   
		   private:
		   
		   	// !n
		   	unsigned int n;
		   
		   	// Result
		   	result_t r;
		   
		   public:
		   
		   	// Constructor take n and initizialize the result
		   	remote_compute_factorial(unsigned int const n) : n(n), r(1) { }
		   
		   	// Function
		   	void operator()() override
		   	{
		   		std::cout << "remote_compute_factorial " + hnc::to_string(n) + "\n";
		   		for (unsigned int i = 2; i <= n; i++)
		   		{
		   			r *= i;
		   		}
		   	}
		   
		   	// Return the result with std::move
		   	result_t move_result() { return std::move(r); }
		   
		   	// Send the result with send_result(T)
		   	void get(int const tag_result) const override { send_result(r, tag_result); }
		   
		   private:
		   
		   	#ifndef hnc_no_boost_serialization
		   
		   	friend class boost::serialization::access;
		   
		   	// Boost Serialization need default constructor
		   	remote_compute_factorial() : n(0), r(1) { }
		   
		   	template<class Archive>
		   	void serialize(Archive & ar, unsigned int const) // unsigned int const version
		   	{
		   		ar & boost::serialization::base_object<hnc::mpi::functor>(*this);
		   		ar & n;
		   		ar & r;
		   	}
		   
		   	#endif
		   };
		   
		   #ifndef hnc_no_boost_serialization
		   BOOST_CLASS_EXPORT(remote_compute_factorial)
		   #endif
		   @endcode
		 *
		 * Exemple: one vector data member, return the sum of the vector
		 * @code
		   // Compute the sum of the std::vector
		   // You need:
		   //   - have result_t type
		   //   - override the operator()
		   //   - overload "result_t move_result()" to send your result with std::move
		   //   - default constructor (for Boost Serialization)
		   class remote_compute_vector_sum : public hnc::mpi::functor
		   {
		   public:
		   
		   	// Result type
		   	using result_t = int;
		   
		   private:
		   
		   	// vector
		   	std::vector<int> v;
		   
		   	// Result
		   	result_t sum;
		   
		   public:
		   
		   	// Constructor take n and initizialize the result
		   	remote_compute_vector_sum(std::vector<int> const & v) : v(v), sum(0) { }
		   
		   	// Function
		   	void operator()() override
		   	{
		   		std::cout << "remote_compute_vector_sum " + hnc::to_string(v) + "\n";
		   		for (int const e : v)
		   		{
		   			sum += e;
		   		}
		   	}
		   
		   	// Return the result with std::move
		   	result_t move_result() { return std::move(sum); }
		   
		   	// Send the result with send_result(T)
		   	void get(int const tag_result) const override { send_result(sum, tag_result); }
		   
		   private:
		   
		   	#ifndef hnc_no_boost_serialization
		   
		   	friend class boost::serialization::access;
		   
		   	// Boost Serialization need default constructor
		   	remote_compute_vector_sum() : sum(0) { }
		   
		   	template<class Archive>
		   	void serialize(Archive & ar, unsigned int const) // unsigned int const version
		   	{
		   		ar & boost::serialization::base_object<hnc::mpi::functor>(*this);
		   		ar & v;
		   		ar & sum;
		   	}
		   
		   	#endif
		   };
		   
		   #ifndef hnc_no_boost_serialization
		   BOOST_CLASS_EXPORT(remote_compute_vector_sum)
		   #endif
		   @endcode
		 */
		class functor
		{
		public:

			/// Type of result (sent by get)
			using result_t = void;

			/// @brief Destructor
			virtual ~functor() { }

			/// @brief Operator() contains the function for the remote thread
			virtual void operator()() { }

			#ifndef hnc_no_boost_mpi
			/// @brief Generic function to send a result to master
			/// @param[in] r          Send the result to the master (by Boost MPI with 1 as tag)
			/// @param[in] tag_result MPI tag result
			template <class T>
			static void send_result(T const & r, int const tag_result)
			{
				boost::mpi::communicator world;
				world.send(0, tag_result, r);
			}
			#else
			template <class T>
			static void send_result(T const & /*r*/, int const tag_result)
			{
				hnc_unused(tag_result);
			}
			#endif

			/**
			 * @brief Return the result with std::move
			 * 
			 * If you want return something:
			 * @code
			   return std::move(your_result_data_member);
			   @endcode
			 * @return the result with std::move
			 */
			result_t move_result() { }

			/**
			 * @brief Send the result
			 * 
			 * @param[in] tag_result MPI tag result
			 * 
			 * If you want send the result:
			 * @code
			   send_result(your_result_data_member, tag_result);
			   @endcode
			 */
			virtual void get(int const tag_result) const
			{
				hnc_unused(tag_result);
			}

			/// @brief Return true if shutdown the node after execute the function
			/// @return true if shutdown the node after execute the function
			virtual bool stop() const { return false; }

		private:

			#ifndef hnc_no_boost_serialization
			
			/// Boost serialization access
			friend class boost::serialization::access;

			/// Boost serialization
			template<class Archive>
			void serialize(Archive & /*ar*/, unsigned int const /*version*/) { }
			
			#endif
		};

		namespace
		{
			/**
			 * @brief Final functor to end MPI environment
			 * 
			 * @code
			   #include <hnc/mpi.hpp>
			   @endcode
			 */
			class final_functor : public hnc::mpi::functor
			{
			public:

				/// @copydoc hnc::mpi::functor::stop()
				virtual bool stop() const { return true; }

			private:

				#ifndef hnc_no_boost_serialization

				/// Boost serialization access
				friend class boost::serialization::access;

				/// Boost serialization
				template<class Archive>
				void serialize(Archive & ar, unsigned int const /*version*/)
				{
					ar & boost::serialization::base_object<hnc::mpi::functor>(*this);
				}

				#endif
			};
		}

		/**
		 * @brief Provides a mechanism to access the result of remote (MPI) operations
		 *
		 * @code
		   #include <hnc/mpi/future.hpp>
		   @endcode
		 *
		 * hnc::mpi::future take a hnc::mpi::functor and a processor id. The remote processor compute the functor. The result is available once by get member function.
		 *
		 * @pre The MPI environment is set @n
		 * You can use hnc::mpi::environment
		 *
		 * You can get the number of processor
		 * @code
		   boost::mpi::communicator world;
		   world.size();
		 * @endcode
		 *
		 * Minimal exemple:
		 * @code
		   #include <iostream>
		   
		   #include <hnc/mpi/future.hpp>
		   
		   
		   // Just a display, no return
		   // You need override the operator()
		   class remote_compute_display : public hnc::mpi::functor
		   {
		   public:
		  
		   	// Function
		   	void operator()() override
		   	{
		   		std::cout << "remote_compute_display\n";
		   	}
		  
		   private:
		  
		   	#ifndef hnc_no_boost_serialization
		  
		   	friend class boost::serialization::access;
		  
		   	template<class Archive>
		   	void serialize(Archive & ar, unsigned int const) // unsigned int const version
		   	{
		   		ar & boost::serialization::base_object<hnc::mpi::functor>(*this);
		   	}
		  
		   	#endif
		   };
		  
		   #ifndef hnc_no_boost_serialization
		   BOOST_CLASS_EXPORT(remote_compute_display)
		   #endif
		   
		   
		   #ifndef hnc_no_boost_mpi
		   int main(int argc, char * argv[])
		   #else
		   int main()
		   #endif
		   {
		   	int nb_test = 0;
		   
		   	#ifndef hnc_no_boost_mpi
		   	hnc_mpi_environment(env);
		   	#endif
		   
		   	// Display on processor 1
		   	remote_compute_display functor;
		   	hnc::mpi::future<void> f(functor, 1);
		   
		   	return 0;
		   }
		   @endcode
		 *
		 * Exemple: sum of a std::vector
		 * @code
		   #include <iostream>
		   #include <vector>
		  
		   #include <hnc/mpi/future.hpp>
		  
		   
		   // Compute the sum of the std::vector
		   // You need:
		   //   - have result_t type
		   //   - override the operator()
		   //   - overload "result_t move_result()" to send your result with std::move
		   //   - default constructor (for Boost Serialization)
		   class remote_compute_vector_sum : public hnc::mpi::functor
		   {
		   public:
		  
		   	// Result type
		   	using result_t = int;
		  
		   private:
		  
		   	// vector
		   	std::vector<int> v;
		  
		   	// Result
		   	result_t sum;
		  
		   public:
		  
		   	// Constructor take n and initizialize the result
		   	remote_compute_vector_sum(std::vector<int> const & v) : v(v), sum(0) { }
		  
		   	// Function
		   	void operator()() override
		   	{
		   		std::cout << "remote_compute_vector_sum " + hnc::to_string(v) + "\n";
		   		for (int const e : v)
		   		{
		   			sum += e;
		   		}
		   	}
		  
		   	// Return the result with std::move
		   	result_t move_result() { return std::move(sum); }
		  
		   	// Send the result with send_result(T)
		   	void get(int const tag_result) const override { send_result(sum, tag_result); }
		  
		   private:
		  
		   	#ifndef hnc_no_boost_serialization
		  
		   	friend class boost::serialization::access;
		  
		   	// Boost Serialization need default constructor
		   	remote_compute_vector_sum() : sum(0) { }
		  
		   	template<class Archive>
		   	void serialize(Archive & ar, unsigned int const) // unsigned int const version
		   	{
		   		ar & boost::serialization::base_object<hnc::mpi::functor>(*this);
		   		ar & v;
		   		ar & sum;
		   	}
		  
		   	#endif
		   };
		  
		   #ifndef hnc_no_boost_serialization
		   BOOST_CLASS_EXPORT(remote_compute_vector_sum)
		   #endif
		  
		  
		   #ifndef hnc_no_boost_mpi
		   int main(int argc, char * argv[])
		   #else
		   int main()
		   #endif
		   {
		   	int nb_test = 0;
		  
		   	#ifndef hnc_no_boost_mpi
		   	hnc_mpi_environment(env);
		   	#endif
		  
		   	// Compute the sum of the vector on processor 1
		   	remote_compute_vector_sum functor({21, 11, 5, 3, 1, 1});
		   	hnc::mpi::future<int> f(functor, 1);
		   	int sum = f.get();
		   	std::cout << "Sum = " << sum << std::endl;
		  
		   	return 0;
		   }
		   @endcode
		 *
		 * @note If you use processor 0 (master), the computation is made in a std::future.
		 *
		 * @note If you compile with hnc_no_boost_mpi define, your code use std::future and you have a multi-thread program instead of a multi-processor program.
		 */
		template <class result_t>
		class future
		{
		private:

			#ifndef hnc_no_boost_mpi
			
			/// Boost communicator
			boost::mpi::communicator m_world;

			#endif

			/// Rank of slave
			int const m_id_proc;

			/// Bool to know if the result is already getted
			bool m_done;

			/// MPI tag result
			int m_tag_result;

			/// Thread for master
			std::future<result_t> m_future_master;

		public:

			#ifndef hnc_no_boost_mpi

			/// @brief Constructor
			/// @param[in,out] f       Functor objet derived of hnc::mpi::functor
			/// @param[in]     id_proc Id (rank) of the process (id_proc % number of process is used)
			template <class F>
			future(F & f, int const id_proc) : m_id_proc(id_proc % m_world.size()), m_done(false)
			{
				static_assert(std::is_same<typename F::result_t, result_t>::value, "hnc::mpi::future creation fails: in \"hnc::mpi::future<result_t> f(Func, 1);\", Func::result_t and result_t must be the same");
				static_assert(std::is_same<decltype(f.move_result()), result_t>::value, "hnc::mpi::future creation fails: in \"hnc::mpi::future<result_t> f(Func, 1);\", Return type of f.move_result() and result_t must be the same");
				// Master
				if (m_id_proc == 0)
				{
					m_future_master = std::async(std::launch::async, [&f]() -> result_t { f(); return f.move_result(); });
				}
				// Slave
				{
					// Get serialization, use a pointer to keep the polymorphism
					hnc::mpi::functor * f_ptr = &f;
					// Get tag result
					m_tag_result = tag_result();
					// Send the function
					m_world.send(m_id_proc, hnc::mpi::tag_functor, std::make_pair(f_ptr, m_tag_result));
				}
			}

			#else
			
			template <class F>
			future(F & f, int const /*id_proc*/) : m_id_proc(0), m_done(false)
			{
				// Copy paste
				static_assert(std::is_same<typename F::result_t, result_t>::value, "hnc::mpi::future creation fails: in \"hnc::mpi::future<result_t> f(Func, 1);\", Func::result_t and result_t must be the same");
				static_assert(std::is_same<decltype(f.move_result()), result_t>::value, "hnc::mpi::future creation fails: in \"hnc::mpi::future<result_t> f(Func, 1);\", Return type of f.move_result() and result_t must be the same");
				// Local future
				m_future_master = std::async(std::launch::async, [&f]() -> result_t { f(); return f.move_result(); });
			}

			#endif

			/// @brief Return the result with std::move
			/// @post the result can be get once time only
			/// @exception std::logic_error if NDEBUG is not defined and multiple get function call
			/// @return the result with std::move
			result_t get();

		private:

			/// @brief Get MPI tag result
			/// @return MPI tag result
			int tag_result() const
			{
				static int tag_result = 0;
				return ++tag_result;
			}
		};

		template <class result_t>
		result_t future<result_t>::get()
		{
			result_t r{};
			// Get result
			if (!m_done)
			{
				// Master
				if (m_id_proc == 0)
				{
					r = m_future_master.get();
				}
				#ifndef hnc_no_boost_mpi
				// Slave
				else
				{
					m_world.recv(m_id_proc, m_tag_result, r);
				}
				m_done = true;
				#endif
			}
			#ifndef NDEBUG
			else
			{
				throw std::logic_error("hnc::mpi::future: get() is already done");
			}
			#endif
			// Move the result
			return r;
		}

		template <>
		void future<void>::get() { }

		/**
		 * @brief Create the MPI environment to use hnc::mpi::future
		 *
		 * @code
		   #include <hnc/mpi/future.hpp>
		   @endcode
		 *
		 * After the creation of the MPI environment, only the master (rank 0) must continue.@n
		 * You can use this code
		 * @code
		   #ifndef hnc_no_boost_mpi
		   hnc::mpi::environment env(argc, argv);
		   {
		   	boost::mpi::communicator world;
		   	if (world.rank() != 0)
		   	{
		   		return 0;
		   	}
		   }
		 * #endif
		 * @endcode
		 * or this macro
		 * @code
		   #ifndef hnc_no_boost_mpi
		   hnc_mpi_environment(env);
		   #endif
		 * @endcode
		 * 
		 * @note You need catch argc and argv in main function
		 * @code
		   int main(int argc, char * argv[])
		   @endcode
		 * 
		 * @note If you do not use argv or argv and you take care about warning, you can use
		 * @code
		   #ifndef hnc_no_boost_mpi
		   int main(int argc, char * argv[])
		   #else
		   int main()
		   #endif
		   @endcode
		 */
		class environment
		{

		#ifndef hnc_no_boost_mpi
			
		public:

			/// Boost MPI environment
			boost::mpi::environment boost_env;

			/**
			 * @brief Constructor
			 * 
			 * Create the MPI environment
			 * 
			 * @param[in] argc argc from main function
			 * @param[in] argv argv from main function
			 */
			environment(int argc, char * argv[]) : boost_env(argc, argv)
			{
				boost::mpi::communicator world;
				// Slave
				if (world.rank() != 0)
				{
					bool end;
					// Wait for a functor
					while (!end)
					{
						// Receive a fonctor in a pointer to keep the polymorphism
						std::pair<hnc::mpi::functor *, int> f_tag_result;
						world.recv(0, hnc::mpi::tag_functor, f_tag_result);
						hnc::mpi::functor * f = f_tag_result.first;
						// Execute
						(*f)();
						// Send result
						f->get(f_tag_result.second);
						// End
						end = f->stop();
						// Delete
						delete f;
					}
				};
			}

			/**
			 * @brief Destructor
			 * 
			 * Send the exit function to all slaves
			 */
			~environment()
			{
				boost::mpi::communicator world;
				// Master
				if (world.rank() == 0)
				{
					// Create the final function
					hnc::mpi::final_functor f_exit;
					// Send the final function
					for (int i = 1; i < world.size(); ++i)
					{
						hnc::mpi::future<void> f(f_exit, i);
					}
				}
			}

		#else

		public:

			environment(int /*argc*/, char * /*argv*/[]) { }

		#endif
			
		};
	}
}

#ifndef hnc_no_boost_serialization
BOOST_CLASS_EXPORT(hnc::mpi::functor)
#endif

#ifndef hnc_no_boost_serialization
BOOST_CLASS_EXPORT(hnc::mpi::final_functor)
#endif

#define hnc_mpi_environment(env) \
hnc::mpi::environment env(argc, argv); \
do \
{ \
	boost::mpi::communicator world; \
	if (world.rank() != 0) \
	{ \
		return 0; \
	} \
} while (0)

#endif
