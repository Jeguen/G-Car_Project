// Copyright © 2012-2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef HNC_SCHEDULER_ITERATION_HPP
#define HNC_SCHEDULER_ITERATION_HPP

#include <chrono>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <functional>


namespace hnc
{
	namespace scheduler
	{
		/**
		 * @brief Excute different versions of for loop. Split iterations, benchmark versions and select the version with the min time. No useless computing, no rollback.
		 *
		 * @code
		   #include <hnc/scheduler.hpp>
		   @endcode
		 *
		 * You have:
		 * - a number of iterations (betwwen first and last with a step)
		 * - different versions of the same computing (per iteration)
		 *
		 * You do not know the best version. Worse, the best version is not the same in all contexts (the best version deplasts on another computing in the computer).
		 *
		 * This function take the number of iterations, several versions and do this until there are no iteration anymore:
		 * 1. execute all versions on few iterations (sample)
		 * 2. execute the last best version on several iterations
		 * 
		 * Example with classic function:
		 * @code
		   int func_value = 0;
		   
		   void func0(int const & first, int const & last)
		   {
		   	for (int i = first; i < last; ++i)
		   	{
		   		++func_value;
		   	}
		   }
		  
		   void func1(int const & first, int const & last)
		   {
		   	for (int i = first; i < last; ++i)
		   	{
		   		++func_value;
		   	}
		   }
		   
		   int main()
		   {
		   	// Compute
		   	hnc::scheduler::iteration(0, 42, {func0, func1});
		   
		   	// func_value value is 42
		   
		   	return 0;
		   }
		   @endcode
		 *
		 * Example with functor object and lambda :
		 * @code
		   class fonctor
		   {
		   public:
		   	fonctor(std::vector<std::vector<int>> & tab2D) : r_tab2D(tab2D) { }
		   
		   	void operator()(std::size_t const & first, std::size_t const & last)
		   	{
		   		for (std::size_t i = first; i < last; ++i)
		   		{
		   			for (std::size_t j = 0; j < r_tab2D.size(); ++j)
		   			{
		   				r_tab2D[i][j] += i * j;
		   			}
		   		}
		   	}
		   
		   private:
		   	std::vector<std::vector<int>> & r_tab2D;
		   };
		   
		   int main()
		   {
		   	std::size_t const N = 200;
		   
		   	// A 2D array [N][N]
		   	std::vector<std::vector<int>> tab2D(N, std::vector<int>(N, 0));
		   	
		   	auto lambda = [&](std::size_t const & first, std::size_t const & last) -> void
		   	{
		   		for (j = 0; j < tab2D.size(); j += 7)
		   		{
		   			for (i = first; i < last; ++i)
		   			{
		   				tab2D[i][j] += i * j;
		   			}
		   		}
		   	};
		   
		   	// Compute
		   	hnc::scheduler::iteration(std::size_t(0), N, {fonctor(tab2D), lambda});
		   	
		   	return 0;
		   }
		   @endcode
		 * 
		 * @param[in] first         First iteration
		 * @param[in] last          Last iteration (not included)
		 * @param[in] versions      Functions with a first and a last and with the same computing
		 * @param[in] nb_it_sample  Number of iterations for sample phases
		 * @param[in] nb_it_compute Number of iterations for compute phases
		 * @param[in] step          Incrementation in the loop (1 by default)
		 *
		 * Function type (in versions) is a std::function, it can be:
		 * - a function without parameter
		 * - a functor object
		 * - a lambda expression without parameter
		 *
		 * @pre The function type signature is (it_t const &, it_t const &)
		 * @pre All versions do the same computing
		 * @pre One iteration in a random version for one iteration id is the same result as another random version for the same id iteration
		 *
		 * @warning If the incrementation (step) have not the good value, the number of iterations computed is not correct
		 * @warning Be carefull about versions if you need the final iterator (you can not mix loop and reverse loop for example)
		 */
		template <class it_t, class incr_t = std::size_t>
		inline void iteration
		(
			it_t first,
			it_t const & last,
			std::vector<std::function<void(it_t const &, it_t const &)>> const & versions,
			it_t const & nb_it_sample = 2 * 4 * 6,
			it_t const & nb_it_compute = (2 * 4 * 6) * 10,
			incr_t const & step = 1
		)
		{
			while (first < last)
			{
				// Index of the best version
				auto best_time = std::numeric_limits<std::chrono::steady_clock::duration::rep>::max();
				std::size_t best_version = 0;
				
				// Samples
				for (std::size_t i = 0; i < versions.size() && first < last; ++i)
				{
					// Compute
					auto time_first = std::chrono::steady_clock::now();
					{
						versions[i](first, std::min(it_t(first) + it_t(nb_it_sample) * it_t(step), last));
					}
					auto time_last = std::chrono::steady_clock::now();
					
					// Save best version
					auto const time = (time_last - time_first).count();
					if (time < best_time)
					{
						best_time = time;
						best_version = i;
					}
					
					// Next iterations
					first += it_t(nb_it_sample) * it_t(step);
				}

				// Compute
				if (first < last)
				{
					// Compute
					versions[best_version](first, std::min(it_t(first) + it_t(nb_it_compute) * it_t(step), last));
					// Next iterations
					first += it_t(nb_it_compute) * it_t(step);
				}
			}
		}
	}
}

#endif
