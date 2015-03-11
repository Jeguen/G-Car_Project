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


#ifndef GCAR_PROJECT_MENU_INTO_APPLICATION_HPP
#define GCAR_PROJECT_MENU_INTO_APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "main_application.hpp"

#define THEME_CONFIG_FILE "../media/TGUI/widgets/Black.conf"

namespace gcar
{
	/**
	 * @brief Provides menu functions
	 *
	 * @code
		#include <TGUI/TGUI.hpp>
	    #include <SFML/Graphics.hpp>
	    #include "menu/main_menu.hpp"
	 * @endcode
	 *
	 */

	namespace menu
	{

		inline void intro_app (sf::RenderWindow & window)
		{
			tgui::Gui gui(window);

			auto progressBar = tgui::ProgressBar::create(THEME_CONFIG_FILE);
			

			try
		    {
		        gui.setGlobalFont("../media/fonts/DejaVuSans.ttf");

				// Get a bound version of the window size
			    // Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
			    auto windowWidth = tgui::bindWidth(gui);
			    auto windowHeight = tgui::bindHeight(gui);

			    sf::Image icon;
			    icon.loadFromFile("../media/img/1.png");
			    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

			    progressBar->setPosition(windowWidth/4, windowHeight * 3/4);
			    progressBar->setSize(windowWidth/2, 30);
			    progressBar->setValue(0);
			    progressBar->hide();
			    gui.add(progressBar);
			    

		    }
		    catch (const tgui::Exception& e)
		    {
		        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
		        exit(1);
		    }

		    sf::SoundBuffer buffer;
		    if (!buffer.loadFromFile("../media/sound/welcome.ogg"))
		    {

		    }

		    sf::Sound sound;
		    sound.setBuffer(buffer);
		    sound.play();
		    sf::Texture texture;
		    if (!texture.loadFromFile("../media/img/Untitled.png"))
		    {
		        // erreur...
		    }

		    sf::Sprite sprite;
		    sprite.setTexture(texture);
		    sprite.setPosition(sf::Vector2f(window.getSize().x/2 - sprite.getTexture()->getSize().x/2 , window.getSize().y/2 - sprite.getTexture()->getSize().y/2));

		    sprite.setColor(sf::Color(255,255,255,0));

		    sf::Clock clock;
		    int alpha = 0;
		    int percent = 0;
		    bool transition = true;

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
								//std::cout << "Mouse left clic" << std::endl;
							}
						}
						// Mouse button released
						else if (event.type == sf::Event::MouseButtonReleased)
						{
							// event.mouseButton.button
						}
                        else if (event.type == sf::Event::Resized)
                        {
                            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                            gui.setView(window.getView());
                        }

						gui.handleEvent(event);
					}
				}

				// Clear the screen
				window.clear(sf::Color(132,132,130));

				sprite.setPosition(sf::Vector2f(window.getSize().x/2 - sprite.getTexture()->getSize().x/2 , window.getSize().y/2 - sprite.getTexture()->getSize().y/2));

				sf::Time elapsed1 = clock.getElapsedTime();
		        std::cout << elapsed1.asSeconds() << std::endl;

		        if(int(elapsed1.asMilliseconds())%1 == 0 && alpha <255 && transition)
		        {
		            alpha++;
		            sprite.setColor(sf::Color(255,255,255,alpha));
		            if(alpha == 255)
		            {
		                transition = false;
		                progressBar->show();
		            }
		        }

		        if (!transition)
		        {
		        	if(int(elapsed1.asMilliseconds())%2 == 0 && percent < 100)
		        	{
		        		percent++;
		        		progressBar->setValue(percent);
		        	}
		        }

		        if(percent == 100)
		        {
		        	menu::start_app(window);
		        }

				// Draw http://www.sfml-dev.org/tutorials/2.1/graphics-draw.php
				// TODO
				window.draw(sprite);
				// Draw GUI
				gui.draw();



				// Display
				window.display();
			}
		}
	}

}
#endif
