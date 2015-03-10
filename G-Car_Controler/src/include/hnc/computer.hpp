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


#ifndef HNC_COMPUTER_HPP
#define HNC_COMPUTER_HPP

#include <iostream>
#include <string>
#include <fstream>

#ifdef hnc_unix
	#include <sys/utsname.h>
	#include <sys/types.h>
	#include <sys/sysctl.h>
#endif

#ifdef hnc_windows
	#include <Windows.h>
#endif

#include "to_string.hpp"
#include "string.hpp"


namespace hnc
{
	/**
	 * @brief Get informations on computer
	 *
	 * @code
	   #include <hnc/computer.hpp>
	   @endcode
	 */
	namespace computer
	{
		/**
		 * @brief Get the name of the operating system
		 * 
		   @code
		   	#include <hnc/computer.hpp>
		   @endcode
		 * 
		 * @return the name of the operating system
		 */
		inline std::string system_name()
		{
			#ifdef hnc_unix
			
				struct utsname infos;
				uname(&infos);
				
				return std::string(infos.sysname);
				
			#elif hnc_windows
				
				// http://msdn.microsoft.com/en-us/library/windows/desktop/ms724833%28v=vs.85%29.aspx
				
				OSVERSIONINFOEX infos;
				ZeroMemory(&infos, sizeof(OSVERSIONINFOEX));
				infos.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
				GetVersionEx((OSVERSIONINFO *)(&infos));
				
				SYSTEM_INFO infos_sys;
				GetSystemInfo(&infos_sys); 
				
				if (infos.dwMajorVersion == 6 && infos.dwMinorVersion == 3 && infos.wProductType == VER_NT_WORKSTATION)
				{
					return "Windows 8.1";
				}
				else if (infos.dwMajorVersion == 6 && infos.dwMinorVersion == 3 && infos.wProductType != VER_NT_WORKSTATION)
				{
					return "Windows Server 2012 R2";
				}
				else if (infos.dwMajorVersion == 6 && infos.dwMinorVersion == 2 && infos.wProductType == VER_NT_WORKSTATION)
				{
					return "Windows 8";
				}
				else if (infos.dwMajorVersion == 6 && infos.dwMinorVersion == 2 && infos.wProductType != VER_NT_WORKSTATION)
				{
					return "Windows Server 2012";
				}
				else if (infos.dwMajorVersion == 6 && infos.dwMinorVersion == 1 && infos.wProductType == VER_NT_WORKSTATION)
				{
					return "Windows 7";
				}
				else if (infos.dwMajorVersion == 6 && infos.dwMinorVersion == 1 && infos.wProductType != VER_NT_WORKSTATION)
				{
					return "Windows Server 2008 R2";
				}
				else if (infos.dwMajorVersion == 6 && infos.dwMinorVersion == 0 && infos.wProductType == VER_NT_WORKSTATION)
				{
					return "Windows Vista";
				}
				else if (infos.dwMajorVersion == 6 && infos.dwMinorVersion == 0 && infos.wProductType != VER_NT_WORKSTATION)
				{
					return "Windows Server 2008";
				}
				else if (infos.dwMajorVersion == 5 && infos.dwMinorVersion == 2 &&  GetSystemMetrics(SM_SERVERR2) != 0)
				{
					return "Windows Server 2003 R2";
				}
				else if (infos.dwMajorVersion == 5 && infos.dwMinorVersion == 2 && infos.wSuiteMask & VER_SUITE_WH_SERVER)
				{
					return "Windows Home Server";
				}
				else if (infos.dwMajorVersion == 5 && infos.dwMinorVersion == 2 &&  GetSystemMetrics(SM_SERVERR2) == 0)
				{
					return "Windows Server 2003";
				}
				else if (infos.dwMajorVersion == 5 && infos.dwMinorVersion == 2 &&  infos.wProductType == VER_NT_WORKSTATION && infos_sys.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
				{
					return "Windows XP Professional x64 Edition";
				}
				else if (infos.dwMajorVersion == 5 && infos.dwMinorVersion == 1)
				{
					return "Windows XP";
				}
				else if (infos.dwMajorVersion == 5 && infos.dwMinorVersion == 0)
				{
					return "Windows 2000";
				}
				else
				{
					return "Windows";
				}
				
			#else
				
				throw hnc::except::incomplete_implementation("hnc::computer::system_name is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}
		
		/**
		 * @brief Get the version of the operating system
		 * 
		   @code
		   	#include <hnc/computer.hpp>
		   @endcode
		 * 
		 * @return the version of the operating system
		 */
		inline std::string system_version()
		{
			#ifdef hnc_unix
			
				struct utsname infos;
				uname(&infos);
				
				return std::string(infos.release);
				
			#elif hnc_windows
				
				// http://msdn.microsoft.com/en-us/library/windows/desktop/ms724833%28v=vs.85%29.aspx
				
				OSVERSIONINFOEX infos;
				ZeroMemory(&infos, sizeof(OSVERSIONINFOEX));
				infos.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
				GetVersionEx((OSVERSIONINFO *)(&infos));
				
				return hnc::to_string(infos.dwMajorVersion) + "." + hnc::to_string(infos.dwMinorVersion);
				
			#else
				
				throw hnc::except::incomplete_implementation("hnc::computer::system_version is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}
		
		/**
		 * @brief Get the model name of the processor
		 * 
		   @code
		   	#include <hnc/computer.hpp>
		   @endcode
		 * 
		 * @return the model name of the processor
		 */
		inline std::string processor_name()
		{
			// http://stackoverflow.com/questions/18592580/how-to-check-cpu-name-model-speed-on-windows-linux-c
			
			#ifdef hnc_linux
			
				std::ifstream cpuinfo("/proc/cpuinfo");
				
				while (cpuinfo.good())
				{
					std::string line;
					std::getline(cpuinfo, line);
					
					// x86_64
					if (hnc::algo::find_range(line, "model name"_s) != line.end())
					{
						hnc::string::remove_multiple_whitespaces(line);
						hnc::algo::replace_all(line, "model name : "_s, ""_s);
						return line;
					}
					// ARM
					else if (hnc::algo::find_range(line, "Processor"_s) != line.end())
					{
						hnc::string::remove_multiple_whitespaces(line);
						hnc::algo::replace_all(line, "Processor : "_s, ""_s);
						return line;
					}
				}
				
				return "Unknown";
				
			#elif hnc_unix
				
				#ifndef hnc_linux
				
					char buffer[512];
					std::size_t buffer_size = sizeof(buffer) / sizeof(char);
					std::fill(buffer, buffer + buffer_size, '\0');
					
					sysctlbyname("machdep.cpu.brand_string", &buffer, &buffer_size, NULL, 0);
					
					std::string processor_name = buffer;
					hnc::string::remove_multiple_whitespaces(processor_name);
					
					return processor_name;
				
				#endif
				
			#elif hnc_windows
				
				// http://msdn.microsoft.com/en-us/library/windows/desktop/ms724958%28v=vs.85%29.aspx
				
				SYSTEM_INFO infos; GetSystemInfo(&infos);
				
				if (infos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) { return "x64 (AMD or Intel)"; }
				else if (infos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) { return "ARM"; }
				else if (infos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) { return "Intel Itanium-based"; }
				else if (infos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) { return "x86"; }
				else if (infos.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_UNKNOWN) { return "Unknown"; }
				
				return "Unknown";
				
			#else
				
				throw hnc::except::incomplete_implementation("hnc::computer::processor_name is not implemented on your platform, please write a bug report or send a mail https://gitorious.org/hnc");
				
			#endif
		}
	}
}

#endif
