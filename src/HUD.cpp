/* 
 * File:   HUD.cpp
 * Author: Ruben
 * 
 * Created on 27 May 2013, 12:09
 */

#include <sstream>
#include "HUD.h"
#include "Player.h"
#include "Resources.h"
#include "GameEngine.h"

HUD* HUD::pinstance = 0;

HUD* HUD::Instance() {
	if(pinstance == 0) {
		pinstance = new HUD;
	}
	return pinstance;
}

HUD::HUD() {
	heart = new Entity(RUTA_HEART_GFX);
	heart->setPosition(30, 30);
	
	textoVidas = new game::Text();
	textoVidas->setFont(RUTA_FONT_GBB);
	textoVidas->setCharacterSize(48);
	textoVidas->setColor(sf::Color(255, 255, 255));
	textoVidas->setString("");
	textoVidas->setPosition(heart->getPosition().x + 10, heart->getPosition().y);
	
	ayuda = new Ayuda();
}

HUD::HUD(const HUD& orig) {
}

HUD::~HUD() {
	delete heart;
	delete textoVidas;
	delete ayuda;
}

void HUD::update(game::Camera camara) {
	game::Player &player = * game::Player::Instance();
	GameEngine &engine = * GameEngine::Instance();
	
	std::ostringstream oss1;
	oss1 << player.getVidas();
	textoVidas->setString(oss1.str());
	
	heart->setPosition(camara.getCenter().x - engine.windowWidth / 2 + 30, 30);
	textoVidas->setPosition(heart->getPosition().x + heart->getSize().x + 20, heart->getPosition().y - heart->getSize().y/2);
	
	ayuda->update(camara);
}

void HUD::draw() {
	GameEngine &engine = * GameEngine::Instance();
	textoVidas->draw();
	heart->draw();
	ayuda->draw();
}

