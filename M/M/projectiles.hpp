#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Projectile
{

public:
	sf::RectangleShape _p;
	int speed = 10;
	int attackDamage = 5;

	Projectile() {
		_p.setSize(sf::Vector2f(10, 10));
		_p.setPosition(0, 0);
		_p.setFillColor(sf::Color::Green);
	}
	//Utilisation d'un vector
	void draw(sf::RenderTarget& renderer) {
		renderer.draw(_p);
	}
};
#endif