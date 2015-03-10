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


#ifndef HNC_RANDOM_HPP
#define HNC_RANDOM_HPP

#include <random>
#include <chrono>

#include "time.hpp"


namespace hnc
{
	/**
	 * @brief Random classes and functions
	 * 
	   @code
	   	#include <hnc/random.hpp>
	   @endcode
	 */
	namespace random
	{
		// Uniform distributions
		
		/**
		 * @brief Uniform distribution
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 */
		template <class T>
		struct uniform_distribution_t;
		
		// int
		
		// Specialization for int
		template <>
		struct uniform_distribution_t<int>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<int>;
		};
		
		// Specialization for unsigned int
		template <>
		struct uniform_distribution_t<unsigned int>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<unsigned int>;
		};
		
		// Specialization for short int
		template <>
		struct uniform_distribution_t<short int>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<short int>;
		};
		
		// Specialization for short unsigned int
		template <>
		struct uniform_distribution_t<short unsigned int>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<short unsigned int>;
		};
		
		// Specialization for long int
		template <>
		struct uniform_distribution_t<long int>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<long int>;
		};
		
		// Specialization for long unsigned int
		template <>
		struct uniform_distribution_t<long unsigned int>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<long unsigned int>;
		};
		
		// Specialization for long long int
		template <>
		struct uniform_distribution_t<long long int>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<long long int>;
		};
		
		// Specialization for long long unsigned int
		template <>
		struct uniform_distribution_t<long long unsigned int>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<long long unsigned int>;
		};
		
		// Specialization for char
		template <>
		struct uniform_distribution_t<char>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<char>;
		};
		
		// Specialization for unsigned char
		template <>
		struct uniform_distribution_t<unsigned char>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<unsigned char>;
		};
		
		// Specialization for signed char
		template <>
		struct uniform_distribution_t<signed char>
		{
			/// Int uniform distribution type
			using type = std::uniform_int_distribution<signed char>;
		};
		
		// double
		
		// Specialization for float
		template <>
		struct uniform_distribution_t<float>
		{
			/// Real uniform distribution type
			using type = std::uniform_real_distribution<float>;
		};
		
		// Specialization for double
		template <>
		struct uniform_distribution_t<double>
		{
			/// Real uniform distribution type
			using type = std::uniform_real_distribution<double>;
		};
		
		// Specialization for long double
		template <>
		struct uniform_distribution_t<long double>
		{
			/// Real uniform distribution type
			using type = std::uniform_real_distribution<long double>;
		};
		
		// bool
		
		// Specialization for bool
		template <>
		struct uniform_distribution_t<bool>
		{
			/// Real uniform distribution type
			using type = std::bernoulli_distribution;
		};
		
		
		// Types
		
		/**
		 * @brief Pseudo random value with uniform distribution
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 */
		template <class T>
		class uniform_t
		{
		private:
			
			/// Random engine
			std::default_random_engine m_random_engine;
			
			/// Uniform distribution
			typename hnc::random::uniform_distribution_t<T>::type m_distribution;
			
		public:
			
			/// @brief Constructor
			/// @param[in] min Minimum value
			/// @param[in] max Maximum value
			/// @param[in] seed Seed (hnc::time::ns() by default)
			uniform_t(T const min, T const max, long unsigned int seed = hnc::time::ns()) :
				m_random_engine(seed),
				m_distribution(min, max)
			{ }
			
			/// @brief Default constructor
			uniform_t() : uniform_t(T(0), T(0)) { }
			
			/// @brief Pseudo random value
			/// @return a pseudo random value
			T operator()()
			{
				return m_distribution(m_random_engine);
			}
			
			/// @brief Pseudo random value
			/// @param[in] min Minimum value
			/// @param[in] max Maximum value
			/// @return a pseudo random value between min and max
			T operator()(T const min, T const max)
			{
				typename hnc::random::uniform_distribution_t<T>::type distribution(min, max);
				return distribution(m_random_engine);
			}
		};
		
		/**
		 * @brief Pseudo random bool with uniform distribution
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 */
		template <>
		class uniform_t<bool>
		{
		private:
			
			/// Random engine
			std::default_random_engine m_random_engine;
			
			/// Uniform distribution
			typename hnc::random::uniform_distribution_t<bool>::type m_distribution;
			
		public:
			
			/// @brief Constructor
			/// @param[in] probability Probability of getting true
			/// @param[in] seed Seed (hnc::time::ns() by default)
			uniform_t(double const probability, long unsigned int seed = hnc::time::ns()) :
				m_random_engine(seed),
				m_distribution(probability)
			{ }
			
			/// @brief Default constructor
			uniform_t() : uniform_t(0.5) { }
			
			/// @brief Pseudo random value
			/// @return a pseudo random value
			bool operator()()
			{
				return m_distribution(m_random_engine);
			}
			
			/// @brief Pseudo random value
			/// @param[in] probability Probability of getting true
			/// @return a pseudo random value
			bool operator()(double const probability)
			{
				typename hnc::random::uniform_distribution_t<bool>::type distribution(probability);
				return distribution(m_random_engine);
			}
		};
		
		
		// Make
		
		/**
		 * @brief Make a pseudo random uniform object
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 *
		 * @param[in] min Minimum value
		 * @param[in] max Maximum value
		 * @param[in] seed Seed (hnc::time::ns() by default)
		 *
		 * @return the hnc::random::uniform_t<T> wanted
		 */
		template <class T>
		hnc::random::uniform_t<T> make_uniform_t(T const min, T const max, long unsigned int seed = hnc::time::ns())
		{
			return hnc::random::uniform_t<T>(min, max, seed);
		}
		
		/**
		 * @brief Make a pseudo random uniform object
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 *
		 * @param[in] seed Seed (hnc::time::ns() by default)
		 *
		 * @return the hnc::random::uniform_t<T> wanted
		 */
		template <class T>
		hnc::random::uniform_t<T> make_uniform_t(long unsigned int seed = hnc::time::ns())
		{
			return hnc::random::uniform_t<T>(T(0), T(0), seed);
		}
		
		/**
		 * @brief Make a pseudo random uniform object for bool
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 *
		 * @param[in] probability Probability of getting true
		 * @param[in] seed Seed (hnc::time::ns() by default)
		 *
		 * @return the hnc::random::uniform_t<bool> wanted
		 */
		inline hnc::random::uniform_t<bool> make_true_false_t(double const probability, long unsigned int seed = hnc::time::ns())
		{
			return hnc::random::uniform_t<bool>(probability, seed);
		}
		
		/**
		 * @brief Make a pseudo random uniform object for bool
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 *
		 * @param[in] seed Seed (hnc::time::ns() by default)
		 *
		 * @return the hnc::random::uniform_t<bool> wanted
		 */
		inline hnc::random::uniform_t<bool> make_true_false_t(long unsigned int seed = hnc::time::ns())
		{
			return hnc::random::uniform_t<bool>(0.5, seed);
		}
		
		
		// Free functions
		
		/**
		 * @brief Pseudo random value with uniform distribution
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 *
		 * @param[in] min Minimum value
		 * @param[in] max Maximum value
		 */
		template <class T>
		T uniform(T const min, T const max)
		{
			static hnc::random::uniform_t<T> random;
			return random(min, max);
		}
		
		/**
		 * @brief Pseudo random bool with uniform distribution
		 * 
		   @code
		   	#include <hnc/random.hpp>
		   @endcode
		 *
		 * @param[in] probability Probability of getting true
		 */
		bool true_false(double const probability = 0.5)
		{
			static hnc::random::uniform_t<bool> random;
			return random(probability);
		}
	}
}

#endif
