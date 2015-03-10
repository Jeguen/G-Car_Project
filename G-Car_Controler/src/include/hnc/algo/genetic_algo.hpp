// Copyright © 2013, 2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_ALGO_GENETIC_ALGO_HPP
#define HNC_ALGO_GENETIC_ALGO_HPP

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
#include <memory>

#include "../log_level.hpp"
#include "../terminal.hpp"
#include "../ostream_std.hpp"
#include "../random.hpp"
#include "../time.hpp"
#include "../openmp.hpp"

namespace hnc
{
	namespace algo
	{
		/**
		 * @brief Genetic algorithm namespace
		 * 
		 * @code
		   #include <hnc/algo.hpp>
		   @endcode
		 */
		namespace genetic_algo
		{
			/// @brief Archipelago type
			template <class T>
			using archipelago_t = std::vector<T>;
			
			/// @brief Island type
			template <class T>
			using island_t = std::vector<T>;
			
			/// @brief Container for a solution and its grade
			template <class solution_t, class grade_t>
			class solution_grade_t
			{
				public:
					
					/// Solution
					solution_t solution;
					
					/// Grade
					grade_t grade;
					
					/// @brief Constructor
					/// @param solution The solution
					/// @param grade The grade
					solution_grade_t(solution_t const & solution = solution_t(), grade_t const & grade = grade_t()) :
						solution(solution), grade(grade)
					{ }
			};
			
			/// @brief Operator < between two hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t>
			/// @param[in] a An hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t>
			/// @param[in] b An hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t>
			/// @return true if a < b, false otherwise
			template <class solution_t, class grade_t>
			bool operator <(hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t> const & a, hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t> const & b)
			{
				return (a.grade < b.grade);
			}
			
			/// @brief Operator << between a std::ostream and a hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t>
			/// @param[in,out] o        Output stream
			/// @param[in]     solution A hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t>
			/// @return the output stream
			template <class solution_t, class grade_t>
			std::ostream & operator <<(std::ostream & o, hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t> const & solution)
			{
				o << "(" << solution.solution << ", " << solution.grade << ")";
				return o;
			}

			/// Log levels
			enum class log_level_t { no_log, minimal_log, minimal_plus_log, archipelago_log, island_log, solution_grade_log };
			
			/**
			 * @brief Genetic algorithm
			 *
			 * @code
			   #include <hnc/algo.hpp>
			   @endcode
			 * 
			 * TODO
			 */
			template
			<
				class solution_t,
				class grade_t,
				class T
			>
			class genetic_algo
			{
			private:
				
				/// Number of thread (OpenMP)
				std::size_t const m_nb_thread;
				
				/// Object contains evolve functions
				std::vector<T> m_evolve_functions;
				
				/// Solutions & grades
				std::vector
				<
					hnc::algo::genetic_algo::archipelago_t
					<
						hnc::algo::genetic_algo::island_t
						<
							hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t>
						>
					>
				> m_solutions;
				
				/// Random probability for crossover and a mutation
				std::vector<hnc::random::uniform_t<double>> m_random_probability;
				
				/// Random index for solution
				std::vector<hnc::random::uniform_t<std::size_t>> m_random_index;
				
			public:
				
				/// Number of archipelagos
				std::size_t const nb_archipelago;
				
				/// Number of islands per archipelago
				std::size_t const nb_island_per_archipelago;
				
				/// Number of solutions per island
				std::size_t const nb_solution_per_island;
				
				/// Probability of crossover
				double const crossover_probability;
				
				/// Probability of mutation
				double const mutation_probability;
				
				/// Number of solution to be migrated during island migration
				std::size_t const nb_migration_per_island;
				
				/// Number of generations to do between a island migration
				std::size_t const nb_generation_between_island_migration;
				
				/// Number of solution to be migrated during archipelago migration
				std::size_t const nb_migration_per_archipelago;
				
				/// Number of generations to do between a archipelago migration
				std::size_t const nb_generation_between_archipelago_migration;
				
				/// Number of time the best solution can be the same
				std::size_t const nb_same_solution_max;
				
				/// Number of generations max
				std::size_t const nb_generation_max;
				
				/// Maximum time in seconds for the algorithm
				long double const max_time;
				
				/// Log level
				log_level_t const log_level;
				
			private:
				
				/// Number of generations
				std::size_t m_nb_generation;
				
				/// Number of time a solution was the best
				std::size_t m_nb_same_solution;
				
				/// Time when start the algorithm
				long double const m_time_start;
				
				/// Actual best solution
				std::reference_wrapper
				<
					hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t> const
				> m_best_solution;
				
			public:
				
				/// @brief Constructor
				/// @param[in] evolve_functions                            Objet that contains generate_solution, evaluate_solution, crossover, mutation and stop member functions
				/// @param[in] nb_archipelago                              Number of archipelagos
				/// @param[in] nb_island_per_archipelago                   Number of islands per archipelago
				/// @param[in] nb_solution_per_island                      Number of solutions per island
				/// @param[in] crossover_probability                       Probability a solution have to do a crossover (0.7 by default)
				/// @param[in] mutation_probability                        Probability a solution have to do a mutation (0.1 by default)
				/// @param[in] nb_migration_per_island                     Number of solution to be migrated during island migration
				/// @param[in] nb_generation_between_island_migration      Number of generations to do between a island migration
				/// @param[in] nb_migration_per_archipelago                Number of solution to be migrated during archipelago migration
				/// @param[in] nb_generation_between_archipelago_migration Number of generations to do between a archipelago migration
				/// @param[in] nb_same_solution_max                        Number of time the best solution can be the same (0 if unlimited, 20 by default)
				/// @param[in] nb_generation_max                    Maximum number of generations (0 if unlimited, 0 by default)
				/// @param[in] max_time                                    Maximum time in seconds for the algorithm
				/// @param[in] log_level                                   A hnc::algo::genetic_algo::log_level_t
				genetic_algo
				(
					T const & evolve_functions,
					std::size_t const nb_archipelago,
					std::size_t const nb_island_per_archipelago,
					std::size_t const nb_solution_per_island,
					double const crossover_probability = 0.7,
					double const mutation_probability = 0.1,
					std::size_t const nb_migration_per_island = 3,
					std::size_t const nb_generation_between_island_migration = 5,
					std::size_t const nb_migration_per_archipelago = 2,
					std::size_t const nb_generation_between_archipelago_migration = 10,
					std::size_t const nb_same_solution_max = 20,
					std::size_t const nb_generation_max = 0,
					long double const max_time = 0.0,
					log_level_t const log_level = hnc::algo::genetic_algo::log_level_t::no_log
				) :
					m_nb_thread(hnc::openmp::nb_thread_max()),
					m_evolve_functions(m_nb_thread, evolve_functions),
					m_solutions
					(
						nb_archipelago,
						hnc::algo::genetic_algo::archipelago_t
						<
							hnc::algo::genetic_algo::island_t
							<
								hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t>
							>
						>
						(
							nb_island_per_archipelago,
							hnc::algo::genetic_algo::island_t
							<
								hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t>
							>
							(
								nb_solution_per_island
							)
						)
					),
					m_random_probability(m_nb_thread, hnc::random::uniform_t<double>(0., 1.)),
					m_random_index(m_nb_thread, hnc::random::uniform_t<std::size_t>(0, nb_solution_per_island - 1)),
					nb_archipelago(nb_archipelago),
					nb_island_per_archipelago(nb_island_per_archipelago),
					nb_solution_per_island(nb_solution_per_island),
					crossover_probability(crossover_probability),
					mutation_probability(mutation_probability),
					nb_migration_per_island(std::min(nb_migration_per_island, nb_solution_per_island)),
					nb_generation_between_island_migration(nb_generation_between_island_migration),
					nb_migration_per_archipelago(std::min(nb_migration_per_archipelago, nb_solution_per_island)),
					nb_generation_between_archipelago_migration(nb_generation_between_archipelago_migration),
					nb_same_solution_max(nb_same_solution_max),
					nb_generation_max(nb_generation_max),
					max_time(max_time),
					log_level(log_level),
					m_nb_generation(1),
					m_nb_same_solution(0),
					m_time_start(hnc::time::s()),
					m_best_solution(m_solutions[0][0][0])
				{
					hnc::out(log_level, log_level_t::minimal_log) << "Create genetic algorithm" << std::endl;
					hnc::out(log_level, log_level_t::minimal_plus_log) << "  " << "(Number of max generations = " << nb_generation_max << ")" << std::endl;
					hnc::out(log_level, log_level_t::minimal_plus_log) << "  " << "(Max time                  = " << max_time << ")" << std::endl;
					hnc::out(log_level, log_level_t::minimal_log) << "  " << "+ Generate the population" << std::endl;
					
					// Generate the population + distribution
					for (std::size_t archipelago = 0; archipelago < m_solutions.size(); ++archipelago)
					{
						hnc::out(log_level, log_level_t::archipelago_log) << "  " << "  " << "Archipelago " << archipelago << "/" << m_solutions.size() << std::endl;
						
						#pragma omp parallel for
						for (std::size_t island = 0; island < m_solutions[archipelago].size(); ++island)
						{
							auto const thread_id = hnc::openmp::thread_id();
							
							hnc::out(log_level, log_level_t::island_log) << "  " << "  " << "  " << "Island " << island << "/" << m_solutions[archipelago].size() << std::endl;
							
							auto & solutions = m_solutions[archipelago][island];
							
							// Generate solution for island
							for (auto & solution : solutions)
							{
								// Generate a solution
								solution.solution = m_evolve_functions[thread_id].generate_solution();
								// Evaluate the solution
								solution.grade = m_evolve_functions[thread_id].evaluate_solution(solution.solution);
							}
							
							std::sort(solutions.begin(), solutions.end());
							
							for (auto & solution : solutions)
							{
								hnc::out(log_level, log_level_t::solution_grade_log) << "  " << "  " << "  " << "  " << "Solution: " << solution << std::endl;
							}
						}
					}
					
					find_best_solution();
					
					// Evolve
					evolve();
				}
				
				/// @brief Return the number of generations
				/// @return the number of generations
				std::size_t nb_generation() const { return m_nb_generation; }
				
				/// @brief Return the number of time a solution was the best
				/// @return the number of time a solution was the bests
				std::size_t nb_same_solution() const { return m_nb_same_solution; }
				
				/// @brief Return the time elapsed in seconds
				/// @return the time elapsed in seconds
				long double time_elapsed() const { return hnc::time::s() - m_time_start; }
				
				/// @brief Return the actual best solution
				/// @return the actual best solution
				hnc::algo::genetic_algo::solution_grade_t<solution_t, grade_t> const & best_solution() const { return m_best_solution.get(); }
				
			private:
				
				/// @brief Solve the problem
				void evolve()
				{
					hnc::out(log_level, log_level_t::minimal_log) << "Evolve genetic algorithm" << std::endl;
					
					while
					(
						// Number of generations
						(nb_generation_max == 0 || nb_generation() <= nb_generation_max) &&
						// Time
						(max_time == 0 || time_elapsed() < max_time) &&
						// The best solution is the same
						(nb_same_solution_max == 0 || nb_same_solution() <= nb_same_solution_max) &&
						// User continue
						! m_evolve_functions[0].stop(best_solution().solution, best_solution().grade)
					)
					{
						hnc::out(log_level, log_level_t::minimal_log) << "  " << "Generation " << nb_generation() << " / " << nb_generation_max << " - Best solution = " << best_solution();
						if (log_level == log_level_t::minimal_log) { std::cout.flush(); }
						hnc::out(log_level, log_level_t::minimal_plus_log) << " (" << nb_same_solution() << " / " << nb_same_solution_max << " times with the same grade)" << std::endl;
						
						grade_t const best_solution_grade_previous = best_solution().grade;
						
						crossover_and_mutation();
						
						if (nb_generation() % nb_generation_between_island_migration == 0)
						{
							migration_between_islands();
						}
						
						if (nb_generation() % nb_generation_between_archipelago_migration == 0)
						{
							migration_between_archipelagos();
						}
						
						++m_nb_generation;
						
						if (best_solution().grade == best_solution_grade_previous)
						{
							++m_nb_same_solution;
						}
						else
						{
							m_nb_same_solution = 0;
						}
						
						hnc::out(log_level, log_level_t::minimal_log) << hnc::terminal::delete_line_string();
					}
					
					hnc::out(log_level, log_level_t::minimal_log) << "End at generation " << m_nb_generation << " / " << nb_generation_max << std::endl;
					hnc::out(log_level, log_level_t::minimal_log) << "The best solution is " << best_solution();
					hnc::out(log_level, log_level_t::minimal_plus_log) << " (" << nb_same_solution() << " / " << nb_same_solution_max << " times with the same grade)";
					hnc::out(log_level, log_level_t::minimal_log) << std::endl;
				}
				
				/// @brief Crossover & mutation
				void crossover_and_mutation()
				{
					hnc::out(log_level, log_level_t::minimal_plus_log) << "  " << "+ Crossover & mutation" << std::endl;
					
					// Do crossover and mutation
					for (std::size_t archipelago = 0; archipelago < m_solutions.size(); ++archipelago)
					{
						hnc::out(log_level, log_level_t::archipelago_log) << "  " << "  " << "Archipelago " << archipelago << "/" << m_solutions.size() << std::endl;
						
						#pragma omp parallel for
						for (std::size_t island = 0; island < m_solutions[archipelago].size(); ++island)
						{
							auto const thread_id = hnc::openmp::thread_id();
							
							hnc::out(log_level, log_level_t::island_log) << "  " << "  " << "  " << "Island " << island << "/" << m_solutions[archipelago].size() << std::endl;
							
							auto & solutions = m_solutions[archipelago][island];
							
							std::size_t const nb_solution = solutions.size();
							
							// Crossover and mutation
							for (std::size_t i = 0; i < nb_solution; ++i)
							{
								// Crossover
								if (m_random_probability[thread_id]() <= crossover_probability)
								{
									auto const random_solution_i = m_random_index[thread_id]();
									
									if (i != random_solution_i)
									{
										auto const & random_solution = solutions[random_solution_i];
										
										auto const new_solution = m_evolve_functions[thread_id].crossover
										(
											solutions[i].solution,
											random_solution.solution
										);
										
										hnc::out(log_level, log_level_t::solution_grade_log) << "  " << "  " << "  " << "  " << "Crossover: " << solutions[i] << " + " << random_solution << " -> " << solutions.back() << std::endl;
										
										solutions.emplace_back
										(
											new_solution,
											m_evolve_functions[thread_id].evaluate_solution(new_solution)
										);
									}
								}
								
								// Mutation
								if (m_random_probability[thread_id]() <= mutation_probability)
								{
									auto const new_solution = m_evolve_functions[thread_id].mutation(solutions[i].solution);
									
									hnc::out(log_level, log_level_t::solution_grade_log) << "  " << "  " << "  " << "  " << "Mutation:  " << solutions[i] << " -> " << solutions.back() << std::endl;
									
									solutions.emplace_back
									(
										new_solution,
										m_evolve_functions[thread_id].evaluate_solution(new_solution)
									);
								}
							}
							
							std::sort(solutions.begin(), solutions.end());
							
							solutions.resize(nb_solution);
							
							for (auto & solution : solutions)
							{
								hnc::out(log_level, log_level_t::solution_grade_log) << "  " << "  " << "  " << "  " << "Solution:  " << solution << std::endl;
							}
						}
					}
					
					find_best_solution();
				}

				/// @brief Migration between islands
				void migration_between_islands()
				{
					hnc::out(log_level, log_level_t::minimal_plus_log) << "  " << "+ Migration between islands" << std::endl;
					
					for (auto & archipelago : m_solutions)
					{
						hnc::out(log_level, log_level_t::archipelago_log) << "  " << "  " << "Archipelago" << std::endl;
						
						for (std::size_t island = 0; island < archipelago.size(); ++island)
						{
							hnc::out(log_level, log_level_t::island_log) << "  " << "  " << "  " << "Island " << island << "/" << archipelago.size() << std::endl;
							
							// Get previous island index
							std::size_t previous_island = (island == 0) ? (archipelago.size() - 1) : (island - 1);
							// Replace x worst solutions by the x bests
							for (std::size_t i = 0; i < nb_migration_per_island; ++i)
							{
								auto & worst_solution = archipelago[island][archipelago[island].size() - 1 - i];
								auto & best_solution = archipelago[previous_island][i];
								hnc::out(log_level, log_level_t::solution_grade_log) << "  " << "  " << "  " << worst_solution << " <- " << best_solution << std::endl;
								worst_solution = best_solution;
							}
							std::sort(archipelago[island].begin(), archipelago[island].end());
						}
					}
				}
				
				/// @brief Migration between archipelagos
				void migration_between_archipelagos()
				{
					hnc::out(log_level, log_level_t::minimal_plus_log) << "  " << "+ Migration between archipelagos" << std::endl;
					
					for (std::size_t archipelago = 0; archipelago < m_solutions.size(); ++archipelago)
					{
						hnc::out(log_level, log_level_t::archipelago_log) << "  " << "  " << "Archipelago " << archipelago << "/" << m_solutions.size() << std::endl;
							
						// Get previous archipelago index
						std::size_t previous_archipelago = (archipelago == 0) ? (m_solutions.size() - 1) : (archipelago - 1);
						// Replace x worst solutions by the x bests
						for (std::size_t i = 0; i < nb_migration_per_archipelago; ++i)
						{
							auto & worst_solution = m_solutions[archipelago][0][m_solutions[archipelago][0].size() - 1 - i];
							auto & best_solution = m_solutions[previous_archipelago][0][i];
							hnc::out(log_level, log_level_t::solution_grade_log) << "  " << "  " << "  " << "  " << worst_solution << " <- " << best_solution << std::endl;
							worst_solution = best_solution;
						}
						std::sort(m_solutions[archipelago][0].begin(), m_solutions[archipelago][0].end());
					}
				}
				
				/// @brief Update best solution
				void find_best_solution()
				{
					m_best_solution = std::cref(m_solutions[0][0][0]); // TODO Use std::reference_wrapper
					
					for (auto const & archipelago : m_solutions)
					{
						for (auto const & island : archipelago)
						{
							auto const & solution = island[0];
							
							if (solution.grade < m_best_solution.get().grade)
							{
								m_best_solution = std::cref(solution);
							}
							
						}
					}
				}
			};
		}
	}
}

#endif
