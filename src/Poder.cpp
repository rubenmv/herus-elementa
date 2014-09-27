/* 
 * File:   Poder.cpp
 * Author: Ruben
 * 
 * Created on 14 May 2013, 16:12
 */

#include "Poder.h"
#include "Resources.h"

Poder::Poder(const int t) {
	tipo = t;
	setSprite(RUTA_OBJETOS_GFX);
	size.x = size.y = 32;
	active = -1;
	clock.restart();
}

Poder::Poder(const Poder& orig) {
}

Poder::~Poder() {
}

void Poder::animate() {}
