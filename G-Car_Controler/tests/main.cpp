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

#include <TGUI/TGUI.hpp>

#include <g-car/hello_world.hpp>

#define THEME_CONFIG_FILE "../media/TGUI/widgets/Black.conf"

int main()
{
	// Windows
	sf::RenderWindow window(sf::VideoMode(1024, 768), "G-Car Controler");
	
	tgui::Gui gui(window);

	if (!gui.setGlobalFont("../media/fonts/DejaVuSans.ttf"))
	{
        return 1;
	}

	// Clock
	sf::Clock clock;
    
    // Hello World
    gcar::hello_world h ("YOLO");
    
    h.message();

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
    child->setIcon("../icon.jpg");

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

    tgui::Slider::Ptr slider(gui);
    slider->load(THEME_CONFIG_FILE);
    slider->setVerticalScroll(false);
    slider->setPosition(40, 250);
    slider->setSize(300, 25);
    slider->setValue(2);

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
    menu->addMenuItem("File", "Load");
    menu->addMenuItem("File", "Save");
    menu->addMenuItem("File", "Exit");
    menu->bindCallback(tgui::MenuBar::MenuItemClicked);
    menu->setCallbackId(2);

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
	
	return 0;
}
