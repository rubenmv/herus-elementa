/*
 * File:   Text.h
 * Author: Ruben
 *
 * Created on 13 May 2013, 23:53
 */

#ifndef TEXT_H
#define	TEXT_H

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "GameEngine.h"


namespace game {

class Text {
public:
	Text();
	Text(const Text& orig);
	virtual ~Text();

	void setFont(const char* fnt);
	void setCharacterSize(int size);
	void setColor(sf::Color color);
	void setString(std::string str);
	void setPosition(float x, float y);
	void draw();

private:
	sf::Text text;
	sf::Font font;
	sf::Vector2f position;
};

}

#endif	/* TEXT_H */

