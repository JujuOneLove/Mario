#ifndef	APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

#include "background.hpp"
#include "mario.hpp"

class Application
{
private:
	sf::RenderWindow	_window;
	Background 			_background;
	Mario 				_mario;
	sf::Event 			_event;


private:
	void processEvents() {

		while (_window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
				_window.close();
		}
	}

	void render() {
		_window.clear();
		_background.draw(_window);
		_mario.draw(_window);
		_mario.gestionEvenement(_window, _event);
		_mario.update(_window);
		_window.display();

	}





public:
	Application() : _window(sf::VideoMode(800, 500), "Mario"),
		_mario()
	{
		_window.setPosition(sf::Vector2i(300, 200));//A centrer
		_window.setFramerateLimit(150);
		cout << "###  Lancement  ###" << endl;
	}


	void run()
	{
		do
		{
			render();
			processEvents();

		} while (_window.isOpen());
	}

};

#endif