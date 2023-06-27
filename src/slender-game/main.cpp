#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920,1080), "View tutorial", sf::Style::Default);
    
    sf::View mainView;
    mainView.setSize(1920,1080);

    sf::RectangleShape object;
    object.setSize(sf::Vector2f(100.f,100.f));
    object.setPosition(800.f,800.f);

    sf::RectangleShape player;
    player.setSize(sf::Vector2f(50.f,50.f));
    player.setPosition(500.f,500.f);

    sf::RectangleShape UIElement;
    UIElement.setSize(sf::Vector2f(300.f,20.f));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        // Update
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-0.5f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(0.5f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(0.f, -0.5f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0.f, 0.5f);
        }

        mainView.setCenter(player.getPosition());

        // Draw
        window.clear();

        // Draw stuff
		window.setView(mainView);
        window.draw(player);
        window.draw(object);

        // Draw UI
        window.setView(window.getDefaultView());
        window.draw(UIElement);

        // Finished drawing
		window.display();
	}
    return 0;
}