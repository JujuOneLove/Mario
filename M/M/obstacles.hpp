#ifndef OBSTACLES_HPP
#define OBSTACLES_HPP

//#include <vector>
#include <SFML/Graphics.hpp>
#include "blocks.hpp"
#include "mario.hpp"

using namespace std;

class Obstacle
{
private:
	Block  _block;
	//_vecBlocks.resize(16*100);

public:

	int _ = 862, H = 21, T = 53, Q = 246, B = 245, T1 = 616, T2 = 617, T3 = 648, T4 = 649, C = 240, L = 279, R = 240;

	void charger(sf::RenderWindow& _window, int tiles[16][100], unsigned int width, unsigned int height) {
		//vector<Block> 	_vecBlocks;

		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				if (tiles[i][j] == H || tiles[i][j] == T || tiles[i][j] == Q || tiles[i][j] == T1 || tiles[i][j] == T2 ||
					tiles[i][j] == T3 || tiles[i][j] == T4 || tiles[i][j] == C || tiles[i][j] == L || tiles[i][j] == R || tiles[i][j] == B) {
					//_block.setPosition(j*32,i*32);
					_block.draw(_window);
				}
			}
		}
	}

	void isColl(Mario& _mario) {
		if (_mario.getBoundingBox().intersects(_block.getBoundingBox())) {
			cout << "col" << endl;
			_block.setColor(sf::Color::Red);
			if (_mario._sprite.getPosition().y <= _block.getBoundingBoxTop()) {//up
				_mario.canMoveUp = false;
				_mario.MarioJumping = false;
				if (_mario._sprite.getPosition().x < _block.getBoundingBoxLeft() - 12) {
					_mario.MarioJumping = true;
					_mario.canMoveRight = false;
				}
				else if (_mario._sprite.getPosition().x > _block.getBoundingBoxLeft() + 23) {
					_mario.MarioJumping = true;
					_mario.canMoveLeft = false;
				}
			}
			else if (_mario._sprite.getPosition().y  > _block.getBoundingBoxTop() - _block.getBoundingBoxHeight()) {
				_mario._velocity.y = 5;
				_mario.MarioJumping = true;
			}

			else {

				if (_mario._sprite.getPosition().x < _block.getBoundingBoxLeft() - 12) {//Left

					_mario.canMoveLeft = false;
					//_sprite.move(speed, 0);
				}
				else if (_mario._sprite.getPosition().x > _block.getBoundingBoxLeft() + 23) {//right
					_mario.canMoveRight = false;
					//_sprite.move(-speed, 0);
				}

			}

			/*	else if (direction == Down) {
			cout << "chute";_mario.
			}*/
		}
		else {
			_block.setColor(sf::Color::White);
			_mario.canMoveRight = true;
			_mario.canMoveLeft = true;
			_mario.canMoveUp = true;
			if (_mario.canMoveUp == true)
				_mario._velocity.y += _mario.gravity;
		}


	}



};
#endif