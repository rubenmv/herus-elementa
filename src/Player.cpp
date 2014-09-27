/* 
 * File:   Player.cpp
 * Author: Ruben
 * 
 * Created on 21 March 2013, 16:09
 */

#include <iostream>
#include "Resources.h"
#include "Player.h"
#include "Input.h"
#include "GameEngine.h"

#define kVelMax 200
#define kFric 0.85
#define kGravity 20
#define kAccel 30
#define jumpPower 450

namespace game {

Player* Player::pinstance = 0;

Player* Player::Instance() {
	if(pinstance == 0) {
		pinstance = new Player;
	}
	return pinstance;
}
	
Player::Player() {
	init();
	
	// Carga el sprite con la textura
	setSprite(RUTA_PLAYER_GFX);
	setSize(48, 48);
	setCentro(this->getSize().x/2, this->getSize().y/2);
	spawn.x = 0.f;
	spawn.y = 0.f;
	setPosition(spawn.x, spawn.y);
	
	// Inicializamos los poderes
	powers[0] = powers[1] = powers[2] = powers[3] = -1;
	// Temporizador para algunas habilidades
	powerTimer.restart();
        frame = 0;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

int Player::getVidas() {
	return vidas;
}

void Player::setVidas(int v) {
	vidas = v;
}

void Player::init() {
	vidas = 3;
	respawn();
}

void Player::respawn() {
	setFrame(1, 1, 1, 1);
	setSpeed(0.f, 0.f);
	setPosition(spawn.x, spawn.y);
	onGround = false;
	facingLeft = false;
	vivo = true;
}

// Devuelve el rectangulo que cubre al sprite
sf::IntRect Player::getBounds() {
	sf::IntRect r(getPosition().x - getSize().x/2 + 5, getPosition().y - getSize().y/2, 30, getSize().y);
	return r;
}

void Player::update() {
	// Motor de juego (reloj y ventana)
	GameEngine &engine = * GameEngine::Instance();
	// Input
	game::Input &input = * game::Input::Instance();
	
	if(this->vivo) {
		// MOVIMIENDO EN EL EJE X
		// Izquierda
		if(input.left) {
			// Si la velocidad no llega al limite
			if(this->getSpeed().x*-1 < kVelMax) {
				// Aplicamos aceleracion a la velocidad
				this->setSpeed(this->getSpeed().x-kAccel, this->getSpeed().y);
			}
			this->facingLeft = true;
		}
		// Derecha
		if(input.right) {
			// Si la velocidad no llega al limite
			if(this->getSpeed().x < kVelMax) {
				// Aplicamos aceleracion a la velocidad
				this->setSpeed(this->getSpeed().x+kAccel, this->getSpeed().y);
			}
			this->facingLeft = false;
		}

		// En aire/salto
		if(input.up && this->onGround) {
			this->setSpeed(this->getSpeed().x, this->getSpeed().y - jumpPower);
			this->onGround = false;
			this->powerTimer.restart();
		}

		// Si la velocidad es muy baja, se para (entre 10 y -10)
		if(this->getSpeed().x < 10.f && this->getSpeed().x > -10.f) {
			this->setSpeed(0, this->getSpeed().y);
		}
		// Si el jugador se mueve, hay friccion
		if(this->getSpeed().x != 0) {
			this->setSpeed(this->getSpeed().x*kFric, this->getSpeed().y);
		}
	}

	// Gravedad
	if(!this->onGround) {
		if(this->powers[0] == 1 &&
			(this->getSpeed().y >= -10.f && this->getSpeed().y <= 10.f) &&
			this->powerTimer.getSeconds() < 1.f ) {
				this->setSpeed(this->getSpeed().x, 0.f);
		}
		else {
			this->setSpeed(this->getSpeed().x, this->getSpeed().y + kGravity);
		}
	}

	// Movemos al jugador antes de comprobar colision con tiles
	this->oldPos = this->getPosition(); // La posicion antes de mover
	this->move(this->getSpeed().x*engine.clock.elapsedSeconds, this->getSpeed().y*engine.clock.elapsedSeconds);

	// Comprobamos si se ha salido de la pantalla y estaba vivo
	if(this->vivo && this->getPosition().y > engine.windowHeight + 50) {
		this->vivo = false;
		this->setVidas(this->getVidas()-1);
	}
}

void Player::animate() {
	// Input
	game::Input &input = * game::Input::Instance();
	
	float tiempo = 100.f;
	int grupo = 0; // Estado normal
	
	// Recorremos los 4 poderes para ver el activo
	for(int i = 0; i < 4; i++) {
		if(powers[i] == 1) {
			grupo = (i+1)*4; // 4 filas por estado
		}
	}
	
	if(vivo) {
		if(!onGround && powers[0] == 1) {
			if(input.left) { // Izquierda
				if(clock.getMiliseconds() > 80.f) {
					if(frame > 1) frame = 1;
					else frame++;

					setFrame(grupo+2, frame, -1 , 1);

					clock.restart();
				}
			}
			else if(input.right) { // Derecha
				if(clock.getMiliseconds() > 80.f) {
					if(frame > 1) frame = 1;
					else frame++;

					// Fila 0: Corriendo
					setFrame(grupo+2, frame, 1 , 1);

					clock.restart();
				}
			}
		}
		else if(input.left) { // Izquierda
			if(clock.getMiliseconds() > tiempo) {
				if(frame > 4) frame = 0;
				else frame++;

				setFrame(grupo+1, frame, -1 , 1);

				clock.restart();
			}
		}
		else if(input.right) { // Derecha
			if(clock.getMiliseconds() > tiempo) {
				if(frame > 4) frame = 0;
				else frame++;

				// Fila 0: Corriendo
				setFrame(grupo+1, frame, 1 , 1);

				clock.restart();
			}
		}
		else { // Parado
			if(clock.getMiliseconds() > tiempo) {
				if(facingLeft) {
					setFrame(grupo+1, 0, -1, 1);
				}
				else {
					setFrame(grupo+1, 0, 1, 1);
				}
				clock.restart();
			}
		}
	}
	else {
		setFrame(2, 4, 1, 1);
	}
}

// Punto de aparicion del jugador
void Player::setSpawn(float x, float y) {
	this->spawn.x = x;
	this->spawn.y = y;
}

// Activa / Desactiva el poder p
void Player::togglePower(int p) {
	// Desactivamos los poderes activos que no sean p
	for(int i = 0; i < 4; i++) {
		if(i != p && powers[i] != -1) {
			powers[i] = 0;
		}
	}
	// Solo si se ha recogido
	if(powers[p] != -1) {
		if(powers[p] == 0) {
			powers[p] = 1;
		}
		else {
			powers[p] = 0;
		}
	}
}

}

