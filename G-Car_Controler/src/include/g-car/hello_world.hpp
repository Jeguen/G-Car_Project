// Copyright © 2015 Rodolphe Cargnello, rodolphe.cargnello@gmail.com

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

#ifndef GCAR_PROJECT_HELLO_WORLD_HPP
#define GCAR_PROJECT_HELLO_WORLD_HPP

namespace gcar
{
	/**
	 * @brief hello_world
	 * 
	 * @code
	 * #include <SFML/Graphics.hpp>
	 * @endcode
	 * 
	 */
	
	class hello_world
	{
	private:
		
		/// Fullscreen
        std::string  m_message;
		
	public:
        
        /// @brief Constructor
		hello_world() = default;
		
        hello_world(std::string message)
        {
            m_message = message;
		}
		
    void message()
        {
            std::cout<< m_message << std::endl;
        }
	};
	
}
#endif 

