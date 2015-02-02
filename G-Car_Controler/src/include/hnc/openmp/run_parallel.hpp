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


#ifndef HNC_OPENMP_RUN_PARALLEL_HPP
#define HNC_OPENMP_RUN_PARALLEL_HPP


namespace hnc
{
	namespace openmp
	{
		template <class func>
		void run_parallel(func & f)
		{
			f();
		}

		/**
		 * @brief Run tasks with OpenMP
		 *
		 * @code
		   #include <hnc/openmp.hpp>
		   @endcode
		 *
		 * OpenMP works with preprocessor, so hnc::openmp::run_parallel is writen for 1, 2, 3, 4, ... functions as parameters (if not, please write the good function and send it to me(!))
		 * @code
		   hnc::openmp::run_parallel(f0, f1, f2); //, f3, fx, ...
		   @endcode
		 *
		 * @param[in,out] f0 Task (a function without parameter)
		 * @param[in,out] f1 Another task (a function without parameter)
		 *
		 * The parameters can be:
		 * - a fonction without parameter
		 * - a functor object
		 * - a lambda expression without parameter
		 *
		 * @warning The call of this function in this function does not work !
		 */
		template <class func0, class func1>
		void run_parallel(func0 & f0, func1 & f1)
		{
			#pragma omp parallel
			{
				#pragma omp sections
				{
					#pragma omp section
					f0();
					#pragma omp section
					f1();
				}
			}
		}

		template <class func0, class func1, class func2>
		void run_parallel(func0 & f0, func1 & f1, func2 & f2)
		{
			#pragma omp parallel
			{
				#pragma omp sections
				{
					#pragma omp section
					f0();
					#pragma omp section
					f1();
					#pragma omp section
					f2();
				}
			}
		}

		template <class func0, class func1, class func2, class func3>
		void run_parallel(func0 & f0, func1 & f1, func2 & f2, func3 & f3)
		{
			#pragma omp parallel
			{
				#pragma omp sections
				{
					#pragma omp section
					f0();
					#pragma omp section
					f1();
					#pragma omp section
					f2();
					#pragma omp section
					f3();
				}
			}
		}

		template <class func0, class func1, class func2, class func3, class func4>
		void run_parallel(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4)
		{
			#pragma omp parallel
			{
				#pragma omp sections
				{
					#pragma omp section
					f0();
					#pragma omp section
					f1();
					#pragma omp section
					f2();
					#pragma omp section
					f3();
					#pragma omp section
					f4();
				}
			}
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5>
		void run_parallel(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5)
		{
			#pragma omp parallel
			{
				#pragma omp sections
				{
					#pragma omp section
					f0();
					#pragma omp section
					f1();
					#pragma omp section
					f2();
					#pragma omp section
					f3();
					#pragma omp section
					f4();
					#pragma omp section
					f5();
				}
			}
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6>
		void run_parallel(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6)
		{
			#pragma omp parallel
			{
				#pragma omp sections
				{
					#pragma omp section
					f0();
					#pragma omp section
					f1();
					#pragma omp section
					f2();
					#pragma omp section
					f3();
					#pragma omp section
					f4();
					#pragma omp section
					f5();
					#pragma omp section
					f6();
				}
			}
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7>
		void run_parallel(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7)
		{
			#pragma omp parallel
			{
				#pragma omp sections
				{
					#pragma omp section
					f0();
					#pragma omp section
					f1();
					#pragma omp section
					f2();
					#pragma omp section
					f3();
					#pragma omp section
					f4();
					#pragma omp section
					f5();
					#pragma omp section
					f6();
					#pragma omp section
					f7();
				}
			}
		}
	}
}

#endif
