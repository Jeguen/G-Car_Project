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


#include <iostream>

#include <SFML/Graphics.hpp>

#include <g-car/hello_world.hpp>

int main()
{
	// Windows
	sf::RenderWindow window(sf::VideoMode(1024, 768), "G-Car Controler");
	
	// Clock
	sf::Clock clock;
    
    // Hello World
    gcar::hello_world h ("YOLO");
    
    h.message();
    
    
	// Start
	while (window.isOpen())
	{
		// Event http://www.sfml-dev.org/tutorials/2.1/window-events.php
		{
			sf::Event event;
			
			while (window.pollEvent(event))
			{
				// Close
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				// Text
				else if (event.type == sf::Event::TextEntered)
				{
					// event.text.unicode
				}
				// Key pressed
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						window.close();
					}
				}
				// Key released
				else if (event.type == sf::Event::KeyReleased)
				{
					// event.key.code
				}
				// Mouse button pressed
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						std::cout << "Mouse left clic" << std::endl;
					}
				}
				// Mouse button released
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					// event.mouseButton.button
				}
			}
		}
		
		// Time http://www.sfml-dev.org/tutorials/2.1/system-time.php
		// In real time program, the moving speed of your objects should be multiply by the time elapsed
		sf::Time elapsed = clock.restart();
		
		// elapsed.asSeconds() is the time elapsed in second in a float
		//std::cout << elapsed.asSeconds() << std::endl;
		
		// Mouse http://www.sfml-dev.org/tutorials/2.1/window-inputs.php
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << "Mouse left button is pressed" << std::endl;
		}
		
		// Keyboard http://www.sfml-dev.org/tutorials/2.1/window-inputs.php
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			std::cout << "Left is pressed" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			std::cout << "Right is pressed" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			std::cout << "Up is pressed" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			std::cout << "Down is pressed" << std::endl;
		}
		
		// Clear the screen
		window.clear(sf::Color::Black);
		
		// Draw http://www.sfml-dev.org/tutorials/2.1/graphics-draw.php
		// TODO
		
		// Display
		window.display();
	}
	
	return 0;
}
