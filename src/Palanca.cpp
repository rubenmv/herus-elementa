/* 
 * File:   Palanca.cpp
 * Author: Ruben
 * 
 * Created on 13 May 2013, 16:08
 */

#include "Palanca.h"
#include "Resources.h"

Palanca::Palanca() {
	// Carga el sprite con la textura
	setSprite(RUTA_OBJETOS_GFX);
	
	setSize(32, 32);
	setCentro(this->getSize().x/2, this->getSize().y/2);
	setFrame(0, 0, 1, 1);
	
	activa = false;
}

Palanca::Palanca(const Palanca& orig) {
}

Palanca::~Palanca() {
}

void Palanca::activar() {
	activa = true;
	setFrame(0, 0, -1, 1);
}
