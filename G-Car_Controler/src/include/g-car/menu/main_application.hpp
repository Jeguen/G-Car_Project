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


#ifndef GCAR_PROJECT_MENU_MAIN_MENU_HPP
#define GCAR_PROJECT_MENU_MAIN_MENU_HPP

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
		#include <TGUI/TGUI.hpp>
	    #include <SFML/Graphics.hpp>
	    #include "menu/main_menu.hpp"
	 * @endcode
	 * 
	 */
	
	namespace menu
	{

		void function(const tgui::Callback& callback)
		{
			std::cout << "You pressed the '" << callback.text.toAnsiString() << "' button." << std::endl;
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
			    tgui::Button::Ptr button = tgui::Button::create(THEME_CONFIG_FILE);
			    button->setPosition(40, 25);
			    button->setText("Quit");
			    button->setSize(300, 40);
			    button->connect("pressed", [&](){ window.close(); });
			    gui.add(button);

			    
			    tgui::ChatBox::Ptr chatbox = tgui::ChatBox::create(THEME_CONFIG_FILE);
			    chatbox->setSize(200, 100);
			    chatbox->setTextSize(20);
			    chatbox->setPosition(400, 25);
			    chatbox->addLine("Line 1", sf::Color::Red);
			    chatbox->addLine("Line 2", sf::Color::Blue);
			    chatbox->addLine("Line 3", sf::Color::Green);
			    chatbox->addLine("Line 4", sf::Color::Yellow);
			    chatbox->addLine("Line 5", sf::Color::Cyan);
			    chatbox->addLine("Line 6", sf::Color::Magenta);
			    gui.add(chatbox);
				
			    tgui::Checkbox::Ptr checkbox = tgui::Checkbox::create(THEME_CONFIG_FILE);
			    checkbox->setPosition(40, 80);
			    checkbox->setText("Checkbox");
			    checkbox->setSize(32, 32);
			    gui.add(checkbox);
				
			    tgui::ChildWindow::Ptr child = tgui::ChildWindow::create(THEME_CONFIG_FILE);
			    child->setSize(200, 100);
			    child->setPosition(400, 460);
			    child->setTitle("Child window");
			    gui.add(child);
				
			    tgui::ComboBox::Ptr comboBox = tgui::ComboBox::create(THEME_CONFIG_FILE);
			    comboBox->setSize(120, 21);
			    comboBox->setPosition(210, 440);
			    comboBox->addItem("Item 1");
			    comboBox->addItem("Item 2");
			    comboBox->addItem("Item 3");
			    comboBox->setSelectedItem("Item 2");
			    gui.add(comboBox);
				
			    tgui::EditBox::Ptr editBox = tgui::EditBox::create(THEME_CONFIG_FILE);
			    editBox->setPosition(40, 200);
			    editBox->setSize(300, 30);
			    gui.add(editBox);

			    tgui::Label::Ptr label = tgui::Label::create(THEME_CONFIG_FILE);
			    label->setText("Label");
			    label->setPosition(40, 160);
			    label->setTextColor(sf::Color(200, 200, 200));
			    label->setTextSize(24);
			    gui.add(label);

			    tgui::ListBox::Ptr listBox = tgui::ListBox::create(THEME_CONFIG_FILE);
			    listBox->setSize(150, 120);
			    listBox->setItemHeight(20);
			    listBox->setPosition(40, 440);
			    listBox->addItem("Item 1");
			    listBox->addItem("Item 2");
			    listBox->addItem("Item 3");
			    gui.add(listBox);

			    tgui::RadioButton::Ptr radioButton = tgui::RadioButton::create(THEME_CONFIG_FILE);
			    radioButton->setPosition(40, 120);
			    radioButton->setText("Radio Button");
			    radioButton->setSize(32, 32);
			    gui.add(radioButton);

			    tgui::Scrollbar::Ptr scrollbar = tgui::Scrollbar::create(THEME_CONFIG_FILE);
			    scrollbar->setPosition(40, 290);
			    scrollbar->setSize(300, 25);
			    scrollbar->setMaximum(5);
			    scrollbar->setLowValue(3);
			    gui.add(scrollbar);

			    tgui::MenuBar::Ptr menu = tgui::MenuBar::create(THEME_CONFIG_FILE);
			    menu->setSize(windowWidth, 20);
			    menu->addMenu("File");
			    menu->addMenuItem("File", "Connect");
			    menu->addMenuItem("File", "Save");
			    menu->addMenuItem("File", "Exit");
			    menu->addMenu("Edit");
			    menu->addMenu("Settings");
			    menu->addMenu("Help");
			    menu->connectEx("MenuItemClicked", function);
			    gui.add(menu);
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