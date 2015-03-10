// Copyright © 2013, 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef HNC_FILESYSTEM_HPP
#define HNC_FILESYSTEM_HPP

#include <string>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <vector>

#include "except.hpp"
#include "unused.hpp"

#ifdef hnc_unix
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <pwd.h>
	#include <dirent.h>
#endif

#ifdef hnc_windows
	#include <Windows.h>
	#include <Shlobj.h>
	#include <Shlwapi.h>
#endif

namespace hnc
{
	/**
	 * @brief Basic manipulation of files and directory
	 *
	 * @code
	   #include <hnc/filesystem.hpp>
	   @endcode
	 *
	 * @image html hnc_filesystem.png
	 * @image latex hnc_filesystem.eps
	 *
	 * @note The default directory separator is '/', use hnc::filesystem::directory_separator to change it
	 * 
	 * @note Consider Boost.Filesystem and C++14
	 */
	namespace filesystem
	{
		// Pathname operations
		
		/**
		 * @brief Directory separator (e.g. '/' by default, '/' on GNU/Linux and all (including Windows), '\' for Windows only)
		 * 
		 * The default directory separator is '/', works on GNU/Linux, Unix and Windows
		 *
		 * http://en.wikipedia.org/wiki/Path_%28computing%29
		 */
		namespace directory_separator
		{
			/// @brief Default (common) directory separator: GNU/Linux, Unix, BSD, Android, MAC OS X, ... and Windows
			char const common = '/';

			/// @brief Directory separator for Windows only
			char const windows = '\\';

			/// @brief Directory separator for Classic Mac OS
			char const classic_mac_os = ':';

			/// @brief Directory separator for TOPS-20, RSX-11, OpenVMS, RISC OS, NonStop Kernel
			char const dot = '.';

			/// @brief Directory separator for Stratus VOS
			char const greater_than = '>';
		}

		/**
		 * @brief Return the filename of a pathname
		 * 
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname            Pathname
		 * @param[in] directory_separator Directory separator char (hnc::filesystem::directory_separator::common by default)
		 *
		 * @return the filename of a pathname
		 */
		std::string filename
		(
			std::string const & pathname,
			char const directory_separator = hnc::filesystem::directory_separator::common
		)
		{
			// Get last separator
			auto it = std::find(pathname.rbegin(), pathname.rend(), directory_separator);
			// Separator found
			if (it != pathname.rend())
			{
				return std::string(it.base(), pathname.end());
			}
			// No separator found
			else
			{
				return pathname;
			}
		}

		/**
		 * @brief Return the dirname of a pathname (without the final directory separator)
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname            Pathname
		 * @param[in] directory_separator Directory separator char (hnc::filesystem::directory_separator::common by default)
		 *
		 * @return the dirname of a pathname (without the final directory separator)
		 */
		std::string dirname
		(
			std::string const & pathname,
			char const directory_separator = hnc::filesystem::directory_separator::common
		)
		{
			// Get last separator
			auto it = std::find(pathname.rbegin(), pathname.rend(), directory_separator);
			// Separator found
			if (it != pathname.rend())
			{
				++it;
				return std::string(pathname.begin(), it.base());
			}
			// No separator found
			else
			{
				return "";
			}
		}

		/**
		 * @brief Return the basename of a pathname
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname            Pathname
		 * @param[in] directory_separator Directory separator char (hnc::filesystem::directory_separator::common by default)
		 *
		 * @return the basename of a pathname
		 */
		std::string basename
		(
			std::string const & pathname,
			char const directory_separator = hnc::filesystem::directory_separator::common
		)
		{
			// Get filename
			std::string filename = hnc::filesystem::filename(pathname, directory_separator);
			// Get last separator
			auto it = std::find(filename.rbegin(), filename.rend(), '.');
			// Separator found
			if (it != filename.rend())
			{
				++it;
				return std::string(filename.begin(), it.base());
			}
			// No separator found
			else
			{
				return filename;
			}
		}

		/**
		 * @brief Return the dirname and the basename of a pathname
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname            Pathname
		 * @param[in] directory_separator Directory separator char (hnc::filesystem::directory_separator::common by default)
		 *
		 * @return the dirname and the basename of a pathname
		 */
		std::string dir_and_basename
		(
			std::string const & pathname,
			char const directory_separator = hnc::filesystem::directory_separator::common
		)
		{
			// Dirname
			std::string dirname = hnc::filesystem::dirname(pathname, directory_separator);
			// Basename
			std::string basename = hnc::filesystem::basename(pathname, directory_separator);

			// Return
			if (dirname.empty()) { return basename; }
			else if (basename.empty()) { return dirname + directory_separator; }
			else { return dirname + directory_separator + basename; }
		}

		/**
		 * @brief Return the extension of a file (without the '.')
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname            Pathname
		 * @param[in] directory_separator Directory separator char (hnc::filesystem::directory_separator::common by default)
		 *
		 * @return the extension of a file (without the '.')
		 */
		std::string extension
		(
			std::string const & pathname,
			char const directory_separator = hnc::filesystem::directory_separator::common
		)
		{
			// Get filename
			std::string filename = hnc::filesystem::filename(pathname, directory_separator);
			// Get last separator
			auto it = std::find(filename.rbegin(), filename.rend(), '.');
			// Separator found
			if (it != filename.rend())
			{
				return std::string(it.base(), filename.end());
			}
			// No separator found
			else
			{
				return "";
			}
		}

		/**
		 * @brief Add prefix (before the basename, after the dirname)
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname            Pathname
		 * @param[in] prefix              Prefix to add
		 * @param[in] directory_separator Directory separator char (hnc::filesystem::directory_separator::common by default)
		 *
		 * @return the pathname with the prefix
		 */
		std::string add_prefix
		(
			std::string const & pathname,
			std::string const & prefix,
			char const directory_separator = hnc::filesystem::directory_separator::common
		)
		{
			// Get dirname with separator
			std::string const dirname = [&pathname, &directory_separator]() -> std::string
			{
				std::string r = hnc::filesystem::dirname(pathname);
				if (r != "") { r += directory_separator; }
				return r;
			}();
			// Get basename
			std::string const basename = hnc::filesystem::basename(pathname);
			// Get extension with .
			std::string const extension = [&pathname]() -> std::string
			{
				std::string r = hnc::filesystem::extension(pathname);
				if (r != "") { r = "." + r; }
				return r;
			}();
			// Return
			return dirname + prefix + basename + extension;
		}

		/**
		 * @brief Add suffix (after the basename, before the extension)
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname            Pathname
		 * @param[in] suffix              Suffix to add
		 * @param[in] directory_separator Directory separator char (hnc::filesystem::directory_separator::common by default)
		 *
		 * @return the pathname with the suffix
		 */
		std::string add_suffix
		(
			std::string const & pathname,
			std::string const & suffix,
			char const directory_separator = hnc::filesystem::directory_separator::common
		)
		{
			// Get dirname with separator
			std::string const dirname = [&pathname, &directory_separator]() -> std::string
			{
				std::string r = hnc::filesystem::dirname(pathname);
				if (r != "") { r += directory_separator; }
				return r;
			}();
			// Get basename
			std::string const basename = hnc::filesystem::basename(pathname);
			// Get extension with .
			std::string const extension = [&pathname]() -> std::string
			{
				std::string r = hnc::filesystem::extension(pathname);
				if (r != "") { r = "." + r; }
				return r;
			}();
			// Return
			return dirname + basename + suffix + extension;
		}

		// I/O operations

		/**
		 * @brief Return true if the file exists, false otherwise
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname Pathname of the file
		 *
		 * @return true if the file exists, false otherwise
		 */
		bool file_exists(std::string const & pathname)
		{
			std::ifstream f(pathname);
			return bool(f);
		}

		/**
		 * @brief Return true if we can read the file, false otherwise
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname Pathname of the file
		 *
		 * @return true if we can read the file, false otherwise
		 */
		bool file_is_readable(std::string const & pathname)
		{
			return hnc::filesystem::file_exists(pathname);
		}

		/**
		 * @brief Return true if we can write the file, false otherwise
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname Pathname of the file
		 *
		 * @return true if we can write the file, false otherwise
		 */
		bool file_is_writeable(std::string const & pathname)
		{
			if (hnc::filesystem::file_exists(pathname))
			{
				std::ofstream f(pathname, std::ofstream::out | std::ofstream::app);
				return bool(f);
			}
			else
			{
				return false;
			}
		}

		/**
		 * @brief Remove a file (with remove function from cstdio)
		 *
		 * http://www.cplusplus.com/reference/cstdio/remove/
		 * 
		 * @param[in] pathname Pathname
		 */
		void remove(std::string const & pathname)
		{
			std::remove(pathname.c_str());
		}

		/**
		 * @brief Copy a file
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * http://stackoverflow.com/questions/10195343/copy-a-file-in-an-sane-safe-and-efficient-way
		 *
		 * @param[in] source_filename      Source filename
		 * @param[in] destination_filename Destination filename
		 */
		void copy_file(std::string const & source_filename, std::string const & destination_filename)
		{
			std::ifstream  source(source_filename, std::ios::binary);
			std::ofstream  destination(destination_filename, std::ios::binary);

			destination << source.rdbuf();
		}

		/**
		 * @brief Read whole text file
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * http://insanecoding.blogspot.fr/2011/11/how-to-read-in-file-in-c.html
		 *
		 * @param[in] filename Text filename
		 *
		 * @return A std::string that contains the whole text file. If file is not ok, returns empty string
		 */
		std::string read_file(std::string const & filename)
		{
			std::ifstream f(filename, std::ios::in | std::ios::binary);

			// File ok
			if (f)
			{
				// Get the size
				f.seekg(0, std::ios::end);
				std::string r(std::size_t(f.tellg()), '\0');

				// Rewind the file
				f.seekg(0, std::ios::beg);

				// Read (and close) the file
				f.read(&r[0], std::streamsize(r.size()));
				f.close();

				// Return
				return r;
			}
			// File not ok
			else
			{
				return std::string();
			}
		}

		// Filename generation

		/**
		 * @brief Return a temporary filename (with tmpnam function from cstdio)
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * http://www.cplusplus.com/reference/cstdio/tmpnam/
		 *
		 * @return the temporary filename
		 */
		std::string tmp_filename()
		{
			// mkstemp
			#ifdef hnc_unix
			
				// Generate filename
				char filename_buffer[] = "/tmp/XXXXXXXX\0";
				int r = mkstemp(filename_buffer);
				hnc_unused(r);
				std::string const filename = filename_buffer;
				
			// std::tmpnam
			#else
				
				// Generate filename
				char filename_buffer[L_tmpnam];
				std::tmpnam(filename_buffer);
				std::string const filename = filename_buffer;
				
				// fopen and fclose file (else fstream does not work...)
				FILE * f = std::fopen(filename.c_str(), "w");
				std::fclose(f);
				
			#endif
			
			// Return
			return filename;
		}

		/**
		 * @brief Return a available filename based on user's proposition (no safe in multi-thread context)
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] pathname_wanted Pathname wanted
		 * @param[in] separator       Separator between pathname wanted and number is the function generate a filename
		 * @param[in] directory_separator Directory separator char (hnc::filesystem::directory_separator::common by default)
		 *
		 * @return a available filename
		 */
		std::string filename_without_overwrite
		(
			std::string const & pathname_wanted,
			std::string const & separator = "_",
			char const directory_separator = hnc::filesystem::directory_separator::common
		)
		{
			// File does not exist
			if (hnc::filesystem::file_exists(pathname_wanted) == false)
			{
				return pathname_wanted;
			}
			// File exists
			else
			{
				// Find the next available pathname
				std::string available_pathname;
				unsigned int i = 0;
				do
				{
					available_pathname = hnc::filesystem::add_suffix(pathname_wanted, separator + std::to_string(i), directory_separator);
					++i;
				}
				while (hnc::filesystem::file_exists(available_pathname) == true);
				// Return
				return available_pathname;
			}
		}
		
		// file, directory
		
		/**
		 * @brief Test if path is a file
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] path Path of the supposed file
		 *
		 * @return true if the path is a file, false otherwise
		 */
		bool is_a_file(std::string const & path)
		{
			#ifdef hnc_unix
				
				struct stat s;
				stat(path.c_str(), &s);
				
				if ((s.st_mode & S_IFMT) == S_IFREG) { return true; }
				else { return false; }
				
			#elif hnc_windows
				
				// http://msdn.microsoft.com/en-us/library/bb773621%28VS.85%29.aspx
				return (PathIsDirectory(path.c_str()) == false);
				
			#else
				
				throw hnc::except::incomplete_implementation("hnc::filesystem::is_a_file is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}
		
		/**
		 * @brief Test if path is a directory
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] path Path of the supposed directory
		 *
		 * @return true if the path is a directory, false otherwise
		 */
		bool is_a_directory(std::string const & path)
		{
			#ifdef hnc_unix
				
				struct stat s;
				stat(path.c_str(), &s);
				
				if ((s.st_mode & S_IFMT) == S_IFDIR) { return true; }
				else { return false; }
				
			#elif hnc_windows
				
				// http://msdn.microsoft.com/en-us/library/bb773621%28VS.85%29.aspx
				return PathIsDirectory(path.c_str());
				
			#else
				
				throw hnc::except::incomplete_implementation("hnc::filesystem::is_a_directory is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}
		
		/**
		 * @brief Test if path is executable
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] path Path
		 * 
		 * @note One Microsoft Windows, an executable is a file with "exe" extension
		 *
		 * @return true if the path is executable, false otherwise
		 */
		bool is_executable(std::string const & path)
		{
			#ifdef hnc_unix
				
				return (access(path.c_str(), X_OK) == 0);
				
			#elif hnc_windows
				
				return (hnc::filesystem::extension(path) == "exe");
				
			#else
				
				throw hnc::except::incomplete_implementation("hnc::filesystem::is_executable is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}
		
		/**
		 * @brief List all files and directories of a directory
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] path Path of the directory
		 *
		 * @return the list of files and directories
		 */
		std::vector<std::string> read_directory(std::string const & path)
		{
			// http://stackoverflow.com/questions/612097/how-can-i-get-a-list-of-files-in-a-directory-using-c-or-c
			
			#ifdef hnc_unix
				
				std::vector<std::string> r;
				
				DIR * dir = opendir(path.c_str());
				
				if (dir != nullptr)
				{
					struct dirent * ent = nullptr;
					
					while ((ent = readdir(dir)) != nullptr)
					{
						r.emplace_back(ent->d_name);
					}
					
					closedir(dir);
				}
				
				return r;
				
			#elif hnc_windows
				
				std::vector<std::string> r;
				
				WIN32_FIND_DATA find_file_data;
				HANDLE h_find = FindFirstFile((path + "/*").c_str(), &find_file_data);
				
				while (h_find != INVALID_HANDLE_VALUE)
				{
					r.emplace_back(find_file_data.cFileName);
					
					if (FindNextFile(h_find, &find_file_data) == 0)
					{
						FindClose(h_find);
						h_find = INVALID_HANDLE_VALUE;
					}
				}
				
				return r;
				
			#else
				
				throw hnc::except::incomplete_implementation("hnc::filesystem::read_directory is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}
		
		/**
		 * @brief Create a directory
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @param[in] path Path of the directory
		 *
		 * @return true if directory is created, false otherwise
		 */
		bool create_directory(std::string const & path)
		{
			#ifdef hnc_unix
			
				// http://linux.die.net/man/3/mkdir
				int const status = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
				return (status == 0);
				
			#elif hnc_windows
				
				// http://stackoverflow.com/questions/8931196/createdirectory-windows-api-usage-in-c
				// http://msdn.microsoft.com/en-us/library/windows/desktop/aa363855%28v=vs.85%29.aspx
				auto const r = CreateDirectory(path.c_str(), NULL);
				return bool(r);
				
			#else
				
				throw hnc::except::incomplete_implementation("hnc::filesystem::create_directory is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}

		/**
		 * @brief Get home directory
		 *
		 * @code
		   #include <hnc/filesystem.hpp>
		   @endcode
		 *
		 * @return the home directory
		 */
		std::string home()
		{
			#ifdef hnc_unix
			
				struct passwd const * const pw = getpwuid(getuid());
				return pw->pw_dir;
				
			#elif hnc_windows
				
				// http://stackoverflow.com/questions/9542611/how-to-get-the-current-users-home-directory-in-windows
				// http://msdn.microsoft.com/en-us/library/windows/desktop/bb762181.aspx
				wchar_t path_wchar[MAX_PATH];
				SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path_wchar);
				
				// http://www.cplusplus.com/forum/general/39766/
				char path_char[MAX_PATH * 8];
				char char_def = ' ';
				WideCharToMultiByte(CP_ACP, 0, path_wchar, -1, path_char, 260, &char_def, NULL);
				
				return path_char;
				
			#else
				
				char const * const r = std::getenv("HOME");
				if (r != nullptr) { return r; }
				
				throw hnc::except::incomplete_implementation("hnc::filesystem::home is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}
	}
}

#endif
