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

#include "../stream_audio.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

#include "help_application.hpp"

#include <opencv2/core/core.hpp>

#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<opencv2/objdetect/objdetect.hpp>
#include "opencv2/video/background_segm.hpp"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


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
		
        ///Serveur
		sf::TcpListener listener;
		sf::TcpSocket socket;
		bool client_ok = false;
        
        ///OpenCV
        cv::Mat frameRGB, frameRGBA;
        cv::BackgroundSubtractorMOG2 bg;//(100, 3, 0.3, 5);
        std::vector < std::vector < cv::Point > >contours;
        cv::Mat fgmask, fgimg, backgroundImage;
        std::string face_cascade_name = "../data/haarcascades/haarcascade_frontalface_alt.xml";
        cv::CascadeClassifier face_cascade;
        std::string window_name = "Capture - Face detection";
        int filenumber; // Number of file to be saved
        std::string filename;
        
        // Function detectAndDisplay
        void detectAndDisplay(cv::Mat frame)
        {
            std::vector<cv::Rect> faces;
            cv::Mat frame_gray, crop, res, gray;
            std::string text;
            std::stringstream sstm;
            
            cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
            equalizeHist(frame_gray, frame_gray);
            
            // Detect faces
            face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
            
            // Set Region of Interest
            cv::Rect roi_b;
            cv::Rect roi_c;
            
            size_t ic = 0; // ic is index of current element
            int ac = 0; // ac is area of current element
            
            size_t ib = 0; // ib is index of biggest element
            int ab = 0; // ab is area of biggest element
            
            for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
                
            {
                roi_c.x = faces[ic].x;
                roi_c.y = faces[ic].y;
                roi_c.width = (faces[ic].width);
                roi_c.height = (faces[ic].height);
                
                ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)
                
                roi_b.x = faces[ib].x;
                roi_b.y = faces[ib].y;
                roi_b.width = (faces[ib].width);
                roi_b.height = (faces[ib].height);
                
                ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element
                
                if (ac > ab)
                {
                    ib = ic;
                    roi_b.x = faces[ib].x;
                    roi_b.y = faces[ib].y;
                    roi_b.width = (faces[ib].width);
                    roi_b.height = (faces[ib].height);
                }
                
                cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
                cv::Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
                rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
            }
            
        }

        /// Détection des movements
        inline void movement_detection(cv::Mat frame)
        {
            bg.operator()(frame, fgimg);
            bg.getBackgroundImage (backgroundImage);
            cv::erode (fgimg, fgimg, cv::Mat ());
            cv::dilate (fgimg, fgimg, cv::Mat ());
            cv::findContours (fgimg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
            cv::drawContours (frame, contours, -1, cv::Scalar (0, 0, 255), 2);

        }
        
        
        /// Accepte la connexion avec le client
		inline void client_connection() 
		{
			listener.accept(socket);
			client_ok = true;
		}

        ///Thread connexion
        sf::Thread t1(&client_connection);
        
        /// Appel des options du menu
		inline void menu_navigation(sf::RenderWindow & window, sf::TcpSocket & socket, const tgui::Callback& callback)
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
    
        /// Fenetre principale de l'application
		inline void start_app (sf::RenderWindow & window)
		{
			cv::VideoCapture cap;// open the video file for reading
            //cap.open("http://192.168.43.1:8080/video?x.mjpeg");
            if(!face_cascade.load("../data/haarcascades/haarcascade_frontalface_alt2.xml"))
            {
                printf("Error loading cascade file for face");
                exit(1);
            }
            cap.open(0);
            if(!cap.isOpened())
			{
				std::cout << "Fail" << std::endl;
			}
            
			sf::Image image;
			sf::Texture texture;
			sf::Sprite sprite;
			
			bool fullscreen = false;
			
            
            /// GUI
			tgui::Gui gui(window);
			auto windowWidth = tgui::bindWidth(gui);
			auto windowHeight = tgui::bindHeight(gui);
			auto canvas = tgui::Canvas::create({512, 384});
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
			    sf::Image icon;
			    icon.loadFromFile("../media/img/icon.png");
			    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
				
				canvas->setPosition(0, 0);
				canvas->setSize(windowWidth/2, windowHeight/2);
				gui.add(canvas);
				
			    // GUI
			    listBox->setSize(windowWidth/2, windowHeight/2);
			    listBox->setItemHeight(20);
			    listBox->setPosition(windowWidth/2, windowHeight/2);
			    listBox->addItem("Velocity :", "velocity");
			    listBox->addItem("Distance traveled:", "distance");
				listBox->addItem("Gyrometre : Upgrade your G-Car !");
			    listBox->addItem("Localisation:Upgrade your G-Car !");
			    listBox->addItem("Odometer: Upgrade your G-Car !");
			    listBox->addItem("Infrared:", "infrared");
			    gui.add(listBox);

				
				slider->setPosition(windowWidth/2, windowHeight/8);
				slider->setSize(windowWidth/2, 15);
				slider->setMaximum(20000);
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
										socket.send("A -1 C -1 D -1 ", 1024);
									}
								 );
			    gui.add(btn_start);
				
				btn_stop->setText("Stop");
			    btn_stop->setSize(windowWidth/4, windowHeight / 12);
			    btn_stop->setPosition(windowWidth/4, windowHeight * 3/4);
			    btn_stop->connect(
									"pressed", [&]()
									{
										socket.send("A 0 C 0 D 0 ", 1024);
									}
								 );
			    gui.add(btn_stop);

			    radio_auto->setPosition(0, windowHeight * 5/8);
			    radio_auto->setText("Automatic");
			    radio_auto->setSize(windowWidth/35, windowWidth/35);
                radio_auto->connect(
                                      "checked", [&]()
                                      {
                                          socket.send("A 99 C 99 D 99 ", 1024);
                                      }
                                      );
			    gui.add(radio_auto);

			    radio_manuel->setSize(windowWidth/35, windowWidth/35);
			    radio_manuel->setPosition(windowWidth * 3/8, windowHeight * 5/8);
			    radio_manuel->setText("Manuel");
                radio_manuel->connect(
                                   "checked", [&]()
                                   {
                                       socket.send("A 1 C 1 D 1 ", 1024);
                                   }
                                   );
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
			radio_manuel->check();
			
			const float YOLO = 1000;
			float move_A = 1000;
			float move_B = 15000;
			float frequence = 50000;
			
            
            bool face_recognisation = false;
            bool movement = false;
            
            bg.set ("nmixtures", 3);
            
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
                        else if (event.type == sf::Event::KeyReleased)
                        {
                            if (event.key.code == sf::Keyboard::F && movement == false)
                            {
                               if(face_recognisation)
                               {
                                   face_recognisation = false;
                               }
                               else
                               {
                                   face_recognisation = true;
                               }
                            }
                            else if (event.key.code == sf::Keyboard::M && face_recognisation == false)
                            {
                                if(movement)
                                {
                                    movement = false;
                                }
                                else
                                {
                                    movement = true;
                                }
                            }
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
				
				float const moving = 30 * elapsed;
				
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
                        
                        if(sf::Joystick::isConnected(0) && sf::Joystick::getButtonCount(0) == 12)
						{
							joystickConnect = true;
							std::size_t angular_speed_value = slider2->getValue();
							if( sf::Joystick::isButtonPressed(0, 5) )// Up
							{
								//move_A = YOLO + slider->getValue();
                                move_A = slider->getValue();
							}
							else if(sf::Joystick::isButtonPressed(0, 7))// Down
							{
								//move_A = YOLO - slider->getValue();
                                move_A = slider->getValue();
							}
							else
							{
								move_A = YOLO;
                            }
                            
                            if (sf::Joystick::isButtonPressed(0, 1))
                            {
                                //move_B -= (int)moving*50;
                                //slider2->setValue(slider2->getValue()- (int)move_B);
                                move_B = 10000;
                                slider2->setValue(0);
                            }
                            else if(sf::Joystick::isButtonPressed(0, 2))// Right
							{
                                //move_B += (int)moving*50;
                                move_B = 20000;
                                //slider2->setValue(slider2->getValue()+ (int)move_B/50);
                                slider2->setValue(100);
							}
							else
							{
								move_B = 15000;
								slider2->setValue(50);
							}
                            
							std::size_t speed_value = slider->getValue();
							if (sf::Joystick::isButtonPressed(0, 0))// Speed Up
							{
								slider->setValue(speed_value-(int)moving);
							}
							else if (sf::Joystick::isButtonPressed(0, 3))// Speed Down
							{
								slider->setValue(speed_value+(int)moving);
							}
                            
						}
						
						/// Send Data
						if(bck_move_A != move_A || bck_move_B != move_B)
						{
							std::string paquet = "A "+std::to_string((float)move_A/10)+" C "+std::to_string(move_B)+" D  "+std::to_string(frequence)+" ";
							socket.send(paquet.c_str(), paquet.size()+1);
							std::cout << "Envoie du paquet : " << paquet.c_str() << std::endl;
						}
					}
					else if(radio_auto->isChecked())
					{
						btn_start->show();
						btn_stop->show();
					}
					
				}
                
				cap >> frameRGB;
				
				if(!frameRGB.empty())
				{
                    if(face_recognisation)
                    {
                        detectAndDisplay(frameRGB);
                    }
                    else if (movement)
                    {
                        movement_detection(frameRGB);
                    }
				}
				
                cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);
                image.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());
				
                texture.loadFromImage(image);
                
                sprite.setTexture(texture);
				sprite.setScale((float)window.getSize().x/2 / texture.getSize().x, (float)window.getSize().y/2 / texture.getSize().y);
				
				// Clear the screen
				window.clear(sf::Color(132,132,130));

				// Draw GUI
				
				canvas->clear();
				canvas->draw(sprite);
				canvas->display();
				gui.draw();

				// Display
				window.display();
			}
		}
	}
	
}
#endif 