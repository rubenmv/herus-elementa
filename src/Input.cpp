/* 
 * File:   Input.cpp
 * Author: Ruben
 * 
 * Created on 12 May 2013, 20:46
 */

#include "Input.h"
#include "SFML/Window/Keyboard.hpp"

namespace game {

Input* Input::pinstance = 0;

Input* Input::Instance() {
	if(pinstance == 0) {
		pinstance = new Input;
	}
	return pinstance;
}

Input::Input() {
}

Input::Input(const Input& orig) {
}

Input::~Input() {
}

void Input::getInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
	  !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))) { left = true; }
	else { left = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
	  !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))) { right = true; }
	else { right = false; }
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { up = true; }
	else { up = false; }
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { down = true; }
	else { down = false; }
}

}