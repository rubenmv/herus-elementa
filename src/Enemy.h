/* 
 * File:   Enemy.h
 * Author: Ruben
 *
 * Created on 28 April 2013, 22:03
 */

#ifndef ENEMY_H
#define	ENEMY_H

#include "Entity.h"
#include "Clock.h"

class Enemy: public Entity  {
public:
	Enemy(const int t);
	Enemy(const Enemy& orig);
	virtual ~Enemy();
	
	int tipo; // 1 = gobo, 2 = kompa
	bool vivo;
	// Distancia maxima por la que se mueven antes de dar la vuelta
	int distance;
	
	void animate();
	
	sf::IntRect getBounds();
	
	game::Clock animClock;
	
private:

};

#endif	/* ENEMY_H */

