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
		inline void start_app (sf::RenderWindow & window)
		{
			tgui::Gui gui(window);
			if (!gui.setGlobalFont("../media/fonts/DejaVuSans.ttf"))
			{
				std::cout << "font not load !" << std::endl;
        		return;
			}

					 // Hello World
		    gcar::hello_world h ("YOLO");

		    h.message();

		    sf::Image icon;
		    icon.loadFromFile("../media/img/icon.png");
		    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		    // GUI
		    tgui::Button::Ptr button(gui);
		    button->load(THEME_CONFIG_FILE);
		    button->setPosition(40, 25);
		    button->setText("Quit");
		    button->setCallbackId(1);
		    button->bindCallback(tgui::Button::LeftMouseClicked);
		    button->setSize(300, 40);

		    tgui::ChatBox::Ptr chatbox(gui);
		    chatbox->load(THEME_CONFIG_FILE);
		    chatbox->setSize(200, 100);
		    chatbox->setTextSize(20);
		    chatbox->setPosition(400, 25);
		    chatbox->addLine("Line 1", sf::Color::Red);
		    chatbox->addLine("Line 2", sf::Color::Blue);
		    chatbox->addLine("Line 3", sf::Color::Green);
		    chatbox->addLine("Line 4", sf::Color::Yellow);
		    chatbox->addLine("Line 5", sf::Color::Cyan);
		    chatbox->addLine("Line 6", sf::Color::Magenta);

		    tgui::Checkbox::Ptr checkbox(gui);
		    checkbox->load(THEME_CONFIG_FILE);
		    checkbox->setPosition(40, 80);
		    checkbox->setText("Checkbox");
		    checkbox->setSize(32, 32);

		    tgui::ChildWindow::Ptr child(gui);
		    child->load(THEME_CONFIG_FILE);
		    child->setSize(200, 100);
		    child->setBackgroundColor(sf::Color(80, 80, 80));
		    child->setPosition(400, 460);
		    child->setTitle("Child window");

		    tgui::ComboBox::Ptr comboBox(gui);
		    comboBox->load(THEME_CONFIG_FILE);
		    comboBox->setSize(120, 21);
		    comboBox->setPosition(210, 440);
		    comboBox->addItem("Item 1");
		    comboBox->addItem("Item 2");
		    comboBox->addItem("Item 3");
		    comboBox->setSelectedItem("Item 2");

		    tgui::EditBox::Ptr editBox(gui);
		    editBox->load(THEME_CONFIG_FILE);
		    editBox->setPosition(40, 200);
		    editBox->setSize(300, 30);

		    tgui::Label::Ptr label(gui);
		    label->load(THEME_CONFIG_FILE);
		    label->setText("Label");
		    label->setPosition(40, 160);
		    label->setTextColor(sf::Color(200, 200, 200));
		    label->setTextSize(24);

		    tgui::ListBox::Ptr listBox(gui);
		    listBox->load(THEME_CONFIG_FILE);
		    listBox->setSize(150, 120);
		    listBox->setItemHeight(20);
		    listBox->setPosition(40, 440);
		    listBox->addItem("Item 1");
		    listBox->addItem("Item 2");
		    listBox->addItem("Item 3");

		    tgui::LoadingBar::Ptr loadingbar(gui);
		    loadingbar->load(THEME_CONFIG_FILE);
		    loadingbar->setPosition(40, 330);
		    loadingbar->setSize(300, 30);
		    loadingbar->setValue(35);

		    tgui::RadioButton::Ptr radioButton(gui);
		    radioButton->load(THEME_CONFIG_FILE);
		    radioButton->setPosition(40, 120);
		    radioButton->setText("Radio Button");
		    radioButton->setSize(32, 32);

		    tgui::Scrollbar::Ptr scrollbar(gui);
		    scrollbar->load(THEME_CONFIG_FILE);
		    scrollbar->setVerticalScroll(false);
		    scrollbar->setPosition(40, 290);
		    scrollbar->setSize(300, 25);
		    scrollbar->setMaximum(5);
		    scrollbar->setLowValue(3);

		    tgui::MenuBar::Ptr menu(gui);
		    menu->load(THEME_CONFIG_FILE);
		    menu->setSize(window.getSize().x, 20);
		    menu->addMenu("File");
		    menu->addMenuItem("File", "Connect");
		    menu->addMenuItem("File", "Save");
		    menu->addMenuItem("File", "Exit");
		    menu->addMenu("Edit");
		    menu->addMenu("Settings");
		    menu->addMenu("Help");
		    menu->bindCallback(tgui::MenuBar::MenuItemClicked);
		    menu->setCallbackId(2);


		    tgui::Panel::Ptr panel(gui);
		    panel->setSize(500,500);
		    panel->setPosition(400,150);

		    tgui::Button::Ptr button1(*panel);
		    button1->load(THEME_CONFIG_FILE);
		    button1->setText("yolo1");
		    button1->setCallbackId(3);
		    button1->bindCallback(tgui::Button::LeftMouseClicked);

		    tgui::Button::Ptr button2(*panel);
		    button2->load(THEME_CONFIG_FILE);
		    button2->setText("yolo2");
		    button2->setCallbackId(4);
		    button2->bindCallback(tgui::Button::LeftMouseClicked);
		    
		    tgui::Button::Ptr button3(*panel);
		    button3->load(THEME_CONFIG_FILE);
		    button3->setText("yolo3");
		    button3->setCallbackId(5);
		    button3->bindCallback(tgui::Button::LeftMouseClicked);

		    tgui::Button::Ptr button4(*panel);
		    button4->load(THEME_CONFIG_FILE);
		    button4->setText("yolo4");
		    button4->setCallbackId(6);
		    button4->bindCallback(tgui::Button::LeftMouseClicked);

		    tgui::Button::Ptr button5(*panel);
		    button5->load(THEME_CONFIG_FILE);
		    button5->setText("yolo5");
		    button5->setCallbackId(7);
		    button5->bindCallback(tgui::Button::LeftMouseClicked);

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

						gui.handleEvent(event);
					}

					tgui::Callback callback;
			        while (gui.pollCallback(callback))
			        {
			            if (callback.id == 1)
			                window.close();

			            else if (callback.id == 2)
			            {
			                if (callback.text == "Exit")
			                    window.close();
			            }
			        }
				}

				// Clear the screen
				window.clear(sf::Color::White);

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