/* 
 * File:   Plataforma.cpp
 * Author: Ruben
 * 
 * Created on 13 May 2013, 16:08
 */

#include "Plataforma.h"
#include "Resources.h"

Plataforma::Plataforma() {
	// Carga el sprite con la textura
	setSprite(RUTA_OBJETOS_GFX);
	setSize(96, 32);
	setCentro(this->getSize().x/2, this->getSize().y/2);
	setFrame(4, 0, 1, 1);
	
	distancia = 0.f;
}

Plataforma::Plataforma(const Plataforma& orig) {
}

Plataforma::~Plataforma() {
}

void Plataforma::activar() {
	activa = true;
	// Se movera mientras distancia sea > 0
	setSpeed(-80.f, 0.f);
	distancia = getSpeed().x*120.f*-1;
}

