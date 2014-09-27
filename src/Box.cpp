/* 
 * File:   Box.cpp
 * Author: Rubén
 * 
 * Created on 25 May 2013, 20:07
 */

#include "Box.h"
#include "Resources.h"

Box::Box() {
	// Carga el sprite con la textura
	setSprite(RUTA_OBJETOS_GFX);
	
	setSize(64, 64);
	setCentro(this->getSize().x/2, this->getSize().y/2);
	setFrame(1, 0, 1, 1);
}

Box::Box(const Box& orig) {
}

Box::~Box() {
}

