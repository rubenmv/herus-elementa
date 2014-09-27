/* 
 * File:   GameEngine.cpp
 * Author: Rubén
 * 
 * Created on 22 May 2013, 00:44
 */

#include "GameEngine.h"

GameEngine* GameEngine::pinstance = 0;

GameEngine* GameEngine::Instance() {
	if(pinstance == 0) {
		pinstance = new GameEngine;
	}
	return pinstance;
}

GameEngine::GameEngine() {
    windowWidth = 800;
    windowHeight = 600;
    
    this->window.create(sf::VideoMode(windowWidth, windowHeight, 32), "Herus Elementa");
    
    // Ventana
    this->window.setFramerateLimit(60);
}

GameEngine::GameEngine(const GameEngine& orig) {
}

GameEngine::~GameEngine() {
}

