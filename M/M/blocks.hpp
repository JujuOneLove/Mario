#ifndef	BLOCKS_HPP
#define BLOCKS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


class Blocks
{
public:
	sf::Vector2f		_normalMap;
	sf::RectangleShape 	_rect;

	Blocks(float i,float j)
	{
		_rect.setSize(sf::Vector2f(32, 32));
		_rect.setPosition(i, j);
		_rect.setFillColor(sf::Color::White);
	}
	~Blocks() {};
	void setColor(sf::Color color) {
		_rect.setFillColor(color);
	}

	sf::FloatRect getBoundingBox() const
	{
		return _rect.getGlobalBounds();
	}
	float getBoundingBoxTop() const
	{
		return _rect.getGlobalBounds().top;
	}
	float getBoundingBoxLeft() const
	{
		return _rect.getGlobalBounds().left;
	}
	float getBoundingBoxWidth() const
	{
		return _rect.getGlobalBounds().width;
	}
	float getBoundingBoxHeight() const
	{
		return _rect.getGlobalBounds().height;
	}

	sf::Vector2f getNormalMap() const
	{
		return _normalMap;
	}

	void setPosition(float x, float y) {
		_rect.setPosition(x, y);
	}

	void draw(sf::RenderTarget& target) const
	{
		target.draw(_rect);
	}

};

#endif