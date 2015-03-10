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

#include<SFML/Network.hpp>


int main()
{
	sf::TcpListener listener;

	// lie l'écouteur à un port
	listener.listen(53000);

	// accepte une nouvelle connexion
	sf::TcpSocket socket;
	listener.accept(socket);
	
	sf::Clock clock;
	sf::Time elapsed1;
	
	while(elapsed1.asSeconds() < 10)
	{
		elapsed1 = clock.getElapsedTime();
		
		std::size_t received;
		char data[100] = "from server";

		// socket TCP:
		socket.send(data, 100);
		
		if (socket.receive(data, 100, received) == sf::Socket::Done)
		{
			std::cout <<  data << std::endl;
		}
	}
	
	
	return 0;
}
