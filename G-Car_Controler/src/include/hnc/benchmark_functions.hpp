// Copyright © 2012-2014 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_BENCHMARK_FUNCTIONS_HPP
#define HNC_BENCHMARK_FUNCTIONS_HPP

#include <vector>
#include <functional>
#include <algorithm>

#include "benchmark.hpp"
#include "gnuplot.hpp"
#include "tabular.hpp"


namespace hnc
{
	/**
	 * @brief Performs a benchmark with some functions
	 * 
	 * @code
	   #include <hnc/benchmark_functions.hpp>
	   @endcode
	 *
	 * User give a vector of functions. hnc::benchmark_functions performs benchmarks and output:
	 * - raw times in a hnc::benchmark
	 * - a Gnuplot image with the median of times for each versions in a hnc::gnuplot::gnuplot_boxes
	 * - a tabular with the median of times for each versions in a hnc::tabular
	 *
	 * @param[in] versions_with_name      A std::vector of { function, name }
	 * @param[in] title                   Title for Gnuplot and tabular
	 * @param[in] gnuplot_output_filename Gnuplot output file
	 * @param[in] nb_run                  Number of runs for each version
	 * @param[in] x_label                 Gnuplot x label ("Versions" by default)
	 * @param[in] y_label                 Gnuplot y label ("Time (in second)" by default)
	 *
	 * Example:
	 * @code
	   // #include <hnc/benchmark_functions.hpp>
	   // #include <hnc/sleep.hpp>
	   // #include <hnc/system.hpp>
	   
	   auto benchmark_functions = hnc::benchmark_functions
	   (
	   	{
	   		{ []() -> void { hnc::sleep::ms(20); }, "v0" },
	   		{ []() -> void { hnc::sleep::ms(40); }, "v1" },
	   		{ []() -> void { hnc::sleep::ms(60); }, "v2" },
	   		{ []() -> void { hnc::sleep::ms(80); }, "v3" },
	   		{ []() -> void { hnc::sleep::ms(30); }, "v4" },
	   		{ []() -> void { hnc::sleep::ms(50); }, "v5" },
	   		{ []() -> void { hnc::sleep::ms(60); }, "v6" }
	   	},
	   	"Title",
	   	"hnc_benchmark_functions_gnuplot",
	   	3
	   );
	   hnc::benchmark const & benchmark = std::get<0>(benchmark_functions);
	   hnc::gnuplot::gnuplot_boxes & gnuplot = std::get<1>(benchmark_functions);
	   hnc::tabular const & tabular = std::get<2>(benchmark_functions);
	   
	   // Bench
	   std::cout << benchmark << std::endl;
	   std::cout << std::endl;
	   
	   // Gnuplot
	   std::cout << gnuplot.script() << std::endl;
	   std::cout << gnuplot.data().at(0).second << std::endl;
	   std::cout << std::endl;
	   gnuplot.write_script_in_file();
	   gnuplot.write_data_in_file();
	   hnc::system("gnuplot", gnuplot.script_filename());
	   
	   // Tabular
	   std::cout << tabular << std::endl;
	   std::cout << std::endl;
	   @endcode
	   
	   Gnuplot:
	   \image html hnc_benchmark_functions_gnuplot.png
	   \image latex hnc_benchmark_functions_gnuplot.eps
	   
	   Tabular:
	   @code
	   // Title
	   // ---------------------------------------------------------------------------------------------------
	   // | v0          | v1          | v2          | v3          | v4          | v5          | v6          |
	   // ---------------------------------------------------------------------------------------------------
	   // | 0.020067159 | 0.040065594 | 0.060067431 | 0.080070083 | 0.030068953 | 0.050067764 | 0.060067917 |
	   // ---------------------------------------------------------------------------------------------------
	   @endcode
	 * 
	 * @return the benchmark with all times, the gnuplot and the tabular with the median times 
	 */
	std::tuple
	<
		hnc::benchmark,
		hnc::gnuplot::gnuplot_boxes,
		hnc::tabular
	>
	benchmark_functions
	(
		std::vector<std::pair<std::function<void()>, std::string>> const & versions_with_name,
		std::string const & title,
		std::string const & gnuplot_output_filename,
		std::size_t const nb_run = 1,
		std::string const & x_label = "Versions",
		std::string const & y_label = "Time (in second)"
	)
	{
		// Benchmark
		hnc::benchmark benchs;
		
		// Runs
		for (std::size_t run = 0; run < nb_run; ++run)
		{
			// Versions
			for (auto const & version_with_name : versions_with_name)
			{
				auto const & version = version_with_name.first;
				auto const & name = version_with_name.second;
				// Get benchmark
				auto & bench = benchs[name];
				// Run
				bench.start();
				version();
				bench.stop();
			}
		}

		// Extract mean
		std::map<std::string, long double> benchs_mean = benchmark_extract_mean(benchs);

		// Create the GNUPlot script
		hnc::gnuplot::gnuplot_boxes gp
		(
			hnc::gnuplot::output_terminal_pdf(gnuplot_output_filename),
			benchs_mean
		);
		gp.set_title(title);
		gp.set_x_label(x_label);
		gp.set_y_label(y_label);
		gp.plot().no_title();

		// Create data for tabular
		std::vector<std::vector<long double>> tabular_data(1);
		std::vector<std::string> tabular_header;
		for (auto const & bench_mean : benchs_mean)
		{
			tabular_header.push_back(bench_mean.first);
			tabular_data[0].push_back(bench_mean.second);
		}
		
		// Create the tabular LaTeX
		hnc::tabular tabular(tabular_data, title, tabular_header);

		// Return
		return std::make_tuple(benchs, gp, tabular);
	}
}

#endif
