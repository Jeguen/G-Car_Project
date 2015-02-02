// Copyright © 2012, 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr
// Copyright © 2013 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HNC_ARGS_HPP
#define HNC_ARGS_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <tuple>

#include "to_type.hpp"
#include "hnc.hpp"


namespace hnc
{
	// Container to tuple
	namespace
	{
		// Compile-time counter
		template <std::size_t>
		class static_int_counter_args { };

		// Container to tuple
		// Read the tuple and affect the * iterator to the tuple with type conversion
		template <class iterator, class tuple, std::size_t n>
		void container_to_tuple(iterator const & it, tuple & t, static_int_counter_args<n>)
		{
			container_to_tuple(it, t, static_int_counter_args<n - 1>());
			using element_t = typename std::tuple_element<n, tuple>::type;
			std::get<n>(t) = hnc::to_<element_t>(*(it + n));
		}

		// Container to tuple, Last element
		template <class iterator, class tuple>
		void container_to_tuple(iterator const & it, tuple & t, static_int_counter_args<0>)
		{
			using element_t = typename std::tuple_element<0, tuple>::type;
			std::get<0>(t) = hnc::to_<element_t>(*it);
		}
	}
	
	/**
	 * @brief Easy utilisation of (int argc, char * * argv)
	 *
	 * @code
	   #include <hnc/args.hpp>
	   @endcode
	 * 
	 * Provides:
	 * - automatic build of help and usage strings
	 * - true / false return for argument without option
	 * - return your type choice (automatic conversion) for option with one argument
	 * - return a vector of your type choice (automatic conversion) for option with several same type arguments
	 * - return a tuple of your type choice (automatic conversion) for option with several (different type) arguments
	 * - automatic build of a vector of exception for errors
	 *
	 * Errors in vector exception are:
	 * - argument is "must be present" but not found
	 * - arguments list for one option are not all present
	 *
	 * Exemple:
	 * @code
	   // ./program_name --opt --int 42 --ints 21 42 73 --types "this is a" tuple with 5 elements
	   
	   #include <iostream>
	   
	   #include <hnc/args.hpp>
	   #include <hnc/ostream_std.hpp>
	   
	   
	   int main(int argc, char * * argv)
	   {
	   
	   	hnc::args args(argc, argv, "Description of your program", "Version & Author");
	   
	   	// One option without argument
	   	bool arg_opt = args.add_option({"--opt", "--option"}, "One option");
	   	// Option with one argument (last boolean means the option must be present, false by default)
	   	int arg_int = args.add_option({"--i", "--int"}, "n", "One integer", 0, true);
	   	// Option with a float (the return type depends on the 4th argument)
	   	float arg_float = args.add_option({"--float"}, "n", "One float", float(0));
	   	args.add_separator();
	   	// Option with several same type arguments
	   	auto arg_ints = args.add_option
	   	(
	   		{"--ints"}, {"n", "n", "n"}, "3 ints",
	   		{0, 0, 0}
	   	);
	   	// Option with several (different type) arguments
	   	auto arg_tuple = args.add_option
	   	(
	   		{"--types"}, {"s", "s", "s", "n", "s"}, "3 strings, 1 int, 1 string",
	   		std::make_tuple(std::string(""), std::string(""), std::string(""), 0, std::string(""))
	   	);
	   	args.add_separator();
	   	bool arg_version = args.add_option({"-v", "--version"}, "Display the version");
	   	bool arg_help    = args.add_option({"-h", "--help", "-?"}, "Display this help");
	   
	   	// Display the args (same as help)
	   	std::cout << args << std::endl;
	   	// You can display: args.usage(), args.help(), args.version() too
	   
	   	// Display the arguments
	   	std::cout << "Arguments:" << std::endl;
	   	for (auto const & arg : args.raw_args())
	   	{
	   		std::cout << "    " << arg << std::endl;
	   	}
	   	std::cout << std::endl;
	   
	   	// Display the option given
	   	std::cout << std::boolalpha;
	   	std::cout << "Options:" << std::endl;
	   	std::cout << "    " << "--opt   " << arg_opt << std::endl;
	   	std::cout << "    " << "--int   " << arg_int << std::endl;
	   	std::cout << "    " << "--float " << arg_float << std::endl;
	   	std::cout << "    " << "--ints  " << arg_ints << std::endl;
	   	std::cout << "    " << "--tuple " << arg_tuple << std::endl;
	   	std::cout << "    " << "-v      " << arg_version << std::endl;
	   	std::cout << "    " << "-h      " << arg_help << std::endl;
	   	std::cout << std::endl;
	   
	   	// Display the errors
	   	std::cout << "Errors:" << std::endl;
	   	for (auto const & error : args.errors())
	   	{
	   		std::cout << "    " << hnc::terminal::error << error.what() << hnc::terminal::color_reset << std::endl;
	   	}
	   	std::cout << std::endl;
	   
	   	return nb_test;
	   }
	   
	   // Output is:
	   
	   // Usage: program_name [--opt|--option] --i|--int <n> [--ints <n> <n> <n>] [--types <s> <s> <s> <n> <s>] [-v|--version] [-h|--help|-?]
	   //
	   // Description of your program
	   //
	   // --opt, --option         One option
	   // --i, --int <n>          One integer
	   //
	   // --ints <n, n, n>        3 ints
	   // --types <s, s, s, n, s> 3 strings, 1 int, 1 string
	   //
	   // -v, --version           Display the version
	   // -h, --help, -?          Display this help
	   //
	   // Version & Author
	   //
	   // Arguments:
	   //    program_name
	   //     --opt
	   //     --int
	   //     42
	   //     --ints
	   //     21
	   //     42
	   //     73
	   //     --types
	   //     this is a
	   //     tuple
	   //     with
	   //     5
	   //     elements
	   //
	   // Options:
	   //     --opt   true
	   //     --int   42
	   //     --ints  [size = 3 | 21 42 73]
	   //     --tuple (this is a, tuple, with, 5, elements)
	   //     -v      false
	   //     -h      false
	   //
	   // Errors:
	   //
	   @endcode
	 *
	 * @warning Arguments of any option (like \<n\> in --option \<n\>) can not begin by --
	 * @warning No safe-content conversion ! ("string" to int give 0)
	 *
	 * @note Consider Boost.Program_options
	 */
	class args
	{
	private:

		/// Raw arguments
		std::vector<std::string> m_args;

		/// Usage
		std::string m_usage;
		
		/// Description
		std::string m_description;

		/// Version & Author
		std::string m_version;

		/// Options and arguments and description
		std::vector<std::tuple<std::vector<std::string>, std::vector<std::string>, std::string>> m_opts_args_desc;

		/// Errors
		std::vector<std::invalid_argument> m_errors;
		
	public:

		/// @brief Constructor
		/// @param[in] args        Vector of arguments
		/// @param[in] description What the program does
		/// @param[in] version     Version, author, license
		args(std::vector<std::string> const & args, std::string const & description = "Description", std::string const & version = "Version & Author")
		:
			m_args(args), m_usage(""), m_description(description), m_version(version)
		{ }

		/// @brief Constructor
		/// @param[in] argc        Number of arguments
		/// @param[in] argv        Vector of arguments
		/// @param[in] description What the program does
		/// @param[in] version     Version, author, licence
		args(int const argc, char const * const * const argv, std::string const & description = "Description", std::string const & version = "Version & Author")
		:
			args(std::vector<std::string>(argv, argv + std::max(argc, 0)), description, version)
		{ }
		
		/// @brief Return original (raw) arguments
		/// @return original (raw) arguments
		std::vector<std::string> const & raw_args() const { return m_args; }

		/// @brief Add option without argument
		/// @param[in] opts        Possible string to get this option
		/// @param[in] description What the option does
		/// @return true if the option is found, else false
		bool add_option
		(
			std::vector<std::string> const & opts,
			std::string const & description
		)
		{
			// Save opts
			m_opts_args_desc.push_back(std::make_tuple(opts, std::vector<std::string>(0), description));
			// Add usage (optional)
			m_usage += "[";
			for (auto const & opt : opts)
			{
				m_usage += opt;
				if (&opt != &opts.back()) { m_usage = m_usage + "|"; }
			}
			m_usage += "] ";
			// Found the opt ?
			for (auto arg = m_args.begin() + 1; arg != m_args.end(); ++arg)
			{
				for (auto const & opt : opts)
				{
					if (opt == *arg) { return true; }
				}
			}
			return false;
		}

		/**
		 * @brief Add option with one argument
		 *
		 * Add a error if:
		 * - the option is found without argument
		 * - the option is not found and it must be present
		 *
		 * @param[in] opts            Possible string to get this option
		 * @param[in] opt_arg         Name of the argument option
		 * @param[in] description     What the option does
		 * @param[in] default_value   Value if option or argument option is not found
		 * @param[in] must_be_present Add an error if the option is not found
		 *
		 * @warning Argument can not begin by --
		 *
		 * @return argument value if the option and its argument is found, else the default value
		 */
		template <class T>
		T add_option
		(
			std::vector<std::string> const & opts,
			std::string const & opt_arg,
			std::string const & description,
			T const & default_value,
			bool const must_be_present = false
		)
		{
			// Save opts
			m_opts_args_desc.push_back(std::make_tuple(opts, std::vector<std::string>(1, opt_arg), description));
			// Add usage (optional)
			std::string opts_string = "";
			for (auto const & opt : opts)
			{
				opts_string += opt;
				if (&opt != &opts.back()) { opts_string += "|"; }
			}
			if (!must_be_present) { m_usage += "["; }
			m_usage += opts_string;
			m_usage += " ";
			m_usage += "<" + opt_arg + ">";
			if (!must_be_present) { m_usage += "]"; }
			m_usage += " ";
			// Found the opt ?
			{
				auto arg = m_args.begin() + 1;
				bool arg_found = false;
				while (arg != m_args.end() && !arg_found)
				{
					for (auto const & opt : opts)
					{
						if (opt == *arg) { arg_found = true; break; }
					}
					++arg;
				}
				// Option found
				if (arg_found)
				{
					// Get the opt_arg
					if (arg != m_args.end() && ( ((*arg).size() == 1) || ( (*arg).size() > 1 && ((*arg)[0] != '-' || (*arg)[1] != '-' )) ))
					{
						return hnc::to_<T>(*arg);
					}
					// Add error, opt_arg is not found
					else
					{
						m_errors.push_back(std::invalid_argument("The option {" + opts_string + "} is found without valid argument"));
					}
				}
				// Option not found
				else
				{
					// And must be present
					if (must_be_present)
					{
						m_errors.push_back(std::invalid_argument("The option {" + opts_string + "} is not found"));
					}
				}
			}
			return default_value;
		}

		/**
		 * @brief Add option with several same type arguments
		 *
		 * Add a error if:
		 * - the option is found without arguments
		 * - the option is not found and it must be present
		 *
		 * @param[in] opts            Possible string to get this option
		 * @param[in] opt_args        Name of the arguments option
		 * @param[in] description     What the option does
		 * @param[in] default_value   Value if option or argument option is not found
		 * @param[in] must_be_present Add an error if the option is not found
		 *
		 * @warning Argument can not begin by --
		 *
		 * @return argument value if the option and its argument is found, else the default value
		 */
		template <class T>
		std::vector<T> add_option
		(
			std::vector<std::string> const & opts,
			std::vector<std::string> const & opt_args,
			std::string const & description,
			std::vector<T> const & default_value,
			bool const must_be_present = false
		)
		{
			// Save opts
			m_opts_args_desc.push_back(std::make_tuple(opts, opt_args, description));
			// Add usage (optional)
			std::string opts_string = "";
			for (auto const & opt : opts)
			{
				opts_string += opt;
				if (&opt != &opts.back()) { opts_string += "|"; }
			}
			if (!must_be_present) { m_usage += "["; }
			m_usage += opts_string;
			m_usage += " ";
			for (auto const & opt_arg : opt_args)
			{
				m_usage += "<" + opt_arg;
				if (!must_be_present && &opt_arg == &opt_args.back())
				{ m_usage += ">] "; }
				else
				{ m_usage += "> "; }
			}
			// Found the opt ?
			{
				auto arg = m_args.begin() + 1;
				bool arg_found = false;
				while (arg != m_args.end() && !arg_found)
				{
					for (auto const & opt : opts)
					{
						if (opt == *arg) { arg_found = true; break; }
					}
					++arg;
				}
				// Option found
				if (arg_found)
				{
					std::vector<T> r;
					bool error = false;
					// Get the arguments option
					for (std::size_t i = 0; i < opt_args.size() && !error; ++i)
					{
						if (arg != m_args.end() && ( ((*arg).size() == 1) || ( (*arg).size() > 1 && ((*arg)[0] != '-' || (*arg)[1] != '-' )) ))
						{
							r.push_back(hnc::to_<T>(*arg));
						}
						else
						{
							error = true;
						}
						++arg;
					}
					// Get the arguments option
					if (!error)
					{
						return r;
					}
					// Add error, one of argument option is not found
					else
					{
						m_errors.push_back(std::invalid_argument("The option {" + opts_string + "} is found without valid arguments"));
					}
				}
				// Option not found
				else
				{
					// And must be present
					if (must_be_present)
					{
						m_errors.push_back(std::invalid_argument("The option {" + opts_string + "} is not found"));
					}
				}
			}
			return default_value;
		}

		/// @copydoc hnc::args::add_option(std::vector<std::string> const &,std::vector<std::string> const &,std::string const &,std::vector<T> const &,bool const)
		template <class T>
		std::vector<T> add_option
		(
			std::vector<std::string> const & opts,
			std::vector<std::string> const & opt_args,
			std::string const & description,
			std::initializer_list<T> const & default_value,
			bool const must_be_present = false
		)
		{ return add_option(opts, opt_args, description, std::vector<T>(default_value), must_be_present); }

		/**
		 * @brief Add option with several (different type) arguments
		 *
		 * Add a error if:
		 * - the option is found without arguments
		 * - the option is not found and it must be present
		 *
		 * @param[in] opts            Possible string to get this option
		 * @param[in] opt_args        Name of the arguments option
		 * @param[in] description     What the option does
		 * @param[in] default_value   Value if option or argument option is not found
		 * @param[in] must_be_present Add an error if the option is not found
		 *
		 * @warning Argument can not begin by --
		 *
		 * @return argument value if the option and its argument is found, else the default value
		 */
		template <class ... T>
		std::tuple<T ...> add_option
		(
			std::vector<std::string> const & opts,
			std::vector<std::string> const & opt_args,
			std::string const & description,
			std::tuple<T ...> const & default_value,
			bool const must_be_present = false
		)
		{
			// Save opts
			m_opts_args_desc.push_back(std::make_tuple(opts, opt_args, description));
			// Add usage (optional)
			std::string opts_string = "";
			for (auto const & opt : opts)
			{
				opts_string += opt;
				if (&opt != &opts.back()) { opts_string += "|"; }
			}
			if (!must_be_present) { m_usage += "["; }
			m_usage += opts_string;
			m_usage += " ";
			for (auto const & opt_arg : opt_args)
			{
				m_usage += "<" + opt_arg;
				if (!must_be_present && &opt_arg == &opt_args.back())
				{ m_usage += ">] "; }
				else
				{ m_usage += "> "; }
			}
			// Found the opt ?
			{
				auto arg = m_args.begin() + 1;
				bool arg_found = false;
				while (arg != m_args.end() && !arg_found)
				{
					for (auto const & opt : opts)
					{
						if (opt == *arg) { arg_found = true; break; }
					}
					++arg;
				}
				// Option found
				if (arg_found)
				{
					bool error = false;
					auto first_arg = arg;
					// Check if the arguments option are valid
					for (std::size_t i = 0; i < opt_args.size() && !error; ++i)
					{
						if (arg != m_args.end() && ( ((*arg).size() == 1) || ( (*arg).size() > 1 && ((*arg)[0] != '-' || (*arg)[1] != '-' )) ))
						{ }
						else
						{ error = true; }
						++arg;
					}
					// Vector to tuple
					if (!error)
					{
						std::tuple<T ...> r = default_value;
						// Vector to tuple
						container_to_tuple(first_arg, r, static_int_counter_args<sizeof...(T) - 1>());
						// Return
						return r;
					}
					// Add error, one of argument option is not found
					else
					{
						m_errors.push_back(std::invalid_argument("The option {" + opts_string + "} is found without valid arguments"));
					}
				}
				// Option not found
				else
				{
					// And must be present
					if (must_be_present)
					{
						m_errors.push_back(std::invalid_argument("The option {" + opts_string + "} is not found"));
					}
				}
			}
			return default_value;
		}

		/// @copydoc hnc::args::add_option(std::vector<std::string> const &,std::vector<std::string> const &,std::string const &,std::tuple<T ...> const &,bool const)
		template <class ... T>
		std::tuple<T ...> add_option
		(
			std::vector<std::string> const & opts,
			std::initializer_list<std::string> const & opt_args,
			std::string const & description,
			std::tuple<T ...> const & default_value,
			bool const must_be_present = false
		)
		{ return add_option(opts, std::vector<std::string>(opt_args), description, default_value, must_be_present); }

		/// @brief Add a separator (one line) in the help text
		/// @param[in] line Line to display, empty string by default
		void add_separator(std::string const & line = "")
		{
			m_opts_args_desc.push_back(std::make_tuple(std::vector<std::string>(1, line), std::vector<std::string>(0), ""));
		}

		/// @brief Return the errors
		/// @return the errors
		std::vector<std::invalid_argument> const & errors()
		{
			return m_errors;
		}

		/// @brief Return the usage
		/// @return the usage
		std::string usage() const
		{
			return ("Usage: " + m_args.at(0) + " " + m_usage + "\n");
		}

		/// @brief Return the help
		/// @return the help
		std::string help() const
		{
			std::string help;
			help += "\n";
			// Usage
			{
				help += usage();
				help += "\n";
			}
			// Description
			{
				help = help + m_description + "\n";
				help += "\n";
			}
			// Options
			{
				// Get max size of the options + argument option
				std::size_t opt_max_size = 0;
				for (auto const & opts_args_desc : m_opts_args_desc)
				{
					std::size_t opt_size = 0;
					// Name option
					for (auto const & opt : std::get<0>(opts_args_desc))
					{ opt_size += opt.size() + 2; } opt_size -= 2;
					opt_size += 1;
					// Arguments option
					for (auto const & arg : std::get<1>(opts_args_desc))
					{
						if (&arg == &std::get<1>(opts_args_desc).front() && &arg == &std::get<1>(opts_args_desc).back())
						{ opt_size += arg.size() + 3; }
						else if (&arg == &std::get<1>(opts_args_desc).front())
						{ opt_size += arg.size() + 1; }
						else if (&arg == &std::get<1>(opts_args_desc).back())
						{ opt_size += arg.size() + 4; }
						else
						{ opt_size += arg.size() + 2; }
					}
					// Update opt_max_size
					opt_max_size = std::max(opt_max_size, opt_size);
				}
				// Display options
				for (auto const & opts_args_desc : m_opts_args_desc)
				{
					std::size_t opt_size = 0;
					// Name option
					for (auto const & opt : std::get<0>(opts_args_desc))
					{
						help = help + opt;
						opt_size += opt.size();
						if (&opt != &std::get<0>(opts_args_desc).back()) { help += ", "; opt_size += 2; }
					}
					help += " "; opt_size += 1;
					// Arguments option
					for (auto const & arg : std::get<1>(opts_args_desc))
					{
						if
						(
							&arg == &std::get<1>(opts_args_desc).front() &&
							&arg == &std::get<1>(opts_args_desc).back()
						)
						{
							help = help + "<" + arg + "> "; opt_size += arg.size() + 3;
						}
						else if (&arg == &std::get<1>(opts_args_desc).front())
						{
							help = help + "<" + arg; opt_size += arg.size() + 1;
						}
						else if (&arg == &std::get<1>(opts_args_desc).back())
						{
							help = help + ", " + arg + "> "; opt_size += arg.size() + 4;
						}
						else
						{
							help = help + ", " + arg; opt_size += arg.size() + 2;
						}
					}
					// Description argument
					help += std::string(opt_max_size - opt_size, ' ') + std::get<2>(opts_args_desc) + "\n";
				}
				help += "\n";
			}
			// Version, author, license
			{
				help = help + m_version + "\n";
			}
			return help;
		}

		/// @brief Return the version, author, license
		/// @return the version, author, license
		std::string version() const
		{
			return m_version;
		}

		/// @brief Return the description
		/// @return the description
		std::string description() const
		{
			return m_description;
		}

		/**
		 * @brief Return the bash completion script
		 * 
		 * http://www.debian-administration.org/article/An_introduction_to_bash_completion_part_2
		 * 
		 * @return the description
		 */
		std::string bash_completion() const
		{
			// Comment
			std::string bash_completion = "";
			bash_completion += "# bash completion for " + m_args[0] + " generated by hnc " + hnc::version() + " codename " + hnc::codename() + "\n";
			bash_completion += "# You can put this file in your /etc/bash_completion.d/ or source it or write it in your ~/.bashrc or ~/.profile\n";
			bash_completion += "\n";
			// Progam name
			bash_completion += "_" + m_args[0] + "()\n";
			bash_completion += "{\n";
			// Variables
			bash_completion += "\tlocal cur prev opts base\n";
			bash_completion += "\tCOMPREPLY=()\n";
			bash_completion += "\tcur=\"${COMP_WORDS[COMP_CWORD]}\"\n";
			bash_completion += "\tprev=\"${COMP_WORDS[COMP_CWORD-1]}\"\n";
			bash_completion += "\n";
			// Arguments for options
			{
				bash_completion += "\tcase \"${prev}\" in\n";
				for (auto const & opts_args_desc : m_opts_args_desc)
				{
					// Skip separator
					if (std::get<0>(opts_args_desc).size() == 1 && std::get<1>(opts_args_desc).empty() && std::get<2>(opts_args_desc).empty()) { }
					// Skip no arg option
					else if (std::get<1>(opts_args_desc).empty())
					{ }
					// Standard option
					else
					{
						for (auto const & opt : std::get<0>(opts_args_desc))
						{
							bash_completion += "\t\t" + opt + ")\n";
							if (! std::get<1>(opts_args_desc).empty())
							{
								std::string args;
								for (auto const & arg : std::get<1>(opts_args_desc))
								{
									args += "<" + arg + "> ";
								}
								bash_completion += "\t\t\tCOMPREPLY=(\"" + args + "\")\n";
								bash_completion += "\t\t\treturn 0\n";
							}
							bash_completion += "\t\t;;\n";
						}
					}
				}
				bash_completion += "\t\t*)\n";
				bash_completion += "\t\t;;\n";
				bash_completion += "\tesac\n";
				bash_completion += "\n";
			}
			// Options
			{
				std::string options;
				for (auto const & opts_args_desc : m_opts_args_desc)
				{
					// Skip separator
					if (std::get<0>(opts_args_desc).size() == 1 && std::get<1>(opts_args_desc).empty() && std::get<2>(opts_args_desc).empty()) { }
					// Standard option
					else
					{
						for (auto const & opt : std::get<0>(opts_args_desc))
						{
							options += opt + " ";
						}
						}
				}
				bash_completion += "\tCOMPREPLY=($(compgen -W \"" + options + "\" -- ${cur}))\n";
				bash_completion += "\n";
				bash_completion += "\treturn 0\n";
			}
			// End
			bash_completion += "}\n";
			bash_completion += "complete -o default -o nospace -F _" + m_args[0] + " " + m_args[0] + "\n";
			// Return
			return bash_completion;
		}
	};
	
	/// @brief Operator << between a std::ostream and a hnc::args
	/// @param[in,out] o    Output stream
	/// @param[in]     args A hnc::args
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, hnc::args const & args)
	{
		o << args.help();
		return o;
	}
}

#endif
