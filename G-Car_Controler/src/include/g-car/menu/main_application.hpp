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
#include <concept_check.hpp>

#include <stdio.h>
#include <thread>
#include <string.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

#include "help_application.hpp"


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
		
		sf::TcpListener listener;
		sf::TcpSocket socket;
		bool client_ok = false;
		
		
		inline void client_connection() 
		{
			listener.accept(socket);
			client_ok = true;
		}

		sf::Thread t1(&client_connection);

		void menu_navigation(sf::RenderWindow & window, sf::TcpSocket & socket, const tgui::Callback& callback)
		{
			std::cout << "You pressed the '" << callback.text.toAnsiString() << "' button." << std::endl;
			if(callback.text.toAnsiString() == "Exit")
			{
				listener.close();
				socket.disconnect();
				t1.terminate();
				exit(0);
			}
			else if(callback.text.toAnsiString() == "About")
			{
				gcar::menu::help_app(window);
			}
			else if(callback.text.toAnsiString() == "Connect")
			{
				t1.launch();
			}
			else if(callback.text.toAnsiString() == "Disconnect")
			{
				client_ok = false;
				socket.disconnect();
			}
		}

		inline void start_app (sf::RenderWindow & window)
		{
			tgui::Gui gui(window);
			auto child = tgui::ChildWindow::create(THEME_CONFIG_FILE);
			auto slider = tgui::Slider::create(THEME_CONFIG_FILE);
			auto slider2 = tgui::Slider::create(THEME_CONFIG_FILE);
			auto radio_auto = tgui::RadioButton::create(THEME_CONFIG_FILE);
			auto radio_manuel = tgui::RadioButton::create(THEME_CONFIG_FILE);
			auto menu = tgui::MenuBar::create(THEME_CONFIG_FILE);
			auto listBox = tgui::ListBox::create(THEME_CONFIG_FILE);
			auto btn_start = tgui::Button::create(THEME_CONFIG_FILE);
			auto btn_stop = tgui::Button::create(THEME_CONFIG_FILE);
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
			    listBox->setSize(windowWidth/2, windowHeight/2);
			    listBox->setItemHeight(20);
			    listBox->setPosition(windowWidth/2, windowHeight/2);
			    listBox->addItem("Vitesse de deplacement :");
			    listBox->addItem("Gyrometre :");
			    listBox->addItem("Positionnement :");
			    listBox->addItem("Odometre :");
			    listBox->addItem("Infrarouge :");
			    gui.add(listBox);

				
				slider->setPosition(windowWidth/2, windowHeight/8);
				slider->setSize(windowWidth/2, 15);
				slider->setMaximum(100);
				slider->setMinimum(0);
				slider->setValue(0);
				gui.add(slider);
				
				auto lbl_speed = tgui::Label::create(THEME_CONFIG_FILE);
				lbl_speed->setText("G-Car' speed :");
				lbl_speed->setPosition(windowWidth/2, windowHeight/8 - 120);
				lbl_speed->setAutoSize(true);
				gui.add(lbl_speed);
				
				slider2->setPosition(windowWidth/2, windowHeight/4);
				slider2->setSize(windowWidth/2, 15);
				slider2->setMaximum(100);
				slider2->setMinimum(0);
				slider2->setValue(50);
				gui.add(slider2);
				
				auto lbl_speed1 = tgui::Label::create(THEME_CONFIG_FILE);
				lbl_speed1->setText("G-Car' angular speed :");
				lbl_speed1->setPosition(windowWidth/2, windowHeight/4 - 60);
				lbl_speed1->setAutoSize(true);
				gui.add(lbl_speed1);
				
			    btn_start->setText("Start");
			    btn_start->setSize(windowWidth/4, windowHeight / 12);
			    btn_start->setPosition(0, windowHeight * 3/4);
			    btn_start->connect(
									"pressed", [&]()
									{
										char data[100] = "start";
										// socket TCP:
										socket.send(data, 100);
									}
								 );
			    gui.add(btn_start);
				
				btn_stop->setText("Stop");
			    btn_stop->setSize(windowWidth/4, windowHeight / 12);
			    btn_stop->setPosition(windowWidth/4, windowHeight * 3/4);
			    btn_stop->connect(
									"pressed", [&]()
									{
										char data[100] = "stop";
										// socket TCP:
										socket.send(data, 100);
									}
								 );
			    gui.add(btn_stop);

			    radio_auto->setPosition(0, windowHeight * 1/2);
			    radio_auto->setText("Automatic");
			    radio_auto->setSize(windowWidth/35, windowWidth/35);
			    gui.add(radio_auto);

			    radio_manuel->setSize(windowWidth/35, windowWidth/35);
			    radio_manuel->setPosition(windowWidth * 3/8, windowHeight * 1/2);
			    radio_manuel->setText("Manuel");
			    gui.add(radio_manuel);
				
			    menu->setSize(windowWidth, 20);
			    menu->addMenu("File");
			    menu->addMenuItem("File", "Save");
			    menu->addMenuItem("File", "Exit");
			    menu->addMenu("Settings");
			    menu->addMenuItem("Settings", "Connect");
			    menu->addMenuItem("Settings", "Disconnect");
			    menu->addMenu("Help");
			    menu->addMenuItem("Help", "About");
			    menu->connectEx("MenuItemClicked", menu_navigation, std::ref(window), std::ref(socket));
			    gui.add(menu);

				auto label = tgui::Label::create(THEME_CONFIG_FILE);
				label->setText("You need to connect the client to this server:\n" + sf::IpAddress::getPublicAddress().toString());
				
				child->setSize(windowWidth/2, windowHeight/2);
				child->setPosition(windowWidth/4, windowHeight/2 - windowHeight/4);
				child->setTitle("Connection");
				child->add(label);
				
				gui.add(child);

		    }
		    catch (const tgui::Exception& e)
		    {
		        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
		        exit(1);
		    }

			// lie l'écouteur à un port
			listener.listen(54000);

			t1.launch();
			
			bool joystickConnect = false;
			sf::Clock clock;
			sf::Clock moving_clock;
			radio_auto->check();
			
			const int YOLO = 5000;
			int move_A = 0;
			int move_B = 0;
			int frequence = 42;
			
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
							listener.close();
							socket.disconnect();
							t1.terminate();
							window.close();
						}
                        else if (event.type == sf::Event::Resized)
                        {
                            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                            gui.setView(window.getView());
                        }
				float const elapsed = clock.restart().asSeconds();

						gui.handleEvent(event);
					}
				}
				
				/// Time
				float const elapsed = clock.restart().asSeconds();
				
				float const moving = 500 * elapsed;
				
				if(!client_ok)
				{
					radio_auto->disable();
					radio_manuel->disable();
					slider->disable();
					slider2->disable();
					listBox->disable();
					btn_start->disable();
					btn_stop->disable();
					child->disable();
				}
				else
				{
					child->hide();
					radio_auto->enable();
					radio_manuel->enable();
					slider->enable();
					listBox->enable();
					btn_start->enable();
					btn_stop->enable();
					child->enable();
				}
				
				
				/// Test if window is focused
				if(window.hasFocus())
				{
					
					if(radio_manuel->isChecked())
					{
						btn_start->hide();
						btn_stop->hide();
						
						auto bck_move_A = move_A;
						auto bck_move_B = move_B;
						
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							move_A = YOLO + slider->getValue();
						}
						else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							move_A = YOLO - slider->getValue();
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						{
							move_B = 10;
							slider2->setValue(slider2->getValue()-(int)moving);
						}
						else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							move_B = 50;
							slider2->setValue(slider2->getValue()+(int)moving);
						}
						else
						{
							move_B = 0;
							slider2->setValue(50);
						}
						
						if(sf::Joystick::isConnected(1))
						{
							joystickConnect = true;
							std::size_t angular_speed_value = slider2->getValue();
							if( sf::Joystick::getAxisPosition(1, sf::Joystick::Y) < 0 )
							{
								move_A = YOLO + slider->getValue();
								
							}
							else if(sf::Joystick::getAxisPosition(1, sf::Joystick::Y) > 0)
							{
								move_A = YOLO - slider->getValue();
							}
							else
							{
								move_A = YOLO;
							}
							if(sf::Joystick::getAxisPosition(1, sf::Joystick::X) < 0)
							{
								move_B = 10;
								slider2->setValue(angular_speed_value-(int)moving);
							}
							else if(sf::Joystick::getAxisPosition(1, sf::Joystick::X) > 0)
							{
								move_B = 50;
								slider2->setValue(angular_speed_value+(int)moving);
							}
							else
							{
								move_B = 0;
								slider2->setValue(50);
							}
							std::size_t speed_value = slider->getValue();
							if (sf::Joystick::isButtonPressed(1, 0))
							{
								slider->setValue(speed_value-(int)moving);
							}
							else if (sf::Joystick::isButtonPressed(1, 3))
							{
								slider->setValue(speed_value+(int)moving);
							}
						}
						else
						{
							joystickConnect = false;
						}
						
						/// Send Data
						if(bck_move_A != move_A || bck_move_B != move_B)
						{
// 							std::string paquet = "A "+std::to_string(move_A)+" B "+std::to_string(move_B)+" C 50000 "
							std::string paquet = "A 960 C 0 D 50000 ";
							socket.send(paquet.c_str(), 1024);
							std::cout << "Envoie du paquet : " << paquet.c_str() << std::endl;
						}
					}
					else if(radio_auto->isChecked())
					{
						btn_start->show();
						btn_stop->show();
					}
					
				}
				
				// Clear the screen
				window.clear(sf::Color(132,132,130));

				// Draw GUI
				gui.draw();

				// Display
				window.display();
			}
		}
	}
	
}
#endif 