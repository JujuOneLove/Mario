#ifndef	BACKGROUND_HPP
#define BACKGROUND_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


class Background
{
private:
	sf::Image 			_imageC;	//sprite bleu
	sf::Texture 		_textureC;
	sf::Sprite 			_spriteCiel;
	vector<sf::Sprite> 	_spriteC;

	sf::Image 			_imageS;	//sprite sol
	sf::Texture 		_textureS;
	sf::Sprite 			_spriteSol;
	vector<sf::Sprite> 	_spriteS;

	sf::Image 			_imageN;	//sprite nuage
	sf::Texture 		_textureN;
	sf::Sprite 			_spriteNuage;
	vector<sf::Sprite> 	_spriteN;

	sf::Image 			_imageP1;
	sf::Image 			_imageP2;
	sf::Image 			_imageP3;
	sf::Image 			_imageP4;
	sf::Texture 		_textureP1;
	sf::Sprite 			_spritePlatF1;
	sf::Texture 		_textureP2;
	sf::Sprite 			_spritePlatF2;
	sf::Texture 		_textureP3;
	sf::Sprite 			_spritePlatF3;
	sf::Texture 		_textureP4;
	sf::Sprite 			_spritePlatF4;
	vector<sf::Sprite> 	_spriteP1;
	vector<sf::Sprite> 	_spriteP2;
	vector<sf::Sprite> 	_spriteP3;
	vector<sf::Sprite> 	_spriteP4;


	int blockSizeC = 64; //taille
	int blockSizeS = 30;
	int blockSizeN = 60;

public:
	Background() {
		//affichage ciel
		if (_imageC.loadFromFile("sky1.png")) { //Affichage du ciel
			_textureC.loadFromImage(_imageC);
			_spriteCiel.setTexture(_textureC);
		}
		for (int i = 0; i<53; i++)
			for (int j = 0; j<4; j++) {
				_spriteCiel.setPosition(i*blockSizeC, blockSizeC*j);
				_spriteC.push_back(_spriteCiel);
			}
		//affichae sol
		if (_imageS.loadFromFile("tile17.png")) { // affichage sol
			_textureS.loadFromImage(_imageS);
			_spriteSol.setTexture(_textureS);
		}
		for (int i = 0; i<113; i++) {
			_spriteSol.setPosition(i*blockSizeS, 200);
			_spriteS.push_back(_spriteSol);
		}
		//affichage nuage
		if (_imageN.loadFromFile("tile76.png")) { // affichage sol
			_textureN.loadFromImage(_imageN);
			_spriteNuage.setTexture(_textureN);
		}
		for (int i = 0; i<28; i++) {
			_spriteNuage.setPosition(i * 2 * blockSizeN, 50);
			_spriteN.push_back(_spriteNuage);
		}
		//affichage plateforme
		if (_imageP1.loadFromFile("tile21.png") &&
			_imageP2.loadFromFile("tile19.png") &&
			_imageP3.loadFromFile("tile20.png") &&
			_imageP4.loadFromFile("tile22.png")) { // affichage sol
			_textureP1.loadFromImage(_imageP1);
			_textureP2.loadFromImage(_imageP2);
			_textureP3.loadFromImage(_imageP3);
			_textureP4.loadFromImage(_imageP4);
			_spritePlatF1.setTexture(_textureP1);
			_spritePlatF2.setTexture(_textureP2);
			_spritePlatF3.setTexture(_textureP3);
			_spritePlatF4.setTexture(_textureP4);
		}
		for (int i = 0; i<5; i++) {
			_spritePlatF1.setPosition(60 + i * 650, 170);
			_spritePlatF2.setPosition(60 + i * 650, 140);
			_spritePlatF3.setPosition(90 + i * 650, 140);
			_spritePlatF4.setPosition(90 + i * 650, 170);
			_spriteP1.push_back(_spritePlatF1);
			_spriteP2.push_back(_spritePlatF2);
			_spriteP3.push_back(_spritePlatF3);
			_spriteP4.push_back(_spritePlatF4);
		}

	}


	~Background() {};

	void update() {
		/*if (_sprite.getPosition().y <= 0)//empeche de sortir de l'ecran
			_sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, 0));*/





	}




	void draw(sf::RenderTarget& renderer) {
		for (int i = 0; i<212; i++)
			renderer.draw(_spriteC[i]);
		for (int i = 0; i<113; i++)
			renderer.draw(_spriteS[i]);
		for (int i = 0; i<28; i++)
			renderer.draw(_spriteN[i]);
		for (int i = 0; i<5; i++) {
			renderer.draw(_spriteP1[i]);
			renderer.draw(_spriteP2[i]);
			renderer.draw(_spriteP3[i]);
			renderer.draw(_spriteP4[i]);

		}


	}


};

#endif