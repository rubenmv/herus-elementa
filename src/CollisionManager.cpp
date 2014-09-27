/* 
 * File:   CollisionManager.cpp
 * Author: Ruben Martinez Vilar
 * 
 * Created on 12 March 2013, 00:01
 */
#include <iostream>
#include "CollisionManager.h"
#include "Player.h"
#include "LevelManager.h"
#include "Input.h"
#include "HUD.h"

namespace game {

CollisionManager* CollisionManager::pinstance = 0;

CollisionManager* CollisionManager::Instance() {
    if(pinstance == 0) {
            pinstance = new CollisionManager;
    }
    return pinstance;
}
	
CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {}

// Determina si se produce una colision entre dos rectangulos
bool CollisionManager::checkCollision(sf::IntRect r1, sf::IntRect r2) {
	// Obtenemos por que lado se produce la colision
	if(r1.intersects(r2)) {
		int l1 = r2.left - r1.left;
		int l2 = r1.left + r1.width - r2.left;
		int l3 = r2.top - r1.top;
		int l4 = r1.top + r1.height - r2.top;
		
		// r1 toca por la izquierda de r2
		if(l1 > l2) { left = true; right = false; }
		else { left = false; right = true; } // Por la derecha
		
		// r1 toca encima de r2
		if(l3 > l4) { top = true; bottom = false; }
		else { top = false; bottom = true; } // r1 toca por debajo de r2
		
		return true;
	}
	
	return false;
}

// Maneja todas las colisiones del nivel actual
void CollisionManager::handleCollisions() {
	// Recogemos el nivel actual
	game::LevelManager *lf1 = game::LevelManager::Instance();
	game::LevelManager *lf2 = lf1->Instance();
	game::LevelManager &levelManager = * game::LevelManager::Instance();
	// Llamamos al jugador
	game::Player *p1 = game::Player::Instance();
	game::Player *p2 = p1->Instance();
	game::Player &player = * game::Player::Instance();
	// Input
	game::Input *i1 = game::Input::Instance();
	game::Input *i2 = i1->Instance();
	game::Input &input = * game::Input::Instance();

	// MAPA CON ZONAS DE MUERTE
	for(int i = 0; i < levelManager.inlevel->deathMap.size(); i++) { // Vector con los rectangulos de colision
		// Rectangulo actual a comprobar
		sf::IntRect recTile = levelManager.inlevel->deathMap[i];
		
		// El jugador colisiona con ese rectangulo
		if(this->checkCollision(player.getBounds(), recTile)) {
			// La primera vez que toca muere
			if(player.vivo) {
				player.setSpeed(0, 0);
				player.setVidas(player.getVidas()-1); // Restamos vida
				player.vivo = false;
			}
		}
	}
	
	int ejeX, ejeY;
	bool colides = false;
	// MAPA SOLIDO	
	for(int i = 0; i < levelManager.inlevel->colisionMap.size(); i++) { // Vector con los rectangulos de colision
		// Rectangulo actual a comprobar
		sf::IntRect recTile = levelManager.inlevel->colisionMap[i];

		// Solo los rectangulos alrededor del jugador
		if( (abs(player.getPosition().x - recTile.left) <= levelManager.inlevel->tileSize.x)
			&& (abs(player.getPosition().y - recTile.top) <= levelManager.inlevel->tileSize.y) ) {

			// El jugador colisiona con ese rectangulo
			if(this->checkCollision(player.getBounds(), recTile)) {
				colides = true;

				// Determinamos cuanto se solapan en cada eje
				// EJE Y
				if(this->top) {
					ejeY =  recTile.top - (player.getPosition().y + player.getSize().y/2);
				}
				else {
					ejeY = (recTile.top + recTile.height) - (player.getPosition().y - player.getSize().y/2);
				}

				// EJE X. Por la izquierda y la derecha
				if(this->left) {
					ejeX =  recTile.left - (player.getPosition().x + player.getSize().x/2);
				}
				else {
					ejeX = (recTile.left + recTile.width) - (player.getPosition().x - player.getSize().x/2);
				}
				
				// Actualizamos solo el eje que ha solapado menos
				// EJE Y
				if(abs(ejeY) <= abs(ejeX) && player.getSpeed().y >= 0) {
					// Toca por encima
					if((player.getPosition().y + player.getSize().y/2) <= recTile.top + 20) {
						// Lo devolvemos a la antigua posicion
						player.setPosition(player.getPosition().x, player.oldPos.y);
						player.setSpeed(player.getSpeed().x, 0);
						player.onGround = true;
					}
					
				}
				// EJE X
				else {
					player.setPosition(player.oldPos.x, player.getPosition().y);
					player.setSpeed(0, player.getSpeed().y);
				}
				
			}
		}
	}
	// PLATAFORMAS
	for(int i = 0; i < levelManager.inlevel->plataformas.size(); i++) {
		// Rectangulo actual a comprobar
		sf::IntRect recTile = levelManager.inlevel->plataformas[i]->getBounds();

		// El jugador colisiona con ese rectangulo
		if(this->checkCollision(player.getBounds(), recTile)) {
			colides = true;

			// Determinamos cuanto se solapan en cada eje
			// EJE Y
			ejeY =  recTile.top - (player.getPosition().y + player.getSize().y/2);

			// EJE X. Por la izquierda y la derecha
			if(this->left) {
				ejeX =  recTile.left - (player.getPosition().x + player.getSize().x/2);
			}
			else {
				ejeX = (recTile.left + recTile.width) - (player.getPosition().x - player.getSize().x/2);
			}

			// Actualizamos solo el eje que ha solapado menos
			// EJE Y
			if(abs(ejeY) <= abs(ejeX) && player.getSpeed().y >= 0) {
				// Toca por encima
				if(this->top) {
					// Lo devolvemos a la antigua posicion
					player.setPosition(player.getPosition().x, player.oldPos.y);
					player.setSpeed(player.getSpeed().x, 0);
					player.onGround = true;
				}
			}
			// EJE X
			else {
				player.setPosition(player.oldPos.x, player.getPosition().y);
				player.setSpeed(0, player.getSpeed().y);
			}	
		}
	}
	
	// CAJAS
	for(int i = 0; i < levelManager.inlevel->cajas.size(); i++) {
		// Rectangulo actual a comprobar
		sf::IntRect recCaja = levelManager.inlevel->cajas[i]->getBounds();

		// El jugador colisiona con ese rectangulo
		if(this->checkCollision(player.getBounds(), recCaja)) {
			colides = true;

			// Determinamos cuanto se solapan en cada eje
			// EJE Y
			ejeY =  recCaja.top - (player.getPosition().y + player.getSize().y/2);

			// EJE X. Por la izquierda y la derecha
			if(this->left) {
				ejeX =  recCaja.left - (player.getPosition().x + player.getSize().x/2);
			}
			else {
				ejeX = (recCaja.left + recCaja.width) - (player.getPosition().x - player.getSize().x/2);
			}

			// Actualizamos solo el eje que ha solapado menos
			// EJE Y
			if(abs(ejeY) <= abs(ejeX) && player.getSpeed().y >= 0) {
				// Toca por encima
				if(this->top) {
					// Lo devolvemos a la antigua posicion
					player.setPosition(player.getPosition().x, player.oldPos.y);
					player.setSpeed(player.getSpeed().x, 0);
					player.onGround = true;
				}
			}
			// EJE X
			else {
				// Tiene el poder activo, puede mover la caja
				if(player.powers[1] == 1) {
					bool izquierda = left;
					levelManager.inlevel->cajas[i]->setSpeed(player.getSpeed().x, 0);
					
						for(int j = 0; j < levelManager.inlevel->colisionMap.size(); j++) { // Vector con los rectangulos de colision
							// Rectangulo actual a comprobar
							sf::IntRect recTile = levelManager.inlevel->colisionMap[j];
							if(this->checkCollision(recCaja, recTile)) {
								// Determinamos cuanto se solapan en cada eje
								ejeY =  recTile.top - (recCaja.top + recCaja.height);

								// EJE X. Por la izquierda y la derecha
								if(this->left) {
									ejeX =  recTile.left - (recCaja.left + recCaja.width);
								}
								else {
									ejeX = (recTile.left + recTile.width) - recCaja.left;
								}

								// Actualizamos solo el eje que ha solapado menos
								// EJE X para caja
								if(abs(ejeY) > abs(ejeX)) {
									if((izquierda && left) || (!izquierda && !left)) {
										levelManager.inlevel->cajas[i]->setSpeed(0, 0); // Se para la caja
										player.setPosition(player.oldPos.x, player.getPosition().y);
										player.setSpeed(0, player.getSpeed().y);
									}
								}
							}
						}
					
				}
				else {
					player.setPosition(player.oldPos.x, player.getPosition().y);
					player.setSpeed(0, player.getSpeed().y);
				}
			}	
		}
	}
	
	// PUERTAS

	int posx = 0;
	for ( std::vector<Door*>::iterator obj = levelManager.inlevel->puertas.begin(); obj != levelManager.inlevel->puertas.end(); obj++ ) {
		// El jugador colisiona con una puerta
		if(checkCollision(player.getBounds(), (*obj)->getBounds())) {
			// La puerta esta cerrada
			if(!(*obj)->activa) {
				player.setPosition(player.oldPos.x, player.getPosition().y);
				player.setSpeed(0, player.getSpeed().y);
			}
			// Esta abierta
			else {
				posx = (*obj)->getPosition().x;
				levelManager.inlevel->finish = true;
			}
		}
	}
	
	// Miramos si hay puertas mas adelante
	for ( std::vector<Door*>::iterator obj = levelManager.inlevel->puertas.begin(); obj != levelManager.inlevel->puertas.end(); obj++ ) {
		// Hay puertas delante, no ha terminado
		if((*obj)->getPosition().x > posx) {
			levelManager.inlevel->finish = false;
		}
	}

	
	
	// REJILLAS
	for ( std::vector<Rejilla*>::iterator obj = levelManager.inlevel->rejillas.begin(); obj != levelManager.inlevel->rejillas.end(); obj++ ) {
		// El jugador colisiona con una llave
		if(checkCollision(player.getBounds(), (*obj)->getBounds())) {
			
			// El poder de agua esta inactivo
			if(player.powers[2] != 1) {
				player.setPosition(player.oldPos.x, player.getPosition().y);
				player.setSpeed(0, player.getSpeed().y);
			}
		}
	}
	
	
	// Si ha habido alguna colision el jugador dejar de esta en el aire
	if(!colides) {
		player.onGround = false;
	}
	
	// ENEMIGOS
	for ( std::vector<Enemy*>::iterator obj = levelManager.inlevel->enemigos.begin(); obj != levelManager.inlevel->enemigos.end(); obj++ ) {
		if(player.vivo) {
			// Colision del jugador con alguno de estos
			if(checkCollision(player.getBounds(), (*obj)->getBounds()) && (*obj)->vivo ) {
				// Gobo
				if((*obj)->tipo == 1) {
					// El jugado muere, toca al gobo desde el suelo
					if((player.getPosition().y + player.getSize().y/2) >= ((*obj)->getPosition().y + (*obj)->getSize().y/2))  {
						player.setVidas(player.getVidas()-1); // Restamos vida
						player.vivo = false;
					}
					// El gobo muere (ajustamos un poco la caja de colision)
					else if((player.getPosition().y + player.getSize().y/2) < (*obj)->getPosition().y + 10) {
						(*obj)->setSpeed(0, -250.f);
						(*obj)->vivo = false;
						(*obj)->setCentro(0, 0); // para la animacion
						player.clock.restart(); // Cuenta un tiempo antes de reiniciar
						// El jugador rebota
						player.setSpeed(player.getSpeed().x, -200.f);
						player.onGround = false;
					}
				}
				// Kompa, el jugador muere siempre
				else if((*obj)->tipo == 2) {
					player.setVidas(player.getVidas()-1); // Restamos vida
					player.vivo = false;
				}
			}
		}
	}
	
	// LLAVES
	for ( std::vector<Key*>::iterator obj = levelManager.inlevel->llaves.begin(); obj != levelManager.inlevel->llaves.end(); obj++ ) {
		// Comprobamos si la llave sigue en pantalla
		if((*obj)->getPosition().y < -50) {
			(*obj)->active = -1; // Para eliminar
		}
		else if((*obj)->active == 1) { // Animacion, movemos la llave
			(*obj)->move(0.f, ((*obj)->getSpeed().y)*((*obj)->clock.getSeconds()));
			(*obj)->clock.restart();
		}
		// El jugador colisiona con una llave
		else if(checkCollision(player.getBounds(), (*obj)->getBounds())) {
			// Buscamos la puerta
			for ( std::vector<Door*>::iterator pobj = levelManager.inlevel->puertas.begin(); pobj != levelManager.inlevel->puertas.end(); pobj++ ) {
				// Cambiamos el estado de la puerta
				if((*obj)->rel == (*pobj)->rel ) {
					(*pobj)->activar();
				}
			}
			// Cambiamos el punto de respawn
			player.setSpawn(player.getPosition().x, player.getPosition().y);
			// Activamos la animacion de la llave
			(*obj)->active = 1;
			(*obj)->setSpeed(0.f, -150.f);
			(*obj)->clock.restart();
		}
	}
	
	// PALANCAS
	for ( std::vector<Palanca*>::iterator obj = levelManager.inlevel->palancas.begin(); obj != levelManager.inlevel->palancas.end(); obj++ ) {
		// El jugador colisiona con una palanca y la pulsa
		if(checkCollision(player.getBounds(), (*obj)->getBounds()) && input.down) {
			// Activamos la palanca
			if(!(*obj)->activa) {
				(*obj)->activar();
				// Plataformas asociadas
				for ( std::vector<Plataforma*>::iterator pobj = levelManager.inlevel->plataformas.begin(); pobj != levelManager.inlevel->plataformas.end(); pobj++ ) {
					if((*obj)->rel == (*pobj)->rel) {
						(*pobj)->activar();
					}
				}
			}
		}
	}
	
	// ANTORCHAS
	for ( std::vector<Torch*>::iterator obj = levelManager.inlevel->antorchas.begin(); obj != levelManager.inlevel->antorchas.end(); obj++ ) {
		if(checkCollision(player.getBounds(), (*obj)->getBounds()) && player.powers[3] == 1 && input.down) {
			// Activamos la antorcha
			if(!(*obj)->activa) {
				(*obj)->activar();
				// Buscamos la puerta
				for ( std::vector<Door*>::iterator pobj = levelManager.inlevel->puertas.begin(); pobj != levelManager.inlevel->puertas.end(); pobj++ ) {
					// Cambiamos el estado de la puerta
					if((*obj)->rel == (*pobj)->rel ) {
						(*pobj)->activar();
					}
				}
			}
		}
	}
		
	// PODERES
	if(levelManager.inlevel->poder->getPosition().y < -50) {
		levelManager.inlevel->poder->active = -1; // Para eliminar
	}
	else if(levelManager.inlevel->poder->active == 1) { // Animacion, movemos el sprite
		levelManager.inlevel->poder->move(0.f, (levelManager.inlevel->poder->getSpeed().y)*(levelManager.inlevel->poder->clock.getSeconds()));
		levelManager.inlevel->poder->clock.restart();
	}
	// El jugador colisiona con el poder
	else if(checkCollision(player.getBounds(), levelManager.inlevel->poder->getBounds())) {
		player.powers[levelManager.nivelActual] = 0;
		levelManager.inlevel->poder->active = 1; // Animacion
		levelManager.inlevel->poder->setSpeed(0.f, -150.f);
		levelManager.inlevel->poder->clock.restart();
		
		// Cambiamos el punto de respawn
		player.setSpawn(player.getPosition().x, player.getPosition().y);
		
		// Activamos el mensaje de ayuda
		HUD &hud = * HUD::Instance();

		switch(levelManager.nivelActual) {
			case 0: // Viento
				hud.ayuda->setActivo(10);
				break;
			case 1: // Tierra
				hud.ayuda->setActivo(11);
				break;
			case 2: // Agua
				hud.ayuda->setActivo(12);
				break;
			case 3: // Fuego
				hud.ayuda->setActivo(13);
				break;
		}	
	}
}

}