/*
 * File:   Clock.h
 * Author: Ruben
 *
 * Created on 07 May 2013, 16:45
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include "SFML/System/Clock.hpp"

namespace game {

class Clock {
public:
	Clock();
	virtual ~Clock();

	float getSeconds();
	float getMiliseconds();
	void restart();

	// Guarda los seg obtenidos en el ultimo restart
	float elapsedSeconds;

private:
	sf::Clock clock;
};

}

#endif	/* CLOCK_H */

