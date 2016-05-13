#ifndef	MARIO_HPP
#define MARIO_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


class Mario
{
private:
	//sf::RenderWindow	_window;
	float speed = 1;
	float jump = 0.5;
	sf::Vector2i 		_positionSouris;
	sf::Texture 		_texture;
	sf::Sprite 			_sprite;
	enum Direction { Down, Left, Right, Up };//Element dans l'ordre du gif
	sf::Vector2i _animationPerso = sf::Vector2i(1, Right);
	sf::Clock 			_time;
	bool updateFPS = true;
	int blockSize = 32;
	sf::View 			_view;
	int screenW = 400, screenH = 224; //taille ecran

	//Gravité et sol
	const float gravity = 0.3;
	sf::Vector2f _velocity = sf::Vector2f(0, 0);



public:
	Mario() {
		if (_texture.loadFromFile("mario_sprite.png")) {
			_texture.setSmooth(true);
			_sprite.setTexture(_texture);
			_sprite.setScale(0.5, 0.5);
		}
		_sprite.setPosition(43, 185);
	}
	~Mario() {};

	void gestionEvenement(sf::RenderWindow& _window, sf::Event& _event) {

		if (_event.type == sf::Event::KeyPressed)
			updateFPS = true;
		else
			updateFPS = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			/*_animationPerso.y = Up;*/
			//_sprite.move(0, -speed);
			_velocity.y = -jump;
		}
		/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			_animationPerso.y = Down;
			//_sprite.move(0, speed);
		}*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			_animationPerso.y = Left;
			//_sprite.move(-speed, 0);
			_velocity.x = -speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			_animationPerso.y = Right;
			//_sprite.move(speed, 0);
			_velocity.x = speed;
		}
		else _velocity.x = 0;


		//Gravite
		if (_sprite.getPosition().y < screenH) {
			_velocity.y += gravity;
		}
		else {

			_velocity.y = 0;
		}

		_sprite.move(_velocity.x, _velocity.y);//Personnage qui bouge

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			updateFPS = false;//arrete l'animation
		}
		/*else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		_positionSouris = sf::Mouse::getPosition(_window);
		cout << "Mouse.x = " << _positionSouris.x << " " << "Mouse.y = " << _positionSouris.y << endl;
		int mouseX = _positionSouris.x;
		int mouseY = _positionSouris.y;
		_sprite.setPosition(mouseX,mouseY);
		}*/
		if (updateFPS == true) {
			if (_time.getElapsedTime().asMilliseconds() >= 50) {
				_animationPerso.x--;
				if (_animationPerso.x*blockSize >= _texture.getSize().x)
					_animationPerso.x = 2;
				_time.restart();
				cout << _sprite.getPosition().x << "," << _sprite.getPosition().y << endl;
			}
		}
		_sprite.setTextureRect(sf::IntRect(_animationPerso.x*blockSize, _animationPerso.y*blockSize, blockSize, blockSize));

		if (_sprite.getPosition().x <= 0)
			//empeche de sortir de l'ecran
			_sprite.setPosition(sf::Vector2f(0, _sprite.getPosition().y));
		
		
		if (_sprite.getPosition().y <= 0)
			//empeche de sortir de l'ecran
			_sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, 0));
		
		
		if ((_sprite.getPosition().y >= 185)&&((_sprite.getPosition().x <= 1100)||((1130<=_sprite.getPosition().x)&&(_sprite.getPosition().x<=1370))|| ((1420 <= _sprite.getPosition().x) && (_sprite.getPosition().x <= 2440)) || ((2470 <= _sprite.getPosition().x) && (_sprite.getPosition().x <= 3384))))
			//Mario touche le sol
			_sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, 185));
		
		
		if (_sprite.getPosition().x >= 3384
			)//empeche de sortir de l'ecran
			_sprite.setPosition(sf::Vector2f(3384, _sprite.getPosition().y));
		
		
		if((_sprite.getPosition().y >= 185) && ((_sprite.getPosition().x > 1100)&&(_sprite.getPosition().x < 1130))||((_sprite.getPosition().x > 1370) && (_sprite.getPosition().x < 1420)) || ((_sprite.getPosition().x > 2440) && (_sprite.getPosition().x < 2470)))
			//Mario peux tomber dans les trous
			_sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, _sprite.getPosition().y));


	}

	void update(sf::RenderWindow& _window) {
		_view.reset(sf::FloatRect(0, 0, screenW, screenH));//a changer par noms Variable
		sf::Vector2f _positionJ = sf::Vector2f(screenW / 2, screenH / 2);
		_positionJ.x = _sprite.getPosition().x + (blockSize / 2) - (screenW / 2);
		_positionJ.y = _sprite.getPosition().y + (blockSize / 2) - (screenH / 2);
		if (_positionJ.x < 0)
			_positionJ.x = 0;
		if (_positionJ.y < 0)
			_positionJ.y = 0;
		_view.reset(sf::FloatRect(_positionJ.x,0, screenW, screenH));
		

		_window.setView(_view);
	}



	void draw(sf::RenderTarget& renderer) {
		renderer.draw(_sprite);
	}



};

#endif