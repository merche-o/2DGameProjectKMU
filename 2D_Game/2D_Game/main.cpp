#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(480, 480), "Skin Tester");
	window.setFramerateLimit(30);

    while (window.isOpen())
    {
	    window.clear();
        sf::Event event;
		while (window.pollEvent(event))
        {
			if (event.type == sf::Event::Closed)
                window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
                window.close();
			}
        }
		
        window.display();
    }

	return (0);
}