// Copyright � 2015 Rodolphe Cargnello, rodolphe.cargnello@gmail.com

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
#include <g-car/menu.hpp>

int main()
{
	// Windows
    sf::RenderWindow window(sf::VideoMode(1024, 768), "G-Car Controler");

    gcar::menu::intro_app(window);

	return 0;
}
