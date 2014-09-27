/* 
 * File:   Door.cpp
 * Author: Ruben
 * 
 * Created on 12 May 2013, 20:22
 */

#include "Door.h"
#include "Resources.h"

Door::Door() {
	// Carga el sprite con la textura
	setSprite(RUTA_OBJETOS_GFX);
	setSize(32, 64);
	setCentro(this->getSize().x/2, this->getSize().y/2);
	setFrame(0, 3, 1, 1);
	
	activa = false;
}

Door::Door(const Door& orig) {
}

Door::~Door() {
}

void Door::activar() {
	activa = true;
	
	setFrame(1, 3, 1, 1);
}

