#ifndef	SONS_HPP
#define SONS_HPP

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class Son
{
public:
	sf::SoundBuffer buffer;
	sf::Sound sound;

	Son()
	{
		if (!buffer.loadFromFile("Super_Mario.wav")) {
			cout << "erreur";
		}
		sound.setBuffer(buffer);
	}

	void init() {
		sound.play();
	}



};

#endif