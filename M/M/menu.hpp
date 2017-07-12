#ifndef	MENUS_HPP
#define MENUS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Menu
{
public:
	sf::RectangleShape 	_menu;

public:
	Menu() {
		_menu.setSize(sf::Vector2f(800, 50));
		_menu.setPosition(0, 0);
		_menu.setFillColor(sf::Color::Blue);


		/*if (_texture.loadFromFile("mario_sprite.png")) {
		_texture.setSmooth(true);
		_sprite.setTexture(_texture);
		_sprite.setScale(1.0, 1.0);
		}*/

	}




	void draw(sf::RenderTarget& target) const
	{
		target.draw(_menu);
	}




};

#endif
