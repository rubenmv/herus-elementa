/* 
 * File:   Rejilla.cpp
 * Author: Rubén
 * 
 * Created on 26 May 2013, 10:41
 */

#include "Rejilla.h"
#include "Resources.h"

Rejilla::Rejilla() {
	// Carga el sprite con la textura
	setSprite(RUTA_OBJETOS_GFX);
	setSize(32, 32);
	setCentro(this->getSize().x/2, this->getSize().y/2);
	setFrame(2, 2, 1, 1);
}

Rejilla::Rejilla(const Rejilla& orig) {
}

Rejilla::~Rejilla() {
}

