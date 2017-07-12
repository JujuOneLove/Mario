#ifndef PERSO_HPP
#define PERSO_HPP

class Player
{
public:
	sf::RectangleShape _rectPlayer;

	sf::View _view;
	sf::Vector2f _velocity = sf::Vector2f(0, 0);

	Player() {
		_rectPlayer.setPosition(0, 0);
		_rectPlayer.setSize(sf::Vector2f(32, 32));
		_rectPlayer.setFillColor(sf::Color::White);

	}

	sf::FloatRect getBoundingBox() const
	{
		return _rectPlayer.getGlobalBounds();
	}

	void update(sf::RenderWindow& _window) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			_rectPlayer.move(0.5f, 0);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			_rectPlayer.move(-0.5f, 0);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			_rectPlayer.move(0, -0.5f);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			_rectPlayer.move(0, 0.5f);


		_view.reset(sf::FloatRect(0, 0, 800, 500));//a changer par noms Variable
		sf::Vector2f _positionJ = sf::Vector2f(800 / 2, 500 / 2);
		_positionJ.x = _rectPlayer.getPosition().x + (32 / 2) - (800 / 2);
		_positionJ.y = _rectPlayer.getPosition().y + (32 / 2) - (500 / 2);
		if (_positionJ.x < 0)
			_positionJ.x = 0;
		if (_positionJ.y < 0)
			_positionJ.y = 0;
		_view.reset(sf::FloatRect(_positionJ.x, 0, 800, 500));


		_window.setView(_view);

		_rectPlayer.move(_velocity.x, _velocity.y);//Personnage qui bouge


		_window.setView(_view);

	}


};
#endif