/* 
 * File:   Key.cpp
 * Author: Ruben
 * 
 * Created on 09 May 2013, 19:47
 */

#include "Key.h"
#include "Resources.h"


Key::Key() {
	// Carga el sprite con la textura
	setSprite(RUTA_OBJETOS_GFX);
	setSize(32, 32);
	setCentro(this->getSize().x/2, this->getSize().y/2);
	setFrame(0, 1, 1, 1);
	
	active = 0;
}

Key::Key(const Key& orig) {
}

Key::~Key() {
}


