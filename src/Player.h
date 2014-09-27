/* 
 * File:   Player.h
 * Author: Ruben Martinez Vilar
 *
 * Created on 21 March 2013, 16:09
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "Entity.h"

namespace game {
class Player: public Entity {
public:
	static Player* Instance();
	virtual ~Player();
	
	bool onGround;
	bool facingLeft;
	bool vivo;
	sf::Vector2f oldPos; // Posicion antes de mover, para controlar colisiones
	
	int  getVidas();
	void setVidas(int v);
	void animate();
	void update();
	
	void setSpawn(float x, float y);
	void respawn();
	void init();
	void togglePower(int p);
	
	int powers[4];
	// Tiempo para algunas habilidades especiales
	game::Clock powerTimer;
	
	sf::IntRect getBounds();
	
private:
	Player();
	Player(const Player& orig);
	Player &operator= (const Player &);
	static Player* pinstance;
		
	int vidas;
	sf::Vector2f spawn;
};
}

#endif	/* PLAYER_H */

