/* 
 * File:   Enemy.cpp
 * Author: Ruben
 * 
 * Created on 28 April 2013, 22:03
 */

#include <iostream>
#include "Enemy.h"
#include "Resources.h"

Enemy::Enemy(const int t) {
	tipo = t;
	
	setSpeed(-50.f, 0.f);
	
	// Gobo
	if(tipo == 1) {
		setSprite(RUTA_GOBO_GFX);
		setSize(24, 28);
		setFrame(0, 0, 1, 1);
		vivo = true;
		setSpeed(-50.f, 0.f);
	}
	// Kompa
	else if(tipo == 2) {
		setSprite(RUTA_KOMPA_GFX);
		setSize(25, 28);
		setFrame(0, 0, -1, 1);
		vivo = true;
		setSpeed(50.f, 0.f);
		
	}
	
	// Posicion inicial para calcular la distancia recorrida
	distance = getPosition().x;
	
	animClock.restart();
}

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
}

// Devuelve el rectangulo que cubre al sprite
sf::IntRect Enemy::getBounds() {
	sf::IntRect r(getPosition().x - getSize().x/2 + 10, getPosition().y - getSize().y/2 + 10, getSize().x - 10, getSize().y - 5);
	return r;
}


void Enemy::animate() {
	// Animaciones enemigos
	if(animClock.getMiliseconds() > 100.f) {
		if(frame > 2) { frame = 0; }
		else { frame++; }

		if(vivo) {
			if(getSpeed().x >= 0) {
				setFrame(0, frame, 1, 1); // Derecha
			}
			else {
				setFrame(0, frame, -1, 1); // Izquierda
			}
		}
		// Muerto
		else if(getPosition().y < 600 + 50) {
			sprite.rotate(20); // Rota si sigue dentro de la pantalla
		}

		animClock.restart();
	}
}