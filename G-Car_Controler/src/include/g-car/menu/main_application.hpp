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


#ifndef GCAR_PROJECT_MENU_MAIN_APPLICATION_HPP
#define GCAR_PROJECT_MENU_MAIN_APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "../hello_world.hpp"


#define THEME_CONFIG_FILE "../media/TGUI/widgets/Black.conf"

namespace gcar
{
	/**
	 * @brief Provides menu functions
	 * 
	 * @code
		#include <SFML/Graphics.hpp>
		#include <TGUI/TGUI.hpp>
		#include "../hello_world.hpp"
	 * @endcode
	 * 
	 */
	
	namespace menu
	{

		void function(const tgui::Callback& callback)
		{
			std::cout << "You pressed the '" << callback.text.toAnsiString() << "' button." << std::endl;
			if(callback.text.toAnsiString() == "Exit")
			{
				exit(0);
			}
		}

		inline void start_app (sf::RenderWindow & window)
		{
			tgui::Gui gui(window);
			
			try
		    {
		        gui.setGlobalFont("../media/fonts/DejaVuSans.ttf");

				// Get a bound version of the window size
			    // Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
			    auto windowWidth = tgui::bindWidth(gui);
			    auto windowHeight = tgui::bindHeight(gui);

			    sf::Image icon;
			    icon.loadFromFile("../media/img/icon.png");
			    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

			    // GUI
			    tgui::ListBox::Ptr listBox = tgui::ListBox::create(THEME_CONFIG_FILE);
			    listBox->setSize(windowWidth/2, windowHeight/2);
			    listBox->setItemHeight(20);
			    listBox->setPosition(windowWidth/2, windowHeight/2);
			    listBox->addItem("Item 1");
			    listBox->addItem("Item 2");
			    listBox->addItem("Item 3");
			    gui.add(listBox);

			    tgui::Button::Ptr btn_selection = tgui::Button::create(THEME_CONFIG_FILE);
			    btn_selection->setText("Select");
			    btn_selection->setSize(windowWidth/4, windowHeight / 12);
			    btn_selection->setPosition(windowWidth * 1/8 , windowHeight * 3/4);
			    btn_selection->connect("pressed", [&](){ std::cout << "Selection" << std::endl; });
			    gui.add(btn_selection);

			    tgui::RadioButton::Ptr radio_auto = tgui::RadioButton::create(THEME_CONFIG_FILE);
			    radio_auto->setPosition(0, windowHeight * 3/4 - btn_selection->getSize().y);
			    radio_auto->setText("Automatic");
			    radio_auto->setSize(windowWidth/35, windowWidth/35);
			    gui.add(radio_auto);

			    tgui::RadioButton::Ptr radio_manuel = tgui::RadioButton::create(THEME_CONFIG_FILE);
			    radio_manuel->setSize(windowWidth/35, windowWidth/35);
			    radio_manuel->setPosition(windowWidth * 3/8, windowHeight * 3/4 - btn_selection->getSize().y );
			    radio_manuel->setText("Manuel");
			    gui.add(radio_manuel);

			    tgui::MenuBar::Ptr menu = tgui::MenuBar::create(THEME_CONFIG_FILE);
			    menu->setSize(windowWidth, 20);
			    menu->addMenu("File");
			    menu->addMenuItem("File", "Save");
			    menu->addMenuItem("File", "Exit");
			    menu->addMenu("Settings");
			    menu->addMenuItem("Settings", "Connect");
			    menu->addMenuItem("Settings", "Disconnect");
			    menu->addMenu("Help");
			    menu->addMenuItem("Help", "About");
			    menu->connectEx("MenuItemClicked", function);
			    gui.add(menu);

			    tgui::Button::Ptr btn_up = tgui::Button::create(THEME_CONFIG_FILE);
			    btn_up->setText("Up");
			    btn_up->setSize(windowWidth/4, windowHeight / 10);
			    btn_up->setPosition(windowWidth *5/8, windowHeight * 1/8);
			    btn_up->connect("pressed", [&](){ std::cout << "Selection" << std::endl; });
			    gui.add(btn_up);
			    
			    tgui::Button::Ptr btn_down = tgui::Button::create(THEME_CONFIG_FILE);
			    btn_down->setText("Down");
			    btn_down->setSize(windowWidth/4, windowHeight / 10);
			    btn_down->setPosition(windowWidth * 5/8 , windowHeight * 3/8);
			    btn_down->connect("pressed", [&](){ std::cout << "Selection" << std::endl; });
			    gui.add(btn_down);

			    tgui::Button::Ptr btn_left = tgui::Button::create(THEME_CONFIG_FILE);
			    btn_left->setText("Left");
			    btn_left->setSize(windowWidth/4, windowHeight / 10);
			    btn_left->setPosition(windowWidth/2 , windowHeight/4);
			    btn_left->connect("pressed", [&](){ std::cout << "Selection" << std::endl; });
			    gui.add(btn_left);

			    tgui::Button::Ptr btn_right = tgui::Button::create(THEME_CONFIG_FILE);
			    btn_right->setText("Right");
			    btn_right->setSize(windowWidth/4, windowHeight / 10);
			    btn_right->setPosition(windowWidth * 3/4 , windowHeight/4);
			    btn_right->connect("pressed", [&](){ std::cout << "Selection" << std::endl; });
			    gui.add(btn_right);

		    }
		    catch (const tgui::Exception& e)
		    {
		        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
		        exit(1);
		    }

		    // Hello World
		    gcar::hello_world h ("Hello G-Car !!!");
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

				// Draw http://www.sfml-dev.org/tutorials/2.1/graphics-draw.php
				// TODO

				// Draw GUI
				gui.draw();

				// Display
				window.display();
			}
		}
	}
	
}
#endif 