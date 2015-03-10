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


#ifndef HNC_BENCHMARK_HPP
#define HNC_BENCHMARK_HPP

#include <chrono>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

#include "time.hpp"
#include "math/median.hpp"
#include "math/geometric_mean.hpp"
#include "math/mean.hpp"
#include "ostreamable.hpp"


namespace hnc
{
	/**
	 * @brief Vector of elapsed times
	 *
	 * @code
	   #include <hnc/benchmark.hpp>
	   @endcode
	 * 
	 * @warning hnc::benchmark_base is just a class to stock benchmark data @n
	 * Please consider hnc::benchmark and hnc::benchmark_name_opt
	 *
	 * hnc::benchmark_base is a vector (std::vector) of elapsed times between start and stop
	 * You can access to the min, max, median, geometric mean, mean and all elapsed times
	 */
	class benchmark_base
	{
	public:

		/// Vector of all elapsed times
		std::vector<long double> all;
		
	private:

		/// Last start time
		long double m_start;

	public:

		/// @brief Start timer for benchmark
		void start()
		{
			m_start = hnc::time::s();
		}

		/// @brief Stop timer and save the duration (elapsed time during last .start()) (in seconds)
		void stop()
		{
			all.push_back(hnc::time::s() - m_start);
		}

		/// @brief Add (push back) a user elapsed time value
		/// @param[in] value value of one elapsed time
		void push_back(double const value) { all.push_back(value); }

		/// @brief Return the minimum of elapsed time
		/// @return the minimum of elapsed time
		long double min() const { return *std::min_element(all.begin(), all.end()); }

		/// @brief Return the maximum of elapsed time
		/// @return the maximum of elapsed time
		long double max() const { return *std::max_element(all.begin(), all.end()); }

		/// @brief Return the median of all elapsed times
		/// @return the median of all elapsed times
		long double median() const { return hnc::math::median(all); }

		/// @brief Return the geometric mean of all elapsed times
		/// @return the geometric mean of all elapsed times
		long double geometric_mean() const { return hnc::math::geometric_mean(all); }

		/**
		 * @brief Return the mean of all elapsed times
		 *
		 * Benchmark is a long tail distribution, mean (may) have no sense; use median (or geometric mean) instead
		 * 
		 * @return the mean of all elapsed times
		 */
		long double mean() const { return hnc::math::mean(all); }
	};
	
	/**
	 * @brief Save benchmarks by name
	 * 
	 * @code
	   #include <hnc/benchmark.hpp>
	   @endcode
	 *
	 * hnc::benchmark is a map (std::map) of hnc::benchmark_base @n
	 * The name of the test (a std::string) is the key and the hnc::benchmark_base is the value
	 *
	 * The value is a vector of elapsed times (in seconds) @n
	 * To get a elapsed time use the start and stop member function
	 *
	 * You can acces to some metrics:
	 * - min
	 * - max
	 * - median
	 * - geometric mean
	 * - mean (benchmark is a long tail distribution, mean (may) have no sense; use media or geometric mean instead)
	 * - all elapsed times
	 *
	 * @code
	   hnc::benchmark b;
	  
	   b["Name of the test"].start();
	   // Some computation
	   b["Name of the test"].stop();
	  
	   // You can add user elapsed time value (a double)
	   b["Name of the test"].push_back(5.);
	  
	   double min            = b["Name of the test"].min();
	   double max            = b["Name of the test"].max();
	   double median         = b["Name of the test"].median();
	   double geometric_mean = b["Name of the test"].geometric_mean();
	   double mean           = b["Name of the test"].mean();
	   std::vector<double> times_elapsed = b["Name of the test"].all;
	  
	   // To avoid b["Name of the test"] repetition, you can get a reference
	   hnc::benchmark_base & bench_name = b["Name of the test"];
	   @endcode
	 */
	typedef std::map<std::string, hnc::benchmark_base> benchmark;
	
	/// @brief Operator << between a std::ostream and a hnc::benchmark
	/// @param[in,out] o Output stream
	/// @param[in]     b A hnc::benchmark
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, hnc::benchmark const & b)
	{
		for (auto const & t : b)
		{
			auto const & key = t.first;
			auto const & value = t.second;
			std::cout << key << ":" << "\n";
			std::cout << "- all:            " << hnc::ostreamable(value.all) << "\n";
			std::cout << "- min:            " << value.min() << "\n";
			std::cout << "- max:            " << value.max() << "\n";
			std::cout << "- median:         " << value.median() << "\n";
			std::cout << "- geometric mean: " << value.geometric_mean() << "\n";
			std::cout << "- mean:           " << value.mean();
			if (t.first != b.rbegin()->first) { std::cout << "\n"; }
		}
		return o;
	}
	
	/**
	 * @brief Return a std::map of double, key is the name of the benchmark, value is the mean
	 * 
	 * @code
	   #include <hnc/benchmark.hpp>
	   @endcode
	 *
	 * @param[in] b hnc::benchmark
	 * 
	 * @return a std::map of double, key is the name of the benchmark, value is the mean
	 */
	std::map<std::string, long double> benchmark_extract_mean(hnc::benchmark const & b)
	{
		std::map<std::string, long double> r;
		
		for (auto const & t : b)
		{
			auto const & key = t.first;
			auto const & value = t.second;
			
			r[key] = value.median();
		}

		return r;
	}

	/**
	 * @brief Save benchmarks by name, and other string (for example, by option)
	 * 
	 * @code
	   #include <hnc/benchmark.hpp>
	   @endcode
	 *
	 * hnc::benchmark_name_opt (Benchmark[name][option]) is a map (std::map) of a map (std::map) of hnc::benchmark_base @n
	 * The name of the test (a std::string) and  the option (std::string) are the keys and the hnc::benchmark_base is the final value
	 *
	 * The value is a vector of elapsed times (in seconds) @n
	 * To get a elapsed time use the start and stop member function
	 *
	 * You can acces to some metrics:
	 * - min
	 * - max
	 * - median
	 * - geometric mean
	 * - mean (benchmark is a long tail distribution, mean (may) have no sense; use media or geometric mean instead)
	 * - all elapsed times
	 *
	 * @code
	   hnc::benchmark_name_opt b;
	  
	   b["Name of the test"]["option 1"].start();
	   // Some computation
	   b["Name of the test"]["option 1"].stop();
	  
	   // You can add user elapsed time value (a double)
	   b["Name of the test"]["option 1"].push_back(5.);
	  
	   double min            = b["Name of the test"].min();
	   double max            = b["Name of the test"].max();
	   double median         = b["Name of the test"].median();
	   double geometric_mean = b["Name of the test"].geometric_mean();
	   double mean           = b["Name of the test"].mean();
	   std::vector<double> times_elapsed = b["Name of the test"]["option 1"].all;
	  
	   // To avoid b["Name of the test"]["option 1"] repetition, you can get a reference
	   hnc::benchmark_base & bench_name_opt = b["Name of the test"]["option 1"];
	   @endcode
	 */
	typedef std::map<std::string, std::map<std::string, hnc::benchmark_base>> benchmark_name_opt;
	
	/// @brief Operator << between a std::ostream and a hnc::benchmark_name_opt
	/// @param[in,out] o Output stream
	/// @param[in]     b A hnc::benchmark_name_opt
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, hnc::benchmark_name_opt const & b)
	{
		for (auto const & t : b)
		{
			auto const & key = t.first;
			auto const & value_map = t.second;
			o << key << ":";
			// Copy paste of << hnc::benchmark (with identation)
			for (auto const & t : value_map)
			{
				auto const & key = t.first;
				auto const & value = t.second;
				o << "\n";
				o << "- " << key << ":" << "\n";
				o << "  " << "- all:            " << hnc::ostreamable(value.all) << "\n";
				o << "  " << "- min:            " << value.min() << "\n";
				o << "  " << "- max:            " << value.max() << "\n";
				o << "  " << "- median:         " << value.median() << "\n";
				o << "  " << "- geometric mean: " << value.geometric_mean() << "\n";
				o << "  " << "- mean:           " << value.mean();
			}
			if (t.first != b.rbegin()->first) { o << "\n"; }
		}
		
		return o;
	}
}

#endif
