/* 
 * File:   Text.cpp
 * Author: Ruben
 * 
 * Created on 13 May 2013, 23:53
 */

#include "Text.h"
#include "SFML/Graphics/Text.hpp"
namespace game {
	
Text::Text() {
}

Text::Text(const Text& orig) {
}

Text::~Text() {
}

void Text::setFont(const char* fnt) {
	font.loadFromFile(fnt);
	text.setFont(font);
}
void Text::setCharacterSize(int size) {
	text.setCharacterSize(size);
}
void Text::setColor(sf::Color color) {
	text.setColor(color);
}
void Text::setString(std::string str) {
	text.setString(str);
}
void Text::setPosition(float x, float y) {
	text.setPosition(x, y);
	position.x = x;
	position.y = y;
}
void Text::draw() {
	GameEngine &engine = * GameEngine::Instance();
	engine.window.draw(text);
}

}