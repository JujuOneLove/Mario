#ifndef	MARIO_HPP
#define MARIO_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "projectiles.hpp"
#include "blocks.hpp"
using namespace std;


class Mario
{
public:
	//sf::RenderWindow	_window;
	sf::RectangleShape _rect;
	float speed = 7;
	float jump = 22;
	sf::Vector2i 		_positionSouris;
	sf::Texture 		_texture;
	sf::Sprite 			_sprite;
	enum Direction { Down, Left, Right, Up };//Element dans l'ordre du gif
	sf::Vector2i _animationPerso = sf::Vector2i(1, Right);

	bool updateFPS = true;
	int blockSize = 32;
	sf::View 			_view;
	int screenW = 400, screenH = 224; //taille ecran

									  //Gravité et sol
	const float gravity = 0.5;
	sf::Vector2f _velocity = sf::Vector2f(0, 0);

	//Jump
	bool MarioJumping = true;

	sf::Clock 	_time;//FPS

					  //ennemi
	int attackDamage = 5;

	//mouvement collisions
	//Block 		_block;

	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;




public:
	Mario() {
		_rect.setSize(sf::Vector2f(32, 32));
		_rect.setFillColor(sf::Color::Blue);


		if (_texture.loadFromFile("mario_sprite.png")) {
			_texture.setSmooth(true);
			_sprite.setTexture(_texture);
			_sprite.setScale(1.0, 1.0);
		}
		_sprite.setPosition(43, 50);
	}

	~Mario() {};

	void gestionEvenement(sf::RenderWindow& _window, sf::Event& _event) {

		if (_event.type == sf::Event::KeyPressed)
			updateFPS = true;
		else
			updateFPS = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (MarioJumping == false)) {
			/*_animationPerso.y = Up;*/
			//_sprite.move(0, -speed);
			_velocity.y = -jump;
			MarioJumping = true;
			canMoveUp == true;

		}

		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (canMoveLeft == true)) {
			if (canMoveLeft == true) {
				_animationPerso.y = Left;
				//_sprite.move(-speed, 0);
				_velocity.x = -speed;


			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (canMoveRight == true)) {
			if (canMoveRight == true) {
				_animationPerso.y = Right;
				//_sprite.move(speed, 0);
				_velocity.x = speed;


			}
		}

		else _velocity.x = 0;


		//Gravite
		if ((_sprite.getPosition().y <= 385) && (MarioJumping == true)) {
			_velocity.y += gravity;
		}
		else {

			_velocity.y = 0;
			MarioJumping = false;
		}


		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		updateFPS = false;//arrete l'animation
		}*/

		if (updateFPS == true) {
			if (_time.getElapsedTime().asMilliseconds() >= 50) {
				_animationPerso.x--;
				if (_animationPerso.x*blockSize >= _texture.getSize().x)
					_animationPerso.x = 2;
				_time.restart();
				cout << _sprite.getPosition().x << "," << _sprite.getPosition().y << "::" << _rect.getPosition().x << "," << _rect.getPosition().y << endl;
			}
		}
		_sprite.setTextureRect(sf::IntRect(_animationPerso.x*blockSize, _animationPerso.y*blockSize, blockSize, blockSize));

		if (_sprite.getPosition().x <= 0)
			//empeche de sortir de l'ecran
			_sprite.setPosition(sf::Vector2f(0, _sprite.getPosition().y));


		if (_sprite.getPosition().y <= 0)
			//empeche de sortir de l'ecran
			_sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, 0));


		if (_sprite.getPosition().y >= 385) {
			//Mario touche le sol
			_sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, 385));
			MarioJumping = false;
			canMoveUp = false;

		}
		if (_sprite.getPosition().x >= 2760)//empeche de sortir de l'ecran
			_sprite.setPosition(sf::Vector2f(2760, _sprite.getPosition().y));


		/*	if((_sprite.getPosition().y >= 185) && ((_sprite.getPosition().x > 1100)&&(_sprite.getPosition().x < 1130))||((_sprite.getPosition().x > 1370) && (_sprite.getPosition().x < 1420)) || ((_sprite.getPosition().x > 2440) && (_sprite.getPosition().x < 2470)))
		//Mario peux tomber dans les trous
		_sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, _sprite.getPosition().y));

		*/
	}





	void update(sf::RenderWindow& _window) {
		_view.reset(sf::FloatRect(0, 0, 800, 500));//a changer par noms Variable
		sf::Vector2f _positionJ = sf::Vector2f(800 / 2, 500 / 2);
		_positionJ.x = _sprite.getPosition().x + (32 / 2) - (800 / 2);
		_positionJ.y = _sprite.getPosition().y + (32 / 2) - (500 / 2);
		if (_positionJ.x < 0)
			_positionJ.x = 0;
		if (_positionJ.y < 0)
			_positionJ.y = 0;
		_view.reset(sf::FloatRect(_positionJ.x, 0, 800, 500));


		_window.setView(_view);

		_sprite.move(_velocity.x, _velocity.y);//Personnage qui bouge


		_window.setView(_view);

		sf::Vector2f _positionRect = sf::Vector2f(43, 50);
		_positionRect.x = _sprite.getPosition().x;
		_positionRect.y = _sprite.getPosition().y;

		_rect.setPosition(_positionRect.x, _positionRect.y);
	}

	//Collisions
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


	bool isColl(Blocks& _block) {
		if (getBoundingBox().intersects(_block.getBoundingBox())) {
			cout << "col" << endl;
			
			if (_sprite.getPosition().y <= _block.getBoundingBoxTop()) {//up
				canMoveUp = false;
				MarioJumping = false;
				if (_sprite.getPosition().x < _block.getBoundingBoxLeft() - 12) {
					MarioJumping = true;
					canMoveRight = false;
				}
				else if (_sprite.getPosition().x > _block.getBoundingBoxLeft() + 23) {
					MarioJumping = true;
					canMoveLeft = false;
				}
			}
			else if (_sprite.getPosition().y  > _block.getBoundingBoxTop() - _block.getBoundingBoxHeight()) {
				_velocity.y = 5;
				MarioJumping = true;
			}

			else {

				if (_sprite.getPosition().x < _block.getBoundingBoxLeft() - 12) {//Left

					canMoveLeft = false;
					//_sprite.move(speed, 0);
				}
				else if (_sprite.getPosition().x > _block.getBoundingBoxLeft() + 23) {//right
					canMoveRight = false;
					//_sprite.move(-speed, 0);
				}
			}
			return true;
		}
		else {
			canMoveRight = true;
			canMoveLeft = true;
			canMoveUp = true;
			if (canMoveUp == true)
				_velocity.y += gravity;
			return false;
		}
	}




	void draw(sf::RenderTarget& renderer) {
		renderer.draw(_sprite);
		//renderer.draw(_rect);
	}



};

#endif