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


#ifndef HNC_OPENMP_RUN_AT_SAME_TIME_HPP
#define HNC_OPENMP_RUN_AT_SAME_TIME_HPP

#if defined(_OPENMP)
#include <omp.h>
#endif


namespace hnc
{
	namespace openmp
	{
		template <class func>
		void run_at_same_time(func & f)
		{
			f();
		}

		/**
		 * @brief Run tasks with OpenMP at same time
		 *
		 * @code
		   #include <hnc/openmp.hpp>
		   @endcode
		 *
		 * Unlike hnc::openmp::run_parallel, this function ensures task are executed at the same time
		 *
		 * OpenMP works with preprocessor, so hnc::openmp::run_at_same_time is writen for 1, 2, 3, 4, ... functions as parameters (if not, please write the good function and send it to me(!))
		 * @code
		   hnc::openmp::run_at_same_time(f0, f1, f2); //, f3, fx, ...
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
		void run_at_same_time(func0 & f0, func1 & f1)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(2);
			#endif
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
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(3);
			#endif
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
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(4);
			#endif
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
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(5);
			#endif
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
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(6);
			#endif
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
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(7);
			#endif
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
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16, class func17>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16, func17 & f17)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
					#pragma omp section
					f17();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16, class func17, class func18>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16, func17 & f17, func18 & f18)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
					#pragma omp section
					f17();
					#pragma omp section
					f18();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16, class func17, class func18, class func19>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16, func17 & f17, func18 & f18, func19 & f19)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
					#pragma omp section
					f17();
					#pragma omp section
					f18();
					#pragma omp section
					f19();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16, class func17, class func18, class func19, class func20>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16, func17 & f17, func18 & f18, func19 & f19, func20 & f20)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
					#pragma omp section
					f17();
					#pragma omp section
					f18();
					#pragma omp section
					f19();
					#pragma omp section
					f20();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16, class func17, class func18, class func19, class func20, class func21>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16, func17 & f17, func18 & f18, func19 & f19, func20 & f20, func21 & f21)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
					#pragma omp section
					f17();
					#pragma omp section
					f18();
					#pragma omp section
					f19();
					#pragma omp section
					f20();
					#pragma omp section
					f21();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16, class func17, class func18, class func19, class func20, class func21, class func22>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16, func17 & f17, func18 & f18, func19 & f19, func20 & f20, func21 & f21, func22 & f22)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
					#pragma omp section
					f17();
					#pragma omp section
					f18();
					#pragma omp section
					f19();
					#pragma omp section
					f20();
					#pragma omp section
					f21();
					#pragma omp section
					f22();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16, class func17, class func18, class func19, class func20, class func21, class func22, class func23>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16, func17 & f17, func18 & f18, func19 & f19, func20 & f20, func21 & f21, func22 & f22, func23 & f23)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
					#pragma omp section
					f17();
					#pragma omp section
					f18();
					#pragma omp section
					f19();
					#pragma omp section
					f20();
					#pragma omp section
					f21();
					#pragma omp section
					f22();
					#pragma omp section
					f23();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}

		template <class func0, class func1, class func2, class func3, class func4, class func5, class func6, class func7, class func8, class func9, class func10, class func11, class func12, class func13, class func14, class func15, class func16, class func17, class func18, class func19, class func20, class func21, class func22, class func23, class func24>
		void run_at_same_time(func0 & f0, func1 & f1, func2 & f2, func3 & f3, func4 & f4, func5 & f5, func6 & f6, func7 & f7, func8 & f8, func9 & f9, func10 & f10, func11 & f11, func12 & f12, func13 & f13, func14 & f14, func15 & f15, func16 & f16, func17 & f17, func18 & f18, func19 & f19, func20 & f20, func21 & f21, func22 & f22, func23 & f23, func24 & f24)
		{
			#if defined(_OPENMP)
			int num_thread = omp_get_max_threads();
			omp_set_num_threads(8);
			#endif
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
					#pragma omp section
					f8();
					#pragma omp section
					f9();
					#pragma omp section
					f10();
					#pragma omp section
					f11();
					#pragma omp section
					f12();
					#pragma omp section
					f13();
					#pragma omp section
					f14();
					#pragma omp section
					f15();
					#pragma omp section
					f16();
					#pragma omp section
					f17();
					#pragma omp section
					f18();
					#pragma omp section
					f19();
					#pragma omp section
					f20();
					#pragma omp section
					f21();
					#pragma omp section
					f22();
					#pragma omp section
					f23();
					#pragma omp section
					f24();
				}
			}
			#if defined(_OPENMP)
			omp_set_num_threads(num_thread);
			#endif
		}
	}
}

#endif
