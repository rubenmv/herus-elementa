/* 
 * File:   Torch.cpp
 * Author: Rubén
 * 
 * Created on 26 May 2013, 13:48
 */

#include <iostream>
#include "Torch.h"

Torch::Torch() {
	// Carga el sprite con la textura
	setSprite(RUTA_TORCH_GFX);
	
	setSize(48, 48);
	setCentro(this->getSize().x/2, this->getSize().y/2);
	setFrame(0, 0, 1, 1);
	
	tempo.restart();
	
	activa = false;
}

Torch::Torch(const Torch& orig) {
}

Torch::~Torch() {}

void Torch::activar() {
	if(!activa) {
		activa = true;
		clock.restart(); // Reinciamos el reloj para realizar la animacion
		tempo.restart(); // Tambien activamos el temporizador
		setFrame(0, 1, 1, 1);
	}
}

void Torch::update() {
	if(activa) {
		// A los 5 segundos se desactiva
		if(tempo.getSeconds() > 5) {
			activa = false;
			// Cambiamos el frame
			setFrame(0, 0, 1, 1);
		}
		// Animamos
		else {
			this->animate();
		}
	}
	else {
		
	}
}

void Torch::animate() {
	float tiempo = 150.f;
	
	if(clock.getMiliseconds() > tiempo) {
		if(frame > 4) frame = 1;
		else frame++;
		
		setFrame(0, frame, 1 , 1);

		clock.restart();
	}
}

