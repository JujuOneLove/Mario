#ifndef GOMBA_HPP
#define GOMBA_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

#include "blocks.hpp"
#include "mario.hpp"


class Goomba
{
private:
	sf::RectangleShape _rect;

	float speed = 3;
	float jump = 15;

	sf::Texture 		_textureG;
	sf::Sprite 			_spriteG;

	enum Direction { Left, Right, Rip };//Element dans l'ordre du gif
	sf::Vector2i _animationPersoG = sf::Vector2i(0, Right);


	bool updateFPS = true;
	sf::View 			_view;
	const float gravity = 0.5;
	sf::Vector2f _velocity = sf::Vector2f(0, 0);
	sf::Clock 	_time;//FPS

	bool MarioJumping = true;


	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;

	bool mort = false;



public:
	Goomba(float i, float j) {
		_rect.setSize(sf::Vector2f(32, 32));
		_rect.setFillColor(sf::Color::Blue);
		if (_textureG.loadFromFile("goomba.png")) {
			_textureG.setSmooth(true);
			_spriteG.setTexture(_textureG);
			_spriteG.setScale(1.9, 1.9);
		}
		_spriteG.setPosition(50, 350);
	}
	~Goomba() {};

	void gestionEvenement(sf::RenderWindow& _window, sf::Event& _event) {

		if (_velocity.x < 0)
			_animationPersoG.y = Left;
		else
			_animationPersoG.y = Right;
		if (mort == true) {
			_animationPersoG.y = Rip;
			_velocity.x = 0;
		}

		//Gravite
		if ((_spriteG.getPosition().y <= 385) && (MarioJumping == true)) {
			_velocity.y += gravity;

		}
		else {

			_velocity.y = 0;
			MarioJumping = false;
		}

		if (canMoveLeft == false)
			_velocity.x = speed;
		if (canMoveRight == false)
			_velocity.x = -speed;
		if ((canMoveRight == true) && (canMoveLeft == true) && (MarioJumping == false) && (mort == false)) {
			if (_velocity.x == 0)
				_velocity.x = speed;
			_velocity.x = _velocity.x;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			updateFPS = false;//arrete l'animation
		}


		if (_time.getElapsedTime().asMilliseconds() >= 50) {
			_animationPersoG.x--;
			if (_animationPersoG.x * 18 >= _textureG.getSize().x)
				_animationPersoG.x = 2;
			_time.restart();
			cout << _spriteG.getPosition().x << "," << _spriteG.getPosition().y << endl;
		}

		_spriteG.setTextureRect(sf::IntRect(_animationPersoG.x * 18, _animationPersoG.y * 18, 18, 18));

		if (_spriteG.getPosition().x <= 0) {
			//empeche de sortir de l'ecran
			_spriteG.setPosition(sf::Vector2f(0, _spriteG.getPosition().y));
			_velocity.x = speed;
		}


		if (_spriteG.getPosition().y >= 385) {
			//Mario touche le sol
			_spriteG.setPosition(sf::Vector2f(_spriteG.getPosition().x, 385));
			MarioJumping = false;
			canMoveUp = false;

		}
		if (_spriteG.getPosition().x >= 2760){//empeche de sortir de l'ecran
			_spriteG.setPosition(sf::Vector2f(2760, _spriteG.getPosition().y));
			_velocity.x = -speed;
		}

	}





	void update(sf::RenderWindow& _window) {
		_spriteG.move(_velocity.x, _velocity.y);//Personnage qui bouge


		sf::Vector2f _positionRect = sf::Vector2f(43, 50);
		_positionRect.x = _spriteG.getPosition().x;
		_positionRect.y = _spriteG.getPosition().y;

		_rect.setPosition(_positionRect.x, _positionRect.y);
	}

	sf::FloatRect getBoundingBox() const
	{
		return _rect.getGlobalBounds();
	}
	float getBoundingBoxTop() const
	{
		return _rect.getGlobalBounds().top;
	}
	float getBoundingBoxHeight() const
	{
		return _rect.getGlobalBounds().height;
	}
	float getBoundingBoxLeft() const
	{
		return _rect.getGlobalBounds().left;
	}



	void isColl(Blocks& _block) {
		if (getBoundingBox().intersects(_block.getBoundingBox())) {
			cout << "col" << endl;
			_block.setColor(sf::Color::Red);
			if (_spriteG.getPosition().y <= _block.getBoundingBoxTop()) {//up
				canMoveUp = false;
				MarioJumping = false;
				if (_spriteG.getPosition().x - 2 < _block.getBoundingBoxLeft() - 12) {
					MarioJumping = true;
					canMoveRight = false;
				}
				else if (_spriteG.getPosition().x > _block.getBoundingBoxLeft() + 23) {
					MarioJumping = true;
					canMoveLeft = false;
				}
			}
			else if (_spriteG.getPosition().y  > _block.getBoundingBoxTop() - _block.getBoundingBoxHeight()) {
				_velocity.y = 5;
				MarioJumping = true;
			}
			else {

				if (_spriteG.getPosition().x < _block.getBoundingBoxLeft() - 12) {//Left

					canMoveLeft = false;
				}
				else if (_spriteG.getPosition().x > _block.getBoundingBoxLeft() + 23) {//right
					canMoveRight = false;
				}
			}
		}
		else {
			canMoveRight = true;
			canMoveLeft = true;
			canMoveUp = true;
			if (canMoveUp == true)
				_velocity.y += gravity;
		}
	}

	void isCollMario(Mario& _mario) {
		if (getBoundingBox().intersects(_mario.getBoundingBox())) {
			cout << "col enemie" << endl;
			if ((getBoundingBoxTop()< _mario.getBoundingBoxTop()) && (mort == false)) {
				mort = true;
			}
			else if ((_spriteG.getPosition().y > _mario.getBoundingBoxTop()) && (mort == false)) {
				cout << "Mario Rip" << endl;
			}
			else {

				if ((_spriteG.getPosition().x < _mario.getBoundingBoxLeft() - 12) && (mort == false)) {//Left

					cout << "Mario Rip" << endl;
				}
				else if ((_spriteG.getPosition().x > _mario.getBoundingBoxLeft() + 23) && (mort == false))//right
					cout << "Mario RIP" << endl;
			}
		}
	}




	void draw(sf::RenderTarget& renderer) {
		renderer.draw(_spriteG);
	}



};

#endif