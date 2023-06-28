#include "Engine.hpp"

int main() {
    Engine engine;
    engine.run();
    return 0;
}

// #include "Candle/RadialLight.hpp"
// #include "Candle/LightingArea.hpp"

// int main() {
//     sf::RenderWindow window(sf::VideoMode(1920,1080), "View tutorial", sf::Style::Default);

//     // create a light source
//     candle::RadialLight light;
//     light.setBeamAngle(90);
//     light.setRange(300);
//     light.setFade(true);

//     // load the image
//     // sf::Texture img1;
//     // if(!img1.loadFromFile("Vincent_Willem_van_Gogh_127.jpg")){
//     //     exit(1);
//     // }
//     // sf::Sprite background(img1);

//     // create the lighting area
//     candle::LightingArea fog(candle::LightingArea::FOG,
//                              sf::Vector2f(0.f, 0.f),
//                              sf::Vector2f(10000.f, 10000.f));
//     fog.setAreaColor(sf::Color::Black);

//     sf::View mainView;
//     mainView.setSize(1920,1080);

//     sf::RectangleShape object;
//     object.setSize(sf::Vector2f(100.f,100.f));
//     object.setPosition(800.f,800.f);

//     sf::RectangleShape player;
//     player.setSize(sf::Vector2f(50.f,50.f));
//     player.setPosition(500.f,500.f);

//     sf::RectangleShape UIElement;
//     UIElement.setSize(sf::Vector2f(300.f,20.f));

// 	while (window.isOpen())
// 	{
// 		sf::Event event;
// 		while (window.pollEvent(event))
// 		{
// 			if (event.type == sf::Event::Closed)
// 				window.close();
// 		}
//         // Update

//         light.setPosition(player.getPosition());
        
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//             player.move(-0.5f, 0.f);
//         } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//             player.move(0.5f, 0.f);
//         }

//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//             player.move(0.f, -0.5f);
//         } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//             player.move(0.f, 0.5f);
//         }

//         mainView.setCenter(player.getPosition());

//         // Draw

//         // Draw stuff
//         fog.clear();
//         fog.draw(light);
//         fog.display();
//         sf::Color myColor(74,103,65);
//         window.clear(myColor);

// 		window.setView(mainView);
//         // window.draw(background);
//         window.draw(object);

//         window.draw(fog);
//         window.draw(player);

//         // Draw UI
//         window.setView(window.getDefaultView());
//         window.draw(UIElement);

//         // Finished drawing
// 		window.display();
// 	}
//     return 0;
// }